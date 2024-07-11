#ifndef SPACE_SHOOTER_GAME
#define SPACE_SHOOTER_GAME

#include "SpaceShooterManager.h"
#include "SpaceShooterState.h"
#include "Ship.h"

class Game : public SpaceShooterState
{
    public:
        Game(SpaceShooterManager*) noexcept;
        virtual ~Game() noexcept;

        bool manage(sleek::device::input *a) noexcept override;

        void run() noexcept;
    private:
        std::shared_ptr<Ship> ship;
};
    
#endif
