#ifndef GEOMETRY
#define GEOMETRY

#include "../math/aabbox.h"
#include "mesh.h"

#include <functional>
#include <vector>

namespace sleek
{
    namespace driver
    {
        class mesh;
        class Geometry
        {
            public:
                Geometry() noexcept;
                virtual ~Geometry() noexcept;

                mesh* createPlane(const math::vec2f &size = math::vec2f(5.f,5.f), const u32 polyCountX = 1, const u32 polyCountY = 1, const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createWall(const math::vec2f &size = math::vec2f(5.f,5.f), const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createCircle(const math::vec2f &radiusxy = math::vec2f(5.f,5.f), const f32 step_x = 10, const f32 step_y = 10, const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createSphere(const f32 radius = 5.f, u32 polyCountX = 16, u32 polyCountY = 16, const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createIcoSphere(const f32 radius = 5.f, u32 subdivide = 0, const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createCube(const math::vec3f &size = math::vec3f(5.f, 5.f, 5.f), const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createPolygone(const math::vec3f&,const math::vec3f&,const math::vec3f&, const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createPyramid(const math::vec3f &size = math::vec3f(5.f, 5.f, 5.f), const math::pixel &color = math::pixel(254,254,254,254)) const noexcept;
                mesh* createTorus(const f32 radiusX = 5.f, const f32 radiusY = 2.5f, const u32 polyCountX = 16, const u32 polyCountY = 16, const math::pixel &color = math::pixel(254,254,254,254)) const noexcept; // not implented
                mesh* createCone(const f32 radius = 5.f, const f32 length = 5.f, const u32 tesselation = 1, const math::pixel &color = math::pixel(254,254,254,254)) const noexcept; // not implented
                mesh* createCylindre(const f32 radius = 5.f, const f32 length = 5.f, const u32 tesselation_x = 100, const u32 tesselation_y = 100, const math::pixel &color = math::pixel(254,254,254,254), bool closeTop = false, f32 oblique = 0.0f) const noexcept; // not implented

                //! @surface must define a vertex grid of [xpath*ypath] and with linear acess of expr "y*xpath+x"
                mesh* createSplineSurface(mesh *surface, u16 xpath, u16 ypath, u16 segments = 100, const math::pixel &color = math::pixel(254,254,254,254));
                mesh* createHeightfieldSurface(std::function<float(float, float)> gen, u16 xpath, u16 ypath, u16 segments = 100, const math::pixel &color = math::pixel(254,254,254,254));
            private:
        };
    }
}

#endif
