#include "Core.h"
#include "MetaballSample.h"
#include "../sleek/node/camera/trackball.h"
#include "../sleek/node/camera/fps.h"

#include <iostream>
#include <unistd.h>
#include <GL/gl.h>

using namespace sleek;
using namespace device;
#define number 100

namespace sample
{
    MetaballSample::MetaballSample(Core *mom) noexcept
        : Sample(mom), rotation(true),  metaball(40)
    {
        smgr = new sleek::scene3d::Scene(screen, mom->getDriver());

        texture.push_back(mom->getLoader()->loadTexture("texture/crate.jpg"));
//        texture.push_back(mom->getLoader()->loadTexture("texture/lena.pgm"));
        texture.push_back(mom->getLoader()->loadTexture("texture/eye.png"));
        texture.push_back(mom->getLoader()->loadTexture("texture/earth.jpg"));

        for(auto &it : texture)
        {
            it->createIdentifier(mom->getContext());
            it->getIdentifier()->update();
        }

        for(int i=0; i<3; i++)
            metaball.balls.push_back({sleek::math::vec3f(0.0f, 0.0f, 0.0f), 25.0f*(i+1)});

        tmp.reset(&metaball);
        metaball.move();
        metaball.update();
        metaball.setThreshold(2.0f);

//        core->getContext()->createVAO(tmp.get(), sleek::driver::VAO_DYNAMIC, sleek::driver::VAO_DYNAMIC);
        core->getContext()->createVAO(tmp.get(), sleek::driver::VAO_STREAM, sleek::driver::VAO_STREAM);
//        core->getContext()->createVAO(tmp.get(), sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);

        auto cube = std::make_shared<scene3d::real::Natif>(smgr);
        auto mesh = std::shared_ptr<driver::mesh>(driver::Geometry().createCube({50, 50, 50}));
        core->getContext()->createVAO(mesh.get(), sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
        cube->setPosition({0,0,0});
        cube->setMesh(mesh);
        cube->setMaterial(buildMaterial(cube.get(), nullptr, "shader/object/default.vert", "shader/object/solid.frag", Sample::material_callback, 0));
        cube->getMaterial()->setFaceCulling(driver::rfc_front);
        smgr->addSceneNode(cube);

        node = std::make_shared<scene3d::real::Natif>(smgr);
        node->setPosition({0,0,0});
        node->setMaterial(buildMaterial(node.get(), nullptr, "shader/object/default.vert", "shader/object/sphere.frag", Sample::material_callback, 1));
        node->setMesh(tmp);
        smgr->addSceneNode(node);

        //auto camera = std::make_shared<scene3d::camera::TrackballCamera>(screen);
        auto camera = std::make_shared<scene3d::camera::FPSCamera>(screen);
        //auto camera = smgr->getCamera();
        camera->setRotation({0, 1, 0});
        camera->setTarget({0, 0, 0});
        camera->setPosition({0, 50, 2*50});
        //camera->setDistance(distance);
        smgr->setCamera(camera);
    }

    MetaballSample::~MetaballSample() noexcept
    {
    }

    bool MetaballSample::manage(sleek::device::input *a) noexcept
    {
        if(smgr->manage(a))
            return false;

        if(a->type == EVENT_KEY_DOWN)
        {
            //! engine test
            if(a->key[KEY_F11])
            {
                screen->setFullScreen(!screen->getInfo().fullscreen);
                return true;
            }

            //! engine test
            if(a->key[KEY_SPACE])
            {
                rotation = !rotation;
                return true;
            }

            //! vertex buffer object, disable and enable
            if(a->key[KEY_F2])
            {
                if(tmp->getIdentifier())
                    tmp->setIdentifier(nullptr);
                else
                {
                    core->getContext()->createVAO(tmp.get());
                    tmp->getIdentifier()->update();
                }
                return true;
            }

            if(a->key[KEY_F1])
            {
                node->getMaterial()->setWireframe(
                    !node->getMaterial()->getWireframe()
                );
                return true;
            }

            if(a->key[KEY_KEY_S])
            {
                return true;
            }
        }

        return false;
    }

    void MetaballSample::render() noexcept
    {
        if(rotation)
        {
            tm.update();

            float c = 2.0f*cos(tm.getTimeMsec()/600);

            metaball.balls[0].position.x = -8.0f*cos(tm.getTimeMsec()/700) - c;
            metaball.balls[0].position.y =  8.0f*sin(tm.getTimeMsec()/600) - c;
            metaball.balls[1].position.y =  10.0f*sin(tm.getTimeMsec()/400) + c;
            metaball.balls[1].position.z =  10.0f*cos(tm.getTimeMsec()/400) - c;
            metaball.balls[2].position.x = -15.0f*cos(tm.getTimeMsec()/400) - 0.2f*sin(tm.getTimeMsec()/600);
            metaball.balls[2].position.z =  15.0f*sin(tm.getTimeMsec()/500) - 0.2f*sin(tm.getTimeMsec()/400);

            metaball.move();
            metaball.update();

            if(tmp->getIdentifier())
                tmp->getIdentifier()->update();
        }

        smgr->render();
    }
}
