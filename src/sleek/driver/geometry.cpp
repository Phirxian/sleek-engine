#include "mesh.h"
#include "geometry.h"
#include <math.h>

#include "../library/glm/glm.hpp"
#include "../math/spline.h"
#include "../math/edgemap.h"

namespace sleek
{
    namespace driver
    {
        Geometry::Geometry() noexcept
        {
        }

        Geometry::~Geometry() noexcept
        {
        }

        mesh* Geometry::createPlane(const math::vec2f &size, const u32 polyCountX, const u32 polyCountY, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
                tmp->vertices.resize(4);
                    tmp->vertices[0].Pos = {-size.x/2, 0,-size.y/2};
                    tmp->vertices[1].Pos = { size.x/2, 0,-size.y/2};
                    tmp->vertices[2].Pos = { size.x/2, 0, size.y/2};
                    tmp->vertices[3].Pos = {-size.x/2, 0, size.y/2};

                    tmp->vertices[0].Coord = {0.0f, 0.0f};
                    tmp->vertices[1].Coord = {1.0f, 0.0f};
                    tmp->vertices[2].Coord = {1.0f, 1.0f};
                    tmp->vertices[3].Coord = {0.0f, 1.0f};

                    tmp->vertices[0].Normal = { 0.0f, 1.0f, 0.f};
                    tmp->vertices[1].Normal = { 0.0f, 1.0f, 0.f};
                    tmp->vertices[2].Normal = { 0.0f, 1.0f, 0.f};
                    tmp->vertices[3].Normal = { 0.0f, 1.0f, 0.f};

                    tmp->vertices[0].Color = color;
                    tmp->vertices[1].Color = color;
                    tmp->vertices[2].Color = color;
                    tmp->vertices[3].Color = color;
                tmp->indices.resize(2);
                    tmp->indices[0] = math::index<3u>(0u,2u,1u);
                    tmp->indices[1] = math::index<3u>(0u,3u,2u);
            return tmp;
        }

        mesh* Geometry::createWall(const math::vec2f &size, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
                tmp->vertices.resize(4);
                    tmp->vertices[0].Pos = {-size.x/2,-size.y/2, 0};
                    tmp->vertices[1].Pos = { size.x/2,-size.y/2, 0};
                    tmp->vertices[2].Pos = { size.x/2, size.y/2, 0};
                    tmp->vertices[3].Pos = {-size.x/2, size.y/2, 0};

                    tmp->vertices[0].Coord = {0.0f, 0.0f};
                    tmp->vertices[1].Coord = {1.0f, 0.0f};
                    tmp->vertices[2].Coord = {1.0f, 1.0f};
                    tmp->vertices[3].Coord = {0.0f, 1.0f};

                    tmp->vertices[0].Normal = { 0.0f, 0.0f, 1.f};
                    tmp->vertices[1].Normal = { 0.0f, 0.0f, 1.f};
                    tmp->vertices[2].Normal = { 0.0f, 0.0f, 1.f};
                    tmp->vertices[3].Normal = { 0.0f, 0.0f, 1.f};

                    tmp->vertices[0].Color = color;
                    tmp->vertices[1].Color = color;
                    tmp->vertices[2].Color = color;
                    tmp->vertices[3].Color = color;
                tmp->indices.resize(2);
                    tmp->indices[0] = math::index<3u>(0u,2u,1u);
                    tmp->indices[1] = math::index<3u>(2u,3u,0u);
            return tmp;
        }

        mesh* Geometry::createCircle(const math::vec2f &radiusxy, const f32 step_x, const f32 step_y, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
                tmp->vertices.resize(step_x*step_y+1);
                register unsigned short psize = 0;
                register float anglex = 0.f, angley = 0.f;
                for(register float x = 0.f; x<step_x; ++x)
                {
                    anglex += radiusxy.x;
                    for(register float y = 0.f; x<step_y; ++y)
                    {
                        angley += radiusxy.y;
                        tmp->vertices[psize].Pos = math::vec3f(sin(anglex), 0, cos(angley));
                        psize++;
                    }
                }
            return tmp;
        }

        mesh* Geometry::createSphere(const f32 radius, u32 polyCountX, u32 polyCountY, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();

            polyCountX = std::max(polyCountX, 2u);
            polyCountY = std::max(polyCountY, 2u);

            const u32 polyCountXPitch = polyCountX+1;

            tmp->indices.reserve(polyCountX*polyCountY*6);
            {
                const u32 polyCountSq = polyCountXPitch * polyCountY;         // top point
                const u32 polyCountSq1 = polyCountSq + 1;                     // bottom point
                const u32 polyCountSqM1 = (polyCountY - 1) * polyCountXPitch; // last row's first vertex
                u32 level = 0;

                for(u32 p1 = 0; p1 < polyCountY-1; ++p1)
                {
                    for(u32 p2 = 0; p2 < polyCountX - 1; ++p2)
                    {
                        const u32 curr = level + p2;
                        tmp->indices.push_back(math::index<3>(curr + polyCountXPitch, curr + 1, curr));
                        tmp->indices.push_back(math::index<3>(curr + polyCountXPitch, curr + 1 + polyCountXPitch, curr + 1));
                    }

                    tmp->indices.push_back(math::index<3>(
                        level + polyCountX - 1 + polyCountXPitch,
                        level + polyCountX,
                        level + polyCountX - 1
                    ));

                    tmp->indices.push_back(math::index<3>(
                        level + polyCountX - 1 + polyCountXPitch,
                        level + polyCountX + polyCountXPitch,
                        level + polyCountX
                    ));

                    level += polyCountXPitch;
                }

                for(u32 p2 = 0; p2 < polyCountX - 1; ++p2)
                {
                    tmp->indices.push_back(math::index<3>(polyCountSq, p2, p2 + 1));
                    tmp->indices.push_back(math::index<3>(polyCountSqM1 + p2, polyCountSq1, polyCountSqM1 + p2 + 1));
                }

                tmp->indices.push_back(math::index<3>(polyCountSq, polyCountX-1, polyCountX));
                tmp->indices.push_back(math::index<3>(polyCountSqM1 + polyCountX - 1, polyCountSq1, polyCountSqM1));
            }

            tmp->vertices.reserve(polyCountX*polyCountY);
            {
                const f64 AngleX = 2 * PI / polyCountX;
                const f64 AngleY = PI / polyCountY;

                u32 i=0;
                f64 axz, ay = 0;

                tmp->vertices.resize((polyCountXPitch * polyCountY) + 2);
                for(u32 y = 0; y < polyCountY; ++y)
                {
                    ay += AngleY;
                    const f64 sinay = sin(ay);
                    axz = 0;

                    for(u32 xz = 0;xz < polyCountX; ++xz)
                    {
                        const math::vec3f pos(
                            radius/2.f * cos(axz) * sinay,
                            radius/2.f * cos(ay),
                            radius/2.f * sin(axz) * sinay
                        );

                        math::vec3f normal = glm::normalize(pos);

                        f32 tu = 0.5f;

                        if(normal.y != -1.0f && normal.y != 1.0f)
                            tu =  acos(math::clamp(normal.x/sinay, -1.0, 1.0)) * 0.5 * RECIPROCAL_PI;
                        if(normal.z < 0.0f)
                            tu = 1-tu;

                        tmp->vertices[i].Pos = pos;
                        tmp->vertices[i].Normal = normal;
                        tmp->vertices[i].Color = color;
                        tmp->vertices[i].Coord.x = tu;
                        tmp->vertices[i].Coord.y = ay*RECIPROCAL_PI;

                        ++i;
                        axz += AngleX;
                    }

                    tmp->vertices[i] = tmp->vertices[i-polyCountX];
                    tmp->vertices[i].Coord.x = 1.0f;
                    ++i;
                }

                tmp->vertices[i].Pos = {0.0f, radius/2.f,0.0f};
                tmp->vertices[i].Normal = math::vec3f(0.0f,-1.f,0.0f);
                tmp->vertices[i].Coord = math::vec2f(0.5f,0.0f);
                tmp->vertices[i].Color = color;

                ++i;

                tmp->vertices[i].Pos = {0.0f, -radius/2.f,0.0f};
                tmp->vertices[i].Normal = math::vec3f(0.0f,1.f,0.0f);
                tmp->vertices[i].Coord = math::vec2f(0.5f,1.0f);
                tmp->vertices[i].Color = color;
            }
            return tmp;
        }

        mesh* Geometry::createIcoSphere(const f32 radius, u32 subdivide, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
            subdivide = std::min(subdivide, 9u);

            //! --------------------------------------

            static constexpr const float phi = (1+sqrt(5))/2.;
            struct triangle { math::vec3f a, b, c; };

            static const math::vec3f vertex[12] = {
                { phi, 1,0}, { phi,-1,0}, {-phi, 1,0}, {-phi,-1,0},
                { 1,0, phi}, { 1,0,-phi}, {-1,0, phi}, {-1,0,-phi},
                {0, phi, 1}, {0, phi,-1}, {0,-phi, 1}, {0,-phi,-1}
            };

            static const uint index[][3] = {
                { 2, 8, 9}, { 9, 8, 0}, { 0, 8, 4}, { 4, 8, 6}, { 6, 8, 2},
                { 3,11,10}, {10,11, 1}, { 1,11, 5}, { 5,11, 7}, { 7,11, 3},
                { 3, 2, 7}, { 7, 2, 9}, { 7, 9, 5}, { 5, 9, 0}, { 5, 0, 1},
                { 1, 0, 4}, { 1, 4,10}, {10, 4, 6}, {10, 6, 3}, { 3, 6, 2}
            };

            //! --------------------------------------

            std::vector<triangle> old_vert;
            std::vector<triangle> cur_vert;

            cur_vert.resize(sizeof(index)/sizeof(index[0]));

            for(int i = 0; i<cur_vert.size(); ++i)
            {
                cur_vert[i].a = glm::normalize(vertex[index[i][0]]);
                cur_vert[i].b = glm::normalize(vertex[index[i][1]]);
                cur_vert[i].c = glm::normalize(vertex[index[i][2]]);
            }

            for(int s = 0; s<subdivide; ++s)
            {
                for(int i = 0; i<cur_vert.size(); ++i)
                {
                    math::vec3f v1 = cur_vert[i].a;
                    math::vec3f v2 = cur_vert[i].b;
                    math::vec3f v3 = cur_vert[i].c;
                    math::vec3f v4 = glm::normalize(v1 + v2);
                    math::vec3f v5 = glm::normalize(v2 + v3);
                    math::vec3f v6 = glm::normalize(v3 + v1);
                    old_vert.push_back({v1, v4, v6});
                    old_vert.push_back({v4, v2, v5});
                    old_vert.push_back({v6, v5, v3});
                    old_vert.push_back({v4, v5, v6});
                }
                old_vert.swap(cur_vert);
                old_vert.clear();
            }

            tmp->vertices.resize(cur_vert.size()*3);
            tmp->indices.resize(cur_vert.size());

            for(unsigned int i = 0; i<cur_vert.size(); ++i)
            {
                tmp->vertices[i*3+0].Pos = cur_vert[i].a * (radius/2.f);
                tmp->vertices[i*3+1].Pos = cur_vert[i].b * (radius/2.f);
                tmp->vertices[i*3+2].Pos = cur_vert[i].c * (radius/2.f);

                tmp->vertices[i*3+0].Normal = cur_vert[i].a;
                tmp->vertices[i*3+1].Normal = cur_vert[i].b;
                tmp->vertices[i*3+2].Normal = cur_vert[i].c;

                tmp->vertices[i*3+0].Color = color;
                tmp->vertices[i*3+1].Color = color;
                tmp->vertices[i*3+2].Color = color;

                tmp->vertices[i*3+0].Coord.x = 0.5f - atan2(cur_vert[i].a.z, cur_vert[i].a.x)/(float)(2.0f*PI);
                tmp->vertices[i*3+1].Coord.x = 0.5f - atan2(cur_vert[i].b.z, cur_vert[i].b.x)/(float)(2.0f*PI);
                tmp->vertices[i*3+2].Coord.x = 0.5f - atan2(cur_vert[i].c.z, cur_vert[i].c.x)/(float)(2.0f*PI);

                tmp->vertices[i*3+0].Coord.y = 0.5f - (0.2f * asin(cur_vert[i].a.y) / 2.0f*PI);
                tmp->vertices[i*3+1].Coord.y = 0.5f - (0.2f * asin(cur_vert[i].b.y) / 2.0f*PI);
                tmp->vertices[i*3+2].Coord.y = 0.5f - (0.2f * asin(cur_vert[i].c.y) / 2.0f*PI);

                tmp->indices[i].vertex[0] = i*3;
                tmp->indices[i].vertex[1] = i*3+2u;
                tmp->indices[i].vertex[2] = i*3+1u;
            }

            return tmp;
        }

        mesh* Geometry::createCube(const math::vec3f &size, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
                tmp->vertices.resize(24);
                    tmp->vertices[ 0].Pos = {-size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[ 1].Pos = { size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[ 2].Pos = { size.x/2, size.y/2, size.z/2};
                    tmp->vertices[ 3].Pos = {-size.x/2, size.y/2, size.z/2};
                    tmp->vertices[ 4].Pos = {-size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[ 5].Pos = {-size.x/2, size.y/2,-size.z/2};
                    tmp->vertices[ 6].Pos = { size.x/2, size.y/2,-size.z/2};
                    tmp->vertices[ 7].Pos = { size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[ 8].Pos = {-size.x/2, size.y/2,-size.z/2};
                    tmp->vertices[ 9].Pos = {-size.x/2, size.y/2, size.z/2};
                    tmp->vertices[10].Pos = { size.x/2, size.y/2, size.z/2};
                    tmp->vertices[11].Pos = { size.x/2, size.y/2,-size.z/2};
                    tmp->vertices[12].Pos = {-size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[13].Pos = { size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[14].Pos = { size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[15].Pos = {-size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[16].Pos = { size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[17].Pos = { size.x/2, size.y/2,-size.z/2};
                    tmp->vertices[18].Pos = { size.x/2, size.y/2, size.z/2};
                    tmp->vertices[19].Pos = { size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[20].Pos = {-size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[21].Pos = {-size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[22].Pos = {-size.x/2, size.y/2, size.z/2};
                    tmp->vertices[23].Pos = {-size.x/2, size.y/2,-size.z/2};

                    tmp->vertices[ 0].Coord = {0.0f, 0.0f};
                    tmp->vertices[ 1].Coord = {1.0f, 0.0f};
                    tmp->vertices[ 2].Coord = {1.0f, 1.0f};
                    tmp->vertices[ 3].Coord = {0.0f, 1.0f};
                    tmp->vertices[ 4].Coord = {1.0f, 0.0f};
                    tmp->vertices[ 5].Coord = {1.0f, 1.0f};
                    tmp->vertices[ 6].Coord = {0.0f, 1.0f};
                    tmp->vertices[ 7].Coord = {0.0f, 0.0f};
                    tmp->vertices[ 8].Coord = {0.0f, 1.0f};
                    tmp->vertices[ 9].Coord = {0.0f, 0.0f};
                    tmp->vertices[10].Coord = {1.0f, 0.0f};
                    tmp->vertices[11].Coord = {1.0f, 1.0f};
                    tmp->vertices[12].Coord = {1.0f, 1.0f};
                    tmp->vertices[13].Coord = {0.0f, 1.0f};
                    tmp->vertices[14].Coord = {0.0f, 0.0f};
                    tmp->vertices[15].Coord = {1.0f, 0.0f};
                    tmp->vertices[16].Coord = {1.0f, 0.0f};
                    tmp->vertices[17].Coord = {1.0f, 1.0f};
                    tmp->vertices[18].Coord = {0.0f, 1.0f};
                    tmp->vertices[19].Coord = {0.0f, 0.0f};
                    tmp->vertices[20].Coord = {0.0f, 0.0f};
                    tmp->vertices[21].Coord = {1.0f, 0.0f};
                    tmp->vertices[22].Coord = {1.0f, 1.0f};
                    tmp->vertices[23].Coord = {0.0f, 1.0f};

                    tmp->vertices[ 0].Normal = { 0.0f, 0.0f, 1.0f};
                    tmp->vertices[ 1].Normal = { 0.0f, 0.0f, 1.0f};
                    tmp->vertices[ 2].Normal = { 0.0f, 0.0f, 1.0f};
                    tmp->vertices[ 3].Normal = { 0.0f, 0.0f, 1.0f};
                    tmp->vertices[ 4].Normal = { 0.0f, 0.0f,-1.0f};
                    tmp->vertices[ 5].Normal = { 0.0f, 0.0f,-1.0f};
                    tmp->vertices[ 6].Normal = { 0.0f, 0.0f,-1.0f};
                    tmp->vertices[ 7].Normal = { 0.0f, 0.0f,-1.0f};
                    tmp->vertices[ 8].Normal = { 0.0f, 1.0f, 0.0f};
                    tmp->vertices[ 9].Normal = { 0.0f, 1.0f, 0.0f};
                    tmp->vertices[10].Normal = { 0.0f, 1.0f, 0.0f};
                    tmp->vertices[11].Normal = { 0.0f, 1.0f, 0.0f};
                    tmp->vertices[12].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[13].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[14].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[15].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[16].Normal = { 1.0f, 0.0f, 0.0f};
                    tmp->vertices[17].Normal = { 1.0f, 0.0f, 0.0f};
                    tmp->vertices[18].Normal = { 1.0f, 0.0f, 0.0f};
                    tmp->vertices[19].Normal = { 1.0f, 0.0f, 0.0f};
                    tmp->vertices[20].Normal = {-1.0f, 0.0f, 0.0f};
                    tmp->vertices[21].Normal = {-1.0f, 0.0f, 0.0f};
                    tmp->vertices[22].Normal = {-1.0f, 0.0f, 0.0f};
                    tmp->vertices[23].Normal = {-1.0f, 0.0f, 0.0f};

                    tmp->vertices[ 0].Color = color; tmp->vertices[ 1].Color = color;
                    tmp->vertices[ 2].Color = color; tmp->vertices[ 3].Color = color;
                    tmp->vertices[ 4].Color = color; tmp->vertices[ 5].Color = color;
                    tmp->vertices[ 6].Color = color; tmp->vertices[ 7].Color = color;
                    tmp->vertices[ 8].Color = color; tmp->vertices[ 9].Color = color;
                    tmp->vertices[10].Color = color; tmp->vertices[11].Color = color;
                    tmp->vertices[12].Color = color; tmp->vertices[13].Color = color;
                    tmp->vertices[14].Color = color; tmp->vertices[15].Color = color;
                    tmp->vertices[16].Color = color; tmp->vertices[17].Color = color;
                    tmp->vertices[18].Color = color; tmp->vertices[19].Color = color;
                    tmp->vertices[20].Color = color; tmp->vertices[21].Color = color;
                    tmp->vertices[22].Color = color; tmp->vertices[23].Color = color;
                tmp->indices.resize(12);
                    tmp->indices[ 0] = math::index<3>( 0u, 2u, 1u);
                    tmp->indices[ 1] = math::index<3>( 0u, 3u, 2u);
                    tmp->indices[ 2] = math::index<3>( 4u, 6u, 5u);
                    tmp->indices[ 3] = math::index<3>( 4u, 7u, 6u);
                    tmp->indices[ 4] = math::index<3>( 8u,10u, 9u);
                    tmp->indices[ 5] = math::index<3>( 8u,11u,10u);
                    tmp->indices[ 6] = math::index<3>(12u,14u,13u);
                    tmp->indices[ 7] = math::index<3>(12u,15u,14u);
                    tmp->indices[ 8] = math::index<3>(16u,18u,17u);
                    tmp->indices[ 9] = math::index<3>(16u,19u,18u);
                    tmp->indices[10] = math::index<3>(20u,22u,21u);
                    tmp->indices[11] = math::index<3>(20u,23u,22u);
            return tmp;
        }

        mesh* Geometry::createPolygone(const math::vec3f &a,const math::vec3f &b,const math::vec3f &c, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
                tmp->vertices.resize(3);
                    tmp->vertices[0].Pos = a;
                    tmp->vertices[1].Pos = b;
                    tmp->vertices[2].Pos = c;
                    tmp->vertices[0].Color = color;
                    tmp->vertices[1].Color = color;
                    tmp->vertices[2].Color = color;
                    tmp->vertices[3].Color = color;
                tmp->indices.resize(1);
                    tmp->indices[0] = math::index<3>(0u, 1u, 2u);
            return tmp;
        }

        mesh* Geometry::createPyramid(const math::vec3f &size, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
                tmp->vertices.resize(16);
                    tmp->vertices[ 0].Pos = {-size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[ 1].Pos = { size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[ 2].Pos = { size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[ 3].Pos = {-size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[ 4].Pos = {-size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[ 5].Pos = { size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[ 6].Pos = {        0, size.y/2,        0};
                    tmp->vertices[ 7].Pos = { size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[ 8].Pos = { size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[ 9].Pos = {        0, size.y/2,        0};
                    tmp->vertices[10].Pos = { size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[11].Pos = {-size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[12].Pos = {        0, size.y/2,        0};
                    tmp->vertices[13].Pos = {-size.x/2,-size.y/2,-size.z/2};
                    tmp->vertices[14].Pos = {-size.x/2,-size.y/2, size.z/2};
                    tmp->vertices[15].Pos = {        0, size.y/2,        0};

                    tmp->vertices[ 0].Coord = {1.0f, 1.0f};
                    tmp->vertices[ 1].Coord = {0.0f, 1.0f};
                    tmp->vertices[ 2].Coord = {0.0f, 0.0f};
                    tmp->vertices[ 3].Coord = {1.0f, 0.0f};
                    tmp->vertices[ 4].Coord = {0.0f, 0.0f};
                    tmp->vertices[ 5].Coord = {1.0f, 0.0f};
                    tmp->vertices[ 6].Coord = {0.5f, 1.0f};
                    tmp->vertices[ 7].Coord = {0.0f, 0.0f};
                    tmp->vertices[ 8].Coord = {1.0f, 0.0f};
                    tmp->vertices[ 9].Coord = {0.5f, 1.0f};
                    tmp->vertices[10].Coord = {0.0f, 0.0f};
                    tmp->vertices[11].Coord = {1.0f, 0.0f};
                    tmp->vertices[12].Coord = {0.5f, 1.0f};
                    tmp->vertices[13].Coord = {0.0f, 0.0f};
                    tmp->vertices[14].Coord = {1.0f, 0.0f};
                    tmp->vertices[15].Coord = {0.5f, 1.0f};

                    tmp->vertices[ 0].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[ 1].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[ 2].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[ 3].Normal = { 0.0f,-1.0f, 0.0f};
                    tmp->vertices[ 4].Normal = {-1.0f,-1.0f,-1.0f};
                    tmp->vertices[ 5].Normal = { 1.0f,-1.0f,-1.0f};
                    tmp->vertices[ 6].Normal = { 0.0f, 1.0f, 0.0f};
                    tmp->vertices[ 7].Normal = { 1.0f,-1.0f,-1.0f};
                    tmp->vertices[ 8].Normal = { 1.0f,-1.0f, 1.0f};
                    tmp->vertices[ 9].Normal = { 0.0f, 1.0f, 0.0f};
                    tmp->vertices[10].Normal = { 1.0f,-1.0f, 1.0f};
                    tmp->vertices[11].Normal = {-1.0f,-1.0f, 1.0f};
                    tmp->vertices[12].Normal = { 0.0f, 1.0f, 0.0f};
                    tmp->vertices[13].Normal = {-1.0f,-1.0f,-1.0f};
                    tmp->vertices[14].Normal = {-1.0f,-1.0f, 1.0f};
                    tmp->vertices[15].Normal = { 0.0f, 1.0f, 0.0f};

                    tmp->vertices[ 0].Color = color; tmp->vertices[ 1].Color = color;
                    tmp->vertices[ 2].Color = color; tmp->vertices[ 3].Color = color;
                    tmp->vertices[ 4].Color = color; tmp->vertices[ 5].Color = color;
                    tmp->vertices[ 6].Color = color; tmp->vertices[ 7].Color = color;
                    tmp->vertices[ 8].Color = color; tmp->vertices[ 9].Color = color;
                    tmp->vertices[10].Color = color; tmp->vertices[11].Color = color;
                    tmp->vertices[12].Color = color; tmp->vertices[13].Color = color;
                    tmp->vertices[14].Color = color; tmp->vertices[15].Color = color;
                tmp->indices.resize(6);
                    tmp->indices[0] = math::index<3>( 0u, 2u, 1u);
                    tmp->indices[1] = math::index<3>( 0u, 3u, 2u);
                    tmp->indices[2] = math::index<3>( 4u, 5u, 6u);
                    tmp->indices[3] = math::index<3>( 7u, 8u, 9u);
                    tmp->indices[4] = math::index<3>(10u,11u,12u);
                    tmp->indices[5] = math::index<3>(13u,14u,15u);
            return tmp;
        }

        mesh* Geometry::createTorus(const f32 radiusX, const f32 radiusY, const u32 polyCountX, const u32 polyCountY, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
            return tmp;
        }

        mesh* Geometry::createCone(const f32 radius, const f32 length, const u32 tesselation, const math::pixel &color) const noexcept
        {
            mesh *tmp = new mesh();
            return tmp;
        }

        mesh* Geometry::createCylindre(const f32 radius, const f32 length, const u32 tesselation_x, u32 tesselation_y, const math::pixel &color, bool closeTop, f32 oblique) const noexcept
        {
            closeTop = false;
            mesh* buffer = new mesh();

            const f32 recTesselation = math::reciprocal((f32)tesselation_x);
            const f32 angleStep = (math::PI * 2.f ) * recTesselation;

            u32 l = 0;
            math::vertex v;
            v.Color = color;
            buffer->vertices.reserve(tesselation_x*2*tesselation_y+4+(closeTop?2:1));
            buffer->indices.reserve((tesselation_x*2+1)*(closeTop?12:9)/3);

            for(float j = 0; j <tesselation_y; j += 2)
            {
                f32 tcx = 0.f;
                f32 lower = j*length/tesselation_y - length/2.0;
                f32 upper = (j+1)*length/tesselation_y - length/2.0;

                for(u32 i = 0; i <= tesselation_x; ++i)
                {
                    const f32 angle = angleStep * i;

                    v.Pos.y = radius * cosf(angle);
                    v.Pos.x = lower;
                    v.Pos.z = radius * sinf(angle);
                    v.Normal = glm::normalize(v.Pos);
                    v.Coord.y = tcx;
                    v.Coord.x = j/tesselation_y;

                    buffer->vertices.push_back(v);

                    v.Pos.y += oblique;
                    v.Pos.x = upper;
                    v.Normal = glm::normalize(v.Pos);
                    v.Coord.x = (j+1)/tesselation_y;

                    buffer->vertices.push_back(v);
                    tcx += recTesselation;
                }
            }

            const u32 next_hull = tesselation_x*2;
            for(int i = 0; i<buffer->vertices.size()-next_hull-4; i += 2)
            {
                buffer->indices.push_back(math::index<3>(i+2u, i+0u, i+2u+next_hull));
                buffer->indices.push_back(math::index<3>(i+2u, i+next_hull+2u, i+next_hull+4u));
            }

            buffer->recalculateBoundingBox();

            return buffer;
        }

        mesh* Geometry::createHeightfieldSurface(std::function<float(float, float)> gen, u16 xpath, u16 ypath, u16 segments, const math::pixel &color)
        {
            u32 XPATH = 20;
            u32 YPATH = 20;
            float sq = (xpath + ypath)/10;

            mesh *surface = new mesh();
            surface->vertices.resize(xpath*ypath);

            for(unsigned y = 0; y<ypath; ++y)
            {
                for(unsigned x = 0; x<xpath; ++x)
                {
                    const unsigned int index = y*xpath + x;
                    surface->vertices[index].Pos = {
                        2*x/xpath - 1.f,
                        gen(x,y)/sq,
                        2*y/ypath - 1.f
                    };
                }
            }

            auto tmp = createSplineSurface(surface, xpath, ypath, segments, color);
            delete surface;

            return tmp;
        }

        mesh* Geometry::createSplineSurface(mesh *surface, u16 xpath, u16 ypath, u16 segments, const math::pixel &color)
        {
            mesh *render = new mesh();
            render->vertices.resize(segments*segments);

            math::spline xsolver(xpath, 3);
            math::spline ysolver(ypath, 3);

            std::vector<math::vec3f> tmp;
            tmp.resize(surface->vertices.size());

            for(u32 i = 0u; i<surface->vertices.size(); ++i)
                tmp[i] = surface->vertices[i].Pos;

            for(float y = 0; y<segments; ++y)
            {
                const unsigned int w = y*segments;
                for(float x = 0; x<segments; ++x)
                {
                    const unsigned int n = w+x;
                    const float u = x/segments;
                    const float v = y/segments;

                    std::vector<math::vec3f> path;

                    for(unsigned k = 0; k<ypath; ++k)
                    {
                        auto view = arv::make_view(&tmp[k*xpath], (size_t)xpath);
                        path.push_back(xsolver.eval_f(u,view));
                    }

                    auto pos = ysolver.eval_f(v, path);

                    render->vertices[n].Pos = pos;
                    render->vertices[n].Normal = {0,1,0};
                    render->vertices[n].Coord = {u,v};
                    render->vertices[n].Color = color;
                }
            }

            const unsigned int last = segments-1;
            render->indices.reserve(last*last*2);

            for(float y = 0; y<last; ++y)
            {
                const unsigned int w = y*segments;
                for(float x = 0; x<last; ++x)
                {
                    const unsigned int n = w+x;
                    render->indices.push_back({n + segments, n + segments + 1, n + 1});
                    render->indices.push_back({n + segments, n + 1, n});
                }
            }

            for(float y = 1; y<last; ++y)
            {
                const unsigned int w = y*segments;
                for(float x = 1; x<last; ++x)
                {
                    const unsigned int n = w+x;

                    math::vec3f vertical = render->vertices[n + segments].Pos
                                         - render->vertices[n - segments].Pos;

                    math::vec3f horizont = render->vertices[n + 1].Pos
                                         - render->vertices[n - 1].Pos;

                    render->vertices[n].Normal = glm::normalize(glm::cross(vertical, horizont));
                }
            }

            return render;
        }

//        void subdivide(mesh* subdiv, int subdivision)
//        {
//            if (subdivision <= 0)
//                return;
//
//            mesh* mesh = new mesh();
//
//            for (int i=0 ; i<subdivision; ++i)
//            {
//                std::vector<math::vec3f> position;
//                std::vector<math::vec4i> quad;
//
//                EdgeMap* edge_map = new EdgeMap(mesh->triangle);
//
//                for (vec3f temp_position: mesh->pos)
//                    position.push_back(temp_position);
//                for (vec2i edge: edge_map->edges())
//                    position.push_back((mesh->pos[edge.x] + mesh->pos[edge.y]) / 2);
//                for (vec3i vertex: mesh->triangle)
//                    position.push_back((mesh->pos[vertex.x] + mesh->pos[vertex.y] + mesh->pos[vertex.z]) / 3);
//                }
//                int edge_offset = mesh->pos.size();
//
//                int triangle_offset = edge_offset + edge_map->edges().size();
//                int quad_offset = triangle_offset + mesh->triangle.size();
//
//                // foreach triangle
//                for (int i=0; i < mesh->triangle.size(); i++)
//                {
//                    // add three quads to the new quad array
//                    vec3i temp_triangle = mesh->triangle[i];
//                    int edge_one = edge_offset + edge_map->edge_index(vec2i(temp_triangle.x, temp_triangle.y));
//                    int edge_two = edge_offset + edge_map->edge_index(vec2i(temp_triangle.y, temp_triangle.z));
//                    int edge_three = edge_offset + edge_map->edge_index(vec2i(temp_triangle.x, temp_triangle.z));
//
//                    int center = triangle_offset + i;
//
//                    quad.push_back(vec4i(temp_triangle.x, edge_one, center, edge_three));
//                    quad.push_back(vec4i(temp_triangle.y, edge_two, center, edge_one));
//                    quad.push_back(vec4i(temp_triangle.z, edge_three, center, edge_two));
//                }
//
//                // averaging pass ----------------------------------
//                // create arrays to compute pos averages (avg_pos, avg_count)
//                vector<vec3f> avg_pos;
//                vector<int> avg_count;
//                // arrays have the same length as the new pos array, and are init to zero
//                avg_pos = vector<vec3f>(position.size(), zero3f);
//                avg_count = vector<int>(position.size(), 0);
//
//                for (vec4i temp_quad: quad)
//                {
//                    // compute quad center using the new pos array
//                    vec3f quad_center = (position[temp_quad.x] + position[temp_quad.y] +
//                                        position[temp_quad.z] + position[temp_quad.w]) / 4;
//
//                    // foreach vertex index in the quad
//                    avg_pos[temp_quad.x] += quad_center;
//                    avg_pos[temp_quad.y] += quad_center;
//                    avg_pos[temp_quad.z] += quad_center;
//                    avg_pos[temp_quad.w] += quad_center;
//
//                    avg_count[temp_quad.x]++;
//                    avg_count[temp_quad.y]++;
//                    avg_count[temp_quad.z]++;
//                    avg_count[temp_quad.w]++;
//                }
//                // normalize avg_pos with its count avg_count
//                for (auto i: range(position.size())){
//                    avg_pos[i] /= avg_count[i];
//                }
//                // correction pass ----------------------------------
//                // foreach pos, compute correction p = p + (avg_p - p) * (4/avg_count)
//                for (auto i: range(position.size())) {
//                    position[i] += (avg_pos[i] - position[i]) * (4.0f / avg_count[i]);
//                }
//
//                mesh->pos = position;
//                mesh->triangle.clear();
//            }
//
//            if(subdivision)
//                smooth_normals(mesh);
//            else
//                facet_normals(mesh);
//
//            *subdiv = *mesh;
//
//            mesh->triangle.clear();
//        }

    }
}
