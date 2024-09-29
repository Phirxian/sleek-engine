#ifndef SPACE_SHOOTER_SHIP
#define SPACE_SHOOTER_SHIP

#include "Object.h"

class Ship : public Object
{
    public:
        Ship(Game*, int tid) noexcept;
        virtual ~Ship() noexcept;

        virtual ObjectType getType() const noexcept { return GOT_SHIP; }

        virtual bool manage(sleek::device::input*) noexcept;
        
        virtual void update(const sleek::math::vec2f& force, float dt);
    private:
        std::chrono::steady_clock::time_point fire_interval;
        sleek::device::KEYCODE key_up, key_left, key_down, key_right;
        bool fire;
};

#endif // NODE
