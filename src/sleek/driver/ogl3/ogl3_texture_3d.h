#ifndef OGL3_TEXTURE_3D
#define OGL3_TEXTURE_3D

#include "../context.h"
#include "ogl3_texture.h"

namespace sleek
{
    namespace driver
    {
        class texture3d;

        template<bool dsa>
        struct ogl3_texture_3d : public identifier
        {
            ogl3_texture_3d(texture3d *o) noexcept;
            virtual ~ogl3_texture_3d() noexcept;

            virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
            {
                return HIT_TEXTURE;
            }

            virtual void* getHardwareTarget() const noexcept { return (void*)GL_TEXTURE_3D; }
            virtual void* getHardwareLink() const noexcept;

            virtual void bind() noexcept;
            virtual void unbind() noexcept;
            virtual void update() noexcept;

            GLuint gl;
        };
    }
}

#endif
