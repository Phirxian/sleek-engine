#ifndef PIXEL
#define PIXEL

#include "../define.h"
#include "../math/function.h"
#include "math.h"

namespace sleek
{
    namespace math
    {
        class pixel
        {
            public:
                pixel(const u32 color = 0xFFFFFFFF) noexcept
                {
                    blue =  (color >>  0) & 0xFF;
                    green = (color >>  8) & 0xFF;
                    red =   (color >> 16) & 0xFF;
                    alpha = (color >> 24) & 0xFF;
                }
                pixel(const u8 r, const u8 g, const u8 b,const u8 a = 255) noexcept
                {
                    red = r;
                    green = g;
                    blue = b;
                    alpha = a;
                }
                ~pixel() noexcept
                {
                }

                inline void set(const u8 r, const u8 g, const u8 b,const u8 a = 255) noexcept
                {
                    red = r;
                    green = g;
                    blue = b;
                    alpha = a;
                }

                inline math::pixel operator * (int i) const noexcept { return math::pixel(red*i, green*i, blue*i, alpha*i); }
                inline math::pixel operator / (int i) const noexcept { return math::pixel(red/i, green/i, blue/i, alpha/i); }
                inline math::pixel operator + (int i) const noexcept { return math::pixel(red+i, green+i, blue+i, alpha+i); }
                inline math::pixel operator - (int i) const noexcept { return math::pixel(red-i, green-i, blue-i, alpha-i); }

                inline void setRed(const u8 i)   noexcept { red = i;   }
                inline void setGreen(const u8 i) noexcept { green = i; }
                inline void setBlue(const u8 i)  noexcept { blue = i;  }
                inline void setAlpha(const u8 i) noexcept { alpha = i; }

                inline u8 getRed()   const noexcept { return red;   }
                inline u8 getGreen() const noexcept { return green; }
                inline u8 getBlue()  const noexcept { return blue;  }
                inline u8 getAlpha() const noexcept { return alpha; }

                inline pixel getInterpolated(const pixel &other, f32 d) const
                {
                    d = math::clamp(d, 0.f, 1.f);
                    const f32 inv = 1.0f - d;

                    return {
                        u8(other.red  *inv + red  *d),
                        u8(other.green*inv + green*d),
                        u8(other.blue *inv + blue *d),
                        u8(other.alpha*inv + alpha*d)
                    };
                }

                inline pixel monochrome() const noexcept
                {
                    pixel tmp = monochrome_with_alpha();
                    tmp.setAlpha(255);
                    return tmp;;
                }

                inline pixel monochrome_with_alpha() const noexcept
                {
                    u8 luminaissance = getLuminaissance();
                    return pixel(luminaissance,luminaissance,luminaissance,alpha);
                }

                inline u8 getLuminaissance() const noexcept
                {
                    return (red+green+blue)/3;
                }

                inline u32 toInt()
                {
                    return red   << 24 |
                           green << 16 |
                           blue  <<  8 |
                           alpha;
                }
            public:
                inline vec3f HSV() const noexcept
                {
                    math::vec3f hsv;

                    f32 M = math::max(getRed(), getGreen(), getBlue());
                    f32 m = math::min(getRed(), getGreen(), getBlue());
                    f32 C = M - m;

                    if(C == 0)
                        hsv.x = 0;
                    else if(M <= getRed())
                        hsv.x = (getGreen() - getBlue()) / C;
                    else if(M <= getGreen())
                        hsv.x = (getBlue() - getRed()) / C + 2;
                    else if(M <= getBlue())
                        hsv.x = (getRed() - getGreen()) / C + 4;

                    hsv.x *= 60;
                    if(hsv.x < 0)
                        hsv.x += 360;

                    hsv.y = M;
                    hsv.z = M == 0 ? 0 : C / hsv.y;

                    return hsv;
                }
            public:
                u8 red;
                u8 green;
                u8 blue;
                u8 alpha;
        };

        inline u16 RGBA16(u32 r, u32 g, u32 b, u32 a=0xFF)
        {
            return (u16)((a & 0x80) << 8 |
                (r & 0xF8) << 7 |
                (g & 0xF8) << 2 |
                (b & 0xF8) >> 3);
        }

        inline u16 RGB16(u32 r, u32 g, u32 b)
        {
            return RGBA16(r,g,b);
        }

        inline u16 RGB16from16(u16 r, u16 g, u16 b)
        {
            return (0x8000 |
                    (r & 0x1F) << 10 |
                    (g & 0x1F) << 5  |
                    (b & 0x1F));
        }

        inline u16 X8R8G8B8toA1R5G5B5(u32 color)
        {
            return (u16)(0x8000 |
                ( color & 0x00F80000) >> 9 |
                ( color & 0x0000F800) >> 6 |
                ( color & 0x000000F8) >> 3);
        }

        inline u16 A8R8G8B8toA1R5G5B5(u32 color)
        {
            return (u16)(( color & 0x80000000) >> 16|
                ( color & 0x00F80000) >> 9 |
                ( color & 0x0000F800) >> 6 |
                ( color & 0x000000F8) >> 3);
        }

        inline u16 A8R8G8B8toR5G6B5(u32 color)
        {
            return (u16)(( color & 0x00F80000) >> 8 |
                ( color & 0x0000FC00) >> 5 |
                ( color & 0x000000F8) >> 3);
        }

        inline u32 A1R5G5B5toA8R8G8B8(u16 color)
        {
            return ( (( -( (s32) color & 0x00008000 ) >> (s32) 31 ) & 0xFF000000 ) |
                    (( color & 0x00007C00 ) << 9) | (( color & 0x00007000 ) << 4) |
                    (( color & 0x000003E0 ) << 6) | (( color & 0x00000380 ) << 1) |
                    (( color & 0x0000001F ) << 3) | (( color & 0x0000001C ) >> 2)
                    );
        }

        inline u32 R5G6B5toA8R8G8B8(u16 color)
        {
            return 0xFF000000 |
                ((color & 0xF800) << 8)|
                ((color & 0x07E0) << 5)|
                ((color & 0x001F) << 3);
        }

        inline u16 R5G6B5toA1R5G5B5(u16 color)
        {
            return 0x8000 | (((color & 0xFFC0) >> 1) | (color & 0x1F));
        }

        inline u16 A1R5G5B5toR5G6B5(u16 color)
        {
            return (((color & 0x7FE0) << 1) | (color & 0x1F));
        }
    }
}

#endif
