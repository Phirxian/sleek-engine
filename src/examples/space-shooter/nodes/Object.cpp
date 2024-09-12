#include <cmath>

#include "Object.h"
#include "../state/Game.h"

using namespace sleek;

Object::Object(Game *game, int tid)
    : game(game), mass(1.0)
{
    auto texture = game->getTexture(tid);
    auto plane = std::shared_ptr<driver::mesh>(driver::Geometry().createPlane({texture->getDimension().x/100.f, texture->getDimension().y/100.f}));

    radius = math::max(texture->getDimension().x, texture->getDimension().y) / 200.f;
    mass = 1+radius;

    node = std::make_shared<scene3d::real::Natif>(game->getSceneManager());
    game->getContext()->createVAO(plane.get(), sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
    node->setPosition({0,0,0});
    node->setMesh(plane);
    node->setMaterial(game->buildMaterial(node.get(), nullptr, "shader/object/default.vert", "shader/object/solid.frag", SpaceShooterState::material_callback, tid));
    node->getMaterial()->setMaterialRender(driver::rmt_solid);
    node->getMaterial()->setMode(driver::rmd_polygon);
    
    game->getSceneManager()->addSceneNode(node);

    instanciated = std::chrono::steady_clock::now();
    collided = std::chrono::steady_clock::now();
}

Object::~Object()
{
    node->setEnable(false);
    game->getSceneManager()->removeNode(node);
}

void Object::setSceneNode(std::shared_ptr<sleek::scene3d::real::Natif> new_node) noexcept
{
    node = new_node;
}

std::shared_ptr<sleek::scene3d::real::Natif> Object::getSceneNode() const noexcept
{
    return node;
}

sleek::math::vec3f Object::getPosition() const noexcept
{
    return {position.x, 0, position.y};
}

bool Object::shouldCollide(Object* other) noexcept
{
    auto current = std::chrono::steady_clock::now();
    auto should_collide = std::chrono::duration_cast<std::chrono::milliseconds>(current - collided).count();

    if (should_collide < 200)
        return false;

    collided = std::chrono::steady_clock::now();
    other->collided = collided;

    return true;
}

bool Object::isColliding(const Object *other, float margin) const noexcept
{
    math::vec2f r = other->position - position;
    float distance = glm::length(r);
    return distance < (radius + other->radius + margin);
}

void Object::update(const sleek::math::vec2f& force, float dt)
{
    old_direction = direction;
    old_position = position;
    old_velocity = velocity;

    math::vec2f acceleration = force / mass;
    velocity += acceleration * dt;

    if (glm::length(direction))
        velocity += direction * dt;

    if (std::isnan(velocity.x + velocity.y) || std::isinf(velocity.x + velocity.y))
        velocity = old_velocity;
    else
    {
        velocity.x = math::clamp(velocity.x, -5.f, 5.0f);
        velocity.y = math::clamp(velocity.y, -5.f, 5.0f);
    }

    position += velocity * dt;

    if (std::isnan(position.x + position.y) || std::isinf(position.x + position.y))
        position = old_position;

    if(node)
    {
        auto xyz = getPosition();
        node->setPosition(xyz);
        
        glm::vec2 vector = position - old_position;

        // Very small value to avoid division by zero
        if (glm::length(vector) < 1e-4f)
            node->setRotation({0,0,0});
        else
        {
            float angle = std::atan2(vector.y, vector.x);
            float angleDegrees = glm::degrees(angle)+90;
            node->setRotation({0,-angleDegrees,0});
        }
    }
}

void Object::render()
{
    node->render();
}