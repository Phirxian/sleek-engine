#pragma once

#include "Sample.h"
#include "../skinning/LinearBlend.h"
#include "../skinning/DualQuaternion.h"

namespace sample
{
    class Core;
    class SkinningSample : public Sample
    {
        public:
            SkinningSample(Core*) noexcept;
            virtual ~SkinningSample() noexcept;
            
            bool manage(sleek::device::input*) noexcept override;

            void render() noexcept;
            
        private:
            sleek::f32 distance;
            bool rotation = 0;
            float pitch = 0.f;
            float rot = 0.f;

            std::vector<std::shared_ptr<sleek::driver::mesh>> mesh;
            std::vector<sleek::scene3d::real::Natif*> node;

            LinearBlend linear_blend;
            DualQuaternion dual_quat;
            DualQuaternion heart;
    };
}
