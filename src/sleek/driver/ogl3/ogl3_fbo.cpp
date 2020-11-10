#include "ogl3_fbo.h"
#include "ogl3_texture_fbo.h"
#include <iostream>

namespace sleek
{
    namespace driver
    {
        static const GLenum ogl3_fbo_attachment[] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3,
            GL_COLOR_ATTACHMENT4,
            GL_COLOR_ATTACHMENT5,
            GL_COLOR_ATTACHMENT6,
            GL_COLOR_ATTACHMENT7,
            GL_COLOR_ATTACHMENT8,
            GL_COLOR_ATTACHMENT9,
            GL_COLOR_ATTACHMENT10,
            GL_COLOR_ATTACHMENT11,
            GL_COLOR_ATTACHMENT12,
            GL_COLOR_ATTACHMENT13,
            GL_COLOR_ATTACHMENT14,
            GL_COLOR_ATTACHMENT15,
            GL_STENCIL_ATTACHMENT
        };

        template<>
        ogl3_fbo<false>::ogl3_fbo(const math::vec2i &size, const std::vector<TextureFormat> &a, bool depthattachment) noexcept : fbo(size, a, depthattachment)
        {
            glGenFramebuffersEXT(1, &framebuffer);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);

            if(usedepth)
                glGenRenderbuffersEXT(1, &depthbuffer);

//            auto fbo_texture = new ogl3_texture_fbo<false>(this, size, GL_DEPTH_ATTACHMENT, 0);
//            textures.push_back(fbo_texture);
//            fbo_texture->update();

    		for(int i = 0; i<attachment.size(); ++i)
    		{
                auto fbo_texture = new ogl3_texture_fbo<false>(this, size, ogl3_fbo_attachment[i], attachment[i]);
                textures.push_back(fbo_texture);
                fbo_texture->update();
    		}

            if(usedepth)
                glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT32, size.x, size.y);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        }

        template<>
        ogl3_fbo<true>::ogl3_fbo(const math::vec2i &size, const std::vector<TextureFormat> &a, bool depthattachment) noexcept : fbo(size, a, depthattachment)
        {
            glGenFramebuffersEXT(1, &framebuffer);

            if(usedepth)
                glGenRenderbuffersEXT(1, &depthbuffer);

//            auto fbo_texture = new ogl3_texture_fbo<true>(this, size, GL_DEPTH_ATTACHMENT, 0);
//            textures.push_back(fbo_texture);
//            fbo_texture->update();

    		for(int i = 0; i<attachment.size(); ++i)
    		{
                auto fbo_texture = new ogl3_texture_fbo<true>(this, size, ogl3_fbo_attachment[i], attachment[i]);
                textures.push_back(fbo_texture);
                fbo_texture->update();
    		}

            if(usedepth)
                glNamedRenderbufferStorageEXT(framebuffer, GL_DEPTH_COMPONENT32, size.x, size.y);
        }

        template<bool dsa>
        ogl3_fbo<dsa>::~ogl3_fbo() noexcept
        {
            if(usedepth)
                glDeleteRenderbuffersEXT(1, &depthbuffer);
            glDeleteFramebuffersEXT(1, &framebuffer);

    		for(int i = 0; i<textures.size(); ++i)
                delete textures[i];
        }

        template<bool dsa>
        void ogl3_fbo<dsa>::resize(const math::vec2i &s) noexcept
        {
    		for(int i = 0; i<textures.size(); ++i)
                ((ogl3_texture_fbo<true>*)textures[i])->resize(s);
            fbo::resize(s);
            update();
        }

        template<bool dsa>
        void* ogl3_fbo<dsa>::getHardwareLink() const noexcept
        {
            return (GLuint*)&framebuffer;
        }

        template<>
        void ogl3_fbo<false>::update() noexcept
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);

            if(usedepth)
                glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);

            glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT32, size.x, size.y);

            for(int i = 0; i<textures.size(); ++i)
            {
                textures[i]->bind();
                textures[i]->update();
            }

            status = glCheckNamedFramebufferStatusEXT(framebuffer, GL_FRAMEBUFFER_EXT);
            check(status);
        }

        template<bool dsa>
        bool ogl3_fbo<dsa>::check(GLuint status)
        {
            switch (status)
            {
                case GL_FRAMEBUFFER_COMPLETE:
                    return true;
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                    std::cout << "FBO has invalid read buffer" << std::endl;
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                    std::cout << "FBO has invalid draw buffer" << std::endl;
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    std::cout << "FBO has one or several incomplete image attachments" << std::endl;
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    std::cout << "FBO missing an image attachment" << std::endl;
                    break;
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    std::cout << "FBO format unsupported" << std::endl;
                    break;
                default:
                    std::cout << "FBO error" << std::endl;
                    break;
            }
            return false;
        }

        template<>
        void ogl3_fbo<true>::update() noexcept
        {
            if(usedepth)
                glNamedFramebufferRenderbufferEXT(framebuffer, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);
            
            glNamedRenderbufferStorageEXT(framebuffer, GL_DEPTH_COMPONENT32, size.x, size.y);

            for(int i = 0; i<textures.size(); ++i)
            {
                textures[i]->bind();
                textures[i]->update();
            }

            status = glCheckNamedFramebufferStatusEXT(framebuffer, GL_FRAMEBUFFER_EXT);
            check(status);
        }

        template<bool dsa>
        void ogl3_fbo<dsa>::bind() noexcept
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
            glDrawBuffers(textures.size(), ogl3_fbo_attachment);
        }

        template<bool dsa>
        void ogl3_fbo<dsa>::bind(int i) noexcept
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
            glDrawBuffers(textures.size(), ogl3_fbo_attachment);
            glClearColor(
                f32(color.red/255.f),
                f32(color.green/255.f),
                f32(color.blue/255.f),
                f32(color.alpha/255.f)
            );
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }


        template<bool dsa>
        void ogl3_fbo<dsa>::unbind() noexcept
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
//            glDrawBuffer(GL_FRONT);
        }
    }
}
