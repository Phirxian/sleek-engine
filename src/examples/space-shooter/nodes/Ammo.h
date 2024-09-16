#ifndef SPACE_SHOOTER_AMMO
#define SPACE_SHOOTER_AMMO

#include "Object.h"

class Ammo : public Object
{
    public:
        Ammo(Game*, int tid) noexcept;
        virtual ~Ammo() noexcept;

        virtual ObjectType getType() const noexcept { return GOT_AMMO; }

        virtual bool shouldInteract(const Object* other) const noexcept;
        
        virtual void update(const sleek::math::vec2f& force, float dt);
    public:
        float dammage;
};

#endif // NODE
