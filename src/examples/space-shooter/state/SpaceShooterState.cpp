#include "Core.h"
#include "SpaceShooterState.h"

#include <iostream>
#include <unistd.h>
#include <GL/gl.h>

using namespace sleek;
using namespace device;

SpaceShooterState::SpaceShooterState(Core *mom) noexcept
    : screen(mom->getDevice()), core(mom)
{
    smgr = new sleek::scene3d::Scene(screen, mom->getDriver());
}

SpaceShooterState::~SpaceShooterState() noexcept
{
    smgr->clear();
}

std::shared_ptr<sleek::driver::material> SpaceShooterState::buildMaterial(
    sleek::scene3d::Node *node, void *user,
    std::string filename_vert, std::string filename_frag,
    sleek::driver::shader_callback callback, int tid
) noexcept
{
    auto shade = core->getContext()->createShader();
    auto mat = std::make_shared<driver::material>();

    mat->setMode(driver::rmd_polygon);
    mat->setShadeModel(driver::rsd_flat);
//        mat->setFaceCulling(driver::rfc_back);
    mat->setMaterialRender(driver::rmt_solid);
    mat->setShader(shade);

    if(tid >= 0 && tid < texture.size() && texture[tid])
        mat->Texture.push_back(texture[tid]->getIdentifier().get());

    auto vert = core->getFileSystem()->read(filename_vert);
    auto frag = core->getFileSystem()->read(filename_frag);

    shade->attacheShader(driver::shd_vert, vert->readAll(), "main");
    shade->attacheShader(driver::shd_frag, frag->readAll(), "main");
    // used to get information from material (like texture binding) by callback
    shade->setLinkToMaterial(mat.get());
    // used to get model view
    shade->user[0] = node;
    shade->user[1] = user;

    shade->compileShader();
    shade->setCallback(callback);

    return mat;
}
