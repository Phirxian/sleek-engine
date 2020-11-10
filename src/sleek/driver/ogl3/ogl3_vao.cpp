#include "ogl3_vao.h"
#include <memory.h>
//#include <GL/gl.h>

#include <functional>
using namespace std::placeholders;

namespace sleek
{
    static GLuint ogl3_call_mode[] =
    {
        GL_STATIC_DRAW,
        GL_DYNAMIC_DRAW,
        GL_STREAM_DRAW
    };

    namespace driver
    {
        template<>
        ogl3_vao_identifer<false>::ogl3_vao_identifer(mesh *o, VAO_ALIGNMENT t, VAO_ALIGNMENT v) noexcept
            : identifier(o), vert(t), element(v)
        {
            vbo_allocated = -1;
            ebo_allocated = -1;

            glGenVertexArrays(1, &gl);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, 0, ogl3_call_mode[t]);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, 0, 0, ogl3_call_mode[v]);

            subdata.resize(o->datas.size());

            for(int i = 0; i<o->datas.size(); ++i)
            {
                glGenBuffers(1, &subdata[i]);
                glBindBuffer(GL_ARRAY_BUFFER, subdata[i]);
                glBufferData(GL_ARRAY_BUFFER, 0, 0, ogl3_call_mode[v]);
            }
        }

        template<>
        ogl3_vao_identifer<true>::ogl3_vao_identifer(mesh *o, VAO_ALIGNMENT t, VAO_ALIGNMENT v) noexcept
            : identifier(o), vert(t), element(v)
        {
            vbo_allocated = -1;
            ebo_allocated = -1;

            glGenVertexArrays(1, &gl);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            glNamedBufferDataEXT(vbo, 0, 0, ogl3_call_mode[v]);
            glNamedBufferDataEXT(ebo, 0, 0, ogl3_call_mode[t]);

            subdata.resize(o->datas.size());

            for(int i = 0; i<o->datas.size(); ++i)
            {
                glGenBuffers(1, &subdata[i]);
                glNamedBufferDataEXT(subdata[i], 0, 0, ogl3_call_mode[v]);
            }
        }

        template<bool dsa>
        ogl3_vao_identifer<dsa>::~ogl3_vao_identifer() noexcept
        {
            for(int i = 0; i<subdata.size(); ++i)
                glDeleteBuffers(1, &subdata[i]);
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ebo);
            glDeleteBuffers(1, &gl);
        }

        template<bool dsa>
        void* ogl3_vao_identifer<dsa>::getHardwareLink() const noexcept
        {
            GLuint *tmp = (GLuint*)&gl;
            return tmp;
        }

        template<bool dsa>
        void ogl3_vao_identifer<dsa>::bind() noexcept
        {
            mesh *tmp = (mesh*)owner;

            glBindVertexArray(gl);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

            constexpr GLboolean normalize = GL_FALSE;

            glVertexAttribPointer(0, 3, GL_FLOAT, normalize, sizeof(math::vertex), (GLubyte*)0 + offsetof(math::vertex, Pos));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, normalize, sizeof(math::vertex), (GLubyte*)0 + offsetof(math::vertex, Normal));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, normalize, sizeof(math::vertex), (GLubyte*)0 + offsetof(math::vertex, Coord));
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, normalize, sizeof(math::vertex), (GLubyte*)0 + offsetof(math::vertex, Color));
            glEnableVertexAttribArray(3);

            for(int i = 0; i<subdata.size(); ++i)
            {
                auto &ref = tmp->datas[i];
                glEnableVertexAttribArray(4+i);
                glBindBuffer(GL_ARRAY_BUFFER, subdata[i]);

                if(ref.type == GL_UNSIGNED_BYTE || ref.type == GL_BYTE || ref.type == GL_UNSIGNED_INT || ref.type == GL_INT)
                    glVertexAttribIPointer(4+i, ref.componant, ref.type, ref.element_size, (GLubyte*)0);
                else
                    glVertexAttribPointer(4+i, ref.componant, ref.type, normalize, ref.element_size, (GLubyte*)0);
            }
        }

        template<bool dsa>
        void ogl3_vao_identifer<dsa>::unbind() noexcept
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        template<>
        void ogl3_vao_identifer<false>::update() noexcept
        {
            mesh *tmp = (mesh*)owner;

            const unsigned int vertex_size = sizeof(*tmp->vertices.data())*tmp->vertices.size();
            const unsigned int index_size = sizeof(*tmp->indices.data())*tmp->indices.size();

            auto upload = std::bind(glBufferData, _1, _2, _3, _4);
            auto update = std::bind(glBufferSubData, _1, 0, _2, _3);

            glBindVertexArray(gl);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

            vbo_allocated != vertex_size ?
                upload(GL_ARRAY_BUFFER, vertex_size, tmp->vertices.data(), ogl3_call_mode[vert]) :
                update(GL_ARRAY_BUFFER, vertex_size, tmp->vertices.data());

            ebo_allocated != vertex_size ?
                upload(GL_ELEMENT_ARRAY_BUFFER, index_size, tmp->indices.data(), ogl3_call_mode[element]) :
                update(GL_ELEMENT_ARRAY_BUFFER, index_size, tmp->indices.data());

            for(int i = 0; i<subdata.size(); ++i)
            {
                const size_t subdata_size = tmp->datas[i].element_size*tmp->datas[i].size;
                glBindBuffer(GL_ARRAY_BUFFER, subdata[i]);
                upload(GL_ARRAY_BUFFER, subdata_size, tmp->datas[i].data, ogl3_call_mode[vert]);
            }

            glBindVertexArray(0);

            vbo_allocated = vertex_size;
            ebo_allocated = index_size;
        }

        template<>
        void ogl3_vao_identifer<true>::update() noexcept
        {
            mesh *tmp = (mesh*)owner;

            const unsigned int vertex_size = sizeof(*tmp->vertices.data())*tmp->vertices.size();
            const unsigned int index_size = sizeof(*tmp->indices.data())*tmp->indices.size();

            auto upload = std::bind(glNamedBufferDataEXT, _1, _2, _3, _4);
            auto update = std::bind(glNamedBufferSubDataEXT, _1, 0, _2, _3);

            vbo_allocated != vertex_size ?
                upload(vbo, vertex_size, tmp->vertices.data(), ogl3_call_mode[vert]) :
                update(vbo, vertex_size, tmp->vertices.data());

            ebo_allocated != vertex_size ?
                upload(ebo, index_size, tmp->indices.data(), ogl3_call_mode[element]) :
                update(ebo, index_size, tmp->indices.data());

            for(int i = 0; i<subdata.size(); ++i)
                upload(subdata[i], tmp->datas[i].size*tmp->datas[i].element_size, tmp->datas[i].data, ogl3_call_mode[vert]);

            vbo_allocated = vertex_size;
            ebo_allocated = index_size;
        }
    }
}
