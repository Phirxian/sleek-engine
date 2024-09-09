#include "texture.h"
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

        texture::texture(const math::vec2i &size, const TextureFormat p, u8 *data) noexcept
            : gpu(nullptr), buffer(0), fmt(p)
        {
            fmt = p;
            pitch = TextureFormatSize[p];
            component = TextureFormatComponant[p];
            original = size;
            buffer = new u8[getBufferSize()];

            if (data)
                std::memcpy(buffer, data, getBufferSize());
        }

        texture::~texture() noexcept
        {
            delete[] buffer;
        }

        /* ***************************************** */

        math::vec2i texture::getDimension() const noexcept
        {
            return original;
        }

        /* ***************************************** */

        void texture::setPixel(const math::vec2i &pos, const math::pixel &color) noexcept
        {
            int idx = indexof(pos);

            if(idx > getBufferSize())
                return;

            u8* pixel = &buffer[idx];
            switch(fmt)
            {
                case TXFMT_LUMINANCE:
                    pixel[0] = color.getLuminance();
                break;
                case TXFMT_LUMINANCE_ALPHA:
                    pixel[0] = color.getLuminance();
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
                    float* floatPixel = reinterpret_cast<float*>(pixel);
                    switch (fmt)
                    {
                        case TXFMT_LUMINANCE_32F:
                            floatPixel[0] = color.getLuminance();
                            break;
                        case TXFMT_LUMINANCE_ALPHA_32F:
                            floatPixel[0] = color.getLuminance();
                            floatPixel[1] = color.getAlpha();
                            break;
                        case TXFMT_RGB_32F:
                            floatPixel[0] = color.getRed();
                            floatPixel[1] = color.getGreen();
                            floatPixel[2] = color.getBlue();
                            break;
                        case TXFMT_RGBA_32F:
                            floatPixel[0] = color.getRed();
                            floatPixel[1] = color.getGreen();
                            floatPixel[2] = color.getBlue();
                            floatPixel[3] = color.getAlpha();
                            break;
                        default:
                            // Handle unsupported formats
                            break;
                    }
                break;
            }
        }

        u8 texture::getComposantCount() const noexcept
        {
            return component;
        }

        u8 texture::getPitch() const noexcept
        {
            return pitch;
        }

        math::pixel texture::getPixel(const math::vec2i &pos) const noexcept
        {
            int index = indexof(pos);
            
            switch(fmt)
            {
                case TXFMT_LUMINANCE:       return math::pixel(buffer[index],buffer[index],buffer[index],255);                  break;
                case TXFMT_LUMINANCE_ALPHA: return math::pixel(buffer[index],buffer[index],buffer[index],buffer[index+1]);      break;
                case TXFMT_RGB:             return math::pixel(buffer[index],buffer[index+1],buffer[index+2],255);              break;
                case TXFMT_RGBA:            return math::pixel(buffer[index],buffer[index+1],buffer[index+2],buffer[index+3]);  break;

                //! float

                case TXFMT_LUMINANCE_32F:
                case TXFMT_LUMINANCE_ALPHA_32F:
                case TXFMT_RGB_32F:
                case TXFMT_RGBA_32F:
                    return reinterpret_cast<std::uintptr_t>(&buffer[index]);
                break;
            }
            
            return math::pixel(0, 0, 0);
        }

        TextureFormat texture::getFormat() const noexcept
        {
            return fmt;
        }

        /* ***************************************** */

        void texture::setIdentifier(std::shared_ptr<identifier> i) noexcept
        {
            gpu = i;
        }

        void texture::createIdentifier(context *cx) noexcept
        {
            gpu = cx->createTexture(this);
        }

        u8* texture::getBuffer() const noexcept
        {
            return buffer;
        }

        u32 texture::getBufferSize() const noexcept
        {
            return original.x*original.y*pitch;
        }

        u32 texture::getPixelCount() const noexcept
        {
            return original.x*original.y;
        }

        std::shared_ptr<identifier> texture::getIdentifier() const noexcept
        {
            return gpu->getptr();
        }

        /* ***************************************** */

        texture* texture::clone() const noexcept
        {
            texture *tmp = new texture(original, fmt);
            memcpy(tmp->buffer, buffer, getBufferSize());
            return tmp;
        }

        void texture::monochrome() noexcept
        {
            if(fmt == TXFMT_RGB || fmt == TXFMT_RGBA)
            {
                for(int i = 0; i<getBufferSize(); i += pitch)
                {
                    buffer[i+0] = (buffer[i]+buffer[i+1]+buffer[i+2])/3;
                    buffer[i+1] = (buffer[i]+buffer[i+1]+buffer[i+2])/3;
                    buffer[i+2] = (buffer[i]+buffer[i+1]+buffer[i+2])/3;
                }
            }
            if(fmt == TXFMT_RGB_32F || fmt == TXFMT_RGBA_32F)
            {
                for(int i = 0; i<getBufferSize(); i+= pitch)
                {
                    float avg = *((float*)(&buffer)+0)
                              + *((float*)(&buffer)+1)
                              + *((float*)(&buffer)+2);

                    *((float*)(&buffer)+0) = avg/3.0;
                    *((float*)(&buffer)+1) = avg/3.0;
                    *((float*)(&buffer)+2) = avg/3.0;
                }
            }
        }

        void texture::flipVertical() noexcept
        {
            u8 tmp[pitch];
            for(int y=0;y<original.y/2;y++)
            {
                for(int x=0;x<original.x;x++)
                {
                    // better performance
                    math::pixel px0 = getPixel({x, original.y-y-1});
                    math::pixel px1 = getPixel({x, y});

                    setPixel({x, y}, px0);
                    setPixel({x, original.y-y-1}, px1);
                    // less performance again unaligned buffer
//                    unsigned long src = (x+(original.y-y-1)*original.x)*pitch;
//                    unsigned long dst = (x+y*original.x)*pitch;
//
//                    memcpy(tmp, buffer+src, pitch);
//                    memcpy(buffer+src, buffer+dst, pitch);
//                    memcpy(buffer+dst, tmp, pitch);
                }
            }
        }

        void texture::flipHorizontal() noexcept
        {
            for(int y=0;y<original.y;y++)
            {
                for(int x=0;x<original.x/2;x++)
                {
                    math::pixel px0 = getPixel({x, y});
                    math::pixel px1 = getPixel({original.x-x-1, y});

                    setPixel({x, y}, px1);
                    setPixel({original.x-x-1, y}, px0);
                }
            }
        }

        void texture::flipDual() noexcept
        {
            flipVertical();
            flipHorizontal();
        }

        void texture::invertColor() noexcept
        {
            switch(fmt)
            {
                case TXFMT_RGB:
                case TXFMT_RGBA:
                    for(int i = 0; i<getBufferSize(); i+= pitch)
                    {
                        buffer[i+0] = 255-buffer[i+0];
                        buffer[i+1] = 255-buffer[i+1];
                        buffer[i+2] = 255-buffer[i+2];
                    }
                break;
                case TXFMT_LUMINANCE:
                case TXFMT_LUMINANCE_ALPHA:
                    for(int i = 0; i<getBufferSize(); i+= pitch)
                        buffer[i] = 255-buffer[i];
                break;

                //! float

                case TXFMT_LUMINANCE_32F:
                case TXFMT_LUMINANCE_ALPHA_32F:
                    for(int i = 0; i<getBufferSize(); i+= pitch)
                    {
                        float &ptr = *(float*)(&buffer[i]);
                        ptr = 1.0-ptr;
                    }
                break;
                case TXFMT_RGB_32F:
                case TXFMT_RGBA_32F:
                    for(int i = 0; i<getBufferSize(); i+= pitch)
                    {
                        *((float*)(&buffer)+0) = 1.0-*((float*)(&buffer)+0);
                        *((float*)(&buffer)+1) = 1.0-*((float*)(&buffer)+1);
                        *((float*)(&buffer)+2) = 1.0-*((float*)(&buffer)+2);
                    }
                break;
            }
        }
    }
}
