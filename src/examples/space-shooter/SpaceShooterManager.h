#ifndef SPACE_SHOOTER_MANAGER
#define SPACE_SHOOTER_MANAGER

#include "../sleek/start.h"
#include "../sleek/driver/mesh.h"
#include "../sleek/loader/ressource.h"
#include "../sleek/gui/interface.h"
#include "../sleek/node/scene.h"
#include "../sleek/math/math.h"

#include "SpaceShooterState.h"

class SpaceShooterManager : public sleek::device::event
{
    public:
        SpaceShooterManager() noexcept;
        virtual ~SpaceShooterManager() noexcept;

        sleek::gui::interface* getGui() const noexcept;
        sleek::device::Device* getDevice() const noexcept;
        sleek::driver::driver* getDriver() const noexcept;
        sleek::driver::context* getContext() const noexcept;
        sleek::loader::loader* getLoader() const noexcept;
        sleek::io::filesystem* getFileSystem() const noexcept;

        std::shared_ptr<sleek::driver::material> buildMaterial(
            sleek::scene3d::Node *node, void *user,
            std::string filename_vert, std::string filename_frag,
            sleek::driver::shader_callback callback, std::shared_ptr<sleek::driver::texture> texture
        ) noexcept;

        bool manage(sleek::device::input *a) noexcept override;

        void setState(GameState);

        void update_title() noexcept;
        void run() noexcept;
    private:
        std::shared_ptr<sleek::device::Device> screen;
        std::shared_ptr<sleek::gui::interface> guienv;
        std::shared_ptr<sleek::driver::driver> driver;
        std::shared_ptr<sleek::driver::context>renderer;
        std::shared_ptr<sleek::loader::loader> loader;
        std::shared_ptr<sleek::io::filesystem> fs;
        std::shared_ptr<sleek::driver::texture>pointor;
    private:
        friend class SpaceShooterState;
        sleek::math::timer time;
        std::shared_ptr<SpaceShooterState> current_state;
        std::shared_ptr<SpaceShooterState> main_menu;
        std::shared_ptr<SpaceShooterState> game;
};
    
#endif
