#include "Metaball.h"
#include "MetaballTables.h"

#include "math/function.h"
#include "glm/glm.hpp"
#include "opengl/gl.h"

namespace sample
{
    Metaball::Metaball(int gridSize) : threshold(1.0)
    {
        grid.resize((gridSize+1)*(gridSize+1)*(gridSize+1));
        cubes.resize(gridSize*gridSize*gridSize);

        vertices.resize(cubes.size()*12);
        indices.reserve(12);

        int currentVertex=0;

        for(int i=0; i<gridSize+1; i++)
        {
            for(int j=0; j<gridSize+1; j++)
            {
                for(int k=0; k<gridSize+1; k++)
                {
                    grid[currentVertex].position = {
                        (i*40.0f)/(gridSize)-20.0f,
                        (j*40.0f)/(gridSize)-20.0f,
                        (k*40.0f)/(gridSize)-20.0f
                    };
                    grid[currentVertex].normal = glm::normalize(grid[currentVertex].position);
                    currentVertex++;
                }
            }
        }

        int currentCube=0;

        for(int i=0; i<gridSize; i++)
        {
            for(int j=0; j<gridSize; j++)
            {
                for(int k=0; k<gridSize; k++)
                {
                    cubes[currentCube].vertices[0] = &grid[(i*(gridSize+1)+j)*(gridSize+1)+k];
                    cubes[currentCube].vertices[1] = &grid[(i*(gridSize+1)+j)*(gridSize+1)+k+1];
                    cubes[currentCube].vertices[2] = &grid[(i*(gridSize+1)+(j+1))*(gridSize+1)+k+1];
                    cubes[currentCube].vertices[3] = &grid[(i*(gridSize+1)+(j+1))*(gridSize+1)+k];
                    cubes[currentCube].vertices[4] = &grid[((i+1)*(gridSize+1)+j)*(gridSize+1)+k];
                    cubes[currentCube].vertices[5] = &grid[((i+1)*(gridSize+1)+j)*(gridSize+1)+k+1];
                    cubes[currentCube].vertices[6] = &grid[((i+1)*(gridSize+1)+(j+1))*(gridSize+1)+k+1];
                    cubes[currentCube].vertices[7] = &grid[((i+1)*(gridSize+1)+(j+1))*(gridSize+1)+k];

                    currentCube++;
                }
            }
        }
    }

    Metaball::~Metaball()
    {
    }

    void Metaball::setThreshold(sleek::f32 i)
    {
        threshold = i;
    }

    sleek::f32 Metaball::getThreshold() const noexcept
    {
        return threshold;
    }

    void Metaball::move()
    {
        for(int j=0; j<grid.size(); j++)
        {
            grid[j].value = 0.f;
            grid[j].normal = {0.f, 0.f, 0.f};
        }

        for(int i=0; i<balls.size(); i++)
        {
            sleek::f32 squaredRadius = balls[i].squaredRadius;
            for(int j=0; j<grid.size(); j++)
            {
                sleek::math::vec3f ballToPoint = grid[j].position - balls[i].position;

                float squaredDistance =	glm::length(ballToPoint);
                      squaredDistance *= squaredDistance;

                if(squaredDistance == 0.0f)
                    continue;

                grid[j].normal += ballToPoint * squaredRadius/(squaredDistance*squaredDistance);
                grid[j].value += squaredRadius/squaredDistance;
            }
        }
    }

    void Metaball::update()
    {
        vertices.clear();
        indices.clear();

        unsigned int index = 0;

        for(int i=0; i<cubes.size(); i++)
        {
            unsigned char cubeIndex = 0;

            for(int k = 0; k<8; ++k)
                cubeIndex |= (cubes[i].vertices[k]->value < threshold) << k;

            int usedEdges = edgeTable[cubeIndex];

            if(usedEdges==0 || usedEdges==255)
                continue;

            for(int currentEdge=0; currentEdge<12; currentEdge++)
            {
                sleek::math::vertex *tmp = &vertices[index*12 + currentEdge];

                if(usedEdges & 1<<currentEdge)
                {
                    VoxelVertex *v1 = cubes[i].vertices[verticesAtEndsOfEdges[currentEdge*2  ]];
                    VoxelVertex *v2 = cubes[i].vertices[verticesAtEndsOfEdges[currentEdge*2+1]];

                    float delta = (threshold - v1->value) / (v2->value - v1->value);

                    tmp->Pos = v1->position + delta*(v2->position - v1->position);
                    tmp->Normal = v1->normal + delta*(v2->normal - v1->normal);
                    tmp->Coord.x = v1->value;
                    tmp->Coord.y = v2->value;
                    tmp->Color = sleek::math::pixel(0xFFFFFFFF);
                }

                vertices.push_back(*tmp);
            }

            for(unsigned int k=0; triTable[cubeIndex][k] != -1; k+=3)
            {
                indices.push_back(sleek::math::index<3>(
                    sleek::u32(index*12 + triTable[cubeIndex][k+0]),
                    sleek::u32(index*12 + triTable[cubeIndex][k+1]),
                    sleek::u32(index*12 + triTable[cubeIndex][k+2])
                ));
            }

            index++;
        }
    }
}
