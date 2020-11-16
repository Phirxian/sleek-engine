#include "decompres_dxt.h"
#include "texture_blp.h"
#include "../../driver/texture.h"
#include "../../compile.h"
#include <iostream>
#include <cstring>

#ifdef texture_loader_jpeg_support
    #include <jpeglib.h>
    #include <exception>
#endif

namespace sleek
{
    namespace loader
    {
        int textureloader_blp::check_header(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_blp_support
                char magic[4];
                file->read(magic, 4);
                bool mimetest = magic[0] == 'B' && magic[1] == 'L' && magic[2] == 'P' &&  std::isalnum(magic[3]);
                return mimetest ? magic[3] : -1;
            #endif
            return -1;
        }

        std::shared_ptr<driver::texture> textureloader_blp::read(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_blp_support
                int version = check_header(file);

                if(version < 0)
                    return nullptr;

                sharedheader shd;

                if(version < '2')
                {
                    blpheader_v1 header;
                    file->read(&header, sizeof(blpheader_v1));

                    shd.compression = header.compression;
                    shd.flags = header.flags;
                    shd.width = header.width;
                    shd.height = header.height;
                    shd.alpha_depth = header.alpha_depth;

                    for(int i = 0; i<16; ++i)
                    {
                        shd.mipmap_offsets[i] = header.mipmap_offsets[i];
                        shd.mipmap_lengths[i] = header.mipmap_lengths[i];
                    }
                }
                else
                {
                    blpheader_v2 header;
                    file->read(&header, sizeof(blpheader_v2));

                    shd.flags = header.alpha_type;
                    shd.width = header.width;
                    shd.height = header.height;
                    shd.alpha_depth = header.alpha_depth;

                    for(int i = 0; i<16; ++i)
                    {
                        shd.mipmap_offsets[i] = header.mipmap_offsets[i];
                        shd.mipmap_lengths[i] = header.mipmap_lengths[i];
                    }

                    if(header.type == 0)
                        shd.compression = JPG;
                    else
                    {
                        switch(header.compression)
                        {
                            case 1:  shd.compression = BLP; break;
                            case 2:  shd.compression = DXT; break;
                            default: shd.compression = RAW; break;
                        }
                        shd.flags = header.alpha_depth;
                    }
                }

                // only the first mipmap is loader, other can be generated by the engine

                switch(shd.compression)
                {
                    case JPG:
                    {
                        u32 jpegHeaderSize = 0;
                        file->read(&jpegHeaderSize, 4);
                        char *data = new char[shd.mipmap_lengths[0] + jpegHeaderSize];
                        file->read(data, jpegHeaderSize);
                        file->seek(shd.mipmap_offsets[0]);
                        file->read(data+jpegHeaderSize, shd.mipmap_lengths[0]);
                        return decompressJpg(shd, data, shd.mipmap_lengths[0] + jpegHeaderSize);
                    }
                    break;
                    case BLP:
                    {
                        file->read(shd.palette, 256*sizeof(u32));
                        for(int i = 0; i<256; ++i)
                        {
                            // from rgba
                            math::pixel c = shd.palette[i];
                            shd.palette[i] = math::pixel(
                                255-c.getRed(),
                                c.getGreen(),
                                c.getBlue(),
                                c.getAlpha()
                            ).toInt();
                        }
                        file->seek(shd.mipmap_offsets[0]);
                        char *data = new char[shd.mipmap_lengths[0]];
                        file->read(data, shd.mipmap_lengths[0]);
                        return decompressBLP(shd, data, shd.mipmap_lengths[0]);
                    }
                    break;
                    case DXT:
                    {
                        file->seek(shd.mipmap_offsets[0]);
                        char *data = new char[shd.mipmap_lengths[0]];
                        file->read(data, shd.mipmap_lengths[0]);
                        return decompressDXT(shd, data, shd.mipmap_lengths[0]);
                    }
                    break;
                    default:
                    {
                        file->seek(shd.mipmap_offsets[0]);
                        char *data = new char[shd.mipmap_lengths[0]];
                        file->read(data, shd.mipmap_lengths[0]);
                        return decompressRaw(shd, data, shd.mipmap_lengths[0]);
                    }
                    break;
                }

                return 0;
            #else
                return nullptr;
            #endif
        }

        bool textureloader_blp::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_blp_support
                //! no floating texture support
                if(img->getFormat() >= 5)
                    return false;

                char blpid[] = "BLP2";
                file->write(blpid, 4);

                blpheader_v2 header;
                header.type = 1;
                header.compression = 1; // RAW
                header.alpha_depth = 8;
                header.alpha_type = 8;
                header.has_mips = 0;
                header.width = img->getDimension().x;
                header.height = img->getDimension().y;

                std::memset(header.mipmap_lengths, 0u, 16*sizeof(sleek::u32));
                std::memset(header.mipmap_offsets, 0u, 16*sizeof(sleek::u32));
                header.mipmap_offsets[0] = sizeof(blpheader_v2)+4;
                header.mipmap_lengths[0] = header.width*header.height*4;

                file->write(&header, sizeof(blpheader_v2));

                math::vec2u pos;
                for(;pos.y < img->getDimension().y; ++pos.y)
                {
                    for(;pos.x < img->getDimension().x; ++pos.x)
                    {
                        math::pixel tmp = img->getPixel(pos);
                        file->write(&tmp, 4);
                    }
                }

                return true;
            #endif
            return false;
        }

        bool textureloader_blp::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "blp";
        }

        std::shared_ptr<driver::texture> textureloader_blp::decompressBLP(const sharedheader &header, char *data, size_t size) const
        {
            auto img = std::make_shared<driver::texture>(
                math::vec2i(header.width, header.height)
            );

            for(int height = 0; height < header.height; ++height)
            {
                for(int width = 0; width < header.width; ++width)
                {
                    unsigned char index = (unsigned char)data[width + header.width*height];
                    img->setPixel({width, height}, math::pixel(header.palette[index]));
                }
            }

            if(header.alpha_depth == 3 || header.alpha_depth == 4)
            {
                char *alpha = data + header.width*header.height;
                math::vec2u pos;

                for(; pos.y < header.height; ++pos.y)
                {
                    for(; pos.x < header.width; ++pos.x)
                    {
                        math::pixel c(img->getPixel(pos));
                        c.setAlpha(alpha[pos.x + header.width*pos.y]);
                        img->setPixel(pos, c);
                    }
                }
            }

            delete [] data;
            return img;
        }

        std::shared_ptr<driver::texture> textureloader_blp::decompressDXT(const sharedheader &header, char *data, size_t size) const
        {
            std::shared_ptr<driver::texture> img = nullptr;

            //TODO: untested section

            if(header.flags == 0)
            {
                img = std::make_shared<driver::texture>(math::vec2i(header.width, header.height), driver::TXFMT_RGBA);
                BlockDecompressImageDXT1(header.width, header.height, (const unsigned char*)data, (unsigned long*)img->getBuffer());
            }
            else if(header.flags == 1)
            {
                std::cout << "blp error >> unsupported DXT3 texture" << std::endl;
            }
            else if(header.flags == 7)
            {
                img = std::make_shared<driver::texture>(math::vec2i(header.width, header.height), driver::TXFMT_RGBA);
                BlockDecompressImageDXT5(header.width, header.height, (const unsigned char*)data, (unsigned long*)img->getBuffer());
            }
            else
            {
                std::cout << "blp error >> unknow DXT compressioon" << std::endl;
            }

            delete [] data;
            return img;
        }

        std::shared_ptr<driver::texture> textureloader_blp::decompressRaw(const sharedheader &header, char *data, size_t size) const
        {
            auto img = std::make_shared<driver::texture>(
                math::vec2i(header.width, header.height),
                header.alpha_depth == 0 ?
                  driver::TXFMT_RGB :
                  driver::TXFMT_RGBA,
                (u8*)data
            );

            return img;
        }

        std::shared_ptr<driver::texture> textureloader_blp::decompressJpg(const sharedheader &header, char *buffer, size_t size) const
        {
            std::shared_ptr<driver::texture> img = nullptr;

            #ifdef texture_loader_jpeg_support
                struct jpeg_error_mgr jerr;
                struct jpeg_decompress_struct cinfo;
                cinfo.err = jpeg_std_error(&jerr);
                jpeg_create_decompress(&cinfo);

                jpeg_mem_src(&cinfo, (unsigned char*)buffer, size);

                if(jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK || !jpeg_start_decompress(&cinfo))
                {
                    jpeg_finish_decompress(&cinfo);
                    jpeg_destroy_decompress(&cinfo);
                    return 0;
                }

                img = std::make_shared<driver::texture>(
                    math::vec2i(cinfo.image_width, cinfo.image_height),
                    (driver::TextureFormat)cinfo.num_components
                );

                const JDIMENSION requiredScanlines = cinfo.output_height;
                const JDIMENSION scanlineSize = cinfo.output_width * cinfo.output_components;

                JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, scanlineSize, requiredScanlines);

                while(cinfo.output_scanline < cinfo.output_height)
                {
                    const JDIMENSION currentScanline = cinfo.output_scanline;
                    const JDIMENSION dimension = jpeg_read_scanlines(&cinfo, scanlines, requiredScanlines);

                    for(int height = 0; height < dimension; ++height)
                    {
                        int width = 0;
                        for(int component = 0; component < scanlineSize; component += cinfo.output_components)
                        {
                            u32 argb = ((u32)scanlines[height][component]) |
                                       ((u32)scanlines[height][component + 1] << 8) |
                                       ((u32)scanlines[height][component + 2] << 16);

                            if(cinfo.output_components == 4)
                                argb |= ((u32)(scanlines[height][component + 3]) << 24);

                            img->setPixel({width, height + currentScanline}, argb);
                            ++width;
                        }
                    }
                }

                jpeg_finish_decompress(&cinfo);
                jpeg_destroy_decompress(&cinfo);
            #endif

            delete [] buffer;
            return img;
        }
    }
}