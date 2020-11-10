#include "DualQuaternion.h"

using namespace sleek::math;

namespace sample
{
    DualQuaternion::DualQuaternion(std::shared_ptr<sleek::driver::mesh> t, weight_definition_callback wdc)
        : Skinning(t, wdc)
    {
        wdc(this);
        
        for(auto &it : handle)
        {
            bones_position.push_back({});
            bones_rotation.push_back({});
        }
        
        std::cout << "bone count : "<< parent.size() << std::endl;
    }

    DualQuaternion::~DualQuaternion()
    {
    }

    void DualQuaternion::animate(float time) noexcept
    {
        Skinning::animate(time);

        for(int i = 0; i<parent.size(); ++i)
        {
            sleek::s32 p = parent[i];

            bones_position[i] = vec3f();
            bones_rotation[i] = quatf();

            if(p != -1)
            {
                mat4f transform;

                transform = glm::translate(transform, handle[p]);
                transform = glm::scale(transform, current.scale[i]);
                transform *= glm::toMat4(quatf(current.rotation[p]));
                transform = glm::translate(transform, current.translation[p]-handle[p]);

                auto tmp = transform*vec4f(bones_position[i], 1);

                bones_position[i] = vec3f(tmp.x, tmp.y, tmp.z);
                bones_rotation[i] = glm::inverse(quatf(-current.rotation[p]));
            }

            bones_position[i] += current.translation[i];
            bones_rotation[i] *= quatf(current.rotation[i]);
        }
    }

    mat4f DualQuaternion::build_animation_matrix(int i) const noexcept
    {
        quatf R = quatf(0.0, 0.0, 0.0, 0.0);

        #define weighted_interpolation(node, W)              \
            node[boneid[i].x]*W.x + node[boneid[i].y]*W.y +  \
            node[boneid[i].z]*W.z + node[boneid[i].w]*W.w

        for(int k = 0; k < 4; k++)
        {
            auto Q = bones_rotation[boneid[i][k]];
            auto dot = glm::dot(Q, R);
            float sign = 1.0 - 2.0*float(dot <= 0.0);
            R += Q * weight[i][k] * sign;
        }

        vec3f T = weighted_interpolation(bones_position, weight[i]);
        vec3f H = weighted_interpolation(handle, weight[i]);
        vec3f S = weighted_interpolation(current.scale, weight[i]);

        #undef weighted_interpolation

        float magnitude = glm::length(R);
        R /= magnitude;
        H /= magnitude;
        T /= magnitude;

        mat4f transform = glm::toMat4(R);
              transform[3] = glm::vec4(T+H, 1.0);
              transform = glm::scale(transform, S);
              transform = glm::translate(transform, -H);

        return transform;
    }
}
