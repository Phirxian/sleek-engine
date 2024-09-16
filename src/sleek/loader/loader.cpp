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
        static std::shared_ptr<driver::mesh> debug(const std::shared_ptr<driver::mesh> &ptr, const char *filename)
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
        static std::shared_ptr<driver::texture> debug(const std::shared_ptr<driver::texture> &ptr, const char *filename)
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
                rtexture.push_back(std::make_pair(new texturemime_blp(), new textureloader_blp()));
                wtexture.push_back(std::make_pair(new texturemime_blp(), new texturewriter_blp()));
                #endif

                #ifdef texture_loader_bmp_support
                rtexture.push_back(std::make_pair(new texturemime_bmp(), new textureloader_bmp()));
                wtexture.push_back(std::make_pair(new texturemime_bmp(), new texturewriter_bmp()));
                #endif

                #ifdef texture_loader_jpeg_support
                rtexture.push_back(std::make_pair(new texturemime_jpg(), new textureloader_jpg()));
                wtexture.push_back(std::make_pair(new texturemime_jpg(), new texturewriter_jpg()));
                #endif

                #ifdef texture_loader_pcx_support
                rtexture.push_back(std::make_pair(new texturemime_pcx(), new textureloader_pcx()));
                wtexture.push_back(std::make_pair(new texturemime_pcx(), new texturewriter_pcx()));
                #endif

                #ifdef texture_loader_pgm_support
                rtexture.push_back(std::make_pair(new texturemime_pgm(), new textureloader_pgm()));
                wtexture.push_back(std::make_pair(new texturemime_pgm(), new texturewriter_pgm()));
                #endif

                #ifdef texture_loader_png_support
                rtexture.push_back(std::make_pair(new texturemime_png(), new textureloader_png()));
                wtexture.push_back(std::make_pair(new texturemime_png(), new texturewriter_png()));
                #endif

                #ifdef texture_loader_tga_support
                rtexture.push_back(std::make_pair(new texturemime_tga(), new textureloader_tga()));
                wtexture.push_back(std::make_pair(new texturemime_tga(), new texturewriter_tga()));
                #endif

                #ifdef texture_loader_tiff_support
                rtexture.push_back(std::make_pair(new texturemime_tiff(), new textureloader_tiff()));
                // unsupported write
                #endif

                #ifdef mesh_loader_3ds_support
                rmesh.push_back(std::make_pair(new meshmime_3ds(), new meshloader_3ds()));
                // unsupported write
                #endif

                #ifdef mesh_loader_txt_support
                rmesh.push_back(std::make_pair(new meshmime_txt(), new meshloader_txt()));
                wmesh.push_back(std::make_pair(new meshmime_txt(), new meshwriter_txt()));
                #endif

                #ifdef mesh_loader_obj_support
                rmesh.push_back(std::make_pair(new meshmime_obj(), new meshloader_obj()));
                wmesh.push_back(std::make_pair(new meshmime_obj(), new meshwriter_obj()));
                #endif
            }
        }
        loader::~loader()
        {
            for(auto e : rtexture)
            {
                delete e.first;
                delete e.second;
            }

            for(auto e : rmesh)
            {
                delete e.first;
                delete e.second;
            }

            for(auto e : wmesh)
            {
                delete e.first;
                delete e.second;
            }

            for(auto e : wtexture)
            {
                delete e.first;
                delete e.second;
            }
        }
        std::shared_ptr<driver::mesh> loader::loadMesh(const std::string &filename) const noexcept
        {
            for(auto e : rmesh)
            {
                if(e.first->match(filename))
                {
                    auto loader = e.second;
                    auto file = fs->read(filename);
                    auto mesh = file ? loader->read(file.get()) : nullptr;
                    debug(mesh, filename.c_str());
                    return mesh;
                }
            }

            std::cout << "no matching loader for " << filename << std::endl;
            return nullptr;
        }
        std::shared_ptr<driver::texture> loader::loadTexture(const std::string &filename) const noexcept
        {
            for(auto e : rtexture)
            {
                if(e.first->match(filename))
                {
                    auto loader = e.second;
                    auto file = fs->read(filename);
                    auto texture = file ? loader->read(file.get()) : nullptr;
                    debug(texture, filename.c_str());
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

            for(auto e : wmesh)
            {
                if(e.first->match(filename))
                {
                    auto writer = e.second;
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

            for(auto e : wtexture)
            {
                if(e.first->match(filename))
                {
                    auto writer = e.second;
                    auto file = fs->write(filename);
                    return file ? writer->write(data.get(), file.get()) : false;
                }
            }

            return false;
        }
    }
}
