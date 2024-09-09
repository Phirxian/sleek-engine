#ifndef ogl3_TEXTURE_2D
#define ogl3_TEXTURE_2D

#include "ogl3.h"
#include "../context.h"

namespace sleek
{
    namespace driver
    {
        static GLuint ogl3_texture_format[] = {
            //! depth
            GL_DEPTH_COMPONENT,

            //! rgb
            #ifdef GL_LUMINANCE
            GL_LUMINANCE,
            GL_LUMINANCE_ALPHA,
            #else
            GL_RED,
            GL_RG,
            #endif
            GL_RGB,
            GL_RGBA,

            //! float

            #ifdef GL_LUMINANCE
            GL_LUMINANCE,
            GL_LUMINANCE_ALPHA,
            #else
            GL_RED,
            GL_RG,
            #endif
            GL_RGB,
            GL_RGBA
        };

        static GLuint ogl3_texture_type[] = {
            //! depth
            GL_UNSIGNED_BYTE,

            //! rgb

            GL_UNSIGNED_BYTE,
            GL_UNSIGNED_BYTE,
            GL_UNSIGNED_BYTE,
            GL_UNSIGNED_BYTE,

            //! float

            GL_FLOAT,
            GL_FLOAT,
            GL_FLOAT,
            GL_FLOAT
        };

        static const unsigned int ogl3_texture_componantes[] = {
            GL_DEPTH_COMPONENT,
            GL_LUMINANCE8_EXT,   GL_RG8,   GL_RGB8,   GL_RGBA8,
            GL_LUMINANCE32F_ARB, GL_RG32F, GL_RGB32F, GL_RGBA32F
        };

        template<bool dsa>
        struct ogl3_texture : public identifier
        {
            ogl3_texture(texture *o) noexcept;
            virtual ~ogl3_texture() noexcept;

            virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
            {
                return HIT_TEXTURE;
            }

            virtual void* getHardwareTarget() const noexcept { return (void*)GL_TEXTURE_2D; }
            virtual void* getHardwareLink() const noexcept;

            virtual void bind() noexcept;
            virtual void unbind() noexcept;
            virtual void update() noexcept;

            GLuint gl;
        };
    }
}

#endif
