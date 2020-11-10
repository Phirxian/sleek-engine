#include "../scene.h"
#include "octree.h"

namespace sleek
{
    namespace scene3d
    {
        namespace real
        {
            Octree::Octree(Scene *smgr) noexcept : Natif(smgr)
            {
            }

            Octree::~Octree() noexcept
            {
            }
        }
    }
}
