#ifndef GRID
#define GRID

#include "../node.h"

namespace sleek
{
    namespace scene3d
    {
        namespace real
        {
            class Grid : public Node
            {
                public:
                    Grid(Scene*, const math::pixel &color = math::pixel(0,128,128)) noexcept;

                    void setQuadSize(const f32) noexcept;
                    void setSpace(const math::aabbox2df&) noexcept;
                    void setColor(const math::pixel&) noexcept;

                    math::pixel getColor() const noexcept;
                    math::aabbox2df getSpace() const noexcept;
                    f32 getQuadSize() const noexcept;

                    virtual void render() noexcept;
                protected:
                    math::aabbox2df space;
                    math::pixel color;
                    f32 size;
            };
        }
    }
}

#endif
