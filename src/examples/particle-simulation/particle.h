#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

class Particle
{
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec2 previousPosition;
        glm::vec2 interpolatedPosition;

        float mass;
        float size;
        bool isResting;
        std::chrono::steady_clock::time_point lastRestingUpdate;

    public:
        Particle(glm::vec2 pos, glm::vec2 vel, float m, float s)
            : position(pos), velocity(vel), previousPosition(pos), interpolatedPosition(pos),
            mass(m), size(s), isResting(false), lastRestingUpdate(std::chrono::steady_clock::now())
        {
        }

        void update(float time_step)
        {
            auto currentTime = std::chrono::steady_clock::now();
            auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastRestingUpdate).count();
            
            if (timeSinceLastUpdate > RESTING_TIMEOUT)
            {
                isResting = false;
                lastRestingUpdate = currentTime;
            }

            if (glm::length(velocity) < VELOCITY_THRESHOLD * time_step)
            {
                isResting = true;
                velocity = glm::vec2(0.0f, 0.0f);
                lastRestingUpdate = currentTime;
            }

            velocity.y += GRAVITY * time_step;
            velocity *= (1.0f - DAMPING_FACTOR * time_step);

            if (!isResting)
                position += velocity * time_step;
        }
};