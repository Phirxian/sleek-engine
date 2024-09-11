#include "Game.h"
#include "../Core.h"
#include "../sleek/node/camera/trackball.h"
#include "../sleek/node/camera/fps.h"

#include "nodes/Ship.h"

#include <iostream>
#include <unistd.h>
#include <GL/gl.h>

using namespace sleek;
using namespace device;
#define number 100

Game::Game(Core *mom) noexcept
    : SpaceShooterState(mom), rotation(true)
{
    smgr = new sleek::scene3d::Scene(screen, mom->getDriver());

    texture.push_back(mom->getLoader()->loadTexture("texture/crate.jpg"));
    texture.push_back(mom->getLoader()->loadTexture("texture/ship/ship-0.png"));
    texture.push_back(mom->getLoader()->loadTexture("texture/planets/planet-11.png"));

    for(auto &it : texture)
    {
        it->createIdentifier(mom->getContext());
        it->getIdentifier()->update();
    }

    /*
    auto cube = std::make_shared<scene3d::real::Natif>(smgr);
    auto mesh = std::shared_ptr<driver::mesh>(driver::Geometry().createCube({50, 50, 50}));
    core->getContext()->createVAO(mesh.get(), sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
    cube->setPosition({0,0,0});
    cube->setMesh(mesh);
    cube->setMaterial(buildMaterial(cube.get(), nullptr, "shader/object/default.vert", "shader/object/solid.frag", SpaceShooterState::material_callback, 0));
    cube->getMaterial()->setFaceCulling(driver::rfc_front);
    smgr->addSceneNode(cube);
    */

    auto ship = std::make_shared<scene3d::real::Natif>(smgr);
    auto plane = std::shared_ptr<driver::mesh>(driver::Geometry().createPlane({25, 25}));
    core->getContext()->createVAO(plane.get(), sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
    ship->setPosition({0,0,0});
    ship->setMesh(plane);
    ship->setMaterial(buildMaterial(ship.get(), nullptr, "shader/object/default.vert", "shader/object/solid.frag", SpaceShooterState::material_callback, 2));
    ship->getMaterial()->setMaterialRender(driver::rmt_solid);
    // ship->getMaterial()->setFaceCulling(driver::rfc_front);

    smgr->addSceneNode(ship);
    
    auto camera = smgr->getCamera();
    camera->setRotation({0, 1, 0});
    camera->setTarget(ship->getPosition());
    camera->setPosition(ship->getPosition() + math::vec3f{0, 150, 1});
}

Game::~Game() noexcept
{
}

bool Game::manage(sleek::device::input *a) noexcept
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

        if(a->key[KEY_KEY_S])
        {
            return true;
        }
    }

    return false;
}

void Game::render() noexcept
{
    smgr->render();
}