#ifndef OGL3_SHADER
#define OGL3_SHADER

#include "ogl3.h"
#include "../shader.h"

namespace sleek
{
    namespace driver
    {
        template<bool dsa>
        class ogl3_shader : public shader
        {
            public:
                ogl3_shader() noexcept;
                virtual ~ogl3_shader() noexcept;

                virtual void* getHardwareTarget() const noexcept { return (void*)GL_FRAGMENT_SHADER; }
                virtual void* getHardwareLink() const noexcept;

                virtual bool compileShader() noexcept;
                virtual void attacheShader(const shader_type, const std::string &prog, const std::string &main) noexcept;
                virtual void detacheShader(const shader_type) noexcept;

                virtual void setVariable(const std::string&, const f32) noexcept;
                virtual void setVariable(const std::string&, const s32) noexcept;
                virtual void setVariable(const std::string&, const u32) noexcept;
                virtual void setVariable(const std::string&, const math::vec2f&) noexcept;
                virtual void setVariable(const std::string&, const math::vec3f&) noexcept;
                virtual void setVariable(const std::string&, const math::vec4f&) noexcept;
                virtual void setVariable(const std::string&, const math::quatf&) noexcept;
                virtual void setTexture(const std::string&, identifier*, const s32) noexcept;

                virtual void setVariable(const std::string&, int count, const f32*) noexcept;
                virtual void setVariable(const std::string&, int count, const s32*) noexcept;
                virtual void setVariable(const std::string&, int count, const u32*) noexcept;
                virtual void setVariable(const std::string&, int count, const math::vec2f*) noexcept;
                virtual void setVariable(const std::string&, int count, const math::vec3f*) noexcept;
                virtual void setVariable(const std::string&, int count, const math::vec4f*) noexcept;
                virtual void setVariable(const std::string&, int count, const math::quatf*) noexcept;

                virtual void setVariable(const std::string&, const math::mat4f&) noexcept;
                virtual void setVariable(const std::string&, int count, const math::mat4f*) noexcept;

                virtual u32 getVariableID(const std::string&) const noexcept;

                virtual void dispatch(const math::vec3i&) noexcept;
                
                virtual void bind() noexcept;
                virtual void unbind() noexcept;
            protected:
                virtual bool LinkAndValidate() noexcept;
            protected:
                GLuint shaders[shd_count], prog;
                unsigned enabled;
        };
    }
}

#endif
