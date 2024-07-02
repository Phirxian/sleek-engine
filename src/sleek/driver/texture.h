#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <iosfwd>
#include <fstream>
#include <string>
#include <memory>

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
        enum TextureFormat : u8
        {
            TXFMT_LUMINANCE = 1,
            TXFMT_LUMINANCE_ALPHA = 2,
            TXFMT_RGB = 3,
            TXFMT_RGBA = 4,

            TXFMT_LUMINANCE_32F = 5,
            TXFMT_LUMINANCE_ALPHA_32F = 6,
            TXFMT_RGB_32F = 7,
            TXFMT_RGBA_32F = 8
        };
        class context;
        class identifier;
        class texture : public std::enable_shared_from_this<texture>
        {
            public:
                struct iterator
                {
                    public:
                        iterator(texture &img, u32 i) : src(img), index(i) { }
                        virtual ~iterator() { }
                        virtual bool operator != (const iterator &other) { return index != other.index; }
                        virtual iterator& operator ++ () { index++; return *this; }
                        virtual u8* operator * () const { return src.getBuffer() + src.indexof(index);  }
                    public:
                        texture &src;
                        u32 index;
                };

                struct const_iterator
                {
                    public:
                        const_iterator(const iterator &it) : src(it.src), index(it.index) { }
                        const_iterator(const texture &img, u32 i) : src(img), index(i) { }
                        virtual ~const_iterator() { }
                        virtual bool operator != (const const_iterator &other) { return index != other.index; }
                        virtual const_iterator& operator ++ () { index++; return *this; }
                        virtual u8* operator * () const { return src.getBuffer() + src.indexof(index);  }
                    public:
                        const texture &src;
                        u32 index;
                };
            public:
                texture(const math::vec2i &s, const TextureFormat a = TXFMT_RGBA, u8 *data = nullptr) noexcept;
                virtual ~texture() noexcept;

                inline std::shared_ptr<texture> getptr() noexcept
                {
                    return shared_from_this();
                }

                inline u32 indexof(const math::vec2i &pos) const noexcept { return (pos.x+pos.y*original.x)*pitch; }
                inline u32 indexof(const u32 &index) const noexcept { return indexof({index%original.x, index/original.x}); }

                inline iterator begin() noexcept { return {*this, 0}; }
                inline iterator start(const u32 &pos) noexcept { return {*this, pos}; }
                inline iterator start(const math::vec2i &pos) noexcept { return {*this, indexof(pos)}; }
                inline iterator end() noexcept { return {*this, getPixelCount()}; }

                inline const_iterator begin() const noexcept { return {*this, 0}; }
                inline const_iterator start(const u32 &pos) const noexcept  { return {*this, pos}; }
                inline const_iterator start(const math::vec2i &pos) const noexcept { return {*this, indexof(pos)}; }
                inline const_iterator end() const noexcept { return {*this, getPixelCount()}; }

                //! if floating texture, pixel is a ptr to the data
                virtual void setPixel(const math::vec2i &, const math::pixel&) noexcept;

                //! if floating texture, pixel is a ptr to the data
                virtual math::pixel getPixel(const math::vec2i&) const noexcept;

                virtual void createIdentifier(context*) noexcept;
                virtual void setIdentifier(std::shared_ptr<identifier>) noexcept;

                virtual math::vec2i getDimension() const noexcept;

                virtual TextureFormat getFormat() const noexcept;
                virtual u8 getComposantCount() const noexcept;
                virtual u8 getPitch() const noexcept;

                virtual std::shared_ptr<identifier> getIdentifier() const noexcept;

                virtual texture *clone() const noexcept;

                virtual u32 getPixelCount() const noexcept;
                virtual u32 getBufferSize() const noexcept;
                virtual u8* getBuffer() const noexcept;
            public:
                void flipVertical() noexcept;
                void flipHorizontal() noexcept;
                void flipDual() noexcept;
                void monochrome() noexcept;
                void invertColor() noexcept;
            protected:
                std::shared_ptr<identifier> gpu;
            private:
                u8 *buffer;
                std::string filename;
                math::vec2i original;
                TextureFormat fmt;
                u8 component;
                u8 pitch;
        };

        using texture_ptr = std::shared_ptr<texture>;
    }
}

#endif
