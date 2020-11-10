#include "texture_bmp.h"
#include "../../driver/texture.h"
#include "../../compile.h"
#include <stdlib.h>

namespace sleek
{
    namespace loader
    {
        #define CTOI(C)(*(int*)&C)

        int textureloader_bmp::check_header(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_bmp_support
                char header[2];
                file->read(header, 2);
                return -!(header[0] == 'B' || header[1] == 'M');
            #endif
            return -1;
        }

        std::shared_ptr<driver::texture> textureloader_bmp::read(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_bmp_support
            unsigned char header[0x36];
            int pitch, offset;
            long size, width, height;
            unsigned char m_bitCount;

            file->read(header, 0x36);

            if(header[0]!='B' || header[1]!='M')
                return nullptr;

            // unsupported compression mode
            if(CTOI(header[0x1E]) < 0 || CTOI(header[0x1E]) > 3)
                return nullptr;

            m_bitCount = CTOI(header[0x1C]);
            if(m_bitCount == 16)      pitch = driver::TXFMT_RGB;
            else if(m_bitCount == 24) pitch = driver::TXFMT_RGB;
            else if(m_bitCount == 32) pitch = driver::TXFMT_RGBA;
            else pitch = m_bitCount;

            offset = CTOI(header[0x0A]);
            size = CTOI(header[0x22]);

            width = CTOI(header[0x12]);
            height = CTOI(header[0x16]);

            if(!size)   size = height*width*(m_bitCount/8);
            if(!offset) offset = 0x36;

            file->seek(offset, false);

            auto bmp = std::make_shared<driver::texture>(
                math::vec2i(width, height),
               (driver::TextureFormat)pitch
            );

            int pos = file->pos();
            file->read(bmp->getBuffer(), size);
            auto buff = bmp->getBuffer();

            switch(CTOI(header[0x1E]))
            {
                case 0:
                    switch(m_bitCount)
                    {
                        case 16:
                            for(u32 i = 0; i < size; i += pitch) // bgr >> rgb
                            {
                                unsigned char colorSwap = buff[i];
                                buff[i]   = buff[i+2];//2
                                buff[i+1] = buff[i+1];//1
                                buff[i+2] = colorSwap;
                            }
                        break;
                        case 24:
                            for(u32 i = 0; i < size; i += pitch) // bgr >> rgb
                            {
                                unsigned char colorSwap = buff[i];
                                buff[i]   = buff[i+2];//2
                                buff[i+1] = buff[i+1];//1
                                buff[i+2] = colorSwap;
                            }
                        break;
                        case 32:
                            for(u32 i = 0; i < size; i += pitch) // bgr >> rgb
                            {
                                unsigned char colorSwap = buff[i];
                                buff[i]   = buff[i+2];//2
                                buff[i+1] = buff[i+1];//1
                                buff[i+3] = buff[i+3];//3
                                buff[i+2] = colorSwap;
                            }
                        break;
                    }
                break;
                case 1:
                    decompress8BitRLE(buff, size, width, height, pitch);
                break;
                case 2:
                    decompress4BitRLE(buff, size, width, height, pitch);
                break;
                case 3:
                    switch(m_bitCount)
                    {
                        case 32:
                            for(u32 i = 0; i < size; i += pitch) // xrgb -> rgb(a = 255)
                            {
                                unsigned char colorSwap = buff[i+2];
                                buff[i]   = buff[i+3];
                                buff[i+2] = buff[i+1];
                                buff[i+1] = colorSwap;
                                buff[i+3] = 255;
                            }
                        break;
                        default: break;
                    }
                break;
            }

            bmp->flipVertical();

            return bmp;
            #else
                return nullptr;
            #endif
        }

        bool textureloader_bmp::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_bmp_support
                //! no floating texture support
                if(img->getFormat() >= 5)
                    return false;

                unsigned char header[0x36] = {0};
                    header[0] = 'B';
                    header[1] = 'M';
                    header[0x1C] = img->getPitch()*8;

                    CTOI(header[0x1E]) = 0;
                    CTOI(header[0x1C]) = 32;    // BGRA 4 component of 8 bit
                    CTOI(header[0x0A]) = 0x36;
                    CTOI(header[0x12]) = img->getDimension().x;
                    CTOI(header[0x16]) = img->getDimension().y;
                    CTOI(header[0x22]) = img->getBufferSize();

                file->write(header, 0x36);

                math::vec2u pos;
                for(;pos.y < img->getDimension().y; ++pos.y)
                {
                    for(;pos.x < img->getDimension().x; ++pos.x)
                    {
                        math::pixel tmp = img->getPixel(pos);
                        std::swap(tmp.red, tmp.blue); // bgr to rgb
                        file->write(&tmp, 4);
                    }
                }

                return true;
            #endif
            return false;
        }

        bool textureloader_bmp::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "bmp" || extention == "dib";
        }

        //! original code from irrlicht
        void textureloader_bmp::decompress8BitRLE(u8*& bmpData, s32 size, s32 width, s32 height, s32 pitch) const
        {
            u8* p = bmpData;
            u8* newBmp = new u8[(width+pitch)*height];
            u8* d = newBmp;
            u8* destEnd = newBmp +(width+pitch)*height;
            s32 line = 0;

            while(bmpData - p < size && d < destEnd)
            {
                if(*p == 0)
                {
                    ++p;
                    switch(*p)
                    {
                        case 0: // end of line
                            ++p;
                            ++line;
                            d = newBmp +(line*(width+pitch));
                            break;
                        case 1: // end of bmp
                            delete [] bmpData;
                            bmpData = newBmp;
                            return;
                        case 2:
                            ++p; d +=(u8)*p;  // delta
                            ++p; d +=((u8)*p)*(width+pitch);
                            ++p;
                            break;
                        default:
                        {
                            // absolute mode
                            s32 count =(u8)*p; ++p;
                            s32 readAdditional =((2-(count%2))%2);
                            s32 i;

                            for(i=0; i<count; ++i)
                            {
                                *d = *p;
                                ++p;
                                ++d;
                            }

                            for(i=0; i<readAdditional; ++i)
                                ++p;
                        }
                    }
                }
                else
                {
                    s32 count =(u8)*p; ++p;
                    u8 color = *p; ++p;
                    for(s32 i=0; i<count; ++i)
                    {
                        *d = color;
                        ++d;
                    }
                }
            }

            delete [] bmpData;
            bmpData = newBmp;
        }

        //! original code from irrlicht
        void textureloader_bmp::decompress4BitRLE(u8*& bmpData, s32 size, s32 width, s32 height, s32 pitch) const
        {
            s32 lineWidth =(width+1)/2+pitch;
            u8* p = bmpData;
            u8* newBmp = new u8[lineWidth*height];
            u8* d = newBmp;
            u8* destEnd = newBmp + lineWidth*height;
            s32 line = 0;
            s32 shift = 4;

            while(bmpData - p < size && d < destEnd)
            {
                if(*p == 0)
                {
                    ++p;

                    switch(*p)
                    {
                        case 0: // end of line
                            ++p;
                            ++line;
                            d = newBmp +(line*lineWidth);
                            shift = 4;
                        break;
                        case 1: // end of bmp
                            delete [] bmpData;
                            bmpData = newBmp;
                        return;
                        case 2:
                        {
                            ++p;
                            s32 x =(u8)*p; ++p;
                            s32 y =(u8)*p; ++p;
                            d += x/2 + y*lineWidth;
                            shift = x%2==0 ? 4 : 0;
                        }
                        break;
                        default:
                        {
                            // absolute mode
                            s32 count =(u8)*p; ++p;
                            s32 readAdditional =((2-((count)%2))%2);
                            s32 readShift = 4;
                            s32 i;

                            for(i=0; i<count; ++i)
                            {
                                s32 color =(((u8)*p) >> readShift) & 0x0f;
                                readShift -= 4;
                                if(readShift < 0)
                                {
                                    ++*p;
                                    readShift = 4;
                                }

                                u8 mask = 0x0f << shift;
                                *d =(*d &(~mask)) |((color << shift) & mask);

                                shift -= 4;
                                if(shift < 0)
                                {
                                    shift = 4;
                                    ++d;
                                }

                            }

                            for(i=0; i<readAdditional; ++i)
                                ++p;
                        }
                    }
                }
                else
                {
                    s32 count =(u8)*p; ++p;
                    s32 color1 =(u8)*p; color1 = color1 & 0x0f;
                    s32 color2 =(u8)*p; color2 =(color2 >> 4) & 0x0f;
                    ++p;

                    for(s32 i=0; i<count; ++i)
                    {
                        u8 mask = 0x0f << shift;
                        u8 toSet =(shift==0 ? color1 : color2) << shift;
                        *d =(*d &(~mask)) |(toSet & mask);

                        shift -= 4;
                        if(shift < 0)
                        {
                            shift = 4;
                            ++d;
                        }
                    }
                }
            }

            delete [] bmpData;
            bmpData = newBmp;
        }
    }
}

