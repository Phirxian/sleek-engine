#ifndef ogl3_TEXTURE_2D_ARRAY
#define ogl3_TEXTURE_2D_ARRAY

#include "../context.h"
#include "ogl3_texture.h"

namespace sleek
{
    namespace driver
    {
        class texture_array;

        template<bool dsa>
        struct ogl3_texture_array : public identifier
        {
            ogl3_texture_array(texture_array *o) noexcept;
            virtual ~ogl3_texture_array() noexcept;

            virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
            {
                return HIT_TEXTURE;
            }

            virtual void* getHardwareTarget() const noexcept { return (void*)GL_TEXTURE_2D_ARRAY; }
            virtual void* getHardwareLink() const noexcept;

            virtual void bind() noexcept;
            virtual void unbind() noexcept;
            virtual void update() noexcept;

            GLuint gl;
        };
    }
}

#endif
