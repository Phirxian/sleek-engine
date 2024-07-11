#include "simulation.h"

Simulation::Simulation() : grabbedParticle(nullptr)
{
    for(int i = 0; i < MAX_PARTICLES; ++i)
    {
        float x = static_cast<float>(rand() % SCREEN_WIDTH);
        float y = static_cast<float>(rand() % SCREEN_HEIGHT);
        float vx = static_cast<float>((rand() % 200) - 100);
        float vy = static_cast<float>((rand() % 200) - 100);
        Particle *p = new Particle(glm::vec2(x, y), glm::vec2(vx, vy), 10.0f);
        particles.emplace_back(p);
    }

    cloud = std::make_unique<PointCloud>(particles);
    index = std::make_unique<KDTree>(2, *cloud, nanoflann::KDTreeSingleIndexAdaptorParams(10));
    index->buildIndex();
}

Simulation::~Simulation()
{
    for(auto particle: particles)
        delete particle;
}

void Simulation::handleMouseDown(int x, int y)
{
    mousePosition = glm::vec2(x, y);
    grabbedParticle = findNearestParticle(mousePosition);
    if(grabbedParticle)
        grabbedParticle->isResting = false;
}

void Simulation::handleMouseUp()
{
    if(grabbedParticle)
    {
        grabbedParticle->velocity = glm::vec2(0.0f, GRAVITY);
        grabbedParticle->isResting = false;
        grabbedParticle = nullptr;
    }
}

void Simulation::handleMouseMove(int x, int y)
{
    mousePosition = glm::vec2(x, y);
    auto nearest = findNearestParticle(mousePosition);
    if (nearest)
    {
        std::cout
        << nearest->isResting
        << "-"
        << glm::length(nearest->velocity)
        << std::endl;
    }
}

Particle *Simulation::findNearestParticle(const glm::vec2 &point)
{
    Particle *nearest = nullptr;
    float minDist = GRAB_RADIUS;

    for(auto particle: particles)
    {
        float dist = glm::distance(point, particle->position);
        if(dist < minDist)
        {
            minDist = dist;
            nearest = particle;
        }
    }

    return nearest;
}

void Simulation::update(float dt, int iteration)
{
    //for (int i = 0; i<3; ++i)
    //    updateFixed(dt/3, 1);
    updateFixed(dt, 3);
}

void Simulation::updateFixed(float timeStep, int iterations)
{
    index->buildIndex();

    for(int iter = 0; iter < iterations; ++iter)
    {
        // Apply forces and update positions
        #pragma omp parallel for
        for (int i = 0; i < particles.size(); ++i)
        {
            auto& particle = particles[i];
            particle->update(timeStep/iterations);

            // Boundary checks
            if (particle->position.x - PARTICLE_RADIUS < 0)
            {
                particle->position.x = PARTICLE_RADIUS;
                particle->velocity.x = -particle->velocity.x * 0.5f; // Dampen the bounce
            }
            else if (particle->position.x + PARTICLE_RADIUS > SCREEN_WIDTH)
            {
                particle->position.x = SCREEN_WIDTH - PARTICLE_RADIUS;
                particle->velocity.x = -particle->velocity.x * 0.5f; // Dampen the bounce
            }

            if (particle->position.y - PARTICLE_RADIUS < 0)
            {
                particle->position.y = PARTICLE_RADIUS;
                particle->velocity.y = -particle->velocity.y * 0.5f; // Dampen the bounce
            }
            else if (particle->position.y + PARTICLE_RADIUS > SCREEN_HEIGHT)
            {
                particle->position.y = SCREEN_HEIGHT - PARTICLE_RADIUS;
                particle->velocity.y = -particle->velocity.y * 0.5f; // Dampen the bounce
            }
        }

        if(grabbedParticle)
        {
            grabbedParticle->position = mousePosition;
            grabbedParticle->velocity = glm::vec2(0.0f, 0.0f);
            grabbedParticle->isResting = false;
        }

        for (int i = 0; i < particles.size(); ++i)
        {
            auto particle = particles[i];

            if(particle->isResting)
                continue;

            const float search_radius = PARTICLE_RADIUS * 2;
            std::vector<nanoflann::ResultItem<unsigned int, float>> ret_matches;

            nanoflann::SearchParameters params;
            const size_t nMatches = index->radiusSearch(&particle->position.x, search_radius * search_radius, ret_matches, params);

            for(size_t i = 0; i < nMatches; i++)
            {
                Particle *neighbor = particles[ret_matches[i].first];
                if(particle != neighbor)
                    resolveCollision(*particle, *neighbor);
            }
        }

        interpolateState(1.0f/iterations);
    }
}

void Simulation::resolveCollision(Particle& particle, Particle& neighbor)
{
    glm::vec2 diff = particle.position - neighbor.position;
    float dist = glm::length(diff);
    if (dist < PARTICLE_RADIUS * 2)
    {
        glm::vec2 normal = glm::normalize(diff);
        float overlap = PARTICLE_RADIUS * 2 - dist;

        // Separate particles
        if (!particle.isResting)
            particle.position += normal * overlap * 0.5f;
            
        if (!neighbor.isResting)
            neighbor.position -= normal * overlap * 0.5f;

        // Resolve collision
        glm::vec2 relativeVelocity = particle.velocity - neighbor.velocity;
        float normalVelocity = glm::dot(relativeVelocity, normal);

        if (normalVelocity < 0 )
        {
            float restitution = 0.5f;
            float j = -(1 + restitution) * normalVelocity;
            j /= 1 / particle.mass + 1 / neighbor.mass;

            glm::vec2 impulse = j * normal;
            
            // Apply impulse and check against VELOCITY_THRESHOLD
            particle.velocity += (impulse / particle.mass);
            neighbor.velocity -= (impulse / neighbor.mass);
        }
    }
}

void Simulation::interpolateState(float alpha)
{
    #pragma omp parallel for
    for(auto &particle: particles)
    {
        // Store the current position as the target position
        glm::vec2 targetPosition = particle->position;

        // Interpolate between the previous position and the target position
        particle->interpolatedPosition = particle->previousPosition + alpha * (targetPosition - particle->previousPosition);

        // Update the previous position for the next frame
        particle->previousPosition = targetPosition;
    }
}

void Simulation::render(std::shared_ptr<sleek::driver::driver> driver)
{
    for(const auto &particle: particles)
        if (particle == grabbedParticle)
            driver->drawCircle(particle->interpolatedPosition, PARTICLE_RADIUS, {255,0,0});
        else
            driver->drawCircle(particle->interpolatedPosition, PARTICLE_RADIUS, {255,255,255});
}