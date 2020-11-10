#include "mesh.h"

namespace sleek
{
    namespace driver
    {
        mesh::mesh() noexcept
        {
            gpu = nullptr;
        }

        mesh::~mesh() noexcept
        {
        }

        void mesh::setIdentifier(std::shared_ptr<identifier> vbo) noexcept
        {
            gpu = vbo;
        }

        std::shared_ptr<identifier> mesh::getIdentifier() const noexcept
        {
            return gpu;
        }

        math::aabbox3df mesh::getBoundingBox() const noexcept
        {
            return box;
        }

        void mesh::recalculateBoundingBox() noexcept
        {
            for(u32 i = 0; i<vertices.size(); ++i)
                box.addInternalPoint(vertices[i].Pos);
        }

        void mesh::clear() noexcept
        {
            vertices.clear();
            indices.clear();
        }
    }
}
