#include "mesh_obj.h"
#include "../../driver/mesh.h"
#include "../../compile.h"

#include <unordered_map>
#include <sstream>

struct OBJVertex
{
    uint32_t p = 0;
    uint32_t n = 0;
    uint32_t uv = 0;

    inline OBJVertex() { }

    void init(const std::string &string)
    {
        std::vector<std::string> tokens = split(string, '/');

        if (tokens.size() >= 1 && !tokens[0].empty())
            p = std::atoi(tokens[0].c_str());

        if (tokens.size() >= 2 && !tokens[1].empty())
            uv = std::atoi(tokens[1].c_str());

        if (tokens.size() >= 3 && !tokens[2].empty())
            n = std::atoi(tokens[2].c_str());
    }
    
    std::vector<std::string> split(const std::string &data, char delim)
    {
        std::vector<std::string> buf;
        std::istringstream line(data);
        for(std::string str; std::getline(line, str, delim);)
            if(str.size() > 0)
                buf.push_back(std::move(str));
        return std::move(buf);
    }
};

namespace sleek
{
    namespace loader
    {
        std::shared_ptr<driver::mesh> meshloader_obj::read(io::filereader *file) const noexcept
        {
            std::shared_ptr<driver::mesh> mesh = nullptr;
            
            #ifdef mesh_loader_obj_support
                std::string line = "";
                
                std::vector<glm::vec3> obj_positions;
                std::vector<glm::vec2> obj_texcoords;
                std::vector<glm::vec3> obj_normals;
                std::vector<OBJVertex> obj_vertices;
                
                mesh = std::make_shared<driver::mesh>();
                
                while(file->as_data())
                {
                    file->getline(line);
                    std::istringstream stream(line);
                    
                    if(line[0] == 'v' && line[1] == ' ')
                    {
                        glm::vec3 pos;
                        stream.get(); // 'v'
                        stream.get(); // ' '
                        stream >> pos[0] >> pos[1] >> pos[2];
                        obj_positions.push_back(pos);
                    }
                    
                    if(line[0] == 'v' && line[1] == 't')
                    {
                        glm::vec2 pos;
                        stream.get(); // 'v'
                        stream.get(); // 't'
                        stream >> pos[0] >> pos[1];
                        obj_texcoords.push_back(pos);
                    }
                    
                    if(line[0] == 'v' && line[1] == 'n')
                    {
                        glm::vec3 pos;
                        stream.get(); // 'v'
                        stream.get(); // 'n'
                        stream >> pos[0] >> pos[1] >> pos[2];
                        obj_normals.push_back(pos);
                    }
                    
                    if(line[0] == 'f')
                    {
                        std::string v1, v2, v3, v4;
                        stream.get(); // 'v'
                        stream.get(); // ' '
                        stream >> v1 >> v2 >> v3 >> v4;
                        
                        OBJVertex verts[6];
                        int nVertices = 3;

                        verts[0].init(v1);
                        verts[1].init(v2);
                        verts[2].init(v3);

                        if(!v4.empty())
                        {
                            verts[3].init(v4);
                            verts[4].init(v1);
                            verts[5].init(v3);
                            nVertices = 6;
                        }
                        
                        for(int i=0; i<nVertices; i += 3)
                        {
                            unsigned int j = obj_vertices.size();
                            mesh->indices.push_back(sleek::math::index<3>(j, j+1, j+2));
                            obj_vertices.push_back(verts[i]);
                            obj_vertices.push_back(verts[i+1]);
                            obj_vertices.push_back(verts[i+2]);
                        }
                    }
                }
                
                mesh->vertices.resize(obj_vertices.size());
                for(uint32_t i=0; i<obj_vertices.size(); ++i)
                    mesh->vertices[i].Pos = obj_positions.at(obj_vertices[i].p-1);

                if(!obj_normals.empty())
                {
                    mesh->vertices.resize(obj_vertices.size());
                    for(uint32_t i=0; i<obj_vertices.size(); ++i)
                        mesh->vertices[i].Normal = obj_normals.at(obj_vertices[i].n-1);
                }

                if(!obj_texcoords.empty())
                {
                    mesh->vertices.resize(obj_vertices.size());
                    for(uint32_t i=0; i<obj_vertices.size(); ++i)
                        mesh->vertices[i].Coord = obj_texcoords.at(obj_vertices[i].uv-1);
                }
                
            #endif
            
            return mesh;
        }

        bool meshwriter_obj::write(driver::mesh *m, io::filewriter *out) const noexcept
        {
            #ifdef mesh_loader_obj_support
            if (!m || !out)
                return false;

            // Write vertices
            for (const auto& vertex : m->vertices)
            {
                out->write(
                    "v " + std::to_string(vertex.Pos.x) + " " 
                         + std::to_string(vertex.Pos.y) + " "
                         + std::to_string(vertex.Pos.z) + "\n"
                    );
            }

            for (const auto& vertex : m->vertices)
            {
                out->write("vt " + std::to_string(vertex.Coord.x) + " " + 
                                    std::to_string(vertex.Coord.y) + "\n");
            }

            for (const auto& vertex : m->vertices)
            {
                out->write("vn " + std::to_string(vertex.Normal.x) + " " + 
                                    std::to_string(vertex.Normal.y) + " " + 
                                    std::to_string(vertex.Normal.z) + "\n");
            }

            // Write faces
            for (const auto& index : m->indices)
            {
                std::string face = "f";
                face += " " + std::to_string(index.vertex[0]);
                face += " " + std::to_string(index.vertex[1]);
                face += " " + std::to_string(index.vertex[2]);
                out->write(face + "\n");
            }

            return true;
            #endif
            
            return false;
        }

        bool meshmime_obj::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "obj";
        }
    }
}
