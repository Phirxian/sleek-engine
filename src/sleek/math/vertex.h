#ifndef VERTEX
#define VERTEX

#include "pixel.h"
#include "aabbox.h"

namespace sleek
{
    namespace math
    {
        struct alignas(512) vertex
        {
            vec3f Pos;
            vec3f Normal;
            vec2f Coord;
            pixel Color;
        };

        struct alignas(256) bones
        {
            vec4f Weight;
            vec4i BoneId;
        };
    }
}

#endif
