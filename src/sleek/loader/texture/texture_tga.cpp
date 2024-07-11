#include "texture_tga.h"
#include "../../driver/texture.h"
#include "../../compile.h"

/* */
/* Supported types: */
/*   */
/*  1 (Uncompressed, color-mapped images) */
/*  2 (RGB uncompressed) */
/*  9 RLE color-mapped */
/* 10 RLE RGB */
/* */

#define ERR_NO_ERROR     0
#define ERR_OPEN         1
#define ERR_READ         2
#define ERR_MEM          3
#define ERR_UNSUPPORTED  4

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static int tgaerror = ERR_NO_ERROR;

namespace sleek
{
    #ifdef texture_loader_tga_support
    inline void convert_16_to_24(const u8 * const src, u8 * const dest) noexcept
    {
        unsigned int t0 = src[0];
        unsigned int t1 = src[1];
        dest[0] = (u8) (t1 & 0x7c) << 1;
        dest[1] = (u8) ((t1 & 0x03) << 6) | ((t0 & 0xe0) >> 2);
        dest[2] = (u8) (t0 & 0x1f) << 3;
    }

    inline void convert_16_to_32(const u8 * const src, u8 * const dest) noexcept
    {
        unsigned int t0 = src[0];
        unsigned int t1 = src[1];
        dest[0] = (u8) (t1 & 0x7c) << 1;
        dest[1] = (u8) ((t1 & 0x03) << 6) | ((t0 & 0xe0) >> 2);
        dest[2] = (u8) (t0 & 0x1f) << 3;
        dest[3] = t1&0x80 ? 255 : 0;
    }

    inline void convert_24_to_24(const u8 * const src, u8 * const dest) noexcept
    {
        dest[0] = src[2];
        dest[1] = src[1];
        dest[2] = src[0];
    }

    inline void convert_32_to_32(const u8 * const src, u8 * const dest) noexcept
    {
        dest[0] = src[2];
        dest[1] = src[1];
        dest[2] = src[0];
        dest[3] = src[3];
    }

    inline void convert_data(const u8 * const src, u8 * const dest, const int x, const int srcformat, const int destformat)
    {
        if (srcformat == 2)
        {
            if (destformat == 3)
                convert_16_to_24(src+x*srcformat,
                    dest+x*destformat);
            else
            {
                assert(destformat == 4);
                convert_16_to_32(src+x*srcformat,
                    dest+x*destformat);
            }
        }
        else if (srcformat == 3)
        {
            assert(destformat == 3);
            convert_24_to_24(src+x*srcformat,
                dest+x*destformat);
        }
        else
        {
            assert(srcformat == 4 && destformat == 4);
            convert_32_to_32(src+x*srcformat,
                dest+x*destformat);
        }
    }

    inline int getInt16(u8 *ptr)
    {
        int res = ptr[0];
        int tmp = ptr[1];
        return res | (tmp<<8);
    }

    inline int getInt24(u8 *ptr)
    {
        int temp1 = ptr[0];
        int temp2 = ptr[1];
        int temp3 = ptr[2];
        return temp1 | (temp2 << 8) | (temp3 << 16);
    }

    inline int getInt32(u8 *ptr)
    {
        int temp1 = ptr[0];
        int temp2 = ptr[1];
        int temp3 = ptr[2];
        int temp4 = ptr[3];
        return temp1 | (temp2 << 8) | (temp3 << 16) | (temp4 << 24);
    }

    inline void rle_new_packet(u8 ** src, int * rleRemaining, int * rleIsCompressed, u8 *rleCurrent, const int rleEntrySize)
    {
        int i;
        u8 code = *(*src)++;
        *rleRemaining = (code & 127) + 1;

        if (code & 128)
        {
            *rleIsCompressed = 1;
            for (i = 0; i < rleEntrySize; i++)
                rleCurrent[i] = *(*src)++;
        }
        else *rleIsCompressed = 0;
    }

    inline void rle_decode(u8 ** src, u8 *dest, const int numbytes, int * rleRemaining, int * rleIsCompressed, u8 *rleCurrent, const int rleEntrySize)
    {
        int i;
        int size = rleEntrySize;
        u8 *stop = dest + numbytes;
        while (dest < stop)
        {
            if (*rleRemaining == 0)  /* start new packet */
                rle_new_packet(src, rleRemaining, rleIsCompressed,
                    rleCurrent, rleEntrySize);

            if (*rleIsCompressed)
            {
                for (i = 0; i < size; i++)
                {
                    *dest++ = rleCurrent[i];
                }
            }
            else
            {
                for (i = 0; i < size; i++)
                {
                    *dest++ = *(*src)++;
                }
            }
            // original code : *rleRemaining)--;
            (*rleRemaining)--;
        }
    }

    unsigned char *simage_tga_load(io::filereader *fin, int *width_ret, int *height_ret, int *numComponents_ret)
    {
        unsigned char header[18];
        int type;
        int width;
        int height;
        int depth;
        int flags;
        int format;
        unsigned char *colormap;
        int colormapLen = 0;
        int indexsize = 0;
        int rleIsCompressed;
        int rleRemaining;
        int rleEntrySize;
        unsigned char rleCurrent[4];
        unsigned char *buffer;
        unsigned char *dest;
        int bpr;
        unsigned char *linebuf;

        tgaerror = ERR_NO_ERROR;     /* clear error */

        fin->read((char*)header,18);

        type = header[2];
        width = getInt16(&header[12]);
        height = getInt16(&header[14]);
        depth = header[16] >> 3;
        flags = header[17];

        /* check for reasonable values in case this is not a tga file */
        if ((type != 1 && type != 2 && type != 10) ||
            (width < 0 || width > 4096) ||
            (height < 0 || height > 4096) ||
            (depth < 1 || depth > 4))
        {
            tgaerror = ERR_UNSUPPORTED;
            return NULL;
        }

        if (header[0])               /* skip identification field */
            fin->seek(header[0], true);

        colormap = NULL;
        if (header[1] == 1)          /* there is a colormap */
        {
            colormapLen = getInt16(&header[5]);
            indexsize = header[7]>>3;
            colormap = new unsigned char [colormapLen*indexsize];
            fin->read((char*)colormap,colormapLen*indexsize);

            if (indexsize == 2)          /* 16 bits */
            {
                if (flags & 1) format = 4;
                else format = 3;
            }
            else
                format = indexsize;
        }
        else
        {
            if (depth == 2)              /* 16 bits */
            {
                if (flags & 1) format = 4;
                else format = 3;
            }
            else format = depth;
        }

        rleIsCompressed = 0;
        rleRemaining = 0;
        rleEntrySize = depth;
        buffer = new unsigned char [width*height*format];
        dest = buffer;
        bpr = format * width;
        linebuf = new unsigned char [width*depth];

        //check the intended image orientation
        bool bLeftToRight = (flags&0x10)==0;
        bool bTopToBottom = (flags&0x20)!=0;
        int lineoffset = bTopToBottom ? -bpr : bpr;
        if (bTopToBottom) //move start point to last line in buffer
            dest += (bpr*(height-1));

        switch(type)
        {
            case 1:                  /* colormap, uncompressed */
            {
                if (colormapLen == 0 || indexsize == 0)
                {
                    tgaerror = ERR_UNSUPPORTED; /* colormap missing or empty */

                    if (colormap) delete [] colormap;
                    delete [] buffer;
                    delete [] linebuf;

                    return NULL;
                }
                unsigned char * formattedMap = new unsigned char[colormapLen * format];
                for (int i = 0; i < colormapLen; i++)
                {
                    convert_data(colormap, formattedMap, i, indexsize, format);
                }

                int x, y;
                for (y = 0; y < height; y++)
                {
                    fin->read((char*)linebuf, width*depth);
                    for (x = 0; x < width; x++)
                    {
                        int index;
                        switch (depth)
                        {
                            case 1:
                                index = linebuf[x];
                            break;
                            case 2:
                                index = getInt16(linebuf + x * 2);
                            break;
                            case 3:
                                index = getInt24(linebuf + x * 3);
                            break;
                            case 4:
                                index = getInt32(linebuf + x * 4);
                            break;
                            default:
                                tgaerror = ERR_UNSUPPORTED;
                                delete [] formattedMap;
                            return NULL;
                        }

                        int adjustedX = bLeftToRight ? x : (width - 1) - x;
                        for (int i = 0; i < format; i++)
                            (dest + adjustedX * format)[i] = (formattedMap + index * format)[i];
                    }
                    dest += lineoffset;
                }

                delete [] formattedMap;
            }
            break;
            case 2:                  /* RGB, uncompressed */
            {
                int x, y;
                for (y = 0; y < height; y++)
                {
                    fin->read((char*)linebuf,width*depth);
                    for (x = 0; x < width; x++)
                        convert_data(linebuf, dest, bLeftToRight ? x : (width-1) - x, depth, format);
                    dest += lineoffset;
                }
            }
            break;
            case 10:                 /* RGB, compressed */
            {
                int size, x, y;
                size = fin->size();

                unsigned char* buf = new unsigned char [size];
                if (buf == NULL)
                {
                    tgaerror = ERR_MEM;
                    break;
                }
                unsigned char* src = buf;

                fin->read((char*)buf,size);

                for (y = 0; y < height; y++)
                {
                    rle_decode(&src, linebuf, width*depth, &rleRemaining,
                        &rleIsCompressed, rleCurrent, rleEntrySize);
                    assert(src <= buf + size);
                    for (x = 0; x < width; x++)
                    {
                        convert_data(linebuf, dest,  bLeftToRight ? x : (width-1) - x, depth, format);
                    }
                    dest += lineoffset;
                }

                if (buf) delete [] buf;
            }
            break;
            default:
                tgaerror = ERR_UNSUPPORTED;
        }

        if (linebuf) delete [] linebuf;
        if (colormap) delete [] colormap;

        if (tgaerror)
        {
            if (buffer) delete [] buffer;
            return NULL;
        }

        *width_ret = width;
        *height_ret = height;
        *numComponents_ret = format;
        return buffer;
    }
    #endif

    namespace loader
    {
        std::shared_ptr<driver::texture> textureloader_tga::read(io::filereader *file) const noexcept
        {
            std::shared_ptr<driver::texture> img = nullptr;

            #ifdef texture_loader_tga_support
                unsigned char *data = NULL;
                int width;
                int height;
                int componant;

                data = simage_tga_load(file, &width,&height,&componant);

                if(!data)
                    return nullptr;

                img = std::make_shared<driver::texture>(math::vec2u{width, height}, (driver::TextureFormat)componant, data);
            #endif

            return img;
        }

        bool texturewriter_tga::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_tga_support
                //! no floating texture supported
                if(img->getFormat() >= 5)
                    return false;

                unsigned int pixelFormat = img->getFormat();
                int width = img->getDimension().x;
                int height = img->getDimension().y;
                int numPerPixel = img->getComposantCount();
                int pixelMultiplier = img->getPitch();

                // Headers
                file->put(0); // Identification field size
                file->put(0); // Color map type
                file->put(2); // Image type
                file->put(0);
                file->put(0); // Color map origin
                file->put(0);
                file->put(0); // Color map length
                file->put(0); // Color map entry size
                file->put(0);
                file->put(0); // X origin of image
                file->put(0);
                file->put(0); // Y origin of image

                file->put((width>>0)&0xff);
                file->put((width>>8)&0xff);  // Width of image
                file->put((height>>0)&0xff);
                file->put((height>>8)&0xff); // Height of image
                file->put(numPerPixel * 8);  // Image pixel size
                file->put(0);                // Image descriptor

                // Swap red/blue channels for BGR images
                int r = 0, g = 1, b = 2;

                // Data
                for(int y=0; y<height; ++y)
                {
                    const u8 *ptr = img->getBuffer() + img->indexof({0,y});

                    for(int x=0; x<width; ++x)
                    {
                        int off = x * numPerPixel;

                        switch(numPerPixel)
                        {
                            case 1:  // LUINANCE
                                file->put(ptr[off] * pixelMultiplier);
                            break;
                            case 2:  // LUMINANCE_ALPHA
                                file->put(ptr[off]   * pixelMultiplier);
                                file->put(ptr[off+1] * pixelMultiplier);
                            break;
                            case 3:  // RGB
                                file->put(ptr[off+b] * pixelMultiplier);
                                file->put(ptr[off+g] * pixelMultiplier);
                                file->put(ptr[off+r] * pixelMultiplier);
                            break;
                            case 4:  // RGBA
                                file->put(ptr[off+b] * pixelMultiplier);
                                file->put(ptr[off+g] * pixelMultiplier);
                                file->put(ptr[off+r] * pixelMultiplier);
                                file->put(ptr[off+3] * pixelMultiplier);
                            break;
                            default:
                                return false;
                        }
                    }
                }

                return true;
            #endif

            return false;
        }

        bool texturemime_tga::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "tga" || extention == "icb" || extention == "vda" || extention == "vst";
        }
    }
}
