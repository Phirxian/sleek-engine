#ifndef OGL3_VAO
#define OGL3_VAO

#include "ogl3.h"
#include "../context.h"

namespace sleek
{
    namespace driver
    {
        template<bool dsa>
        struct ogl3_vao_identifer : public identifier
        {
            ogl3_vao_identifer(mesh *o, VAO_ALIGNMENT, VAO_ALIGNMENT) noexcept;
            virtual ~ogl3_vao_identifer() noexcept;

            virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
            {
                return HIT_VAO;
            }

            virtual void* getHardwareTarget() const noexcept { return (void*)GL_ARRAY_BUFFER; }
            virtual void* getHardwareLink() const noexcept;

            virtual void bind() noexcept;
            virtual void unbind() noexcept;
            virtual void update() noexcept;

            VAO_ALIGNMENT vert;
            VAO_ALIGNMENT element;

            GLuint vbo;
            GLuint ebo;
            GLuint gl;

            std::vector<GLuint> subdata;

            GLuint vbo_allocated;
            GLuint ebo_allocated;
        };
    }
}

#endif
