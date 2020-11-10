#pragma once
#define GLM_SWIZZLE_XYZW

#include "../library/glm/vec2.hpp"
#include "../library/glm/vec3.hpp"
#include "../library/glm/vec4.hpp"
#include "../library/glm/mat4x4.hpp"
#include "../library/glm/mat3x3.hpp"
#include "../library/glm/gtc/quaternion.hpp"
#include "../define.h"

namespace sleek
{
    namespace math
    {
        using namespace glm;

        template<typename T>
        using vec2  = glm::tvec2<T, GLM_Precision>;
        using vec2f = vec2<f32>;
        using vec2i = vec2<s32>;
        using vec2u = vec2<u32>;
        using vec2c = vec2<u8>;

        template<typename T>
        using vec3  = glm::tvec3<T, GLM_Precision>;
        using vec3f = vec3<f32>;
        using vec3i = vec3<s32>;
        using vec3u = vec3<u32>;
        using vec3c = vec3<u8>;

        template<typename T>
        using vec4  = glm::tvec4<T, GLM_Precision>;
        using vec4f = vec4<f32>;
        using vec4i = vec4<s32>;
        using vec4u = vec4<u32>;
        using vec4c = vec4<u8>;

        template<typename T>
        using mat3 = glm::tmat3x3<T, GLM_Precision>;
        using mat3f = mat3<f32>;
        using mat3i = mat3<s32>;
        using mat3u = mat3<u32>;

        template<typename T>
        using mat4 = glm::tmat4x4<T, GLM_Precision>;
        using mat4f = mat4<f32>;
        using mat4i = mat4<s32>;
        using mat4u = mat4<u32>;

        template<typename T>
        using quat  = glm::tquat<T, GLM_Precision>;
        using quatf = quat<f32>;
        using quati = quat<s32>;
        using quatu = quat<u32>;
    }
}
