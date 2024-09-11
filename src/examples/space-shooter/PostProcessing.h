#pragma once

#include "../sleek/start.h"

class Core;
class PostProcessing : public sleek::device::event
{
    public:
        PostProcessing(Core*) noexcept;
        virtual ~PostProcessing() noexcept;

        bool manage(sleek::device::input *a) noexcept override;

        void begin() noexcept;
        void end() noexcept;

        void draw() noexcept;
    protected:
        std::vector<std::shared_ptr<sleek::driver::shader>> pp;
        std::vector<std::shared_ptr<sleek::driver::fbo>> fb;
        std::shared_ptr<sleek::driver::material> mt;
        sleek::driver::mesh *mesh;
        Core *core;
};
