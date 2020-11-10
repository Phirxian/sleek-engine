#ifndef OCTREE
#define OCTREE

#include "natif.h"

namespace sleek
{
    namespace scene3d
    {
        namespace real
        {
            class Octree : public Natif
            {
                public:
                    Octree(Scene*) noexcept;
                    ~Octree() noexcept;
            };
        }
    }
}

#endif
