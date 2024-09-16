#include "Game.h"
#include "../Core.h"
#include "../sleek/math/function.h"

#include "nodes/Ship.h"

#include <iostream>
#include <unistd.h>
#include <cmath>

using namespace sleek;
using namespace device;
#define number 100

Game::Game(Core *mom) noexcept
    : SpaceShooterState(mom), rotation(true), boundary{5.f, 5.f}
{
    smgr = new sleek::scene3d::Scene(screen, mom->getDriver());

    textures.push_back(mom->getLoader()->loadTexture("texture/background-stars.jpg"));
    textures.push_back(mom->getLoader()->loadTexture("texture/ship/ship-0.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/planets/planet-11.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/big-0.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/big-1.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/big-2.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/medium-0.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/medium-1.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/medium-2.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/medium-3.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/small-0.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/small-1.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/small-2.png"));
    textures.push_back(mom->getLoader()->loadTexture("texture/asteroid/small-3.png"));

    for(auto &it : textures)
    {
        if(it)
        {
            it->createIdentifier(mom->getContext());
            it->getIdentifier()->update();
        }
    }
    
    player = std::make_shared<Ship>(this, 1);
    player->position = {0,0};
    player->mass = 10.0f;
    objects.push_back(player);

    // background
    if (false)
    {
        auto texture = getTexture(0);
        auto plane = std::shared_ptr<driver::mesh>(driver::Geometry().createPlane({texture->getDimension().x/100.f, texture->getDimension().y/100.f}));
        background = std::make_shared<scene3d::real::Natif>(getSceneManager());
        getContext()->createVAO(plane.get(), sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
        background->setPosition({0,0,0});
        background->setMesh(plane);
        background->setMaterial(buildMaterial(background.get(), nullptr, "shader/object/default.vert", "shader/object/solid.frag", SpaceShooterState::material_callback, 0));
        background->getMaterial()->setMaterialRender(driver::rmt_solid);
        background->getMaterial()->setMode(driver::rmd_polygon);
        getSceneManager()->addSceneNode(background);
    }

    for(int i = 0; i < 100; ++i)
        spawnAsteroid(i);

    //objects.pop_back();

    auto camera = smgr->getCamera();
    camera->setRotation({0, 1, 0});
    camera->setNearValue(0.1);
    camera->setFarValue(10000);
}

Game::~Game() noexcept
{
}

math::vec2f Game::calculateForce(const Object *obj1, const Object *obj2) const noexcept
{
    math::vec2f r = obj2->position - obj1->position;
    float rMag = glm::length(r);

    if (rMag < 0.01f)
        return glm::vec2(0, 0);

    math::vec2f rHat = r / rMag;

    float forceMag = 0.01 * obj1->mass * obj2->mass / (rMag * rMag);

    return rHat * forceMag;
}

void Game::handleCollision(Object *obj1, Object *obj2)
{
    // Calculate the vector from obj1 to obj2
    math::vec2f vector = obj2->position - obj1->position;
    float distance = glm::length(vector);
    float overlap = (obj1->radius + obj2->radius) - distance;

    if (obj1 == player.get() || obj2 == player.get())
    {
        std::cout << "handle collision "
                << obj1 << "-" << obj2
                << " overlap " << overlap
                << " distance " << distance
                << std::endl;
    }

    // Check for division by zero set to 1e-6f
    // Check for stupid overlapping set it higher
    if (overlap > 0.3f || distance < 0.01f)
    {
        // If distance is too small, use a random direction or handle it differently
        std::uniform_real_distribution<float> d(0.02f, 1.f);
        vector = math::vec2f(d(gen), d(gen));
        distance = glm::length(vector);
        overlap = (obj1->radius + obj2->radius) * 2;

        // Resolve overlap smoothly
        math::vec2f direction = vector / distance;
        float factor = 1.f;

        if (obj1 == player.get() || obj2 == player.get())
            factor = 2.0f;

        if (obj1 != player.get())
        {
            obj1->position -= direction * overlap * factor;
            obj1->velocity = -obj1->velocity * 0.5f;
        }

        if (obj2 != player.get())
        {
            obj2->velocity = -obj2->velocity * 0.5f;
            obj2->position += direction * overlap * factor;
        }

        return;
    }
    /*/

    // Update velocities after collision
    math::vec2f v1 = obj1->velocity;
    math::vec2f v2 = obj2->velocity;
    float m1 = obj1->mass;
    float m2 = obj2->mass;

    // Calculate the normal of the collision
    math::vec2f normal = vector / distance;

    // Calculate the tangent of the collision
    math::vec2f tangent = math::vec2f(-normal.y, normal.x);

    // Project velocities onto tangent and normal
    float v1n = glm::dot(v1, normal);
    float v1t = glm::dot(v1, tangent);
    float v2n = glm::dot(v2, normal);
    float v2t = glm::dot(v2, tangent);

    // Perform collision response
    float newV1n = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
    float newV2n = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

    // Convert back to Cartesian coordinates
    obj1->velocity = normal * newV1n + tangent * v1t;
    obj2->velocity = normal * newV2n + tangent * v2t;
    */

    // Update velocities after collision
    math::vec2f v1 = obj1->velocity;
    math::vec2f v2 = obj2->velocity;
    float m1 = obj1->mass;
    float m2 = obj2->mass;
    obj1->velocity = (v1 * (m1 - m2) + 2 * m2 * v2) / (m1 + m2);
    obj2->velocity = (v2 * (m2 - m1) + 2 * m1 * v1) / (m1 + m2);
}

void Game::simulate(float dt, int steps)
{
    for (int step = 0; step < steps; ++step)
    {
        for (unsigned i=0; i<objects.size(); ++i)
        {
            auto obj = objects[i];
            math::vec2f totalForce(0, 0);

            for (const auto& otherObj : objects)
            {
                if (obj.get() != otherObj.get())
                {
                    totalForce += calculateForce(obj.get(), otherObj.get());

                    if (obj->isColliding(otherObj.get()))
                        if (obj->shouldCollide(otherObj.get()))
                            handleCollision(obj.get(), otherObj.get());
                }
            }

            totalForce.x = math::clamp(totalForce.x, -10.f, 10.0f);
            totalForce.y = math::clamp(totalForce.y, -10.f, 10.0f);

            obj->update(totalForce, dt/steps);
        }

        for (unsigned i=0; i<objects.size(); ++i)
        {
            auto obj = objects[i];
            obj->position.x = math::clamp(obj->position.x, -boundary.x, boundary.x);
            obj->position.y = math::clamp(obj->position.y, -boundary.y, boundary.y);

            if(obj->position.x < -boundary.x)
            {
                obj->position.x = -boundary.x;
                obj->velocity.x = -obj->velocity.x * 0.5f;
            }

            if(obj->position.x > boundary.x)
            {
                obj->position.x = boundary.x;
                obj->velocity.x = -obj->velocity.x * 0.5f;
            }

            if(obj->position.y < -boundary.y)
            {
                obj->position.y = -boundary.y;
                obj->velocity.y = -obj->velocity.y * 0.5f;
            }

            if(obj->position.y > boundary.y)
            {
                obj->position.y = boundary.y;
                obj->velocity.y = -obj->velocity.y * 0.5f;
            }
        }
    }
}

bool Game::manage(sleek::device::input *a) noexcept
{
    if(player->manage(a))
        return true;

    if(smgr->manage(a))
        return false;

    if(a->type == EVENT_KEY_DOWN)
    {
        //! engine test
        if(a->key[KEY_F11])
        {
            screen->setFullScreen(!screen->getInfo().fullscreen);
            return true;
        }

        if(a->key[KEY_F2])
        {
            if (objects.size() > 2)
            {
                //unused.push_back(objects[objects.size()-1]);
                objects.pop_back();
            }
            return true;
        }

        if(a->key[KEY_F3])
        {
            spawnAsteroid(5);
            return true;
        }

        //! engine test
        if(a->key[KEY_SPACE])
        {
            rotation = !rotation;
            return true;
        }

        if(a->key[KEY_KEY_S])
        {
            return true;
        }
    }

    return false;
}

void Game::spawnAsteroid(int i)
{
    std::uniform_real_distribution<float> xDist(-boundary.x, boundary.x);
    std::uniform_real_distribution<float> yDist(-boundary.y, boundary.y);
    std::uniform_real_distribution<float> vDist(-0.1f, 0.1f);

    auto asteroid = std::make_shared<Object>(this, 3 + i%11);
    bool validPosition = false;
    float vx = vDist(gen);
    float vy = vDist(gen);
    glm::vec2 position;
    glm::vec2 velocity;

    for(unsigned retry=0; retry<5000 && !validPosition; ++retry)
    {
        float x = xDist(gen);
        float y = yDist(gen);
        asteroid->position = {x,y};
        validPosition = true;

        for (const auto& obj : objects)
        {
            if(asteroid->isColliding(obj.get(), 0.1f))
            {
                validPosition = false;
                break;
            }
        }
    }

    if (validPosition)
    {
        asteroid->velocity = {vx, vy};
        objects.push_back(asteroid);
        std::cout << "new asteroid " << i << " at {" << position.x << "," << position.y << "}" << std::endl;
    }
}

void Game::render() noexcept
{
    time.update();
    float delta = time.getTimeSec();
    time.reset();

    simulate(delta, 10);

    auto camera = smgr->getCamera();
    camera->setTarget(player->getPosition());
    camera->setPosition(player->getPosition() + math::vec3f{0, 7.5, 0.1});

    camera->render();
    //background->render();
    for(auto &obj : objects)
        obj->render();
        
    //smgr->render();
}