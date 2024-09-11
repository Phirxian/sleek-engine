#include "Game.h"

#include "../sleek/gui/element/button.h"
#include "../sleek/gui/element/statictext.h"
#include "../sleek/node/real/grid.h"
#include "Ship.h"

#include <string>
#include <sstream>
#include <unistd.h>

using namespace sleek;
using namespace device;

Game::Game(SpaceShooterManager *mgr) noexcept
    : SpaceShooterState(mgr)
{
    auto texture = mgr->getLoader()->loadTexture("texture/ship/ship-0.png");

    ship = std::make_shared<Ship>(smgr.get());
    ship->setTexture(texture);
    ship->getTexture()->createIdentifier(mgr->getContext());
    ship->getTexture()->getIdentifier()->update();
    ship->setMaterial(mgr->buildMaterial(ship.get(), nullptr, "shader/object/default.vert", "shader/object/solid.frag", nullptr, texture));
    smgr->addSceneNode(ship);

    auto grid = std::make_shared<scene3d::real::Grid>(smgr.get());
    grid->setMaterial(std::make_shared<driver::material>());
    smgr->addSceneNode(grid);

    auto cube = std::make_shared<scene3d::real::Natif>(smgr.get());
    auto mesh = std::shared_ptr<driver::mesh>(driver::Geometry().createCube({50, 50, 50}));
    mgr->getContext()->createVAO(mesh.get(), sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
    cube->setMaterial(mgr->buildMaterial(cube.get(), nullptr, "shader/object/default.vert", "shader/object/solid.frag", nullptr, texture));
    cube->setPosition({0,0,0});
    cube->setMesh(mesh);
    cube->getMaterial()->setFaceCulling(driver::rfc_front);
    smgr->addSceneNode(cube);
}

Game::~Game() noexcept
{
}

bool Game::manage(sleek::device::input *e) noexcept
{
    if(smgr->manage(e))
        return true;

    if(e->type == EVENT_KEY_DOWN)
    {
        if(e->key[KEY_UP])
        {
            ship->setPosition(ship->getPosition() + math::vec3f(0, 0.1, 0));
            return true;
        }
        if(e->key[KEY_DOWN])
        {
            ship->setPosition(ship->getPosition() - math::vec3f(0, 0.1, 0));
            return true;
        }
        if(e->key[KEY_LEFT])
        {
            ship->setPosition(ship->getPosition() - math::vec3f(0.1, 0, 0));
            return true;
        }
        if(e->key[KEY_RIGHT])
        {
            ship->setPosition(ship->getPosition() + math::vec3f(0.1, 0, 0));
            return true;
        }
    }

    return event::manage(e);
}

void Game::run() noexcept
{
    std::cout
    << ship->getPosition().x << ","
    << ship->getPosition().y << ","
    << ship->getPosition().z << std::endl;

    //smgr->getCamera()->setTarget(ship->getPosition());
    //smgr->getCamera()->setPosition(ship->getPosition() + math::vec3f(0, 0, 150));
    smgr->render();
    //guienv->render();
}
