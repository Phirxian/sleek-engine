#include "../scene.h"
#include "grid.h"

namespace sleek
{
    namespace scene3d
    {
        namespace real
        {
            Grid::Grid(Scene *smgr, const math::pixel &clr) noexcept : Node(smgr)
            {
                space = math::aabbox2df(math::vec2f(-150,-150), math::vec2f(150.5,150.5));
                color = clr;
                size = 10;
            }

            void Grid::setQuadSize(const f32 i) noexcept
            {
                size = i;
            }

            void Grid::setSpace(const math::aabbox2df &i) noexcept
            {
                space = i;
            }

            void Grid::setColor(const math::pixel &i) noexcept
            {
                color = i;
            }

            math::pixel Grid::getColor() const noexcept
            {
                return color;
            }

            math::aabbox2df Grid::getSpace() const noexcept
            {
                return space;
            }

            f32 Grid::getQuadSize() const noexcept
            {
                return size;
            }

            void Grid::render() noexcept
            {
                if(!enabled)
                    return;

                Node::render();

                for(float x = space.getUpperLeft().x; x<space.getLowerRight().x; x += size)
                    smgr->getDrawManager()->drawLine(
                        math::vec3f(x,0,space.getUpperLeft().y),
                        math::vec3f(x,0,space.getLowerRight().y),
                        color
                    );

                for(float z = space.getUpperLeft().y; z<space.getLowerRight().y; z += size)
                    smgr->getDrawManager()->drawLine(
                        math::vec3f(space.getUpperLeft().x,0,z),
                        math::vec3f(space.getLowerRight().x,0,z),
                        color
                    );
            }
        }
    }
}
