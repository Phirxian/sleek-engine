#include "ogl3_texture_fbo.h"
#include "ogl3_texture.h"
#include <memory.h>
//#include <GL/gl.h>

namespace sleek
{
    namespace driver
    {
        template<>
        ogl3_texture_fbo<false>::ogl3_texture_fbo(fbo *o, math::vec2i size, u32 a, u32 fmt) noexcept
            : identifier(o), attachment(a), framebuffer(*(GLuint*)o->getHardwareLink()), format(fmt)
        {
            glGenTextures(1, &gl);
            glBindTexture(GL_TEXTURE_2D, gl);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(
                GL_TEXTURE_2D, 0,
                ogl3_texture_componantes[fmt],
                size.x, size.y, 0,
                ogl3_texture_format[fmt],
                ogl3_texture_type[fmt], 0
            );
        }

        template<>
        ogl3_texture_fbo<true>::ogl3_texture_fbo(fbo *o, math::vec2i size, u32 a, u32 fmt) noexcept
            : identifier(o), attachment(a), framebuffer(*(GLuint*)o->getHardwareLink()), format(fmt)
        {
            glGenTextures(1, &gl);

            glTextureParameteriEXT(gl, GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
//            glTextureParameteriEXT(gl, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//            glTextureParameteriEXT(gl, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTextureImage2DEXT(
                gl, GL_TEXTURE_2D, 0,
                ogl3_texture_componantes[fmt],
                size.x, size.y, 0,
                ogl3_texture_format[fmt],
                ogl3_texture_type[fmt], 0
            );
        }

        template<bool i>
        ogl3_texture_fbo<i>::~ogl3_texture_fbo() noexcept
        {
            glDeleteTextures(1, &gl);
        }

        template<bool i>
        void* ogl3_texture_fbo<i>::getHardwareLink() const noexcept
        {
            GLuint *tmp = (GLuint*)&gl;
            return tmp;
        }

//! TODO recheck why I do this trick
//        template <bool dsa>
//        void ogl3_texture_fbo<dsa>::resize(const math::vec2i &size) noexcept
//        {
//            this->~ogl3_texture_fbo<dsa>();
//            new (this) ogl3_texture_fbo<dsa>((fbo*)owner, size, attachment, format);
//        }


        template <>
        void ogl3_texture_fbo<false>::resize(const math::vec2i &size) noexcept
        {
            glBindTexture(GL_TEXTURE_2D, gl);
            glTexImage2D(
                GL_TEXTURE_2D, 0,
                ogl3_texture_componantes[format],
                size.x, size.y, 0,
                ogl3_texture_format[format],
                ogl3_texture_type[format], 0
            );
        }

        template <>
        void ogl3_texture_fbo<true>::resize(const math::vec2i &size) noexcept
        {
            glTextureImage2DEXT(
                gl, GL_TEXTURE_2D, 0,
                ogl3_texture_componantes[format],
                size.x, size.y, 0,
                ogl3_texture_format[format],
                ogl3_texture_type[format], 0
            );
        }

        template<bool i>
        void ogl3_texture_fbo<i>::bind() noexcept
        {
            glBindTexture(GL_TEXTURE_2D, gl);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        template<bool i>
        void ogl3_texture_fbo<i>::unbind() noexcept
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        template<>
        void ogl3_texture_fbo<false>::update() noexcept
        {
            glFramebufferTexture2DEXT(
                GL_FRAMEBUFFER_EXT, attachment,
                GL_TEXTURE_2D, gl, 0
            );
        }

        template<>
        void ogl3_texture_fbo<true>::update() noexcept
        {
            glNamedFramebufferTexture2DEXT(
                framebuffer, attachment,
                GL_TEXTURE_2D, gl, 0
            );
        }
    }
}
