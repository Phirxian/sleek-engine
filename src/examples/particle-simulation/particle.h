#include <glm/glm.hpp>
#include <iostream>

class Particle
{
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec2 previousPosition;
        glm::vec2 interpolatedPosition;

        float mass;
        bool isResting;

    public:
        Particle(glm::vec2 pos, glm::vec2 vel, float m)
        {
            position = pos;
            velocity = vel;
            previousPosition = pos;
            interpolatedPosition = pos;
            mass = m;
            isResting = false;
        }

        void update(float time_step)
        {
            if(glm::length(velocity) < VELOCITY_THRESHOLD)
            {
                isResting = true;
                velocity = glm::vec2(0.0f, 0.0f);
            }
            else
            {
                isResting = false;
            }
            
            if(!isResting)
            {
                velocity.y += GRAVITY * time_step;
                velocity *= (1.0f - DAMPING_FACTOR * time_step);
                position += velocity * time_step;
            }
        }
};