#include "../../device/device.h"
#include "ogl3_context.h"
#include "ogl3_driver.h"
#include "ogl3_texture.h"
#include "ogl3_texture_array.h"
#include "ogl3_texture_3d.h"
#include "ogl3_fbo.h"
#include "ogl3_vao.h"
#include "ogl3_shader.h"
#include <string.h>

#ifdef glfw3_device_support
#include <GLFW/glfw3.h>
#endif

namespace sleek
{
    namespace driver
    {
        ogl3_context::ogl3_context(std::shared_ptr<device::Device> &d, std::shared_ptr<context> s) noexcept
            : context(d, s), dsa(false), txarray(false), tx3d(false)
        {
            auto sogl = (s && s->getType() == RCTX_OGL3) ?
                        reinterpret_cast<ogl3_context*>(s.get()) : 0;

            if(d->getType() != device::DWM_SDL && d->getType() != device::DWM_GLFW3)
            {
                #if defined __linux
                    cx = nullptr;

                    if(checkExtension("GLX_ARB_create_context") && d->getInfo().fbconfig)
                    {
                        typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
                        glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
                        if(glXCreateContextAttribsARB)
                        {
                            int context_attribs[] =
                            {
                                #ifdef GLX_CONTEXT_MAJOR_VERSION_ARB
                                GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                                GLX_CONTEXT_MINOR_VERSION_ARB, 1,
                                #else
                                GL_MAJOR_VERSION, 3,
                                GL_MINOR_VERSION, 1,
                                #endif
                                None
                            };

                            cx = glXCreateContextAttribsARB(
                                (Display*)d->getInfo().display,
                               *(GLXFBConfig*)d->getInfo().fbconfig,
                                0, True, context_attribs
                            );

                            if(!cx)
                                printf("glXCreateContextAttribsARB failed\n");
                        }
                    }

                    if(!cx)
                        cx = glXCreateContext((Display*)d->getInfo().display, (XVisualInfo*)d->getInfo().visual, sogl ? sogl->cx : 0, GL_TRUE);

                    printf("Direct Rendering: %s\n", glXIsDirect((Display*)d->getInfo().display, cx) ? "Yes" : "No");
                #elif defined WIN32 || WIN64
                    cx = wglCreateContext((HDC)d->getInfo().display);
                #endif
            }

            bind();

            printf("OpenGL version: %s\n",(char*)glGetString(GL_VERSION));
            printf("OpenGL render: %s\n",(char*)glGetString(GL_RENDERER));
            printf("OpenGL vendor: %s\n",(char*)glGetString(GL_VENDOR));

            #if defined GL_VERSION_2_0 || defined GL_ARB_shader_objects
                if(checkExtension("GL_ARB_shader_objects"))
                {
                    printf("GLSL available: ");
                    if(checkExtension("GL_ARB_vertex_shader")) printf("vertex");
                    if(checkExtension("GL_ARB_fragment_shader")) printf("/fragment");
                    #if defined GL_ARB_geometry_shader4 || defined GL_EXT_geometry_shader4 || defined GL_NV_geometry_program4 || defined GL_NV_geometry_shader4
                        if(checkExtension("GL_ARB_geometry_shader4") ||
                           checkExtension("GL_EXT_geometry_shader4") ||
                           checkExtension("GL_NV_geometry_program4") ||
                           checkExtension("GL_NV_geometry_shader4"))
                            printf("/geometry");
                    #endif
                    if(checkExtension("GL_ARB_compute_shader")) printf("/compute");
                    printf("\n");
                }
                else
                {
                    printf("GLSL extention not found\n");
                }
            #else
                printf("GLSL extention not compiled\n");
            #endif

            //!

            if(checkExtension("GL_ARB_multitexture"))
            {
                int texture_unity = reserved_texture;
                #ifdef GL_MAX_TEXTURE_UNITS_ARB
                glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&texture_unity);
                #else
                glGetIntegerv(GL_MAX_TEXTURE_UNITS, &texture_unity);
                #endif
                printf("Max texture units initialized: %d\n", texture_unity);
            }
            else printf("GL_ARB_multitexture: test fail\n");

            dsa = checkExtension("GL_EXT_direct_state_access");
            printf("GL_EXT_direct_state_access: %s\n", dsa ? "Yes" : "No");

            txarray = checkExtension("GL_EXT_texture_array");
            printf("GL_EXT_texture_array: %s\n", txarray ? "Yes" : "No");

            tx3d = checkExtension("GL_EXT_texture3D");
            printf("GL_EXT_texture3D: %s\n", tx3d ? "Yes" : "No");

            printf("GL_MAX_TEXTURE_SIZE: %d\n", queryHardwareLimitation(GL_MAX_TEXTURE_SIZE));
            printf("GL_MAX_VERTEX_ATTRIBS: %d\n", queryHardwareLimitation(GL_MAX_VERTEX_ATTRIBS));
            printf("GL_MAX_COLOR_ATTACHMENTS: %d\n", queryHardwareLimitation(GL_MAX_COLOR_ATTACHMENTS));
            printf("GL_MAX_DRAW_BUFFERS: %d\n", queryHardwareLimitation(GL_MAX_DRAW_BUFFERS));

            printf("=========================================================================\n");
        }

        ogl3_context::~ogl3_context() noexcept
        {
            if(win->getType() != device::DWM_SDL && win->getType() != device::DWM_GLFW3)
            {
                #if defined __linux
                    glXDestroyContext((Display*)win->getInfo().display, cx);
                #elif defined WIN32 || WIN64
                    wglDeleteContext(cx);
                #endif
            }
        }

        int ogl3_context::queryHardwareLimitation(int i) const noexcept
        {
            GLint limitation = 0;
            glGetIntegerv(i, &limitation);
            return limitation;
        }

        void ogl3_context::setAntialiasing(const AntiailiasingMode &i) noexcept
        {
            aam = i;
            switch(i)
            {
                case DAM_FAST:
                    glHint(GL_FOG_HINT, GL_FASTEST);
                    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
                    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
                    glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
                    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
                break;
                case DAM_NICE:
                    glHint(GL_FOG_HINT, GL_NICEST);
                    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
                    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
                    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
                    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
                break;
                default:
                    glHint(GL_FOG_HINT, GL_DONT_CARE);
                    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
                    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_DONT_CARE);
                    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
                    glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
                break;
            }
        }

        void ogl3_context::setViewport(const math::vec2i& i) noexcept
        {
            viewport = i;

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(0, i.x, 0, i.y, 0.f,1.f);
            glViewport(0, 0, i.x, i.y);
            testError(__LINE__, __FILE__);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            testError(__LINE__, __FILE__);
        }

        AntiailiasingMode ogl3_context::getAntiailiasing() const noexcept
        {
            return aam;
        }

        math::vec2i ogl3_context::getViewport() const noexcept
        {
            return viewport;
        }

        std::shared_ptr<driver> ogl3_context::createDriver() noexcept
        {
            return std::make_shared<ogl3_driver>(win, getptr());
        }

        std::shared_ptr<identifier> ogl3_context::createTexture(texture *o, bool DSA) const noexcept
        {
            if(dsa && DSA) return std::make_shared<ogl3_texture<true>>(o);
            return std::make_shared<ogl3_texture<false>>(o);
        }

        std::shared_ptr<identifier> ogl3_context::createTextureArray(texture_array *o, bool DSA) const noexcept
        {
            if(dsa && DSA) return std::make_shared<ogl3_texture_array<true>>(o);
            return std::make_shared<ogl3_texture_array<false>>(o);
        }

        std::shared_ptr<identifier> ogl3_context::createTexture3d(texture3d *o, bool DSA) const noexcept
        {
            if(dsa && DSA) return std::make_shared<ogl3_texture_3d<true>>(o);
            return std::make_shared<ogl3_texture_3d<false>>(o);
        }

        std::shared_ptr<fbo> ogl3_context::createFBO(const math::vec2i &size, const std::vector<TextureFormat> &attachements, bool depthattachment, bool DSA) const noexcept
        {
            std::shared_ptr<fbo> tmp;

            if(dsa && DSA) tmp = std::make_shared<ogl3_fbo<true>>(size, attachements, depthattachment);
            else tmp = std::make_shared<ogl3_fbo<false>>(size, attachements, depthattachment);

            return tmp;
        }

        std::shared_ptr<identifier> ogl3_context::createVAO(mesh *o, VAO_ALIGNMENT t, VAO_ALIGNMENT a, bool DSA) const noexcept
        {
            std::shared_ptr<identifier> tmp;

            if(dsa && DSA) tmp = std::make_shared<ogl3_vao_identifer<true>>(o, t, a);
            else tmp = std::make_shared<ogl3_vao_identifer<false>>(o, t, a);

            tmp->update();
            o->setIdentifier(tmp);
            return tmp;
        }

        std::shared_ptr<shader> ogl3_context::createShader(bool DSA) const noexcept
        {
            if(dsa && DSA) return std::make_shared<ogl3_shader<true>>();
            return std::make_shared<ogl3_shader<false>>();
        }

        std::shared_ptr<texture> ogl3_context::createScreenshot(const math::aabbox2du &rec) const noexcept
        {
            auto tmp = std::make_shared<texture>(rec.getSize(), TXFMT_RGB);
            glReadBuffer(GL_FRONT);
            glReadPixels(
                rec.upperleft.x, rec.upperleft.y,
                rec.lowerright.x, rec.lowerright.y,
                GL_RGB, GL_UNSIGNED_BYTE,
                tmp->getBuffer()
            );
            glReadBuffer(GL_BACK);
            return tmp;
        }

        bool ogl3_context::checkExtension(const char *name) noexcept
        {
            #ifdef glfw3_device_support
            if(win->getType() == device::DWM_GLFW3)
                return glfwExtensionSupported(name);
            #endif

            const GLubyte *extensions = NULL;
            const GLubyte *debut;
            GLubyte *place, *fin;

            place = (GLubyte*)strchr(name, ' ');

            if(place || *name == '\0')
                return false;

            extensions = glGetString(GL_EXTENSIONS);

            #if defined __linux
                if(!extensions)
                    extensions = (const GLubyte*)glXQueryExtensionsString(
                        (Display*)win->getInfo().display, 0
                    );
            #else
                #error TODO
            #endif

            if(!extensions)
            {
                printf("query extensions string failed\n");
                return false;
            }

            debut = extensions;
            for(;;)
            {
                place =(GLubyte *) strstr((const char *) debut, name);
                if(!place) break;
                fin = place + strlen(name);
                if(place == debut || *(place - 1) == ' ')
                    if(*fin == ' ' || *fin == '\0')
                        return true;
                debut = fin;
            }

            return false;
        }

        bool ogl3_context::testError(int line, const std::string &file) const noexcept
        {
            GLenum er;

            while((er = glGetError()) != GL_NO_ERROR)
                std::cerr << (file.c_str() + SOURCE_PATH_SIZE) << ":" << line << " >> GL: " << GLErrorString(er) << std::endl;

            return er != GL_NO_ERROR;
        }

        bool ogl3_context::testError() const noexcept
        {
            GLenum er;

            while((er = glGetError()) != GL_NO_ERROR)
                std::cerr << "GL:" << GLErrorString(er) << std::endl;

            return er != GL_NO_ERROR;
        }

        bool ogl3_context::bind() noexcept
        {
            testError(__LINE__, __FILE__);

            if(win->getType() == device::DWM_SDL)
                return true;

            if(win->getType() == device::DWM_GLFW3)
                return true;

            #if defined __linux
                return glXMakeCurrent(
                    (Display*)win->getInfo().display,
                    *(Window*)win->getInfo().window,
                    cx
                );
            #elif defined WIN32 || WIN64
                return wglMakeCurrent(dc, gl);
            #endif
        }

        void ogl3_context::begin(const math::pixel &color) noexcept
        {
            glClearColor((f32)(color.red/255.f),(f32)(color.green/255.f),(f32)(color.blue/255.f),(f32)(color.alpha/255.f));
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix();
            glStencilFunc(GL_ALWAYS, 0x0, 0x4);
            glStencilMask(0x4);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0_ARB);
            glColor4ub(255,255,255,255);
            testError(__LINE__, __FILE__);
        }

        void ogl3_context::end() noexcept
        {
            testError(__LINE__, __FILE__);
            glPopMatrix();
            glFlush();
            glDisable(GL_TEXTURE_2D);
        }
    }
}
