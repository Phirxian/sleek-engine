#include "ogl3_texture.h"
#include <memory.h>
#include <iostream>

namespace sleek
{
    namespace driver
    {
        template<>
        ogl3_texture<false>::ogl3_texture(texture *o) noexcept : identifier(o)
        {
            glGenTextures(1, &gl);
            glBindTexture(GL_TEXTURE_2D, gl);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        template<>
        ogl3_texture<true>::ogl3_texture(texture *o) noexcept : identifier(o)
        {
            glGenTextures(1, &gl);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTextureParameteriEXT(gl, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        template<bool i>
        ogl3_texture<i>::~ogl3_texture() noexcept
        {
            glDeleteTextures(1, &gl);
            int error = glGetError();
            if (error!= GL_NO_ERROR)
                std::cerr << "Error deleting Texture: " << error << std::endl;
        }

        template<bool i>
        void* ogl3_texture<i>::getHardwareLink() const noexcept
        {
            GLuint *tmp = (GLuint*)&gl;
            return tmp;
        }

        template<bool i>
        void ogl3_texture<i>::bind() noexcept
        {
            glBindTexture(GL_TEXTURE_2D, gl);
        }

        template<bool i>
        void ogl3_texture<i>::unbind() noexcept
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        template<>
        void ogl3_texture<false>::update() noexcept
        {
            texture *tmp = static_cast<texture*>(owner);
            //glEnable(GL_TEXTURE_2D);
            //glActiveTexture(GL_TEXTURE0_ARB);

            bind();

            glTexImage2D(
                GL_TEXTURE_2D, 0, ogl3_texture_componantes[tmp->getFormat()],
                tmp->getDimension().x, tmp->getDimension().y, 0,
                ogl3_texture_format[tmp->getFormat()],
                ogl3_texture_type[tmp->getFormat()],
                tmp->getBuffer()
            );
        }

        template<>
        void ogl3_texture<true>::update() noexcept
        {
            texture *tmp = static_cast<texture*>(owner);
            glTextureImage2DEXT(
                gl, GL_TEXTURE_2D, 0, ogl3_texture_componantes[tmp->getFormat()],
                tmp->getDimension().x, tmp->getDimension().y, 0,
                ogl3_texture_format[tmp->getFormat()],
                ogl3_texture_type[tmp->getFormat()],
                tmp->getBuffer()
            );
        }
    }
}
