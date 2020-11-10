#include "frustum.h"
#include <math.h>

namespace sleek
{
    namespace scene3d
    {
        namespace camera
        {
            void NormalizePlane(float frustum[6][4], const int side) noexcept
            {
                float magnitude = (float)sqrt( frustum[side][FPL_A] * frustum[side][FPL_A] + frustum[side][FPL_B] * frustum[side][FPL_B] + frustum[side][FPL_C] * frustum[side][FPL_C] );
                frustum[side][FPL_A] /= magnitude; frustum[side][FPL_B] /= magnitude;
                frustum[side][FPL_C] /= magnitude; frustum[side][FPL_D] /= magnitude;
            }

            void Frustum::calculate() noexcept
            {
                float   proj[16];								// This will hold our projection matrix
                float   modl[16];								// This will hold our modelview matrix
                float   clip[16];								// This will hold the clipping planes

                /**
                 * TODO add driver get matrix
                 */

//                glGetFloatv( GL_PROJECTION_MATRIX, proj );
//                glGetFloatv( GL_MODELVIEW_MATRIX, modl );

                clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
                clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
                clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
                clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

                clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
                clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
                clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
                clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

                clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
                clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
                clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
                clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

                clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
                clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
                clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
                clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

                m_Frustum[FSD_RIGHT][FPL_A] = clip[ 3] - clip[ 0];
                m_Frustum[FSD_RIGHT][FPL_B] = clip[ 7] - clip[ 4];
                m_Frustum[FSD_RIGHT][FPL_C] = clip[11] - clip[ 8];
                m_Frustum[FSD_RIGHT][FPL_D] = clip[15] - clip[12];

                NormalizePlane(m_Frustum, FSD_RIGHT);

                m_Frustum[FSD_LEFT][FPL_A] = clip[ 3] + clip[ 0];
                m_Frustum[FSD_LEFT][FPL_B] = clip[ 7] + clip[ 4];
                m_Frustum[FSD_LEFT][FPL_C] = clip[11] + clip[ 8];
                m_Frustum[FSD_LEFT][FPL_D] = clip[15] + clip[12];

                NormalizePlane(m_Frustum, FSD_LEFT);

                m_Frustum[FSD_BOTTOM][FPL_A] = clip[ 3] + clip[ 1];
                m_Frustum[FSD_BOTTOM][FPL_B] = clip[ 7] + clip[ 5];
                m_Frustum[FSD_BOTTOM][FPL_C] = clip[11] + clip[ 9];
                m_Frustum[FSD_BOTTOM][FPL_D] = clip[15] + clip[13];

                NormalizePlane(m_Frustum, FSD_BOTTOM);

                m_Frustum[FSD_TOP][FPL_A] = clip[ 3] - clip[ 1];
                m_Frustum[FSD_TOP][FPL_B] = clip[ 7] - clip[ 5];
                m_Frustum[FSD_TOP][FPL_C] = clip[11] - clip[ 9];
                m_Frustum[FSD_TOP][FPL_D] = clip[15] - clip[13];

                NormalizePlane(m_Frustum, FSD_TOP);

                m_Frustum[FSD_BACK][FPL_A] = clip[ 3] - clip[ 2];
                m_Frustum[FSD_BACK][FPL_B] = clip[ 7] - clip[ 6];
                m_Frustum[FSD_BACK][FPL_C] = clip[11] - clip[10];
                m_Frustum[FSD_BACK][FPL_D] = clip[15] - clip[14];

                NormalizePlane(m_Frustum, FSD_BACK);

                m_Frustum[FSD_FRONT][FPL_A] = clip[ 3] + clip[ 2];
                m_Frustum[FSD_FRONT][FPL_B] = clip[ 7] + clip[ 6];
                m_Frustum[FSD_FRONT][FPL_C] = clip[11] + clip[10];
                m_Frustum[FSD_FRONT][FPL_D] = clip[15] + clip[14];

                NormalizePlane(m_Frustum, FSD_FRONT);
            }

            bool Frustum::point(const math::vec3f &i, const float tolerance) noexcept
            {
                if(m_Frustum[0][FPL_A] * i.x + m_Frustum[0][FPL_B] * i.y + m_Frustum[0][FPL_C] * i.z + m_Frustum[0][FPL_D] < -tolerance) return false;
                if(m_Frustum[1][FPL_A] * i.x + m_Frustum[1][FPL_B] * i.y + m_Frustum[1][FPL_C] * i.z + m_Frustum[1][FPL_D] < -tolerance) return false;
                if(m_Frustum[2][FPL_A] * i.x + m_Frustum[2][FPL_B] * i.y + m_Frustum[2][FPL_C] * i.z + m_Frustum[2][FPL_D] < -tolerance) return false;
                if(m_Frustum[3][FPL_A] * i.x + m_Frustum[3][FPL_B] * i.y + m_Frustum[3][FPL_C] * i.z + m_Frustum[3][FPL_D] < -tolerance) return false;
                if(m_Frustum[4][FPL_A] * i.x + m_Frustum[4][FPL_B] * i.y + m_Frustum[4][FPL_C] * i.z + m_Frustum[4][FPL_D] < -tolerance) return false;
                if(m_Frustum[5][FPL_A] * i.x + m_Frustum[5][FPL_B] * i.y + m_Frustum[5][FPL_C] * i.z + m_Frustum[5][FPL_D] < -tolerance) return false;
                return true;
            }

            bool Frustum::sphere(const math::vec3f &i, float r) noexcept
            {
                r *= 1.5f;
                if(m_Frustum[0][FPL_A] * i.x + m_Frustum[0][FPL_B] * i.y + m_Frustum[0][FPL_C] * i.z + m_Frustum[0][FPL_D] <= -r) return false;
                if(m_Frustum[1][FPL_A] * i.x + m_Frustum[1][FPL_B] * i.y + m_Frustum[1][FPL_C] * i.z + m_Frustum[1][FPL_D] <= -r) return false;
                if(m_Frustum[2][FPL_A] * i.x + m_Frustum[2][FPL_B] * i.y + m_Frustum[2][FPL_C] * i.z + m_Frustum[2][FPL_D] <= -r) return false;
                if(m_Frustum[3][FPL_A] * i.x + m_Frustum[3][FPL_B] * i.y + m_Frustum[3][FPL_C] * i.z + m_Frustum[3][FPL_D] <= -r) return false;
                if(m_Frustum[4][FPL_A] * i.x + m_Frustum[4][FPL_B] * i.y + m_Frustum[4][FPL_C] * i.z + m_Frustum[4][FPL_D] <= -r) return false;
                if(m_Frustum[5][FPL_A] * i.x + m_Frustum[5][FPL_B] * i.y + m_Frustum[5][FPL_C] * i.z + m_Frustum[5][FPL_D] <= -r) return false;
                return true;
            }

        }
    }
}
