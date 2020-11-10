#ifndef __SAMPLE_SKINNING_KEYFRAME__
#define __SAMPLE_SKINNING_KEYFRAME__

#include "../sleek/start.h"
#include <vector>

namespace sample
{
    struct KeyFrame
    {
        //! data of this class is computed from the interpolation of this two other classes
        void interpolate(const KeyFrame&, const KeyFrame&, float progression);
        // transformation applied to each bones
        std::vector<sleek::math::vec3f> rotation;
        std::vector<sleek::math::vec3f> translation;
        std::vector<sleek::math::vec3f> scale;
        // time reference
        float time_stamp;
    };
}

#endif
