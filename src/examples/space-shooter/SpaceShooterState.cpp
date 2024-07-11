#include "SpaceShooterManager.h"
#include "SpaceShooterState.h"

SpaceShooterState::SpaceShooterState(SpaceShooterManager *mgr) noexcept
    : mgr(mgr)
{
    guienv = sleek::gui::createGUIEnvironment(mgr->screen, mgr->driver);
    smgr = std::make_shared<sleek::scene3d::Scene>(mgr->getDevice(), mgr->getDriver());
}

SpaceShooterState::~SpaceShooterState() noexcept
{

}
