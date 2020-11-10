#ifndef MATH_FUNCTION
#define MATH_FUNCTION

#include <memory>

#include "../library/glm/glm.hpp"
#include "../library/glm/detail/func_geometric.hpp"
#include "../library/glm/gtx/transform.hpp"
#include "../library/glm/gtx/quaternion.hpp"

namespace sleek
{
    namespace math
    {
        constexpr float PI = 3.14159265359;

        template<typename T>
        inline T min(T a, T b)
        {
            return a < b ? a : b;
        }

        template<typename T, typename... Ts>
        inline T min(T a, T b, Ts&&... vs)
        {
            return a < b ?
                min(a, std::forward<Ts>(vs)...) :
                min(b, std::forward<Ts>(vs)...);
        }

        template<typename T>
        inline T max(T a, T b)
        {
            return a > b ? a : b;
        }

        template<typename T, typename... Ts>
        inline T max(T a, T b, Ts&&... vs)
        {
            return a > b ?
                max(a, std::forward<Ts>(vs)...) :
                max(b, std::forward<Ts>(vs)...);
        }

        template<typename T>
        inline T clamp(T value, T _min, T _max)
        {
            if(value < _min)
                return _min;

            if(value > _max)
                return _max;

            return value;
        }

        inline f32 reciprocal(const f32 f)
        {
            //! TODO
//            f32 rec;
//            __asm rcpss xmm0, f               // xmm0 = rcpss(f)
//            __asm movss xmm1, f               // xmm1 = f
//            __asm mulss xmm1, xmm0            // xmm1 = f * rcpss(f)
//            __asm mulss xmm1, xmm0            // xmm2 = f * rcpss(f) * rcpss(f)
//            __asm addss xmm0, xmm0            // xmm0 = 2 * rcpss(f)
//            __asm subss xmm0, xmm1            // xmm0 = 2 * rcpss(f)
//                                              //        - f * rcpss(f) * rcpss(f)
//            __asm movss rec, xmm0             // return xmm0
//            return rec;
            return 1.f / f;
        }
    }
}

#endif
