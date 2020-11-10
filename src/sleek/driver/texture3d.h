#ifndef TEXTURE_3D
#define TEXTURE_3D

#include <iosfwd>
#include <fstream>
#include <string>
#include <memory>

#include "texture.h"
#include "../math/math.h"
#include "../math/pixel.h"

namespace sleek
{
    namespace device
    {
        class Device;
    }
    namespace driver
    {
        class context;
        class identifier;
        class texture3d : public std::enable_shared_from_this<texture3d>
        {
            public:
                texture3d(const math::vec3i &s, const TextureFormat a = TXFMT_RGBA) noexcept;
                virtual ~texture3d() noexcept;

                inline std::shared_ptr<texture3d> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual void setPixel(const math::vec3i &, const math::pixel&) noexcept;

                virtual void createIdentifier(context*) noexcept;
                virtual void setIdentifier(std::shared_ptr<identifier>&) noexcept;

                virtual math::vec3i getDimension() const noexcept;
                virtual math::pixel getPixel(const math::vec3i&) const noexcept;

                virtual TextureFormat getFormat() const noexcept;
                virtual u8 getComposantCount() const noexcept;
                virtual u8 getPitch() const noexcept;

                virtual std::shared_ptr<identifier> getIdentifier() const noexcept;

                virtual texture3d *clone() const noexcept;

                virtual u32 getBufferSize() const noexcept;
                virtual u8* getBuffer() const noexcept;
            protected:
                std::shared_ptr<identifier> gpu;
            private:
                bool isloaded;
                u8 *buffer;
                std::string filename;
                math::vec3i original;
                TextureFormat fmt;
                u8 component;
                u8 pitch;
        };
    }
}

#endif
