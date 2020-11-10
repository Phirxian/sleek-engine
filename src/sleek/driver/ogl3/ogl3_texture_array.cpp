#include "ogl3_texture_array.h"
#include "../texture_array.h"
#include <memory.h>
//#include <GL/gl.h>

namespace sleek
{
    namespace driver
    {
        template<>
        ogl3_texture_array<false>::ogl3_texture_array(texture_array *o) noexcept : identifier(o)
        {
            glGenTextures(1, &gl);
            glBindTexture(GL_TEXTURE_2D_ARRAY, gl);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        template<>
        ogl3_texture_array<true>::ogl3_texture_array(texture_array *o) noexcept : identifier(o)
        {
            glGenTextures(1, &gl);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        template<bool dsa>
        ogl3_texture_array<dsa>::~ogl3_texture_array() noexcept
        {
            glDeleteTextures(1, &gl);
        }

        template<bool dsa>
        void* ogl3_texture_array<dsa>::getHardwareLink() const noexcept
        {
            GLuint *tmp = (GLuint*)&gl;
            return tmp;
        }

        template<bool dsa>
        void ogl3_texture_array<dsa>::bind() noexcept
        {
            glBindTexture(GL_TEXTURE_2D_ARRAY, gl);
        }

        template<bool dsa>
        void ogl3_texture_array<dsa>::unbind() noexcept
        {
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        }

        template<>
        void ogl3_texture_array<false>::update() noexcept
        {
            texture_array *tmp = static_cast<texture_array*>(owner);
            glBindTexture(GL_TEXTURE_2D_ARRAY, gl);

//            glTexStorage3D(
//                GL_TEXTURE_2D_ARRAY, 0, tmp->getFormat(),
//                tmp->getDimension().x, tmp->getDimension().y, tmp->count()
//            );

            glTexImage3D(
                GL_TEXTURE_2D_ARRAY, 0, tmp->getFormat(),
                tmp->getDimension().x, tmp->getDimension().y, tmp->count(),
                0, ogl3_texture_format[tmp->getFormat()], GL_UNSIGNED_BYTE, nullptr
            );

            for(int i = 0; i < tmp->count(); i++)
            {
                glTexSubImage3D(
                    GL_TEXTURE_2D_ARRAY, 0, 0, 0,
                    i, tmp->getDimension().x, tmp->getDimension().y, 1,
                    ogl3_texture_format[tmp->getFormat()], GL_UNSIGNED_BYTE,
                    tmp->getBuffer(i)
                );
            }
        }

        template<>
        void ogl3_texture_array<true>::update() noexcept
        {
            texture_array *tmp = static_cast<texture_array*>(owner);

//            glTextureStorage3DEXT(
//                gl, GL_TEXTURE_2D_ARRAY, 0, tmp->getFormat(),
//                tmp->getDimension().x, tmp->getDimension().y, tmp->count()
//            );

            glTextureImage3DEXT(
                gl, GL_TEXTURE_2D_ARRAY, 0, tmp->getFormat(),
                tmp->getDimension().x, tmp->getDimension().y, tmp->count(),
                0, ogl3_texture_format[tmp->getFormat()], GL_UNSIGNED_BYTE, nullptr
            );

            for(int i = 0; i < tmp->count(); i++)
            {
                glTextureSubImage3DEXT(
                    gl, GL_TEXTURE_2D_ARRAY, 0, 0, 0,
                    i, tmp->getDimension().x, tmp->getDimension().y, 1,
                    ogl3_texture_format[tmp->getFormat()], GL_UNSIGNED_BYTE,
                    tmp->getBuffer(i)
                );
            }
        }
    }
}
