#include "scene.h"
#include <algorithm>

namespace sleek
{
    namespace scene3d
    {
        Scene::Scene(device::Device *s, driver::driver *d) noexcept
            : screen(s), mom(d)
        {
            cm = new camera::Camera(screen);
//            setFog(100.f, 1000.f, 0.35f, math::pixel(35,35,35,255));
        }

        Scene::~Scene() noexcept
        {
            clear();
            delete cm;
        }

        /* ***************************************** */

        Node *Scene::addSceneNode(Node *t) noexcept
        {
            nd.push_back(t);
            return t;
        }

        void Scene::removeNode(Node *t) noexcept
        {
            for(auto i = nd.begin(); i != nd.end(); ++i)
            {
                if(*i == t)
                {
                    nd.erase(i);
                    break;
                }
            }
        }

        /* ***************************************** */

        void Scene::clear() noexcept
        {
            while(nd.size())
                removeNode(getNode(0));
        }

        /* ***************************************** */

        bool Scene::manage(device::input *i) noexcept
        {
            return cm->manage(i);
        }

        void Scene::render() noexcept
        {
            cm->render();

            std::sort(nd.begin(), nd.end());
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
            return cm;
        }
    }
}
