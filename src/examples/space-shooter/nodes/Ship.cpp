#include "Ship.h"

using namespace sleek;

Ship::Ship(Game *game, int tid) noexcept : Object(game, tid)
{
}

Ship::~Ship() noexcept
{
}

bool Ship::manage(device::input *e) noexcept
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

void Ship::update(const sleek::math::vec2f& force, float dt)
{
    Object::update(force, dt);
    auto xyz = getPosition();
    //std::cout << xyz.x << "," << xyz.y << "," << xyz.z << " \t :" << node->getRotation().y << std::endl;
}