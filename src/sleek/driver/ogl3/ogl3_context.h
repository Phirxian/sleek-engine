#ifndef __OGL3_CONTEXT_HEADER__
#define __OGL3_CONTEXT_HEADER__

#include "ogl3.h"
#include "../context.h"

namespace sleek
{
    namespace driver
    {
        class ogl3_scissor : public scissor
        {
            public:
                ogl3_scissor(math::aabbox2di);
                virtual ~ogl3_scissor();
        };

        class ogl3_context : public context
        {
            public:
                ogl3_context(std::shared_ptr<device::Device>&, std::shared_ptr<context> shared = nullptr) noexcept;
                virtual ~ogl3_context() noexcept;

                virtual RENDER_CONTEXT getType() const noexcept
                {
                    return RCTX_OGL3;
                }

                virtual scissor createScissorContext(math::aabbox2di) const noexcept;

                virtual std::shared_ptr<driver>  createDriver() noexcept;
                virtual std::shared_ptr<texture> createScreenshot(const math::aabbox2du&) const noexcept;

                virtual std::shared_ptr<identifier> createTexture(texture *o, bool dsa = true) const noexcept;
                virtual std::shared_ptr<identifier> createTextureArray(texture_array*, bool dsa = true) const noexcept;
                virtual std::shared_ptr<identifier> createTexture3d(texture3d*, bool dsa = true) const noexcept;

                virtual std::shared_ptr<fbo>        createFBO(const math::vec2i &size, const std::vector<TextureFormat>&, bool depthattachment = false, bool dsa = true) const noexcept;
                virtual std::shared_ptr<identifier> createVAO(mesh *o, VAO_ALIGNMENT t = VAO_STATIC, VAO_ALIGNMENT e = VAO_STATIC, bool dsa = true) const noexcept;
                virtual std::shared_ptr<shader>     createShader(bool dsa = true) const noexcept;

                virtual void setViewport(const math::vec2i& i) noexcept;
                virtual void setAntialiasing(const AntiailiasingMode &i) noexcept;

                virtual AntiailiasingMode getAntiailiasing() const noexcept;
                virtual math::vec2i getViewport() const noexcept;

                virtual int queryHardwareLimitation(int) const noexcept;

                bool testError(int line, const std::string &file) const noexcept;

                virtual bool bind() noexcept;
                virtual void begin(const math::pixel &clearcolor = math::pixel(0xFFAAFFFF)) noexcept;
                virtual void end() noexcept;
            protected:
                math::vec2i viewport;
                AntiailiasingMode aam;

                #if defined __linux
                    GLXContext cx;
                #elif defined WIN32 || WIN64
                    HGLRC cx;
                #endif

                bool checkExtension(const char *name) noexcept;
                bool testError() const noexcept;
            private:
                bool dsa, txarray, tx3d;
        };
    }
}

#endif
