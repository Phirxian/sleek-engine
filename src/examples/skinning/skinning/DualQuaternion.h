#ifndef __SAMPLE_DUAL_QUATERNION_MESH__
#define __SAMPLE_DUAL_QUATERNION_MESH__

#include "Skinning.h"

namespace sample
{
    class DualQuaternion : public Skinning
    {
        friend void callback(sleek::driver::shader *i) noexcept;
        public:
            DualQuaternion(std::shared_ptr<sleek::driver::mesh>, Skinning::weight_definition_callback);
            virtual ~DualQuaternion();

            static void shader_callback(sleek::driver::shader *i) noexcept
            {
                auto *mesh = static_cast<DualQuaternion*>(i->user[1]);

                i->setVariable("handle",     mesh->handle.size(), mesh->handle.data());
                i->setVariable("position",   mesh->bones_position.size(), mesh->bones_position.data());
                i->setVariable("rotation",   mesh->bones_rotation.size(), mesh->bones_rotation.data());
                i->setVariable("scale",      mesh->current.scale.size(),  mesh->current.scale.data());

                Skinning::shader_callback(i);
            };

            virtual void animate(float time) noexcept;
        protected:
            virtual sleek::math::mat4f build_animation_matrix(int i) const noexcept;
            std::vector<sleek::math::vec3f> bones_position;
            std::vector<sleek::math::quatf> bones_rotation;
    };
}

#endif
