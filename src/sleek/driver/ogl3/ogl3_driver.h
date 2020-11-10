#ifndef OGL3_DRIVER
#define OGL3_DRIVER

#include "ogl3.h"
#include "../driver.h"

namespace sleek
{
    namespace device
    {
        class Device;
    }
    namespace driver
    {
        class ogl3_driver : public driver
        {
            public:
                ogl3_driver(std::shared_ptr<device::Device>, std::shared_ptr<context>) noexcept;
                virtual ~ogl3_driver() noexcept;

                virtual void drawPixel(const math::vec2i, const math::pixel c = {}) const noexcept;
                virtual void drawPixel(const math::vec3f, const math::pixel c = {}) const noexcept;
                virtual void drawLine(const math::vec2i, const math::vec2i, const math::pixel c = {}) const noexcept;
                virtual void drawLine(const math::vec3f, const math::vec3f, const math::pixel c = {}) const noexcept;
                virtual void drawArc(const math::vec2i, u32, u32, u32, const math::pixel c = {}) const noexcept;

                virtual void drawCube(const math::aabbox2di, const math::vec3f rot, const math::pixel upperleft, const math::pixel upperright, const math::pixel lowerleft, const math::pixel lowerright) const noexcept;
                virtual void drawCube(const math::aabbox2di, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept;
                virtual void drawCube(const math::aabbox3df, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept;
                virtual void drawCube(const math::vec2i, const math::vec2i, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept;
                virtual void drawCube(const math::vec3f, const math::vec3f, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept;

                virtual void drawCircle(const math::vec2i pos, u32 radius = 5.f, const math::pixel c = {}) const noexcept;

                virtual void drawPolygon(const math::vec2i, const math::vec2i, const math::vec2i, const math::pixel c = {}) const noexcept;
                virtual void drawPolygon(const math::vec3f, const math::vec3f, const math::vec3f, const math::pixel c = {}) const noexcept;
                virtual void drawPolygonList(const math::vec2i *a, u32 n, const math::vec2i, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept;
                virtual void drawPolygonList(const math::vec3f *a, u32 n, const math::vec3f, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept;

                virtual void drawFBO(fbo*) const noexcept;

                virtual void drawTexture(texture*, const math::vec2i pos = {0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}) const noexcept;
                virtual void drawTexture(texture*, const math::vec3f pos = {0, 0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}) const noexcept;

                virtual void drawTextureCenter(texture*, const math::vec2i pos = {0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}) const noexcept;
                virtual void drawTextureCenter(texture*, const math::vec3f pos = {0, 0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}) const noexcept;

                virtual void drawTextureScale(texture*, const math::vec2i pos = {0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec3f scl = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}) const noexcept;
                virtual void drawTextureScale(texture*, const math::vec3f pos = {0, 0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec3f scl = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}) const noexcept;

                virtual void drawMesh(mesh*, math::vec3f, math::vec3f rot = {0, 0, 0}) const noexcept;

                virtual void setActiveMaterial(std::shared_ptr<material>) noexcept;
                virtual std::shared_ptr<material> getActiveMaterial() const noexcept;

                virtual void ObjectRenderBegin() const noexcept;
                virtual void ObjectRenderEnd() const noexcept;

                virtual void beginTo2D() const noexcept;
                virtual void endFrom2D() const noexcept;
            protected:
                //display list (quad and point render accelerator)
                GLuint quad, quadc, cubec;
        };
    }
}

#endif
