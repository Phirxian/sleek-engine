#include "scene.h"
#include <algorithm>

namespace sleek
{
    namespace scene3d
    {
        Scene::Scene(device::Device *s, driver::driver *d) noexcept
            : screen(s), mom(d)
        {
            cm = std::make_shared<camera::Camera>(screen);
//            setFog(100.f, 1000.f, 0.35f, math::pixel(35,35,35,255));
        }

        Scene::~Scene() noexcept
        {
            clear();
        }

        /* ***************************************** */

        std::shared_ptr<Node> Scene::addSceneNode(std::shared_ptr<Node> t) noexcept
        {
            nd.push_back(t);
            return t;
        }

        void Scene::removeNode(std::shared_ptr<Node> t) noexcept
        {
            auto it = std::find_if(
                nd.begin(), nd.end(),
                [t](const std::shared_ptr<Node>& node) {
                    return node.get() == t.get();
                }
            );

            if (it != nd.end())
                nd.erase(it);
        }

        /* ***************************************** */

        void Scene::clear() noexcept
        {
            nd.clear();
        }

        /* ***************************************** */

        bool Scene::manage(device::input *e) noexcept
        {
            return cm->manage(e);
        }

        void Scene::render() noexcept
        {
            cm->render();

            std::sort(nd.begin(), nd.end(), [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
                return a->operator<(b.get());
            });
            
            for(auto &it : nd)
                it->render();
        }

        void Scene::enableDebugDraw(bool a) noexcept
        {
            debug_draw = a;
        }

        bool Scene::isDebugDraw() const noexcept
        {
            return debug_draw;
        }

        void Scene::setCamera(std::shared_ptr<camera::Camera> camera) noexcept
        {
            assert(camera.get() != nullptr);
            cm = camera;
        }

        device::Device *Scene::getDevice() const noexcept
        {
            return screen;
        }

        driver::driver *Scene::getDrawManager() const noexcept
        {
            return mom;
        }

        camera::Camera *Scene::getCamera() const noexcept
        {
            return cm.get();
        }
    }
}
