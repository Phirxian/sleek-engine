#include "LinearBlend.h"

namespace sample
{
    LinearBlend::LinearBlend(std::shared_ptr<sleek::driver::mesh> t, weight_definition_callback wdc)
        : Skinning(t, wdc)
    {
        wdc(this);
        
        for(auto &it : handle)
            bones.push_back(glm::mat4());
        
        std::cout << "bone count : "<< parent.size() << std::endl;
    }

    LinearBlend::~LinearBlend()
    {
    }

    void LinearBlend::animate(float time) noexcept
    {
        Skinning::animate(time);

        for(int i = 0; i<bones.size(); ++i)
        {
            bones[i] = parent[i] == -1 ? sleek::math::mat4f() : bones[parent[i]];
            bones[i] = glm::translate(bones[i],  handle[i]);
            bones[i] *= glm::toMat4(sleek::math::quatf(current.rotation[i]));
            bones[i] = glm::scale(bones[i], current.scale[i]);
            bones[i] = glm::translate(bones[i], current.translation[i]-handle[i]);
        }
    }

    sleek::math::mat4f LinearBlend::build_animation_matrix(int i) const noexcept
    {
        sleek::math::vec4f W = weight[i];
        return bones[boneid[i].x] * W.x
             + bones[boneid[i].y] * W.y
             + bones[boneid[i].z] * W.z
             + bones[boneid[i].w] * W.w;
    }
}
