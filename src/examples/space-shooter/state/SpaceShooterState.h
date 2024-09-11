
#pragma once

#include "../sleek/start.h"
#include "../sleek/driver/mesh.h"
#include "../sleek/loader/ressource.h"
#include "../sleek/gui/interface.h"
#include "../sleek/math/math.h"
#include <map>

class Core;
class SpaceShooterState : public sleek::device::event
{
    public:
        SpaceShooterState(Core*) noexcept;
        virtual ~SpaceShooterState() noexcept;

        std::shared_ptr<sleek::driver::material> buildMaterial(
            sleek::scene3d::Node *node, void *user,
            std::string filename_vert,
            std::string filename_frag,
            sleek::driver::shader_callback callback,
            int tid
        ) noexcept;

        static void material_callback(sleek::driver::shader *i) noexcept
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
        
        virtual void render() noexcept = 0;
        
    protected:
        sleek::device::Device *screen;
        sleek::scene3d::Scene *smgr;
        
        std::vector<std::shared_ptr<sleek::driver::texture>> texture;
        
        sleek::math::timer tm;
        Core *core;
};