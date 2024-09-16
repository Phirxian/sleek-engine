
#pragma once

#include "../sleek/start.h"
#include "../sleek/driver/mesh.h"
#include "../sleek/loader/ressource.h"
#include "../sleek/gui/interface.h"
#include "../sleek/math/math.h"
#include <thread>
#include <chrono>
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
            sleek::driver::material_callback callback,
            int tid
        ) noexcept;

        std::string loadShaderCode(const std::string& filename);

        static void material_callback(sleek::driver::material *mat) noexcept
        {
            auto i = mat->getShader();
            auto *node = static_cast<sleek::scene3d::real::Natif*>(mat->user[0]);
            auto *camera = node->getScene()->getCamera();

            i->setVariable("model",      node->getModelMatrix());
            i->setVariable("view",       camera->getViewMatrix());
            i->setVariable("projection", camera->getProjectionMatrix());

            if (mat->Texture.size())
                i->setTexture("base", mat->Texture[0], 0);
        };

        sleek::driver::context* getContext() const noexcept;
        sleek::scene3d::Scene* getSceneManager() const noexcept { return smgr; }
        sleek::device::Device* getDevice() const noexcept { return screen; }
        sleek::math::timer* getTimer() noexcept { return &tm; }

        inline std::shared_ptr<sleek::driver::texture> getTexture(int i) const noexcept { return textures[i]; }
        
        virtual void render() noexcept = 0;
        
    protected:
        sleek::device::Device *screen;
        sleek::scene3d::Scene *smgr;
        
        std::vector<std::shared_ptr<sleek::driver::texture>> textures;
        std::map<std::string, std::shared_ptr<sleek::driver::shader>> shader_cache;
        std::map<std::string, std::string> shaders_source_cache;
        
        sleek::math::timer tm;
        Core *core;
};