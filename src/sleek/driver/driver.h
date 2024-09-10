#ifndef DRAW
#define DRAW

#include "fbo.h"
#include "texture.h"
#include "../device/device.h"
#include "../compile.h"
#include "material.h"
#include "geometry.h"

namespace sleek
{
    namespace device
    {
        class Device;
    }
    namespace driver
    {
        class context;

        enum DriverMatrixType
        {
            DMT_PROJECTION,
            DMT_MODELVIEW,
            DMT_COUNT
        };

        class driver : public std::enable_shared_from_this<driver>
        {
            public:
                driver(std::shared_ptr<device::Device>, std::shared_ptr<context>) noexcept;
                virtual ~driver() noexcept;

                inline std::shared_ptr<driver> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual void pushScissor(math::aabbox2di box);
                virtual math::aabbox2di popScissor();
                virtual void clearScissor();

                virtual void drawPixel(const math::vec2i, const math::pixel c = {}) const noexcept = 0;
                virtual void drawPixel(const math::vec3f, const math::pixel c = {}) const noexcept = 0;
                virtual void drawLine(const math::vec2i, const math::vec2i, const math::pixel c = {}) const noexcept = 0;
                virtual void drawLine(const math::vec3f, const math::vec3f, const math::pixel c = {}) const noexcept = 0;
                virtual void drawArc(const math::vec2i, u32, u32, u32, const math::pixel c = {}) const noexcept = 0;

                virtual void drawCube(const math::aabbox2di, const math::vec3f rot, const math::pixel upperleft, const math::pixel upperright, const math::pixel lowerleft, const math::pixel lowerright) const noexcept = 0;
                virtual void drawCube(const math::aabbox2di, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept = 0;
                virtual void drawCube(const math::aabbox3df, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept = 0;
                virtual void drawCube(const math::vec2i, const math::vec2i, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept = 0;
                virtual void drawCube(const math::vec3f, const math::vec3f, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept = 0;

                virtual void drawCircle(const math::vec2i pos, u32 radius = 5.f, const math::pixel c = {}) const noexcept = 0;

                virtual void drawPolygon(const math::vec2i, const math::vec2i, const math::vec2i, const math::pixel c = {}) const noexcept = 0;
                virtual void drawPolygon(const math::vec3f, const math::vec3f, const math::vec3f, const math::pixel c = {}) const noexcept = 0;
                virtual void drawPolygonList(const math::vec2i *a, u32 n, const math::vec2i, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept = 0;
                virtual void drawPolygonList(const math::vec3f *a, u32 n, const math::vec3f, const math::vec3f rot = {0, 0, 0}, const math::pixel c = {}) const noexcept = 0;

                virtual void drawFBO(fbo*) const noexcept = 0;

                virtual void drawTexture(texture*, const math::vec2i pos = {0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}, const math::pixel clr = {255,255,255,255}) const noexcept = 0;
                virtual void drawTexture(texture*, const math::vec3f pos = {0, 0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}, const math::pixel clr = {255,255,255,255}) const noexcept = 0;

                virtual void drawTextureCenter(texture*, const math::vec2i pos = {0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}, const math::pixel clr = {255,255,255,255}) const noexcept = 0;
                virtual void drawTextureCenter(texture*, const math::vec3f pos = {0, 0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}, const math::pixel clr = {255,255,255,255}) const noexcept = 0;

                virtual void drawTextureScale(texture*, const math::vec2i pos = {0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec3f scl = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}, const math::pixel clr = {255,255,255,255}) const noexcept = 0;
                virtual void drawTextureScale(texture*, const math::vec3f pos = {0, 0, 0}, const math::vec3f rot = {0, 0, 0}, const math::vec3f scl = {0, 0, 0}, const math::vec2f uv = {1.f, 1.f}, const math::pixel clr = {255,255,255,255}) const noexcept = 0;

                virtual void drawMesh(mesh*, const math::vec3f, const math::vec3f rot = {0, 0, 0}) const noexcept = 0;

                virtual void setActiveMaterial(std::shared_ptr<material>) noexcept = 0;
                virtual std::shared_ptr<material> getActiveMaterial() const noexcept = 0;

                virtual void ObjectRenderBegin() const noexcept = 0;
                virtual void ObjectRenderEnd() const noexcept = 0;

                virtual void beginTo2D() const noexcept = 0;
                virtual void endFrom2D() const noexcept = 0;

                virtual std::shared_ptr<context> getContext();
            protected:
                std::vector<math::aabbox2di> scissor;
                std::shared_ptr<device::Device> src;
                std::shared_ptr<context> ctx;
                std::shared_ptr<material> mat;
                u32 tricounter;
        };
    }
}

#endif
