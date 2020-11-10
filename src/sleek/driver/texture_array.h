#ifndef __TEXTURE_2D_ARRAY__
#define __TEXTURE_2D_ARRAY__

#include "texture.h"
#include <vector>

namespace sleek
{
    namespace driver
    {
        class texture_array : public std::enable_shared_from_this<texture_array>
        {
            typedef std::vector<std::shared_ptr<texture>> texture_store;
            public:
                texture_array(const math::vec2i &s, const TextureFormat a = TXFMT_RGBA) noexcept;
                virtual ~texture_array() noexcept;

                inline std::shared_ptr<texture_array> getptr() noexcept
                {
                    return shared_from_this();
                }

                // can fail if the texture as not the same size & format
                virtual bool push_back(std::shared_ptr<texture>) noexcept;

                // can fail if the texture as not the same size & format
                virtual bool insert(texture_store::iterator, std::shared_ptr<texture>) noexcept;

                virtual void erase(texture_store::iterator) noexcept;

                virtual u32 count() noexcept;

                virtual math::vec2i getDimension() const noexcept;
                virtual math::pixel getPixel(const math::vec2i&, int) const noexcept;

                virtual TextureFormat getFormat() const noexcept;
                virtual u8 getComposantCount() const noexcept;
                virtual u8 getPitch() const noexcept;

                virtual std::shared_ptr<identifier> getIdentifier() const noexcept;

                virtual u8* getBuffer(int) const noexcept;
            protected:
                std::shared_ptr<identifier> gpu;
                texture_store textures;
                math::vec2i original;
                TextureFormat fmt;
                u8 component;
                u8 pitch;
        };
    }
}

#endif
