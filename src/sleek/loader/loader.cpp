#include "loader.h"
#include "../driver/texture.h"
#include "../driver/mesh.h"
#include "../compile.h"

#include "mesh/mesh_3ds.h"
#include "mesh/mesh_txt.h"
#include "mesh/mesh_obj.h"
#include "texture/texture_bmp.h"
#include "texture/texture_png.h"
#include "texture/texture_jpg.h"
#include "texture/texture_tiff.h"
#include "texture/texture_pgm.h"
#include "texture/texture_tga.h"
#include "texture/texture_blp.h"
#include "texture/texture_pcx.h"
#include <iostream>

namespace sleek
{
    namespace loader
    {
        static std::shared_ptr<driver::mesh> debug_texture(const std::shared_ptr<driver::mesh> &ptr, const char *filename)
        {
            std::cout << "Mesh \"" << filename << "\" ";
            if(ptr)
            {
                std::cout
                    << "\t triangle{" << ptr->indices.size() << "}"
                    << "\t attribut{" << ptr->datas.size() << "}"
                    << std::endl;
            }
            else
            {
                std::cout << "failed to load" << std::endl;
            }
            return ptr;
        }
        
        static std::shared_ptr<driver::texture> debug_texture(const std::shared_ptr<driver::texture> &ptr, const char *filename)
        {
            std::cout << "Texture \"" << filename << "\" ";
            if(ptr)
            {
                std::cout
                    << "\t vec2{" << ptr->getDimension().x << ", " << ptr->getDimension().y << "}"
                    << "\t bits{" << ptr->getPitch()*8 << "}"
                    << "\t format{" << driver::TextureFormatName[ptr->getFormat()-1] << "}"
                    << std::endl;
                //ptr->filename = filename;
            }
            else
            {
                std::cout << "failed to load" << std::endl;
            }
            return ptr;
        }

        static std::shared_ptr<driver::mesh> debug_mesh(const std::shared_ptr<driver::mesh> &ptr, const char *filename)
        {
            std::cout << "Texture \"" << filename << "\" ";
            if(ptr)
            {
                std::cout
                    << "\t vertices{" << ptr->vertices.size() << "}"
                    << "\t indices{" << ptr->indices.size() << "}"
                    << "\t attributes{" << ptr->datas.size() << "}"
                    << std::endl;
                //ptr->filename = filename;
            }
            else
            {
                std::cout << "failed to load" << std::endl;
            }
            return ptr;
        }

        loader::loader(std::shared_ptr<io::filesystem> f)
            : fs(f)
        {
            if(!fs)
            {
                std::cerr << "error >> loader with nullptr as filesystem" << std::endl;
            }
            else
            {
                #ifdef texture_loader_blp_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_blp>(), std::make_unique<textureloader_blp>()));
                wtexture.push_back(std::make_pair(std::make_unique<texturemime_blp>(), std::make_unique<texturewriter_blp>()));
                #endif

                #ifdef texture_loader_bmp_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_bmp>(), std::make_unique<textureloader_bmp>()));
                wtexture.push_back(std::make_pair(std::make_unique<texturemime_bmp>(), std::make_unique<texturewriter_bmp>()));
                #endif

                #ifdef texture_loader_jpeg_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_jpg>(), std::make_unique<textureloader_jpg>()));
                wtexture.push_back(std::make_pair(std::make_unique<texturemime_jpg>(), std::make_unique<texturewriter_jpg>()));
                #endif

                #ifdef texture_loader_pcx_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_pcx>(), std::make_unique<textureloader_pcx>()));
                wtexture.push_back(std::make_pair(std::make_unique<texturemime_pcx>(), std::make_unique<texturewriter_pcx>()));
                #endif

                #ifdef texture_loader_pgm_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_pgm>(), std::make_unique<textureloader_pgm>()));
                wtexture.push_back(std::make_pair(std::make_unique<texturemime_pgm>(), std::make_unique<texturewriter_pgm>()));
                #endif

                #ifdef texture_loader_png_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_png>(), std::make_unique<textureloader_png>()));
                wtexture.push_back(std::make_pair(std::make_unique<texturemime_png>(), std::make_unique<texturewriter_png>()));
                #endif

                #ifdef texture_loader_tga_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_tga>(), std::make_unique<textureloader_tga>()));
                wtexture.push_back(std::make_pair(std::make_unique<texturemime_tga>(), std::make_unique<texturewriter_tga>()));
                #endif

                #ifdef texture_loader_tiff_support
                rtexture.push_back(std::make_pair(std::make_unique<texturemime_tiff>(), std::make_unique<textureloader_tiff>()));
                // unsupported write
                #endif

                #ifdef mesh_loader_3ds_support
                rmesh.push_back(std::make_pair(std::make_unique<meshmime_3ds>(), std::make_unique<meshloader_3ds>()));
                // unsupported write
                #endif

                #ifdef mesh_loader_txt_support
                rmesh.push_back(std::make_pair(std::make_unique<meshmime_txt>(), std::make_unique<meshloader_txt>()));
                wmesh.push_back(std::make_pair(std::make_unique<meshmime_txt>(), std::make_unique<meshwriter_txt>()));
                #endif

                #ifdef mesh_loader_obj_support
                rmesh.push_back(std::make_pair(std::make_unique<meshmime_obj>(), std::make_unique<meshloader_obj>()));
                wmesh.push_back(std::make_pair(std::make_unique<meshmime_obj>(), std::make_unique<meshwriter_obj>()));
                #endif
            }
        }
        loader::~loader()
        {
            // unique_ptr automatically handles cleanup, no manual deletion needed
        }
        std::shared_ptr<driver::mesh> loader::loadMesh(const std::string &filename) const noexcept
        {
            for(const auto& e : rmesh)
            {
                if(e.first->match(filename))
                {
                    auto loader = e.second.get();
                    auto file = fs->read(filename);
                    auto mesh = file ? loader->read(file.get()) : nullptr;
                    debug_mesh(mesh, filename.c_str());
                    return mesh;
                }
            }

            std::cout << "no matching loader for " << filename << std::endl;
            return nullptr;
        }
        std::shared_ptr<driver::texture> loader::loadTexture(const std::string &filename) const noexcept
        {
            for(const auto& e : rtexture)
            {
                if(e.first->match(filename))
                {
                    auto loader = e.second.get();
                    auto file = fs->read(filename);
                    auto texture = file ? loader->read(file.get()) : nullptr;
                    debug_texture(texture, filename.c_str());
                    return texture;
                }
            }

            std::cout << "no matching loader for " << filename << std::endl;
            return nullptr;
        }
        bool loader::writeMesh(std::shared_ptr<driver::mesh> data, const std::string &filename) const noexcept
        {
            if(!data)
                return false;

            for(const auto& e : wmesh)
            {
                if(e.first->match(filename))
                {
                    auto writer = e.second.get();
                    auto file = fs->write(filename);
                    return file ? writer->write(data.get(), file.get()) : false;
                    // if false, file should be deleted ?
                }
            }

            return false;
        }
        bool loader::writeTexture(std::shared_ptr<driver::texture> data, const std::string &filename) const noexcept
        {
            if(!data)
                return false;

            for(const auto& e : wtexture)
            {
                if(e.first->match(filename))
                {
                    auto writer = e.second.get();
                    auto file = fs->write(filename);
                    return file ? writer->write(data.get(), file.get()) : false;
                }
            }

            return false;
        }
    }
}
