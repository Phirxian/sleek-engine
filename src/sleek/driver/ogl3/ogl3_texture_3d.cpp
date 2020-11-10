#include "ogl3_texture_3d.h"
#include "../texture3d.h"
#include <memory.h>
//#include <GL/gl.h>

namespace sleek
{
    namespace driver
    {
        template<>
        ogl3_texture_3d<false>::ogl3_texture_3d(texture3d *o) noexcept : identifier(o)
        {
            glGenTextures(1, &gl);
            glBindTexture(GL_TEXTURE_3D, gl);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        template<>
        ogl3_texture_3d<true>::ogl3_texture_3d(texture3d *o) noexcept : identifier(o)
        {
            glGenTextures(1, &gl);
            glTextureParameteriEXT(gl, GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteriEXT(gl, GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteriEXT(gl, GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTextureParameteriEXT(gl, GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        template<bool dsa>
        ogl3_texture_3d<dsa>::~ogl3_texture_3d() noexcept
        {
            glDeleteTextures(1, &gl);
        }

        template<bool dsa>
        void* ogl3_texture_3d<dsa>::getHardwareLink() const noexcept
        {
            GLuint *tmp = (GLuint*)&gl;
            return tmp;
        }

        template<bool dsa>
        void ogl3_texture_3d<dsa>::bind() noexcept
        {
            glBindTexture(GL_TEXTURE_3D, gl);
        }

        template<bool dsa>
        void ogl3_texture_3d<dsa>::unbind() noexcept
        {
            glBindTexture(GL_TEXTURE_3D, 0);
        }

        template<>
        void ogl3_texture_3d<false>::update() noexcept
        {
            texture3d *tmp = static_cast<texture3d*>(owner);
            glBindTexture(GL_TEXTURE_3D, gl);

//            glTexStorage3D(
//                GL_TEXTURE_3D, 0, tmp->getFormat(),
//                tmp->getDimension().x, tmp->getDimension().y, tmp->getDimension().z
//            );

            glTexImage3D(
                GL_TEXTURE_3D, 0, tmp->getFormat(),
                tmp->getDimension().x, tmp->getDimension().y, tmp->getDimension().z, 0,
                ogl3_texture_format[tmp->getFormat()-1],
                ogl3_texture_type[tmp->getFormat()-1],
                nullptr
            );

            glTexSubImage3D(
                GL_TEXTURE_3D, 0, 0, 0, 0,
                tmp->getDimension().x, tmp->getDimension().y, tmp->getDimension().z,
                ogl3_texture_format[tmp->getFormat()-1],
                ogl3_texture_type[tmp->getFormat()-1],
                tmp->getBuffer()
            );
        }

        template<>
        void ogl3_texture_3d<true>::update() noexcept
        {
            texture3d *tmp = static_cast<texture3d*>(owner);

//            glTextureStorage3DEXT(
//                gl, GL_TEXTURE_3D, 0, tmp->getPitch(),
//                tmp->getDimension().x, tmp->getDimension().y, tmp->getDimension().z
//            );

            glTextureImage3DEXT(
                gl, GL_TEXTURE_3D, 0, tmp->getPitch(),
                tmp->getDimension().x, tmp->getDimension().y, tmp->getDimension().z, 0,
                ogl3_texture_format[tmp->getFormat()-1],
                ogl3_texture_type[tmp->getFormat()-1],
                nullptr
            );

            glTextureSubImage3DEXT(
                gl, GL_TEXTURE_3D, 0, 0, 0, 0,
                tmp->getDimension().x, tmp->getDimension().y, tmp->getDimension().z,
                ogl3_texture_format[tmp->getFormat()-1],
                ogl3_texture_type[tmp->getFormat()-1],
                tmp->getBuffer()
            );
        }
    }
}
