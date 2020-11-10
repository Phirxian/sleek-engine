#ifndef BILLBOARD
#define BILLBOARD

#include "../node.h"
#include "math/timer.h"

namespace sleek
{
    namespace scene3d
    {
        namespace billboard
        {
            class Billboard : public Node
            {
                public:
                    Billboard(Scene*) noexcept;
                    Billboard(Scene*, driver::texture*) noexcept;

                    virtual void render() noexcept;
                protected:
            };
        }
    }
}

#endif
