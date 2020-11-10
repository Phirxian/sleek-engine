#ifndef OGL3_FBO
#define OGL3_FBO

#include "ogl3.h"
#include "../fbo.h"

namespace sleek
{
    namespace driver
    {
        template<bool dsa>
        class ogl3_fbo : public fbo
        {
            public:
                ogl3_fbo(const math::vec2i &size, const std::vector<TextureFormat> &, bool depthbuffer = true) noexcept;
                virtual ~ogl3_fbo() noexcept;

                virtual void* getHardwareTarget() const noexcept { return (void*)GL_FRAMEBUFFER; }
                virtual void* getHardwareLink() const noexcept;
                virtual void resize(const math::vec2i &size) noexcept;

                virtual void update() noexcept;
                virtual void bind() noexcept;
                virtual void bind(int i) noexcept;
                virtual void unbind() noexcept;

                virtual bool check(GLuint);
            protected:
                GLenum status;
                GLuint framebuffer;
                GLuint depthbuffer;
            private:
        };
    }
}

#endif
