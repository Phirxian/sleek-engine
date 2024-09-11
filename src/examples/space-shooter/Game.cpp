#include "Game.h"

#include "../sleek/gui/element/button.h"
#include "../sleek/gui/element/statictext.h"
#include "Ship.h"

#include <string>
#include <sstream>
#include <unistd.h>

using namespace sleek;

Game::Game(SpaceShooterManager *mgr) noexcept
    : SpaceShooterState(mgr)
{
    ship = std::make_shared<Ship>(smgr.get());
    ship->setTexture(mgr->getLoader()->loadTexture("texture/space-sheep.png"));
    ship->getTexture()->createIdentifier(mgr->getContext());
    ship->getTexture()->getIdentifier()->update();
    smgr->addSceneNode(ship);
}

Game::~Game() noexcept
{
}

bool Game::manage(sleek::device::input *e) noexcept
{
    if(smgr->manage(e))
        return true;

    return event::manage(e);
}

void Game::run() noexcept
{
    smgr->getCamera()->setTarget({0, 15, 0});
    smgr->getCamera()->setPosition(ship->getPosition());
    smgr->render();
    guienv->render();
}
