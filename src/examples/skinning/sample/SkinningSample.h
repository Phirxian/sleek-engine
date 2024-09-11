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
            bool rotation = 0;

            std::vector<std::shared_ptr<sleek::driver::mesh>> mesh;
            std::vector<std::shared_ptr<sleek::scene3d::real::Natif>> node;

            LinearBlend linear_blend;
            DualQuaternion dual_quat;
            DualQuaternion heart;
    };
}
