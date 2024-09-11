#pragma once

#include "SpaceShooterState.h"

class Core;
class Game : public SpaceShooterState
{
    public:
        Game(Core*) noexcept;
        virtual ~Game() noexcept;

        bool manage(sleek::device::input*) noexcept override;

        void render() noexcept;
        
    private:
        bool rotation = 0;
};
