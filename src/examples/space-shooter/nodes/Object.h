#pragma once

#include "../sleek/math/math.h"
#include "../sleek/math/function.h"
#include "../sleek/node/node.h"
#include "../sleek/node/real/natif.h"

#include <chrono>

enum ObjectType
{
    GOT_BASIC,
    GOT_SHIP,
    GOT_AMMO,
};

class Game;
class Object
{
    public:
        Object(Game*, int tid);
        virtual ~Object();

        virtual void setScale(float);
        virtual float getScale();

        virtual ObjectType getType() const noexcept { return GOT_BASIC; }

        void setSceneNode(std::shared_ptr<sleek::scene3d::real::Natif>) noexcept;
        std::shared_ptr<sleek::scene3d::real::Natif> getSceneNode() const noexcept;

        bool isColliding(const Object* other, float margin = 0.0f) const noexcept;
        virtual bool shouldInteract(const Object* other) const noexcept;
        bool shouldCollide(Object* other) noexcept;
        
        sleek::math::vec3f getPosition() const noexcept;

        virtual void update(const sleek::math::vec2f& force, float dt);

        virtual void render();
    public:
        Game *game;
        Object *owner;

        std::chrono::steady_clock::time_point instanciated;
        std::chrono::steady_clock::time_point collided;

        std::shared_ptr<sleek::scene3d::real::Natif> node;
        sleek::math::vec2f position, velocity, direction;
        sleek::math::vec2f old_position, old_velocity, old_direction;

        float mass, radius, base_radius, health, scale;
};