#ifndef SCENE
#define SCENE

#include "../device/device.h"
#include "../driver/fbo.h"

//#include "node.h"

#include "billboard/billboard.h"
#include "billboard/sprite.h"
#include "camera/camera.h"
#include "real/natif.h"
#include "real/octree.h"
#include "real/grid.h"

namespace sleek
{
    namespace scene3d
    {
        class Scene : public sleek::device::event, public std::enable_shared_from_this<Scene>
        {
            public:
                Scene(device::Device *, driver::driver *) noexcept;
                virtual ~Scene() noexcept;

                inline std::shared_ptr<Scene> getptr() noexcept
                {
                    return shared_from_this();
                }

                Node *addSceneNode(Node*) noexcept;
                u32   getNumberNode() const noexcept { return nd.size(); }
                Node *getNode(u32 i) const noexcept { return nd[i]; }
                void removeNode(Node*) noexcept;

                void clear() noexcept;

                void enableDebugDraw(bool) noexcept;
                bool isDebugDraw() const noexcept;

                device::Device *getDevice() const noexcept;
                driver::driver *getDrawManager() const noexcept;
                camera::Camera *getCamera() const noexcept;

                virtual bool manage(device::input*) noexcept;

                void render() noexcept;
            protected:
                device::Device *screen;
                camera::Camera *cm;
                driver::driver *mom;
            private:
                bool debug_draw;
                std::vector<Node*> nd;
                const char *currentScene;
        };
    }
}
#endif // Scene_H
