#pragma once

#include "Sample.h"
#include "../metaball/Metaball.h"

namespace sample
{
    class Core;
    class MetaballSample : public Sample
    {
        public:
            MetaballSample(Core*) noexcept;
            virtual ~MetaballSample() noexcept;

            bool manage(sleek::device::input*) noexcept override;

            void render() noexcept;
            
        private:
            sleek::f32 distance;
            bool rotation = 0;
            std::shared_ptr<sleek::driver::mesh> tmp;
            
        private:
            Metaball metaball;
            sleek::scene3d::real::Natif *node;
    };
}
