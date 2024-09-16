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
    if(other->getType() == GOT_AMMO)
        return false;
    return Object::shouldInteract(other);
}

bool Ammo::manage(device::input *e) noexcept
{
    if (e->type == device::EVENT_NOTHINK)
        return false;

    if (e->type == device::EVENT_KEY_DOWN)
    {
        if (e->key_state[device::KEY_KEY_W])
            direction.y -= 2;
        if (e->key_state[device::KEY_KEY_S])
            direction.y += 2;
        if (e->key_state[device::KEY_KEY_A])
            direction.x -= 2;
        if (e->key_state[device::KEY_KEY_D])
            direction.x += 2;
    }

    if (e->type == device::EVENT_KEY_UP)
    {
        if (e->key[device::KEY_KEY_W])
            direction.y = 0.f;
        if (e->key[device::KEY_KEY_S])
            direction.y = 0.f;
        if (e->key[device::KEY_KEY_A])
            direction.x = 0.f;
        if (e->key[device::KEY_KEY_D])
            direction.x = 0.f;
    }

    direction.x = math::clamp(direction.x, -1.f, 1.f)*4;
    direction.y = math::clamp(direction.y, -1.f, 1.f)*4;

    //std::cout << e->type << " direction " << direction.x << "," << direction.y << std::endl;

    return false;
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