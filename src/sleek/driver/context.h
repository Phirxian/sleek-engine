#ifndef __CONTEXT_HEADER__
#define __CONTEXT_HEADER__

#include "../compile.h"
#include "../device/device_stub.h"
#include "../math/aabbox.h"

#include "fbo.h"
#include "shader.h"
#include "mesh.h"

#include "texture.h"
#include "texture_array.h"
#include "texture3d.h"

namespace sleek
{
    namespace driver
    {
        enum RENDER_CONTEXT
        {
            // ready to use
            // but there have some old deprecated fixed-pipline remaining here
            RCTX_OGL3,
            // experiemental at this time
            RCTX_OGL4,
            // not yet
            RCTX_D3D_12,
            // not yet
            RCTX_VK,
            // do not use
            RCTX_COUNT
        };

        enum AntiailiasingMode
        {
            DAM_OFF,
            DAM_FAST,
            DAM_NICE,
            DAM_COUNT
        };

        class driver;
        class mesh;

        class context : public std::enable_shared_from_this<context>
        {
            public:
                context(std::shared_ptr<device::Device>&, std::shared_ptr<context> shared = nullptr) noexcept;
                ~context() noexcept;

                virtual RENDER_CONTEXT getType() const noexcept = 0;

                virtual std::shared_ptr<driver>     createDriver() noexcept = 0;
                virtual std::shared_ptr<texture>    createScreenshot(const math::aabbox2du&) const noexcept = 0;

                virtual std::shared_ptr<identifier> createTexture(texture*, bool dsa = true) const noexcept = 0;
                virtual std::shared_ptr<identifier> createTextureArray(texture_array*, bool dsa = true) const noexcept = 0;
                virtual std::shared_ptr<identifier> createTexture3d(texture3d*, bool dsa = true) const noexcept = 0;

                virtual std::shared_ptr<fbo>        createFBO(const math::vec2i &size, const std::vector<TextureFormat> &attachments, bool depthattachment = false, bool dsa = true) const noexcept = 0;
                virtual std::shared_ptr<identifier> createVAO(mesh *o, VAO_ALIGNMENT v = VAO_STATIC, VAO_ALIGNMENT e = VAO_STATIC, bool dsa = true) const noexcept = 0;
                virtual std::shared_ptr<shader>     createShader(bool dsa = true) const noexcept = 0;

                virtual void setViewport(const math::vec2i& i) noexcept = 0;
                virtual void setAntialiasing(const AntiailiasingMode &i) noexcept = 0;

                virtual AntiailiasingMode getAntiailiasing() const noexcept = 0;
                virtual math::vec2i getViewport() const noexcept = 0;

                virtual int queryHardwareLimitation(int) const noexcept = 0;

                inline std::shared_ptr<context> getptr()
                {
                    return shared_from_this();
                }

                virtual bool testError(int line, const std::string &file) const noexcept = 0;

                virtual bool bind() noexcept = 0;
                virtual void begin(const math::pixel &clearcolor = {0xFFAAFFFF}) noexcept = 0;
                virtual void end() noexcept = 0;
            protected:
                std::shared_ptr<device::Device> win;
                std::shared_ptr<context> shared;
        };

        // build platform dependent render context
        // shared context must be the same type

        std::shared_ptr<context> createContextRenderer(
            RENDER_CONTEXT,
            std::shared_ptr<device::Device>&,
            std::shared_ptr<context> shared = nullptr
        ) noexcept;
    }
}

#endif
