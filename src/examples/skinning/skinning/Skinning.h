#ifndef __SAMPLE_HARDWARE_SKINNING_MESH__
#define __SAMPLE_HARDWARE_SKINNING_MESH__

#include "../sleek/driver/mesh.h"
#include "../sleek/driver/shader.h"
#include "KeyFrame.h"

namespace sample
{
    class Skinning
    {
        public:
            struct Bone
            {
                // definition
                sleek::s32 &parent;
                sleek::math::vec3f &handle;
                // transformation applied to the bone
                sleek::math::vec3f &rotation;
                sleek::math::vec3f &translation;
                sleek::math::vec3f &scale;
            };
            using animation_callback = void(*)(Skinning*, float time);
            using weight_definition_callback = void(*)(Skinning*);
        public:
            Skinning(std::shared_ptr<sleek::driver::mesh>, weight_definition_callback);
            virtual ~Skinning();

            static void shader_callback(sleek::driver::shader *i) noexcept
            {
                auto *node = static_cast<sleek::scene3d::real::Natif*>(i->user[0]);
                auto *camera = node->getScene()->getCamera();

                i->setVariable("color",      sleek::math::vec4f{1,1,1,1});
                i->setVariable("model",      node->getModelMatrix());
                i->setVariable("view",       camera->getViewMatrix());
                i->setVariable("projection", camera->getProjectionMatrix());

                i->setTexture("base", i->getLinkFromMaterial()->Texture[0], 0);
            };

            inline std::shared_ptr<sleek::driver::mesh> getptr() const noexcept
            {
                return buffer;
            }
            
            inline sleek::driver::mesh* operator *() const noexcept
            {
                return buffer.get();
            }

            Bone getBone(int i) noexcept
            {
                return Bone{parent[i], handle[i], current.rotation[i], current.translation[i], current.scale[i]};
            }
            
            void addBone(sleek::s32 p, const sleek::math::vec3f &h)
            {
                parent.push_back(p);
                handle.push_back(h);
                current.rotation.push_back(sleek::math::vec3f(0,0,0));
                current.translation.push_back(sleek::math::vec3f(0,0,0));
                current.scale.push_back(sleek::math::vec3f(1,1,1));
            }

            virtual sleek::s32 getBoneCount() const noexcept
            {
                return parent.size();
            }

            void setAnimationCallback(animation_callback f) noexcept
            {
                callback = f;
            }

            virtual void getCurrentFrame(std::shared_ptr<sleek::driver::mesh> out) const noexcept;

            virtual void animate(float time) noexcept
            {
                if(callback)
                    callback(this, time);
            }

            virtual sleek::math::mat4f build_animation_matrix(int i) const noexcept = 0;
        public:
            // bones definition
            std::vector<sleek::s32> parent;
            std::vector<sleek::math::vec3f> handle;
            // bones transformations translation/scale/rotation
            KeyFrame current;
            // gpu data associated to each vertices
            std::vector<sleek::math::vec4c> boneid;
            std::vector<sleek::math::vec4f> weight;
        protected:
            std::shared_ptr<sleek::driver::mesh> buffer;
            animation_callback callback;

    };
}

#endif
