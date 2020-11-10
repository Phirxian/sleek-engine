#ifndef SPLINES_HPP
#define SPLINES_HPP

#include "math.h"
#include "../library/array_view.h"
#include <vector>

namespace sleek
{
    namespace math
    {
        class spline
        {
            public:
                spline(unsigned int size, unsigned int k = 2u) noexcept;

                vec3f eval_f(float u, const arv::array_view<math::vec3f>& point) const noexcept
                {
                    u = std::max(std::min(u, 1.f), 0.f);
                    return eval(u, point, _k);
                }

            protected:
                vec3f eval(float u, const arv::array_view<vec3f>& point, unsigned int k, int off = 0) const noexcept;

            private:
                unsigned int _k;
                std::vector<float> _knots;
        };
    }
}

#endif
