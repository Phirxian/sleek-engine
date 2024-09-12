#include "../material.h"
#include "ogl3_shader.h"
#include <stdlib.h>
#include <cstring>

#define GL_GEOMETRY_SHADER          0x8DD9
#define GL_TESS_CONTROL_SHADER      0x8E88
#define GL_TESS_EVALUATION_SHADER   0x8E87
#define GL_COMPUTE_SHADER           0x91B9

unsigned int ogl3_shader_type[] = {
    GL_FRAGMENT_SHADER,
    GL_VERTEX_SHADER,
    GL_GEOMETRY_SHADER,
    GL_TESS_CONTROL_SHADER,
    GL_TESS_EVALUATION_SHADER,
    GL_COMPUTE_SHADER,
    0
};

namespace sleek
{
    namespace driver
    {
        template<>
        ogl3_shader<false>::ogl3_shader() noexcept : shader(), compiled(GL_FALSE), enabled(0)
        {
            if(!(prog = glCreateProgram()))
                printf("Can't creat shader programme\n");
            std::memset(shaders, 0, shd_count);
        }

        template<>
        ogl3_shader<true>::ogl3_shader() noexcept : shader(), compiled(GL_FALSE), enabled(0)
        {
            if(!(prog = glCreateProgram()))
                printf("Can't creat shader programme\n");
        }

        template<bool dsa>
        ogl3_shader<dsa>::~ogl3_shader() noexcept
        {
            for(int i = 0; i<shd_count; ++i)
                detacheShader((shader_type)i);
            glDeleteProgram(prog);
        }

        template<bool dsa>
        void* ogl3_shader<dsa>::getHardwareLink() const noexcept
        {
            GLuint *tmp = (GLuint*)&prog;
            return tmp;
        }

        template<bool dsa>
        void ogl3_shader<dsa>::setLinkToMaterial(material* i) noexcept
        {
            link = i;
        }

        template<bool dsa>
        material* ogl3_shader<dsa>::getLinkFromMaterial() const noexcept
        {
            return link;
        }

        template<bool dsa>
        void ogl3_shader<dsa>::attacheShader(const shader_type i, const std::string &data, const std::string &main) noexcept
        {
            GLint lenght = data.size();
            const char *tmp = data.c_str();

            if((~enabled >> i) & 1 && !glIsShader(shaders[i]))
            {
                shaders[i] = glCreateShader(ogl3_shader_type[i]);
                if(!shaders[i])
                    printf("Can't create %s shader\n", shader_type_name[i]);
            }

            glShaderSource(shaders[i], 1, (const GLchar**)&tmp, &lenght);

            if((~enabled >> i) & 1)
                glAttachShader(prog, shaders[i]);

            enabled |= 1 << i;
            source[i] = data;
        }

        template<bool dsa>
        void ogl3_shader<dsa>::detacheShader(const shader_type i) noexcept
        {
            enabled &= ~(1 << i);
            glDetachShader(prog, shaders[i]);
            glDeleteShader(shaders[i]);
        }

        template<bool dsa>
        void ogl3_shader<dsa>::compileShader() noexcept
        {
            compiled = GL_TRUE;

            for(int i = 0; i<shd_count; ++i)
            {
                if((enabled >> i) & 0x1)
                {
                    glCompileShader(shaders[i]);
                    glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &compiled);
                    if(compiled != GL_TRUE)
                    {
                        #ifdef __linux
                            GLsizei logsize = 1024;
                            char *log = NULL;
                            log = new char[logsize];
                            glGetShaderInfoLog(shaders[i], logsize, &logsize, log);
                            printf("%s\n", log);
                            delete[] log;
                        #endif
                    }
                }
            }

            LinkAndValidate();
        }

        template<bool dsa>
        void ogl3_shader<dsa>::LinkAndValidate() noexcept
        {
            glLinkProgram(prog);
            glGetProgramiv(prog, GL_LINK_STATUS, &compiled);
            if(compiled != GL_TRUE)
            {
                #ifdef __linux
                    char *log = NULL;
                    GLsizei logsize = 1024;
                    log = new char[logsize];
                    memset(log, '\0', logsize);
                    glGetInfoLogARB(prog, logsize, &logsize, log);
                    printf("%s\n", log);
                    delete[] log;
                #endif
            }
            else
            {
                glValidateProgram(prog);
                glGetProgramiv(prog, GL_VALIDATE_STATUS, &compiled);
                if(compiled != GL_TRUE)
                {
                    #ifdef __linux
                        char *log = NULL;
                        GLsizei logsize = 1024;
                        log = new char[logsize];
                        memset(log, '\0', logsize);
                        glGetInfoLogARB(prog, logsize, &logsize, log);
                        printf("%s\n", log);
                        delete[] log;
                    #endif
                }

            }
        }

        template<bool dsa>
        u32 ogl3_shader<dsa>::getVariableID(const std::string &name) const noexcept
        {
            return glGetUniformLocation(prog, name.c_str());
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const f32 val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform1f(id, val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const f32 val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform1fEXT(prog, id, val);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const f32 *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform1fv(id, count, val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const f32 *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform1fvEXT(prog, id, count, val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const s32 val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform1i(id, val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const s32 val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform1iEXT(prog, id, val);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const s32 *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform1iv(id, count, val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const s32 *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform1ivEXT(prog, id, count, val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const u32 val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform1ui(id, val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const u32 val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform1uiEXT(prog, id, val);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const u32 *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform1uiv(id, count, val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const u32 *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform1uivEXT(prog, id, count, val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const math::vec3f &val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform3f(id, val.x, val.y, val.z);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const math::vec3f &val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform3fEXT(prog, id, val.x, val.y, val.z);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const math::vec3f *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform3fv(id, count, (GLfloat*)val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const math::vec3f *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform3fvEXT(prog, id, count, (GLfloat*)val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const math::vec4f &val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform4f(id, val.x, val.y, val.z, val.w);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const math::vec4f &val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform4fEXT(prog, id, val.x, val.y, val.z, val.w);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const math::vec4f *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform4fv(id, count, (GLfloat*)val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const math::vec4f *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform4fvEXT(prog, id, count, (GLfloat*)val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const math::quatf &val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform4f(id, val.x, val.y, val.z, val.w);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const math::quatf &val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform4fEXT(prog, id, val.x, val.y, val.z, val.w);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const math::quatf *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform4fv(id, count, (GLfloat*)val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const math::quatf *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform4fvEXT(prog, id, count, (GLfloat*)val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const math::vec2f &val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform2f(id, val.x, val.y);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const math::vec2f &val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform2fEXT(prog, id, val.x, val.y);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const math::vec2f *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniform2fv(id, count, (GLfloat*)val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const math::vec2f *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniform2fvEXT(prog, id, count, (GLfloat*)val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, const math::mat4f &val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniformMatrix4fv(id, 1, GL_FALSE, (GLfloat*)&val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, const math::mat4f &val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniformMatrix4fvEXT(prog, id, 1, GL_FALSE, (GLfloat*)&val);
        }

        template<>
        void ogl3_shader<false>::setVariable(const std::string &name, int count, const math::mat4f *val) noexcept
        {
            bind();
            int id = getVariableID(name);
            glUniformMatrix4fv(id, count, GL_FALSE, (GLfloat*)val);
        }

        template<>
        void ogl3_shader<true>::setVariable(const std::string &name, int count, const math::mat4f *val) noexcept
        {
            int id = getVariableID(name);
            glProgramUniformMatrix4fvEXT(prog, id, count, GL_FALSE, (GLfloat*)val);
        }

        //////////////////////////////////////////////////////////////////////////

        template<bool dsa>
        void ogl3_shader<dsa>::setTexture(const std::string &name, identifier *val, const s32 textureUnit) noexcept
        {
            glActiveTextureARB(GL_TEXTURE0_ARB + textureUnit);
            if(val) val->bind();
            setVariable(name, textureUnit);
        }

        //////////////////////////////////////////////////////////////////////////

        template<bool dsa>
        void ogl3_shader<dsa>::bind() noexcept
        {
            glUseProgram(prog);
        }

        template<bool dsa>
        void ogl3_shader<dsa>::unbind() noexcept
        {
            glUseProgram(0);
        }
        
        template<bool dsa>
        void ogl3_shader<dsa>::dispatch(const math::vec3i &size) noexcept
        {
            printf("ogl3_shader<%d>::dispatch no implementation provided\n", dsa);
        }
    }
}
