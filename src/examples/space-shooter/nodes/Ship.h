#ifndef SPACE_SHOOTER_SHIP
#define SPACE_SHOOTER_SHIP

#include "Object.h"

class Ship : public Object
{
    public:
        Ship(Game*, int tid) noexcept;
        virtual ~Ship() noexcept;

        virtual bool manage(sleek::device::input*) noexcept;
        
        virtual void update(const sleek::math::vec2f& force, float dt);
};

#endif // NODE
