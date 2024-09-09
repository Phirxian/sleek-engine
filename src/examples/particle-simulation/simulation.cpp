#include "simulation.h"
#include <random>

Simulation::Simulation(sleek::driver::texture *texture) : grabbedParticle(nullptr), texture(texture)
{
    solid = std::make_shared<sleek::driver::material>();
    solid->setMaterialRender(sleek::driver::rmt_add);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(0.0f, SCREEN_WIDTH);
    std::uniform_real_distribution<float> yDist(0.0f, SCREEN_HEIGHT / 2);
    std::uniform_real_distribution<float> vDist(-100.0f, 100);

    for(int i = 0; i < MAX_PARTICLES; ++i)
    {
        float x = xDist(gen);
        float y = yDist(gen);
        float vx = vDist(gen);
        float vy = vDist(gen);
        Particle *p = new Particle(glm::vec2(x, y), glm::vec2(vx, vy), 10.0f);
        particles.emplace_back(p);
    }

    addStaticPlatform(glm::vec2(100, SCREEN_HEIGHT / 2 + 100), glm::vec2(200, 20));
    addStaticPlatform(glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300), glm::vec2(SCREEN_HEIGHT / 2, 20));

    for(int i = 0; i < particles.size(); ++i)
    {
        auto &particle = particles[i];
        for(const auto &platform: platforms)
            if(checkCollisionWithPlatform(*particle, platform))
                resolveCollisionWithPlatform(*particle, platform);
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

void Simulation::addStaticPlatform(glm::vec2 position, glm::vec2 size)
{
    platforms.emplace_back(position, size);
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
    if(nearest)
    {
        std::cout << nearest->isResting << "-" << glm::length(nearest->velocity) << std::endl;
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
    // for (int i = 0; i<3; ++i)
    //     updateFixed(dt/3, 1);
    updateFixed(dt, 3);
}

bool Simulation::checkCollisionWithPlatform(Particle &particle, const StaticPlatform &platform)
{
    float minX = platform.position.x - platform.size.x / 2;
    float maxX = platform.position.x + platform.size.x / 2;
    float minY = platform.position.y - platform.size.y / 2;
    float maxY = platform.position.y + platform.size.y / 2;

    auto lx = particle.position.x + PARTICLE_RADIUS > minX;
    auto rx = particle.position.x - PARTICLE_RADIUS < maxX;
    auto ly = particle.position.y + PARTICLE_RADIUS > minY;
    auto ry = particle.position.y - PARTICLE_RADIUS < maxY;

    return lx && rx && ly && ry;
}

void Simulation::resolveCollisionWithPlatform(Particle &particle, const StaticPlatform &platform)
{
    float minX = platform.position.x - platform.size.x / 2;
    float maxX = platform.position.x + platform.size.x / 2;
    float minY = platform.position.y - platform.size.y / 2;
    float maxY = platform.position.y + platform.size.y / 2;

    // Determine the closest edge
    float dxLeft = particle.position.x - (minX - PARTICLE_RADIUS);
    float dxRight = (maxX + PARTICLE_RADIUS) - particle.position.x;
    float dyTop = particle.position.y - (minY - PARTICLE_RADIUS);
    float dyBottom = (maxY + PARTICLE_RADIUS) - particle.position.y;

    float minDistance = std::min(std::min(dxLeft, dxRight), std::min(dyTop, dyBottom));

    // Compute the normal and move the particle
    if(minDistance == dxLeft)
    {
        particle.position.x = minX - PARTICLE_RADIUS;
        particle.velocity.x = -particle.velocity.x * 0.5f;
    }
    else if(minDistance == dxRight)
    {
        particle.position.x = maxX + PARTICLE_RADIUS;
        particle.velocity.x = -particle.velocity.x * 0.5f;
    }
    else if(minDistance == dyTop)
    {
        particle.position.y = minY - PARTICLE_RADIUS;
        particle.velocity.y = -particle.velocity.y * 0.5f;
    }
    else if(minDistance == dyBottom)
    {
        particle.position.y = maxY + PARTICLE_RADIUS;
        particle.velocity.y = -particle.velocity.y * 0.5f;
    }
}

void Simulation::updateFixed(float timeStep, int iterations)
{
    index->buildIndex();

    for(int iter = 0; iter < iterations; ++iter)
    {
// Apply forces and update positions
#pragma omp parallel for
        for(int i = 0; i < particles.size(); ++i)
        {
            auto &particle = particles[i];
            particle->update(timeStep / iterations);

            // Boundary checks
            if(particle->position.x - PARTICLE_RADIUS < 0)
            {
                particle->position.x = PARTICLE_RADIUS;
                particle->velocity.x = -particle->velocity.x * 0.5f; // Dampen the bounce
            }
            else if(particle->position.x + PARTICLE_RADIUS > SCREEN_WIDTH)
            {
                particle->position.x = SCREEN_WIDTH - PARTICLE_RADIUS;
                particle->velocity.x = -particle->velocity.x * 0.5f; // Dampen the bounce
            }

            if(particle->position.y - PARTICLE_RADIUS < 0)
            {
                particle->position.y = PARTICLE_RADIUS;
                particle->velocity.y = -particle->velocity.y * 0.5f; // Dampen the bounce
            }
            else if(particle->position.y + PARTICLE_RADIUS > SCREEN_HEIGHT)
            {
                particle->position.y = SCREEN_HEIGHT - PARTICLE_RADIUS;
                particle->velocity.y = -particle->velocity.y * 0.5f; // Dampen the bounce
            }

            for(const auto &platform: platforms)
                if(checkCollisionWithPlatform(*particle, platform))
                    resolveCollisionWithPlatform(*particle, platform);
        }

        if(grabbedParticle)
        {
            grabbedParticle->position = mousePosition;
            grabbedParticle->velocity = glm::vec2(0.0f, 0.0f);
            grabbedParticle->isResting = false;
        }

        for(int i = 0; i < particles.size(); ++i)
        {
            auto particle = particles[i];

            if(particle->isResting)
                continue;

            const float search_radius = PARTICLE_RADIUS * 2;
            std::vector<nanoflann::ResultItem<unsigned int, float>> ret_matches;

            nanoflann::SearchParameters params;
            const size_t nMatches = index->radiusSearch(&particle->position.x, search_radius * search_radius, ret_matches, params);

            for(size_t k = 0; k < nMatches; k++)
            {
                Particle *neighbor = particles[ret_matches[k].first];
                if(particle != neighbor)
                    resolveCollision(*particle, *neighbor);
            }
        }

        // interpolateState(1.0f/iterations);
    }
}

void Simulation::resolveCollision(Particle &particle, Particle &neighbor)
{
    glm::vec2 diff = particle.position - neighbor.position;
    float dist = glm::length(diff);

    if(dist < PARTICLE_RADIUS * 2)
    {
        glm::vec2 normal = glm::normalize(diff);
        float overlap = PARTICLE_RADIUS * 2 - dist;

        // Separate particles
        if(!particle.isResting)
            particle.position += normal * overlap * 0.5f;

        if(!neighbor.isResting)
            neighbor.position -= normal * overlap * 0.5f;

        // Resolve collision
        glm::vec2 relativeVelocity = particle.velocity - neighbor.velocity;
        float normalVelocity = glm::dot(relativeVelocity, normal);

        if(normalVelocity < 0)
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
        glm::vec2 targetPosition = particle->position;
        particle->position = particle->previousPosition + alpha * (targetPosition - particle->previousPosition);
        particle->previousPosition = targetPosition;
    }
}

void Simulation::render(std::shared_ptr<sleek::driver::driver> driver)
{
    driver->setActiveMaterial(solid);

    for(const auto &platform: platforms)
    {
        sleek::math::vec2i ul = {platform.position.x - platform.size.x / 2, platform.position.y - platform.size.y / 2};
        sleek::math::vec2i lr = {platform.position.x + platform.size.x / 2, platform.position.y + platform.size.y / 2};
        driver->drawCube(ul, lr, {0, 0, 0}, {128, 128, 128});
    }

    for(const auto &particle: particles)
    {
        if(texture)
        {
            sleek::math::vec2i pos = {particle->position.x - PARTICLE_RADIUS, particle->position.y - PARTICLE_RADIUS};
            sleek::math::vec3f scl = {PARTICLE_RADIUS * 2, PARTICLE_RADIUS * 2, PARTICLE_RADIUS * 2};

            if(particle == grabbedParticle)
                driver->drawTextureScale(texture, pos, {0, 0, 0}, scl, {1.f, 1.f}, {255, 0, 0});
            else if(particle->isResting)
                driver->drawTextureScale(texture, pos, {0, 0, 0}, scl, {1.f, 1.f}, {0, 255, 0});
            else
                driver->drawTextureScale(texture, pos, {0, 0, 0}, scl, {1.f, 1.f}, {255, 255, 255});
        }
        else
        {
            sleek::math::vec2i ul = particle->position - PARTICLE_RADIUS;
            sleek::math::vec2i lr = particle->position + PARTICLE_RADIUS;

            if(particle == grabbedParticle)
                driver->drawCube(ul, lr, {0, 0, 0}, {255, 0, 0});
            else if(particle->isResting)
                driver->drawCube(ul, lr, {0, 0, 0}, {0, 255, 0});
            else
                driver->drawCube(ul, lr, {0, 0, 0}, {255, 255, 255});
        }
    }
}