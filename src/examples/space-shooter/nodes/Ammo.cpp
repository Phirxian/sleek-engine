#include "Ammo.h"
#include "../state/Game.h"

using namespace sleek;

Ammo::Ammo(Game *game, int tid) noexcept
    : Object(game, tid), dammage(50.f)
{
}

Ammo::~Ammo() noexcept
{
}

bool Ammo::shouldInteract(const Object* other) const noexcept
{
    if(!other)
        return false;

    if(other->getType() == GOT_AMMO)
        if(other->owner == owner)
            return false;

    return Object::shouldInteract(other);
}

void Ammo::update(const sleek::math::vec2f& force, float dt)
{
    Object::update(force, dt);
    auto xyz = getPosition();
    //std::cout << xyz.x << "," << xyz.y << "," << xyz.z << " \t :" << node->getRotation().y << std::endl;

    auto current = std::chrono::steady_clock::now();
    auto should_delete = std::chrono::duration_cast<std::chrono::milliseconds>(current - instanciated).count();

    if (should_delete > 1000)
        game->remove(this);

    if (abs(velocity.x) + abs(velocity.y) < 1e-2)
        game->remove(this);
}