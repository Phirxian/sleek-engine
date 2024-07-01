#include "texture3d.h"
#include "context.h"

#include <cstring>

namespace sleek
{
    namespace driver
    {
        static const unsigned int TextureFormatSize[] = {
            1, 2,  3,  4,
            4, 8, 12, 16
        };

        static const unsigned int TextureFormatComponant[] = {
            1, 2, 3, 4,
            1, 2, 3, 4
        };

        texture3d::texture3d(const math::vec3i &size, const TextureFormat p) noexcept
            : gpu(nullptr), buffer(0), isloaded(false), fmt(p)
        {
            pitch = TextureFormatSize[p-1];
            component = TextureFormatComponant[p-1];
            original = size;
            buffer = new u8[getBufferSize()];
        }

        texture3d::~texture3d() noexcept
        {
            delete[] buffer;
        }

        /* ***************************************** */

        math::vec3i texture3d::getDimension() const noexcept
        {
            return original;
        }

        u8 texture3d::getComposantCount() const noexcept
        {
            return component;
        }

        u8 texture3d::getPitch() const noexcept
        {
            return pitch;
        }

        /* ***************************************** */

        void texture3d::setPixel(const math::vec3i &pos, const math::pixel &color) noexcept
        {
            u8* pixel = &buffer[(pos.x + pos.y*original.x + pos.z*original.y*original.y)*pitch];
            switch(fmt)
            {
                case TXFMT_LUMINANCE:
                    pixel[0] = color.getLuminaissance();
                break;
                case TXFMT_LUMINANCE_ALPHA:
                    pixel[0] = color.getLuminaissance();
                    pixel[1] = color.getAlpha();
                break;
                case TXFMT_RGB:
                    pixel[0] = color.getRed();
                    pixel[1] = color.getGreen();
                    pixel[2] = color.getBlue();
                break;
                case TXFMT_RGBA:
                    pixel[0] = color.getRed();
                    pixel[1] = color.getGreen();
                    pixel[2] = color.getBlue();
                    pixel[3] = color.getAlpha();
                break;

                //! float

                case TXFMT_LUMINANCE_32F:
                case TXFMT_LUMINANCE_ALPHA_32F:
                case TXFMT_RGB_32F:
                case TXFMT_RGBA_32F:
                {
                    float *ptr = reinterpret_cast<float*>(pixel);
                    std::memcpy((float*)(&pixel), ptr, pitch);
                }
                break;
            }
        }

        math::pixel texture3d::getPixel(const math::vec3i &pos) const noexcept
        {
            register unsigned long index = (pos.x + pos.y*original.x + pos.z*original.y*original.y)*pitch;
            switch(fmt)
            {
                case TXFMT_LUMINANCE: return math::pixel(buffer[index],buffer[index],buffer[index],255); break;
                case TXFMT_LUMINANCE_ALPHA: return math::pixel(buffer[index],buffer[index],buffer[index],buffer[index+1]); break;
                case TXFMT_RGB:  return math::pixel(buffer[index],buffer[index+1],buffer[index+2],255); break;
                case TXFMT_RGBA: return math::pixel(buffer[index],buffer[index+1],buffer[index+2],buffer[index+3]); break;

                //! float

                case TXFMT_LUMINANCE_32F:
                case TXFMT_LUMINANCE_ALPHA_32F:
                case TXFMT_RGB_32F:
                case TXFMT_RGBA_32F:
                    return reinterpret_cast<std::uintptr_t>(&buffer[index]);
                break;
            }

            return math::pixel(0);
        }

        TextureFormat texture3d::getFormat() const noexcept
        {
            return fmt;
        }

        /* ***************************************** */

        void texture3d::setIdentifier(std::shared_ptr<identifier> &i) noexcept
        {
            gpu = i;
        }

        void texture3d::createIdentifier(context *cx) noexcept
        {
            gpu = cx->createTexture3d(this);
        }

        u8* texture3d::getBuffer() const noexcept
        {
            return buffer;
        }

        u32 texture3d::getBufferSize() const noexcept
        {
            return original.x*original.y*original.z*pitch;
        }

        std::shared_ptr<identifier> texture3d::getIdentifier() const noexcept
        {
            return gpu->getptr();
        }

        /* ***************************************** */

        texture3d* texture3d::clone() const noexcept
        {
            texture3d *tmp = new texture3d(original, fmt);
            memcpy(tmp->buffer, buffer, getBufferSize());
            return tmp;
        }
    }
}
