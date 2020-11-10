#ifndef RENDER_TYPE_FOR_MATERIAL
#define RENDER_TYPE_FOR_MATERIAL

#include "rtype.h"

namespace sleek
{
    namespace driver
    {
        enum render_mode
        {
            rmd_point,
            rmd_line,
            rmd_line_loop,
            rmd_polygon,
            rmd_quad,
            rmd_count
        };
        enum render_shade
        {
            rsd_flat   = 0x001,
            rsd_smooth = 0x002
        };
        enum render_wireframe
        {
            rwf_fill,
            rwf_wireframe
        };
        enum render_material
        {
            rmt_solid        = 0x001,
            rmt_add          = 0x002,
            rmt_sub          = 0x004,
            rmt_lighting     = 0x008,
            rmt_fog          = 0x016
        };
        enum render_antialiasing
        {
            ral_off      = 0x001,
            ral_line     = 0x002,
            ral_polygone = 0x004
        };
        enum render_face_culling
        {
            rfc_off   = 0x000,
            rfc_front = 0x001,
            rfc_back  = 0x002
        };
    }
}

#endif
