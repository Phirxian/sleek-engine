#include "../scene.h"
#include "natif.h"

namespace sleek
{
    namespace scene3d
    {
        namespace real
        {
            Natif::Natif(Scene *smgr) noexcept : Node(smgr)
            {
            }

            Natif::~Natif() noexcept
            {
            }

            void Natif::setMesh(std::shared_ptr<driver::mesh> i) noexcept
            {
                mesh = i;
            }

            std::shared_ptr<driver::mesh> Natif::getMesh() const noexcept
            {
                return mesh;
            }

            void Natif::render() noexcept
            {
                if(!enabled)
                    return;

                Node::render();

                if(mesh)
                    smgr->getDrawManager()->drawMesh(mesh.get(), pos, rot);
            }
        }
    }
}
