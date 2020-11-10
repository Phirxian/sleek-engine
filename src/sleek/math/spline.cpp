#include "spline.h"

#include <algorithm>
#include <cstring>

namespace sleek
{
    namespace math
    {
        spline::spline(unsigned int size, unsigned int k) noexcept
            : _k(k), _knots(_k + size)
        {
            const int n = size - 1;
            _knots.resize(k+n+1);

            float step = 1.f / float(n-_k+2);
            for (auto i = 0u; i < _knots.size(); ++i)
                _knots[i] = i*step - step*(_k-1);
        }

        vec3f spline::eval(float u, const arv::array_view<vec3f>& point, unsigned int k, int off) const noexcept
        {
            if(point.size() < k)
                return point[0];

            unsigned int dec = 0;
            for(; u > _knots[dec+k+off]; dec++);

            vec3f out[k];
            std::memcpy(out, point.data()+dec, k*sizeof(vec3f));

            const float *node_ptr = _knots.data() + dec+off+1;

            // solving without evil recursiv function

            for(k--; k != 0; k--)
            {
                for(auto i = 0u; i <= k; ++i)
                {
                    const float n0 = node_ptr[i+k];
                    const float n1 = node_ptr[i];
                    const float f0 = (n0 - u) / (n0 - n1);
                    const float f1 = (u - n1) / (n0 - n1);
                    out[i] = out[i] * f0 + out[i+1] * f1;
                }
                node_ptr++;
            }

            return out[0];
        }
    }
}
