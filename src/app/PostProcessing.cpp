#include "PostProcessing.h"
#include "Core.h"

#include <GL/gl.h>
using namespace sleek;

#define REDUX_COUNT 2

//    {"shader/screen/normal_debug.frag",   1, 0, driver::TXFMT_RGBA},
//    {"shader/screen/redux_debug.frag",    1, 0, driver::TXFMT_RGBA},
//    {"shader/screen/position_debug.frag", 1, 0, driver::TXFMT_RGBA},
//    {"shader/screen/redux_debug.frag",  1,   0, driver::TXFMT_RGBA},

struct postprocess
{
    const char *fragment;
    unsigned int passcount;
    unsigned int size;
    driver::TextureFormat format;
};

std::vector<postprocess> postprocess_pass = {
//    {"shader/screen/redux.frag",        1, 512, driver::TXFMT_RGBA_32F},
//    {"shader/screen/redux2.frag",       5,  64, driver::TXFMT_RGBA_32F},
//
    {"shader/screen/ssao.frag",         1,   0, driver::TXFMT_LUMINANCE},
    {"shader/screen/blur.frag",         1, 512, driver::TXFMT_LUMINANCE},
    {"shader/screen/fxaa.frag",         1,   0, driver::TXFMT_RGBA},

//    {"shader/screen/tonemap.frag",    1,   0, driver::TXFMT_RGBA},
//    {"shader/screen/debug.frag",      1,   0, driver::TXFMT_RGBA},
};

namespace sample
{
    PostProcessing::PostProcessing(Core *c) noexcept
        : core(c)
    {
        mesh = driver::Geometry().createWall(math::vec2f(2,2));

        core->getContext()->createVAO(mesh);
        mesh->getIdentifier()->update();

        mt = std::make_shared<driver::material>();
        auto scenefb = core->getContext()->createFBO(
            c->getDevice()->getInfo().size, {
                // albedo
                driver::TXFMT_RGBA,
                // normal (normal.z can be computed)
                driver::TXFMT_RGB_32F,
//                driver::TXFMT_LUMINANCE_ALPHA,
                // position.xy
                driver::TXFMT_RGB_32F,
            },
            true
        );
        scenefb->setBackground(0x00FFFFFF);
        scenefb->update();
        fb.push_back(scenefb);

        mt->setMode(driver::rmd_polygon);
        mt->setShadeModel(driver::rsd_flat);
        mt->setFaceCulling(driver::rfc_back);
        mt->setMaterialRender(driver::rmt_solid);
        mt->Texture.push_back(scenefb->getTexture(0)); // albedo
        mt->Texture.push_back(scenefb->getTexture(1)); // normal
        mt->Texture.push_back(scenefb->getTexture(2)); // position
        mt->Texture.push_back(scenefb->getTexture(0)); // last  {updated later}
        mt->Texture.push_back(scenefb->getTexture(0)); // redux {updated later}

        std::vector<sleek::driver::TextureFormat> attachment;

        for(int i = 0; i<postprocess_pass.size(); ++i)
        {
            auto vert = core->getFileSystem()->read("shader/screen/default.vert");
            auto frag = core->getFileSystem()->read(postprocess_pass[i].fragment);

            auto lpp = core->getContext()->createShader();
            lpp->attacheShader(driver::shd_vert, vert->readAll(),"main");
            lpp->attacheShader(driver::shd_frag, frag->readAll(),"main");
            lpp->compileShader();

            lpp->setLinkToMaterial(mt.get());
            lpp->user[0] = core->getDevice();
            lpp->user[1] = this;

            lpp->setCallback([](driver::shader *i) noexcept {
                device::Device *dev = (device::Device*)i->user[0];

                i->setTexture("redux",       i->getLinkFromMaterial()->Texture[4], 4);
                i->setTexture("last",        i->getLinkFromMaterial()->Texture[3], 3);
                i->setTexture("position",    i->getLinkFromMaterial()->Texture[2], 2);
                i->setTexture("normal",      i->getLinkFromMaterial()->Texture[1], 1);
                i->setTexture("base",        i->getLinkFromMaterial()->Texture[0], 0);

                i->setVariable("resolution", dev->getInfo().size);
                i->setVariable("znear", 1.0f); // default camera znear
                i->setVariable("zfar", 500.f); // default camera zfar
            });

            pp.push_back(lpp);

            auto size = postprocess_pass[i].size == 0 ?
                        c->getDevice()->getInfo().size :
                        math::vec2i(postprocess_pass[i].size);

            auto lfb = core->getContext()->createFBO(size, {postprocess_pass[i].format});
            lfb->setBackground(0x00000000);
            lfb->update();
            fb.push_back(lfb);
        }
    }

    PostProcessing::~PostProcessing() noexcept
    {
        //dtor
    }

    bool PostProcessing::manage(sleek::device::input *a) noexcept
    {
        if(a->type == sleek::device::EVENT_WINDOW_RESIZE)
        {
            for(int i = 0; i<pp.size(); ++i)
                if(postprocess_pass[i].size == 0)
                    fb[i+1]->resize(core->getDevice()->getInfo().size);
            fb[0]->resize(core->getDevice()->getInfo().size);
        }
    }

    void PostProcessing::begin() noexcept
    {
        fb[0]->bind(driver::ECB_COLOR | driver::ECB_DEPTH);
    }

    void PostProcessing::end() noexcept
    {
        fb[0]->unbind();
    }

    void PostProcessing::draw() noexcept
    {
        auto *driver = core->getDriver();
        mt->Texture[3] = fb[0]->getTexture(0);
        mt->Texture[4] = fb[REDUX_COUNT]->getTexture(0);
        driver->setActiveMaterial(mt);

        for(int i = 0; i<pp.size()-1; ++i)
        {
            for(int j = 0; j<postprocess_pass[i].passcount; ++j)
            {
                float steep = j;
                pp[i]->setVariable("steep", steep);

                mt->setShader(pp[i]);
                fb[i+1]->bind();
                pp[i]->bind();

                glViewport(0,0, fb[i+1]->getSize().x, fb[i+1]->getSize().y);

                core->getDriver()->beginTo2D();
                core->getDriver()->drawMesh(mesh, {0,0,0});
                core->getDriver()->endFrom2D();

                if(fb[i+1]->getTextureCount() > 0)
                    mt->Texture[3] = fb[i+1]->getTexture(0);

                fb[i+1]->unbind();
            }
        }

        float steep = pp.size()-1;
        pp[pp.size()-1]->setVariable("steep", steep);
        mt->setShader(pp[pp.size()-1]);
        pp[pp.size()-1]->bind();

        auto size = fb[pp.size()]->getSize();

        glViewport(0,0, size.x, size.y);
        core->getDriver()->beginTo2D();
        core->getDriver()->drawMesh(mesh, {0,0,0});
        core->getDriver()->endFrom2D();

        size = core->getDevice()->getInfo().size;
        glViewport(0,0, size.x, size.y);
    }
}
