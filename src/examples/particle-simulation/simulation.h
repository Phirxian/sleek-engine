#include "../sleek/start.h"

#include "nanoflann.hpp"
#include "const.h"
#include "particle.h"

#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <vector>

struct PointCloud
{
    std::vector<Particle *> &particles;

    PointCloud(std::vector<Particle *> &pts) : particles(pts)
    {
    }

    inline size_t kdtree_get_point_count() const
    {
        return particles.size();
    }

    inline float kdtree_get_pt(const size_t idx, const size_t dim) const
    {
        float *data = &particles[idx]->position.x;
        return *(data+dim);
    }

    template<class BBOX> bool kdtree_get_bbox(BBOX &) const
    {
        return false;
    }
};

class Simulation
{
    public:
        Simulation();
        ~Simulation();

        void handleMouseDown(int x, int y);
        void handleMouseMove(int x, int y);
        void handleMouseUp();

        Particle *findNearestParticle(const glm::vec2 &point);

        void update(float dt, int iteration = 3);
        void updateFixed(float timeStep, int iterations);

        void resolveCollision(Particle& particle, Particle& neighbor);
        void interpolateState(float alpha);

        void render(std::shared_ptr<sleek::driver::driver> renderer);

    private:
        std::vector<Particle *> particles;
        typedef nanoflann::KDTreeSingleIndexAdaptor<
            nanoflann::L2_Simple_Adaptor<float, PointCloud>, PointCloud, 2 /* dimensionality */
            >
            KDTree;
        std::unique_ptr<PointCloud> cloud;
        std::unique_ptr<KDTree> index;

        Particle *grabbedParticle;
        glm::vec2 mousePosition;
};