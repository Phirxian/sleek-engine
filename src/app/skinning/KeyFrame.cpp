#include "KeyFrame.h"
#include "../library/glm/gtc/quaternion.hpp"
#include "../library/glm/gtx/rotate_vector.inl"

namespace sample
{
    void KeyFrame::interpolate(const KeyFrame &a, const KeyFrame &b, float progression)
    {
        rotation.resize(a.rotation.size());
        translation.resize(a.translation.size());
        scale.resize(a.scale.size());
        
        #pragma omp for
        for(int i = 0; i<scale.size(); ++i)
        {
            translation[i] = glm::slerp(a.translation[i], b.translation[i], progression);
            rotation[i] = glm::slerp(a.rotation[i], b.rotation[i], progression);
            scale[i] = glm::slerp(a.scale[i], b.scale[i], progression);
        }
        
        time_stamp = a.time_stamp * progression +
                     b.time_stamp * (1.0-progression);
    }
}
