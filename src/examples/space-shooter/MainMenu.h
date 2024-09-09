#ifndef SPACE_SHOOTER_MAIN_MENU
#define SPACE_SHOOTER_MAIN_MENU

#include "SpaceShooterManager.h"
#include "SpaceShooterState.h"

class MainMenu : public SpaceShooterState
{
    public:
        MainMenu(SpaceShooterManager*) noexcept;
        virtual ~MainMenu() noexcept;

        bool manage(sleek::device::input *a) noexcept override;

        void run() noexcept;
    private:
        SpaceShooterManager *ssm;
        std::shared_ptr<sleek::gui::button> play;
        std::shared_ptr<sleek::gui::button> quit;
        sleek::math::timer time;
};
    
#endif
