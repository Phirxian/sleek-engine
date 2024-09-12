#pragma once

#include "state/SpaceShooterState.h"
#include "PostProcessing.h"

class Core : public sleek::device::event
{
    public:
        Core() noexcept;
        virtual ~Core() noexcept;

        void setGUI(sleek::gui::interface*) noexcept;
        void setSMGR(sleek::gui::interface*) noexcept;

        sleek::gui::interface* getGui() const noexcept;
        sleek::device::Device* getDevice() const noexcept;
        sleek::driver::driver* getDriver() const noexcept;
        sleek::driver::context* getContext() const noexcept;
        sleek::loader::loader* getLoader() const noexcept;
        sleek::io::filesystem* getFileSystem() const noexcept;

        bool manage(sleek::device::input *a) noexcept override;

        void update_title() noexcept;
        void run() noexcept;
    private:
        std::shared_ptr<sleek::gui::interface> guienv;
        std::shared_ptr<sleek::device::Device> screen;
        std::shared_ptr<sleek::driver::driver> driver;
        std::shared_ptr<sleek::driver::context>renderer;
        std::shared_ptr<sleek::loader::loader> loader;
        std::shared_ptr<sleek::io::filesystem> fs;
        std::shared_ptr<sleek::driver::texture>pointor;
    private:
        sleek::math::timer time;
        PostProcessing *pp;
        SpaceShooterState *scene;
};