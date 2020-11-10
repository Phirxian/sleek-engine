#ifndef MESH
#define MESH

#include "context.h"
#include "material.h"
#include "../math/vertex.h"
#include "../math/index.h"

namespace sleek
{
    namespace driver
    {
        class driver;
        class Geometry;

        class mesh : public std::enable_shared_from_this<mesh>
        {
            public:
                struct MeshAttribut
                {
                    void *data;
                    int type;
                    int componant;
                    size_t element_size;
                    size_t size;
                };
            public:
                mesh() noexcept;
                ~mesh() noexcept;

                inline std::shared_ptr<mesh> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual void clear() noexcept;
                virtual void recalculateBoundingBox() noexcept;
                virtual math::aabbox3df getBoundingBox() const noexcept;

                virtual void setIdentifier(std::shared_ptr<identifier>) noexcept;
                virtual std::shared_ptr<identifier> getIdentifier() const noexcept;

                std::vector<math::vertex> vertices;
                std::vector<math::index<3>> indices;

                std::vector<MeshAttribut> datas;
            protected:
                friend class Geometry;
                friend class driver;

                math::aabbox3df box;
                math::vec3f scale;

                std::shared_ptr<identifier> gpu;
        };
    }
}

#endif
