#include "texture_png.h"
#include "../../driver/texture.h"
#include "../../compile.h"
#include <stdlib.h>
#include <png.h>

extern "C" {
    void* memccpy(void *dest, const void *src, int c, size_t n);
}

namespace sleek
{
    namespace loader
    {
        #ifdef texture_loader_png_support
        static void png_cpexcept_error(png_structp png_ptr, png_const_charp msg)
        {
            printf("PNG fatal error: %s", msg);
            longjmp(png_jmpbuf(png_ptr), 1);
        }

        // PNG function for warning handling
        static void png_cpexcept_warn(png_structp png_ptr, png_const_charp msg)
        {
            printf("PNG warning: %s", msg);
        }

        void PNGAPI user_read_data_fcn(png_structp png_ptr, png_bytep data, png_size_t length)
        {
            io::filereader *file = (io::filereader*)png_get_io_ptr(png_ptr);
            int pos = file->pos();
            file->read((char*)data,(u32)length);

            if((file->pos()-pos) != length)
                png_error(png_ptr, "Read Error");
        }

        void PNGAPI user_write_data_fcn(png_structp png_ptr, png_bytep data, png_size_t length)
        {
            io::filewriter *file = (io::filewriter*)png_get_io_ptr(png_ptr);
            file->write((char*)data,(u32)length);
        }
        #endif

        int textureloader_png::check_header(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_png_support
                png_byte magic[8];
                file->read(magic, sizeof(magic));
                return -!png_check_sig(magic, sizeof (magic));
            #endif
            return -1;
        }

        std::shared_ptr<driver::texture> textureloader_png::read(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_png_support
                png_byte magic[8];
                png_structp png_ptr;
                png_infop info_ptr;
                int bit_depth = 0, color_type = 0;
                png_bytep *row_pointers = 0;
                png_uint_32 w = 0, h = 0;
                GLubyte *texels = 0;

                file->read(magic, sizeof(magic));

                if(!png_check_sig(magic, sizeof (magic)))
                    return nullptr;

                png_ptr = png_create_read_struct(
                    PNG_LIBPNG_VER_STRING, NULL,
                    (png_error_ptr)png_cpexcept_error,
                    (png_error_ptr)png_cpexcept_warn
                );

                if(!png_ptr)
                    return nullptr;

                info_ptr = png_create_info_struct(png_ptr);
                if(!info_ptr || setjmp(png_jmpbuf(png_ptr)))
                {
                    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
                    if(row_pointers)
                        free(row_pointers);
                    return nullptr;
                }

                png_set_read_fn(png_ptr, file, user_read_data_fcn);
                png_set_sig_bytes(png_ptr, sizeof (magic));
                png_read_info(png_ptr, info_ptr);

                bit_depth = png_get_bit_depth(png_ptr, info_ptr);
                color_type = png_get_color_type(png_ptr, info_ptr);

                if(color_type == PNG_COLOR_TYPE_PALETTE)
                    png_set_palette_to_rgb(png_ptr);

                if(bit_depth < 8)
                {
                    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                        png_set_expand_gray_1_2_4_to_8(png_ptr);
                    else png_set_packing(png_ptr);
                }

                if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
                    png_set_tRNS_to_alpha(png_ptr);

                if(bit_depth == 16)
                    png_set_strip_16(png_ptr);

                if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                    png_set_gray_to_rgb(png_ptr);

                //! internal png format change to bgr/rgb
                png_set_bgr(png_ptr);

                png_read_update_info(png_ptr, info_ptr);
                png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, 0, 0, 0);

                int internalFormat = 0;
                if(color_type == PNG_COLOR_TYPE_GRAY)       internalFormat = driver::TXFMT_LUMINANCE;
                if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA) internalFormat = driver::TXFMT_LUMINANCE_ALPHA;
                if(color_type == PNG_COLOR_TYPE_RGB)        internalFormat = driver::TXFMT_RGB;
                if(color_type == PNG_COLOR_TYPE_RGB_ALPHA)  internalFormat = driver::TXFMT_RGBA;

                texels = (GLubyte*)malloc(sizeof(GLubyte)*w*h*internalFormat);
                row_pointers = new png_bytep[h];

                // vertival flip or not ? comment = not
                //for(register unsigned int i = 0; i < h; ++i) row_pointers[i] = (png_bytep)(texels+(i*w*internalFormat));
                for(register unsigned int i = 0; i < h; ++i) row_pointers[i] = (png_bytep)(texels+((h-(i+1))*w*internalFormat));

                png_read_image(png_ptr, row_pointers);
                png_read_end(png_ptr, 0);
                png_destroy_read_struct(&png_ptr, &info_ptr, 0);
                delete row_pointers;

                auto tmp = std::make_shared<driver::texture>(math::vec2i(w, h), (driver::TextureFormat)internalFormat);
                memccpy(tmp->getBuffer(), (u8*)texels, 1, tmp->getBufferSize());

                tmp->flipVertical();

                return tmp;
            #else
                return nullptr;
            #endif
        }

        bool textureloader_png::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_png_support
                //! no floating texture supported
                if(img->getFormat() >= 5)
                    return false;

                png_structp p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
                png_infop info_ptr = png_create_info_struct(p);

                static const int png_color_type[] = {
                    PNG_COLOR_TYPE_GRAY,
                    PNG_COLOR_TYPE_GRAY_ALPHA,
                    PNG_COLOR_TYPE_RGB,
                    PNG_COLOR_TYPE_RGB_ALPHA
                };

                png_set_IHDR(
                    p, info_ptr,
                    img->getDimension().x,
                    img->getDimension().y,
                    8, png_color_type[img->getComposantCount()],
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT
                );

                std::vector<u8*> rows(img->getDimension().y);
                for (size_t y = 0; y<img->getDimension().y; ++y)
                    rows[y] = img->getBuffer() + img->indexof({0,y});

                png_set_rows(p, info_ptr, &rows[0]);
                png_set_write_fn(p, file, user_write_data_fcn, NULL);
                png_write_png(p, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
                png_destroy_write_struct(&p, NULL);

                return true;
            #endif
            return false;
        }

        bool textureloader_png::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "png" || extention == "jng" || extention == "mnj" || extention == "apng";
        }
    }
}
