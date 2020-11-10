#ifndef __SAMPLE_META_BALL__
#define __SAMPLE_META_BALL__

#include "start.h"
#include "driver/mesh.h"
#include <vector>

namespace sample
{
    struct MetaBallPosition
    {
        sleek::math::vec3f position;
        sleek::f32 squaredRadius;
    };

    struct VoxelVertex
    {
        sleek::math::vec3f position;
        sleek::math::vec3f normal;
        sleek::f32 value;
    };

    struct VoxelCube
    {
        VoxelVertex * vertices[8];
    };

    class Metaball : public sleek::driver::mesh
    {
        public:
            Metaball(int size = 40);
            ~Metaball();

            void setThreshold(sleek::f32);
            sleek::f32 getThreshold() const noexcept;

            std::vector<MetaBallPosition> balls;

            void move();

            void update();
        protected:
            std::vector<VoxelVertex> grid;
            std::vector<VoxelCube> cubes;
        protected:
            sleek::f32 threshold;
    };
}

#endif
