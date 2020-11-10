#ifndef FRUSTUM
#define FRUSTUM

#include "../../math/math.h"

namespace sleek
{
    namespace scene3d
    {
        namespace camera
        {
            enum FrustumSide { FSD_RIGHT = 0, FSD_LEFT = 1, FSD_BOTTOM = 2, FSD_TOP = 3, FSD_BACK = 4, FSD_FRONT = 5 };
            enum FrustumPlane { FPL_A = 0, FPL_B = 1, FPL_C = 2, FPL_D = 3 };

            struct Frustum
            {
                void calculate() noexcept;
                bool point(const math::vec3f&, const float tolerance) noexcept;
                bool sphere(const math::vec3f&, float r) noexcept;
                float m_Frustum[6][4];
            };

            void NormalizePlane(float frustum[6][4], int side) noexcept;
        }
    }
}

#endif
