#ifndef SAMPLE_ENGINE
#define SAMPLE_ENGINE

#include "../sleek/start.h"
#include "../sleek/driver/mesh.h"
#include "../sleek/loader/ressource_loader.h"
#include "../sleek/gui/interface.h"
#include "../sleek/math/math.h"


#include "metaball/Metaball.h"
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
                sleek::scene3d::Node *node,
                std::string filename_vert,
                std::string filename_frag,
                int tid
            ) noexcept;

            sleek::scene3d::Scene* getSceneManager() const noexcept { return smgr; }
            sleek::device::Device* getDevice() const noexcept { return screen; }
            sleek::math::timer* getTimer() noexcept { return &tm; }

            bool manage(sleek::device::input*) noexcept override;

            void render() noexcept;
        private:
            sleek::f32 distance;
            bool rotation = 0;
            std::vector<std::shared_ptr<sleek::driver::texture>> texture;
            std::shared_ptr<sleek::driver::mesh> tmp;
        private:
            //SparseMetaball metaball;
            Metaball metaball;
        private:
            sleek::math::timer tm;
            sleek::device::Device *screen;
            sleek::scene3d::Scene *smgr;
            sleek::scene3d::real::Natif *node;
            Core *core;
    };
}
#endif // GAME_MENU
