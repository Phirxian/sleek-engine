#include "mesh_txt.h"
#include "glm/detail/func_geometric.hpp"
#include "driver/mesh.h"
#include "compile.h"

namespace sleek
{
    namespace loader
    {
        std::shared_ptr<driver::mesh> meshloader_txt::read(io::filereader *in) const noexcept
        {
            #ifdef mesh_loader_txt_support
                int     nvert;
                std::string	oneline(255, '\0');
                float   rx, ry, rz;

                auto tmp = std::make_shared<driver::mesh>();

                do
                {
                    in->read(const_cast<char*>(oneline.c_str()), 255);
                    int i = oneline.find('\n');
                    if(i != -1)
                        in->seek(255-i, true);
                }
                while(oneline[0] == '/' || oneline[0] == '\n');

                if(oneline.substr(0,9) != "Vertices:")
                    return nullptr;

                sscanf(oneline.c_str(), "Vertices: %d\n", &nvert);
                tmp->vertices.resize(nvert);

                for(int i=0;i<nvert;i++)
                {
                    do
                    {
                        in->read(const_cast<char*>(oneline.c_str()), 255);
                        int i = oneline.find('\n');
                        if(i != -1)
                            in->seek(255-i, true);
                    }
                    while(oneline[0] == '/' || oneline[0] == '\n');

                    sscanf(oneline.c_str(), "%f %f %f", &rx, &ry, &rz);
                    tmp->vertices[i].Pos = math::vec3f(rx,ry,rz);
                    tmp->vertices[i].Normal = glm::normalize(tmp->vertices[i].Pos);

                    math::index<3> in;
                        in.vertex[0] = i+0;
                        in.vertex[1] = i+1;
                        in.vertex[2] = i+2;
                    tmp->indices.push_back(in);
                }

                return tmp;
            #else
                return nullptr;
            #endif
        }

        bool meshloader_txt::write(driver::mesh *m, io::filewriter *out) const noexcept
        {
            #ifdef mesh_loader_txt_support
                std::string data = "Vertices: ";
                            data += std::to_string(m->vertices.size());
                            data += '\n';
                out->write(data.c_str(), data.size());

                for(u32 i =0; i<m->vertices.size(); ++i)
                {
                    data = "";
                    data += std::to_string(m->vertices[i].Pos.x);
                    data += " ";
                    data += std::to_string(m->vertices[i].Pos.y);
                    data += " ";
                    data += std::to_string(m->vertices[i].Pos.z);
                    out->write(data.c_str(), data.size());
                }

                return true;
            #else
                return false;
            #endif
        }

        bool meshloader_txt::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "txt";
        }
    }
}
