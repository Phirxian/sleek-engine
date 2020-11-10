#ifndef OGL3_TEXTURE_FBO
#define OGL3_TEXTURE_FBO

#include "ogl3.h"
#include "../context.h"

namespace sleek
{
    namespace driver
    {
        template<bool dsa>
        struct ogl3_texture_fbo : public identifier
        {
            ogl3_texture_fbo(fbo*, math::vec2i size, u32, u32) noexcept;
            virtual ~ogl3_texture_fbo() noexcept;

            virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
            {
                return HIT_TEXTURE;
            }

            virtual void* getHardwareTarget() const noexcept { return (void*)GL_TEXTURE_2D; }
            virtual void* getHardwareLink() const noexcept;

            virtual void resize(const math::vec2i &) noexcept;

            virtual void bind() noexcept;
            virtual void unbind() noexcept;
            virtual void update() noexcept;

            GLuint attachment;
            GLuint framebuffer;
            GLuint format;
            GLuint gl;
        };
    }
}

#endif
