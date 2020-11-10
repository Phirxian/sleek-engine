#ifndef MATERIAL
#define MATERIAL

#include "../compile.h"
#include "../define.h"
#include "shader.h"
#include "rtype.h"
#include "context.h"
#include "../math/math.h"

namespace sleek
{
    namespace driver
    {
        class material : public std::enable_shared_from_this<material>
        {
            public:
                material() noexcept : psize(1)
                {
                    scale = math::vec3f(1);

                    fac = rfc_off;
                    ant = ral_off;
                    mode = rmd_polygon;
                    mat = rmt_solid;
                    shd = rsd_smooth;
                    wire = rwf_fill;

                    Texture.reserve(reserved_texture);
                    effect = 0;
                }

                ~material() noexcept
                {
                }

                inline std::shared_ptr<material> getptr() noexcept
                {
                    return shared_from_this();
                }

                inline void setShader(std::shared_ptr<identifier> i) noexcept { effect = i; }

                inline void setWireframe(const u32 i) noexcept { wire = i; }
                inline void setMode(const render_mode i) noexcept { mode = i; }
                inline void setPointSize(const f32 i) noexcept { psize = i; }
                inline void setShadeModel(const u32 i) noexcept { shd = i; }
                inline void setFaceCulling(const u32 i) noexcept { fac = i; }
                inline void setAntialiasing(const u32 i) noexcept { ant = i; }
                inline void setMaterialRender(const u32 i) noexcept { mat = i; }
                inline void setScale(const math::vec3f &i) noexcept { scale = i; }

                /** ***************************************************** **/

                inline math::vec3f getScale() const noexcept { return scale; }
                inline u32 getMaterialRender() const noexcept { return mat; }
                inline u32 getAntialiasing() const noexcept { return ant; }
                inline u32 getFaceCulling() const noexcept { return fac; }
                inline u32 getShadeModel() const noexcept { return shd; }
                inline f32 getPointSize() const noexcept { return psize; }
                inline render_mode getMode() const noexcept { return mode; }
                inline u32 getWireframe() const noexcept { return wire; }

                inline std::shared_ptr<identifier> getShader() const noexcept { return effect; }

                std::vector<identifier*> Texture;
            public:
                render_mode mode;
                f32 psize;
                u32 ant, mat, shd, fac, wire;
                math::vec3f scale;

                std::shared_ptr<identifier> effect;
        };
    }
}

#endif
