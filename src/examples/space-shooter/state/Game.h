#pragma once

#include "SpaceShooterState.h"
#include "../sleek/node/real/natif.h"
#include "nodes/Ship.h"

#include <random>

class Core;
class Object;

class Game : public SpaceShooterState
{
    public:
        Game(Core*) noexcept;
        virtual ~Game() noexcept;

        bool manage(sleek::device::input*) noexcept override;

        void spawnAmmo(Object*, sleek::math::vec2f pos, sleek::math::vec2f velocity, int tid);
        void spawnAsteroid(int tid);

        void remove(Object*) noexcept;

        void render() noexcept;
        
    protected:
        sleek::math::vec2f calculateForce(const Object *obj1, const Object *obj2) const noexcept;
        void handleCollision(Object *obj1, Object *obj2);
        void simulate(float dt, int steps);

    private:
        std::mt19937 gen;
        sleek::math::vec2f boundary;
        sleek::math::timer time;
        std::shared_ptr<sleek::scene3d::real::Natif> background;
        std::vector<std::shared_ptr<Object>> objects;
        std::vector<std::shared_ptr<Object>> unused;
        std::shared_ptr<Ship> player;
        bool rotation = 0;
};
