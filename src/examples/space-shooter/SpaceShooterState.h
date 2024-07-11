#ifndef SPACE_SHOOTER_STATE
#define SPACE_SHOOTER_STATE

#include "../sleek/start.h"

class SpaceShooterManager;

enum GameState
{
    GS_MAIN_MENU,
    GS_GAME
};

class SpaceShooterState : public sleek::device::event
{
    public:
        SpaceShooterState(SpaceShooterManager *mgr) noexcept;
        virtual ~SpaceShooterState() noexcept;

        virtual bool manage(sleek::device::input *a) noexcept = 0;

        virtual void run() noexcept = 0;
    protected:
        std::shared_ptr<sleek::gui::interface> guienv;
        std::shared_ptr<sleek::scene3d::Scene> smgr;
        SpaceShooterManager *mgr;
        sleek::math::timer time;
};
    
#endif
