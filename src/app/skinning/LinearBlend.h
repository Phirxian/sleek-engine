#ifndef __SAMPLE_LINEAR_BLEND_MESH__
#define __SAMPLE_LINEAR_BLEND_MESH__

#include "Skinning.h"

namespace sample
{
    class LinearBlend : public Skinning
    {
        friend void callback(sleek::driver::shader *i) noexcept;
        public:
            LinearBlend(std::shared_ptr<sleek::driver::mesh>, Skinning::weight_definition_callback);
            virtual ~LinearBlend();

            static void shader_callback(sleek::driver::shader *i) noexcept
            {
                auto *mesh = static_cast<LinearBlend*>(i->user[1]);

                i->setVariable("bones", mesh->bones.size(), mesh->bones.data());

                Skinning::shader_callback(i);
            };

            virtual void animate(float time) noexcept;
        protected:
            virtual sleek::math::mat4f build_animation_matrix(int i) const noexcept;
            std::vector<sleek::math::mat4f> bones;
    };
}

#endif
