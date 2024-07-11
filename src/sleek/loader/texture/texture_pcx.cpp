// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "texture_pcx.h"
#include "color_converter.h"
#include "../../driver/texture.h"
#include "../../compile.h"

#include <cstring>

namespace sleek
{
    namespace loader
    {
        int texture_pcx::check_header(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_blp_support
                char header[2];
                file->read(header, 2);
                // Manufacturer and Encoding
                return -!(header[0] == 0x0a && header[1] == 0x01);
            #endif
            return -1;
        }

        std::shared_ptr<driver::texture> texture_pcx::read(io::filereader *file) const noexcept
        {
            std::shared_ptr<driver::texture> img;

            #ifdef texture_loader_pcx_support
                pcxheader header;
                s32* paletteData = 0;

                file->read(&header, sizeof(header));

                // not a pcx
                if(header.Manufacturer != 0x0a && header.Encoding != 0x01)
                    return 0;

                // unsupported type
                if(header.BitsPerPixel != 8 && header.BitsPerPixel != 4 && header.BitsPerPixel != 1)
                    return nullptr;

                if(header.BitsPerPixel == 8 && header.Planes == 1)
                {
                    const long pos = file->pos();
                    file->seek(file->size()-256*3, false);

                    u8 *tempPalette = new u8[768];
                    paletteData = new s32[256];
                    file->read(tempPalette, 768);

                    for(s32 i=0; i<256; i++)
                        paletteData[i] = 0xff000000 | tempPalette[i*3+0] << 16 | tempPalette[i*3+1] << 8 | tempPalette[i*3+2];

                    delete [] tempPalette;

                    file->seek(pos);
                }
                else if(header.BitsPerPixel == 4)
                {
                    paletteData = new s32[16];
                    for( s32 i=0; i<16; i++ )
                        paletteData[i] = 0xff000000 | header.Palette[i*3+0] << 16 | header.Palette[i*3+1] << 8 | header.Palette[i*3+2];
                }

                const s32 width = header.XMax - header.XMin + 1;
                const s32 height = header.YMax - header.YMin + 1;
                const s32 imagebytes = header.BytesPerLine * header.Planes * header.BitsPerPixel * height / 8;
                u8* PCXData = new u8[imagebytes];

                u8 cnt, value;
                s32 lineoffset=0, linestart=0, nextmode=1;

                for(s32 offset = 0; offset < imagebytes; offset += cnt)
                {
                    file->read(&cnt, 1);

                    if(cnt & 0xc0 != 0xc0)
                        value = cnt, cnt = 1;
                    else
                    {
                        cnt &= 0x3f;
                        file->read(&value, 1);
                    }

                    if (header.Planes==1)
                        memset(PCXData+offset, value, cnt);
                    else
                    {
                        for (u8 i=0; i<cnt; ++i)
                        {
                            PCXData[linestart+lineoffset] = value;
                            lineoffset += 3;

                            if (lineoffset>=3*header.BytesPerLine)
                            {
                                lineoffset=nextmode;
                                if (++nextmode == 3)
                                    nextmode = 0;
                                if (lineoffset == 0)
                                    linestart += 3*header.BytesPerLine;
                            }
                        }
                    }
                }

                s32 pad = std::abs(header.BytesPerLine - width * header.BitsPerPixel / 8) * header.Planes;

                if(header.BitsPerPixel == 8)
                {
                     img = std::make_shared<driver::texture>(math::vec2i{width, height}, driver::TXFMT_RGB);

                     if(header.Planes == 1)
                        convert8BitTo24Bit(PCXData, (u8*)img->getBuffer(), width, height, (u8*)paletteData, pad);

                     if(header.Planes == 3)
                        convert24BitTo24Bit(PCXData, (u8*)img->getBuffer(), width, height, pad);
                }
                else if (header.BitsPerPixel == 4)
                {
                    img = std::make_shared<driver::texture>(math::vec2i{width, height}, driver::TXFMT_LUMINANCE_ALPHA);

                    if (header.Planes == 4)
                        convert4BitTo16Bit(PCXData, (s16*)img->getBuffer(), width, height, paletteData, pad);
                }
                else if (header.BitsPerPixel == 1)
                {
                    img = std::make_shared<driver::texture>(math::vec2i{width, height}, driver::TXFMT_LUMINANCE_ALPHA);

                    if (header.Planes == 4)
                        convert4BitTo16Bit(PCXData, (s16*)img->getBuffer(), width, height, paletteData, pad);

                    if (header.Planes == 1)
                        convert1BitTo16Bit(PCXData, (s16*)img->getBuffer(), width, height, pad);
                }

                delete [] paletteData;
                delete [] PCXData;
            #endif

            return img;
        }

        bool texture_pcx::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_pcx_support
                if(img->getFormat() >= 5)
                    return false;

                pcxheader header;
                header.Manufacturer = 10;
                header.Version = 5;
                header.Encoding = 1;
                header.BitsPerPixel = 8;
                header.XMin = 0;
                header.YMin = 0;
                header.XMax = img->getDimension().x;
                header.XMax = img->getDimension().y;
                header.HorizDPI = 300;
                header.VertDPI = 300;
                header.Reserved = 0;
                header.Planes = 3;
                header.BytesPerLine = header.XMax + header.XMax&0x1;
                header.PaletteType = 1;
                header.HScrSize = 800;
                header.VScrSize = 600;

                std::memset(header.Palette, 0, 48);
                std::memset(header.Filler, 0, 54);

                file->write(&header, sizeof(pcxheader));

                for(u32 i=0; i<img->getDimension().y; ++i)
                {
                    u8 cnt = 0, value = 0;

                    for(u32 j=0; j<3; ++j)
                    {
                        for(u32 k=0; k<img->getDimension().x; ++k)
                        {
                            const auto pixel = img->getPixel({k,i});
                            const char *pix = (char*)&pixel;

                            if(cnt != 0 && cnt<63 && value == pix[j])
                            {
                                ++cnt;
                            }
                            else
                            {
                                if(cnt != 0)
                                {
                                    if(cnt>1 || value&0xc0 ==0xc0)
                                    {
                                        cnt |= 0xc0;
                                        file->put(cnt);
                                    }
                                    file->put(value);
                                }

                                cnt = 1;
                                value = pix[j];
                            }
                        }
                    }

                    if(cnt > 1 || value&0xc0 == 0xc0)
                    {
                        cnt |= 0xc0;
                        file->put(cnt);
                    }

                    file->put(value);
                }

                return true;
            #endif
            return false;
        }

        bool texture_pcx::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "pcx";
        }
    }
}
