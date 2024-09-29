#include "Ship.h"
#include "Ammo.h"

#include "../state/Game.h"
#include "sleek/device/keyboard.h"

using namespace sleek;

Ship::Ship(Game *game, int tid) noexcept
    : Object(game, tid), fire(false)
{
    fire_interval = std::chrono::steady_clock::now();
    
    if (game->getDevice()->getKeyboardLayout() == sleek::device::KEYBOARD_LAYOUT::KBD_QWERTY)
    {
        key_up = device::KEY_KEY_W;
        key_left = device::KEY_KEY_A;
        key_down = device::KEY_KEY_S;
        key_right = device::KEY_KEY_Q;
    }
    else
    {
        key_up = device::KEY_KEY_Z;
        key_left = device::KEY_KEY_Q;
        key_down = device::KEY_KEY_S;
        key_right = device::KEY_KEY_D;
    }
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
        if (e->key_state[key_up])
            direction.y -= 2;
        if (e->key_state[key_down])
            direction.y += 2;
        if (e->key_state[key_left])
            direction.x -= 2;
        if (e->key_state[key_right])
            direction.x += 2;
    }

    fire = e->key_state[device::KEY_SPACE];

    if (e->type == device::EVENT_KEY_UP)
    {
        if (e->key[key_up])
            direction.y = 0.f;
        if (e->key[key_down])
            direction.y = 0.f;
        if (e->key[key_left])
            direction.x = 0.f;
        if (e->key[key_right])
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

    auto current = std::chrono::steady_clock::now();
    auto should_fire = std::chrono::duration_cast<std::chrono::milliseconds>(current - fire_interval).count();

    if (fire && should_fire > 50)
    {
        std::uniform_int_distribution<int> randomDistribution(0, 100);
        std::uniform_real_distribution<float> spreadDistribution(-1.f, 1.f);
        
        float angleDegrees = -node->getRotation().y;
        float spreadRadian = glm::radians(spreadDistribution(game->gen) * 2.f);
        float angleRadian = glm::radians(angleDegrees) + spreadRadian;

        // {0,-1} up vector, simplified rotation
        math::vec2f rotated = math::vec2f(sin(angleRadian), -cos(angleRadian));

        game->spawnAmmo(this, position, rotated * 10.f, randomDistribution(game->gen));
        fire_interval = current;
    }
}