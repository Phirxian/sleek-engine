#include "mesh_3ds.h"
#include "../../driver/mesh.h"
#include "../../compile.h"
#include <sys/stat.h>

namespace sleek
{
    namespace loader
    {
        long filelenght(int f) noexcept
        {
            struct stat buf;
            fstat(f, &buf);
            return buf.st_size;
        }
        std::shared_ptr<driver::mesh> meshloader_3ds::read(io::filereader *file) const noexcept
        {
            #ifdef mesh_loader_3ds_support
            unsigned char lchar = 0;
            unsigned int lchunk_lenght = 0;
            unsigned short lchunk_id = 0, lqty = 0, lface_flags = 0;

            auto tmp = std::make_shared<driver::mesh>();
            while(file->pos() < 200)
            {
                file->read(&lchunk_id, 2);
                file->read(&lchunk_lenght, 4);

                switch (lchunk_id)
                {
                    case 0x4d4d: break;
                    case 0x3d3d: break;
                    case 0x4000: break;
                    case 0x4100: break;
                    case 0x4110:
                        file->read(&lqty, sizeof(unsigned short));
                        tmp->vertices.resize(lqty);

                        for(u32 i = 0; i < lqty; i++)
                        {
                            file->read(&tmp->vertices[i].Pos.x, sizeof(f32));
                            file->read(&tmp->vertices[i].Pos.y, sizeof(f32));
                            file->read(&tmp->vertices[i].Pos.z, sizeof(f32));
                        }
                    break;
                    case 0x4120:
                        file->read(&lqty, sizeof(unsigned short));
                        tmp->indices.resize(lqty);

                        for(u32 i = 0; i < lqty; i++)
                        {
                            file->read(&tmp->indices[i].vertex[0], sizeof(unsigned short));
                            file->read(&tmp->indices[i].vertex[1], sizeof(unsigned short));
                            file->read(&tmp->indices[i].vertex[2], sizeof(unsigned short));
                            file->read(&lface_flags, sizeof(unsigned short));
                        }
                    break;
                    case 0x4140:
                        file->read(&lqty, sizeof(unsigned short));
                        for(u32 i = 0; i < lqty; i++)
                        {
                            file->read(&tmp->vertices[i].Coord.x, sizeof(f32));
                            file->read(&tmp->vertices[i].Coord.y, sizeof(f32));
                        }
                    break;
                    default:
                        file->seek(lchunk_lenght - 6, true);
                    break;
                }
            }
            return tmp;
            #else
                return nullptr;
            #endif
        }

        bool meshmime_3ds::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "3ds";
        }
    }
}
