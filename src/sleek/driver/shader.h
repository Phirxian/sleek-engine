#ifndef SHADER
#define SHADER

#include "texture.h"
#include "identifier.h"
#include "../math/math.h"
#include <vector>
#include <map>

namespace sleek
{
    namespace driver
    {
        enum shader_type
        {
            shd_frag = 1,
            shd_vert = 2,
            shd_geom = 3,
            shd_tesc = 4, // tesselation control
            shd_tese = 5, // tesselation eval
            shd_comp = 6, // compute shader
            shd_count
        };

        static const char* shader_type_name[] =
        {
            nullptr,
            "fragment",
            "vertex",
            "geometrie",
            "tesselation_control",
            "tesselation_eval",
            "compute",
            nullptr
        };

        class material;
        class shader;

        typedef void(*shader_callback)(shader*);

        class shader : public identifier
        {
            public:
                shader() noexcept;
                virtual ~shader() noexcept;

                virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
                {
                    return HIT_SHADER;
                }

                virtual void* getHardwareLink() const noexcept = 0;

                virtual bool compileShader() noexcept = 0;
                virtual void attacheShader(const shader_type, const std::string &prog, const std::string &main) noexcept = 0;
                virtual void detacheShader(const shader_type) noexcept = 0;

                virtual void setVariable(const std::string&, const f32) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const f32*) noexcept = 0;

                virtual void setVariable(const std::string&, const s32) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const s32*) noexcept = 0;

                virtual void setVariable(const std::string&, const u32) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const u32*) noexcept = 0;

                virtual void setVariable(const std::string&, const math::vec2f&) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const math::vec2f*) noexcept = 0;

                virtual void setVariable(const std::string&, const math::vec3f&) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const math::vec3f*) noexcept = 0;

                virtual void setVariable(const std::string&, const math::vec4f&) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const math::vec4f*) noexcept = 0;

                virtual void setVariable(const std::string&, const math::quatf&) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const math::quatf*) noexcept = 0;

                virtual void setVariable(const std::string&, const math::mat4f&) noexcept = 0;
                virtual void setVariable(const std::string&, int count, const math::mat4f*) noexcept = 0;

                virtual void setTexture(const std::string&, identifier*, const s32) noexcept = 0;

                virtual u32 getVariableID(const std::string&) const noexcept = 0;

                virtual void setCallback(const shader_callback) noexcept;
                virtual shader_callback getCallback() const noexcept;

                virtual std::string getShader(shader_type) const noexcept;

                virtual void update() noexcept;
                
                //! compute shader
                virtual void dispatch(const math::vec3i&) noexcept = 0;

                virtual void bind() noexcept = 0;
                virtual void unbind() noexcept = 0;
            public:
                void* user[shader_userdata];
            protected:
                shader_callback callback;
                std::string source[shd_count];
                int compiled;
        };
    }
}

#endif
