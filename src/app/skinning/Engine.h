#ifndef SAMPLE_ENGINE
#define SAMPLE_ENGINE

#include "../sleek/start.h"
#include "../sleek/driver/mesh.h"
#include "../sleek/loader/ressource_loader.h"
#include "../sleek/gui/interface.h"
#include "../sleek/math/math.h"

#include "skinning/LinearBlend.h"
#include "skinning/DualQuaternion.h"
#include <map>

namespace sample
{
    class Core;
    class Engine : public sleek::device::event
    {
        public:
            Engine(Core*) noexcept;
            virtual ~Engine() noexcept;

            std::shared_ptr<sleek::driver::material> buildMaterial(
                sleek::scene3d::Node *node, void *user,
                std::string filename_vert,
                std::string filename_frag,
                sleek::driver::shader_callback callback,
                int tid
            ) noexcept;

            static void callback(sleek::driver::shader *i) noexcept
            {
                auto *node = static_cast<sleek::scene3d::real::Natif*>(i->user[0]);
                auto *camera = node->getScene()->getCamera();

                i->setVariable("model",      node->getModelMatrix());
                i->setVariable("view",       camera->getViewMatrix());
                i->setVariable("projection", camera->getProjectionMatrix());

                i->setTexture("base", i->getLinkFromMaterial()->Texture[0], 0);
            };

            sleek::scene3d::Scene* getSceneManager() const noexcept { return smgr; }
            sleek::device::Device* getDevice() const noexcept { return screen; }
            sleek::math::timer* getTimer() noexcept { return &tm; }

            bool manage(sleek::device::input*) noexcept override;

            void render() noexcept;
        private:
            sleek::f32 distance;
            bool rotation = 0;
            float pitch = 0.f;
            float rot = 0.f;

            std::vector<std::shared_ptr<sleek::driver::texture>> texture;
            std::vector<std::shared_ptr<sleek::driver::mesh>> mesh;
            std::vector<sleek::scene3d::real::Natif*> node;

            LinearBlend linear_blend;
            DualQuaternion dual_quat;
            DualQuaternion heart;
        private:
            sleek::math::timer tm;
            sleek::device::Device *screen;
            sleek::scene3d::Scene *smgr;
            sleek::scene3d::real::Grid *grid;
            Core *core;
    };
}
#endif // GAME_MENU
