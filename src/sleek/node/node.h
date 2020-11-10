#ifndef NODE
#define NODE

#include "../reference.h"
#include "../driver/mesh.h"
#include "../driver/driver.h"
#include "../driver/geometry.h"

namespace sleek
{
    namespace scene3d
    {
        class Scene;
        class Node : public reference, public std::enable_shared_from_this<Node>
        {
            public:
                Node(Scene*) noexcept;
                virtual ~Node() noexcept;

                inline std::shared_ptr<Node> getptr() noexcept
                {
                    return std::enable_shared_from_this<Node>::shared_from_this();
                }

                inline Scene* getScene() const noexcept { return smgr; }

                virtual void setEnable(bool) noexcept;
                virtual void setPosition(const math::vec3f&) noexcept;
                virtual void setRotation(const math::vec3f&) noexcept;
                virtual void setScale(const math::vec3f&) noexcept;
                virtual void setMaterial(std::shared_ptr<driver::material>) noexcept;

                virtual math::mat4f getModelMatrix() const noexcept;

                virtual math::vec3f getPosition() const noexcept;
                virtual math::vec3f getRotation() const noexcept;
                virtual math::vec3f getScale() const noexcept;
                virtual bool getEnable() const noexcept;

                virtual std::shared_ptr<driver::material>   getMaterial() noexcept;

                //! used for sorting
                virtual bool operator < (Node*);

                virtual void render() noexcept;
            protected:
                Node() noexcept {}
                Scene *smgr;

                std::shared_ptr<driver::material> mat;
                math::vec3f pos, rot, sca;
                bool enabled;
        };
    }
}
#endif // NODE
