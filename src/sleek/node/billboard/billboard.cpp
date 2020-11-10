#include "../scene.h"
#include "billboard.h"

namespace sleek
{
    namespace scene3d
    {
        namespace billboard
        {
            Billboard::Billboard(Scene *smgr) noexcept : Node(smgr)
            {
            }

            Billboard::Billboard(Scene *smgr, driver::texture *i) noexcept : Node(smgr)
            {
                //mat->Texture[0] = i;
            }

            void Billboard::render() noexcept
            {
                if(!enabled)
                    return;

                Node::render();

                //if(mat->Texture[0])
                //   smgr->getDrawManager()->drawTextureCenter(mat->Texture[0].get(), pos, rot);
            }
        }
    }
}
