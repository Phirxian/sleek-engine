#include "../../device/device.h"
#include "ogl3_context.h"
#include "ogl3_driver.h"

#include <cstddef>

static const GLuint ogl3_render_mode[] =
{
    GL_POINTS,
    GL_LINES,
    GL_LINE_LOOP,
    GL_TRIANGLES,
    GL_QUADS
};

namespace sleek
{
    namespace driver
    {
        ogl3_driver::ogl3_driver(std::shared_ptr<device::Device> dev, std::shared_ptr<context> c) noexcept
            : driver(dev, c)
        {
            quad  = glGenLists(1);
            quadc = glGenLists(1);
            cubec = glGenLists(1);

            glNewList(quad , GL_COMPILE);
                glBegin(GL_QUADS);
                glQuad();
                glEnd();
            glEndList();

            glNewList(quadc, GL_COMPILE);
                glBegin(GL_QUADS);
                glQuadCenter();
                glEnd();
            glEndList();

            glNewList(quadc, GL_COMPILE);
                glBegin(GL_QUADS);
                glCubeCenter();
                glEnd();
            glEndList();

            setActiveMaterial(mat);
        }

        ogl3_driver::~ogl3_driver() noexcept
        {
            glDeleteLists(quad , 1);
            glDeleteLists(quadc, 1);
            glDeleteLists(cubec, 1);
        }

        void ogl3_driver::beginTo2D() const noexcept
        {
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, ctx->getViewport().x, ctx->getViewport().y, 0, -1.f, 1.f);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }

        void ogl3_driver::endFrom2D() const noexcept
        {
            glEnable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        void ogl3_driver::ObjectRenderBegin() const noexcept
        {
            glPushMatrix();
            if(mat && mat->effect)
                mat->effect->update();
            ctx->testError(-1, "shader_callback");
            glColor4f(255,255,255,255);
        }

        void ogl3_driver::ObjectRenderEnd() const noexcept
        {
            glPopMatrix();
        }

        void ogl3_driver::drawPixel(const math::vec2i pos, const math::pixel clr) const noexcept
        {
            ObjectRenderBegin();
                beginTo2D();
                    glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                    glBegin(GL_POINTS);
                        glVertex2f(pos.x, pos.y);
                    glEnd();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawPixel(const math::vec3f pos, const math::pixel clr) const noexcept
        {
            if(!src->ready()) return;
            ObjectRenderBegin();
                glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                glBegin(GL_POINTS);
                    glVertex3f(pos.x, pos.y, pos.z);
                glEnd();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawLine(const math::vec2i a, const math::vec2i b, const math::pixel clr) const noexcept
        {
            if(!src->ready()) return;
            ObjectRenderBegin();
                beginTo2D();
                    glBegin(GL_LINES);
                        glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                        glVertex2f(a.x, a.y);
                        glVertex2f(b.x, b.y);
                    glEnd();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawLine(const math::vec3f a, const math::vec3f b, const math::pixel clr) const noexcept
        {
            if(!src->ready()) return;
            ObjectRenderBegin();
                glBegin(GL_LINES);
                    glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                    glVertex3f(a.x, a.y, a.z);
                    glVertex3f(b.x, b.y, b.z);
                glEnd();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawArc(const math::vec2i pos, u32 radius, u32 start, u32 end, const math::pixel clr) const noexcept
        {
            if(!src->ready())
                return;

            f32 p = sqrt(radius*radius);

            math::vec2i vdata[] = {
                math::vec2i(
                    sin(start*DegToRad)*radius+pos.x,
                    cos(start*DegToRad)*radius+pos.y
                ),
                pos
            };

            for(f32 i = start+p; i<end+p; i += p)
            {
                vdata[1] = math::vec2i(sin(i*DegToRad)*radius+pos.x, cos(i*DegToRad)*radius+pos.y);
                drawLine(vdata[0], vdata[1], clr);
                vdata[0] = vdata[1];
            }
        }

        void ogl3_driver::drawCube(const math::aabbox2di c, const math::vec3f rot, const math::pixel upperleft, const math::pixel upperright, const math::pixel lowerleft, const math::pixel lowerright) const noexcept
        {
            if(!src->ready()) return;
            math::vec2i pos = c.getCenter();

            ObjectRenderBegin();
                beginTo2D();
                    glTranslatef(pos.x,pos.y,0);
                    glRotatef(rot.x,rot.y,rot.z);
                    glScalef(c.getSize().x, c.getSize().y,1);

                    glBegin(ogl3_render_mode[mat->getMode()]);
                    glNormal3f(0,0,0);

                    glColor4f(lowerleft.red, lowerleft.green, lowerleft.blue, lowerleft.alpha);
                    glTexCoord3i(0,0,0);
                    glVertex3f(-0.5f, 0.5f,0);

                    glColor4f(upperleft.red, upperleft.green, upperleft.blue, upperleft.alpha);
                    glTexCoord3i(0,1,0);
                    glVertex3f(-0.5f,-0.5f,0);

                    glColor4f(upperright.red, upperright.green, upperright.blue, upperright.alpha);
                    glTexCoord3i(1,1,0);
                    glVertex3f( 0.5f,-0.5f,0);

                    glColor4f(lowerright.red, lowerright.green, lowerright.blue, lowerright.alpha);
                    glTexCoord3i(1,0,0);
                    glVertex3f( 0.5f, 0.5f,0);

                    glEnd();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawCube(const math::aabbox2di c, const math::vec3f rot, const math::pixel clr) const noexcept
        {
            if(!src->ready()) return;
            math::vec2i pos = c.getCenter();

            ObjectRenderBegin();
                beginTo2D();
                    glTranslatef(pos.x,pos.y,0);
                    glRotatef(rot.x,rot.y,rot.z);
                    glScalef(c.getSize().x, c.getSize().y,1);
                    glBegin(ogl3_render_mode[mat->getMode()]);
                        glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                        glQuadCenter();
                    glEnd();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawCube(const math::aabbox3df c, const math::vec3f rot, const math::pixel clr) const noexcept
        {
            if(!src->ready()) return;
            math::vec3f pos = c.getCenter();

            ObjectRenderBegin();
                glTranslatef(pos.x,pos.y,pos.z);
                glRotatef(rot.x,rot.y,rot.z);
                glScalef(c.getSize().x, c.getSize().y, c.getSize().z);
                glBegin(GL_QUADS);
                    glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                    glCubeCenter();
                glEnd();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawCube(const math::vec2i a, const math::vec2i b, const math::vec3f rot, const math::pixel clr) const noexcept
        {
            drawCube(math::aabbox2di(a,b), rot, clr);
        }

        void ogl3_driver::drawCube(const math::vec3f a, const math::vec3f b, const math::vec3f rot, const math::pixel clr) const noexcept
        {
            drawCube(math::aabbox3df(a,b), rot, clr);
        }

        void ogl3_driver::drawCircle(const math::vec2i pos, u32 radius, const math::pixel clr) const noexcept
        {
            f32 p = sqrt(radius*radius);
            math::vec2i start = math::vec2i(sin(0*DegToRad)*radius, cos(0*DegToRad)*radius);
            for(register f32 i = 0; i<360; i += 12)
            {
                math::vec2i end = math::vec2i(sin(i*DegToRad)*radius, cos(i*DegToRad)*radius);
                drawLine(start+pos, end+pos, clr);
                start = end;
            }
        }

        void ogl3_driver::drawPolygon(const math::vec2i a, const math::vec2i b, const math::vec2i c, const math::pixel clr) const noexcept
        {
            drawLine(a, b, clr);
            drawLine(b, c, clr);
            drawLine(c, a, clr);
        }

        void ogl3_driver::drawPolygon(const math::vec3f a, const math::vec3f b, const math::vec3f c, const math::pixel clr) const noexcept
        {
            drawLine(a, b, clr);
            drawLine(b, c, clr);
            drawLine(c, a, clr);
        }

        void ogl3_driver::drawPolygonList(const math::vec2i *a, u32 n, const math::vec2i pos, const math::vec3f rot, const math::pixel clr) const noexcept
        {
            ObjectRenderBegin();
                beginTo2D();
                    glTranslatef(pos.x,pos.y,0);
                    glRotatef(rot.x,rot.y,rot.z);
                        glBegin(ogl3_render_mode[mat->getMode()]);
                            glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                            for(u32 i = 0; i< n; ++i)
                                glVertex2f(a[i].x,a[i].y);
                        glEnd();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawPolygonList(const math::vec3f *a, u32 n, const math::vec3f pos, const math::vec3f rot, const math::pixel clr) const noexcept
        {
            ObjectRenderBegin();
                glTranslatef(pos.x,pos.y,pos.z);
                glRotatef(rot.x,rot.y,rot.z);
                glBegin(ogl3_render_mode[mat->getMode()]);
                    glColor4f(clr.red, clr.green, clr.blue, clr.alpha);
                    for(u32 i = 0; i< n; ++i)
                        glVertex3f(a[i].x,a[i].y, a[i].z);
                glEnd();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawFBO(fbo *tex) const noexcept
        {
            ObjectRenderBegin();
                beginTo2D();
                    glEnable(GL_TEXTURE_2D);
                    glActiveTexture(GL_TEXTURE0_ARB);
                    tex->getTexture(0)->bind();
                    glColor4f(255,255,255,255);
                    glTranslatef(0,0,0);
                    glScalef(tex->getSize().x,tex->getSize().y,1);
                    glBegin(GL_QUADS);
                        glNormal3f(0,0,0);
                        glTexCoord3f(0,1,0); glVertex3f(0,0,0);
                        glTexCoord3f(1,1,0); glVertex3f(1,0,0);
                        glTexCoord3f(1,0,0); glVertex3f(1,1,0);
                        glTexCoord3f(0,0,0); glVertex3f(0,1,0);
                    glEnd();
                    glDisable(GL_TEXTURE_2D);
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawTexture(texture *tex, const math::vec2i pos, const math::vec3f rot, const math::vec2f uv) const noexcept
        {
            ObjectRenderBegin();
                beginTo2D();
                    glEnable(GL_TEXTURE_2D);
                    glActiveTexture(GL_TEXTURE0_ARB);
                    tex->getIdentifier()->bind();
                    glColor4f(255,255,255,255);
                    glTranslatef(pos.x,pos.y,0);
                    glRotatef(rot.x,rot.y,rot.z);
                    glScalef(tex->getDimension().x,tex->getDimension().y,1);
                    glBegin(GL_QUADS);
                        glNormal3f(0,0,0);
                        glTexCoord3f(0,0,0);        glVertex3f(0,0,0);
                        glTexCoord3f(uv.x,0,0);     glVertex3f(1,0,0);
                        glTexCoord3f(uv.x,uv.y,0);  glVertex3f(1,1,0);
                        glTexCoord3f(0,uv.y,0);     glVertex3f(0,1,0);
                    glEnd();
                    tex->getIdentifier()->unbind();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawTexture(texture *tex, const math::vec3f pos, const math::vec3f rot, const math::vec2f uv) const noexcept
        {
            ObjectRenderBegin();
                glEnable(GL_TEXTURE_2D);
                glActiveTexture(GL_TEXTURE0_ARB);
                tex->getIdentifier()->bind();
                glColor4f(255,255,255,255);
                glTranslatef(pos.x,pos.y,pos.z);
                glRotatef(rot.x,rot.y,rot.z);
                glScalef(tex->getDimension().x,tex->getDimension().y,1);
                glBegin(GL_QUADS);
                    glNormal3f(0,0,0);
                    glTexCoord3f(0,uv.y,0);     glVertex3f(-0.5f,-0.5f,0);
                    glTexCoord3f(uv.x,uv.y,0);  glVertex3f( 0.5f,-0.5f,0);
                    glTexCoord3f(uv.x,0,0);     glVertex3f( 0.5f, 0.5f,0);
                    glTexCoord3f(0,0,0);        glVertex3f(-0.5f, 0.5f,0);
                glEnd();
                tex->getIdentifier()->unbind();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawTextureScale(texture *tex, const math::vec2i pos, const math::vec3f rot, const math::vec3f scl, const math::vec2f uv) const noexcept
        {
            ObjectRenderBegin();
                beginTo2D();
                    glEnable(GL_TEXTURE_2D);
                    glActiveTexture(GL_TEXTURE0_ARB);
                    tex->getIdentifier()->bind();
                    glColor4f(255,255,255,255);
                    glTranslatef(pos.x,pos.y,0);
                    glRotatef(rot.x,rot.y,rot.z);
                    glScalef(scl.x,scl.y,scl.z);
                    glBegin(GL_QUADS);
                        glNormal3f(0,0,0);
                        glTexCoord3f(0,0,0);        glVertex3f(0,0,0);
                        glTexCoord3f(uv.x,0,0);     glVertex3f(1,0,0);
                        glTexCoord3f(uv.x,uv.y,0);  glVertex3f(1,1,0);
                        glTexCoord3f(0,uv.y,0);     glVertex3f(0,1,0);
                    glEnd();
                    tex->getIdentifier()->unbind();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawTextureScale(texture *tex, const math::vec3f pos, const math::vec3f rot, const math::vec3f scl, const math::vec2f uv) const noexcept
        {
            ObjectRenderBegin();
                glEnable(GL_TEXTURE_2D);
                glActiveTexture(GL_TEXTURE0_ARB);
                tex->getIdentifier()->bind();
                glColor4f(255,255,255,255);
                glTranslatef(pos.x,pos.y,pos.z);
                glRotatef(rot.x,rot.y,rot.z);
                glScalef(scl.x,scl.y,scl.z);
                glBegin(GL_QUADS);
                    glNormal3f(0,0,0);
                    glTexCoord3f(0,uv.y,0);     glVertex3f(-0.5f,-0.5f,0);
                    glTexCoord3f(uv.x,uv.y,0);  glVertex3f( 0.5f,-0.5f,0);
                    glTexCoord3f(uv.x,0,0);     glVertex3f( 0.5f, 0.5f,0);
                    glTexCoord3f(0,0,0);        glVertex3f(-0.5f, 0.5f,0);
                glEnd();
                tex->getIdentifier()->unbind();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawTextureCenter(texture *tex, const math::vec2i pos, const math::vec3f rot, const math::vec2f uv) const noexcept
        {
            ObjectRenderBegin();
                beginTo2D();
                    glEnable(GL_TEXTURE_2D);
                    glActiveTexture(GL_TEXTURE0_ARB);
                    tex->getIdentifier()->bind();
                    glColor4f(255,255,255,255);
                    glTranslatef(pos.x,pos.y,0);
                    glRotatef(rot.x,rot.y,rot.z);
                    glScalef(tex->getDimension().x,tex->getDimension().y,1);
                    glBegin(GL_QUADS);
                        glNormal3f(0,0,0);
                        glTexCoord3f(0,uv.y,0);     glVertex3f(-0.5f,-0.5f,0);
                        glTexCoord3f(uv.x,uv.y,0);  glVertex3f( 0.5f,-0.5f,0);
                        glTexCoord3f(uv.x,0,0);     glVertex3f( 0.5f, 0.5f,0);
                        glTexCoord3f(0,0,0);        glVertex3f(-0.5f, 0.5f,0);
                    glEnd();
                    tex->getIdentifier()->unbind();
                endFrom2D();
            ObjectRenderEnd();
        }

        void ogl3_driver::drawTextureCenter(texture *tex, const math::vec3f pos, const math::vec3f rot, const math::vec2f uv) const noexcept
        {
            ObjectRenderBegin();
                glEnable(GL_TEXTURE_2D);
                glActiveTexture(GL_TEXTURE0_ARB);
                tex->getIdentifier()->bind();
                glColor4f(255,255,255,255);
                glTranslatef(pos.x,pos.y,pos.z);
                glRotatef(rot.x,rot.y,rot.z);
                glScalef(tex->getDimension().x,tex->getDimension().y,1);
                glBegin(GL_QUADS);
                    glNormal3f(0,0,1);
                    glTexCoord3f(0,uv.y,0);     glVertex3f(-0.5f,-0.5f,0);
                    glTexCoord3f(uv.x,uv.y,0);  glVertex3f( 0.5f,-0.5f,0);
                    glTexCoord3f(uv.x,0,0);     glVertex3f( 0.5f, 0.5f,0);
                    glTexCoord3f(0,0,0);        glVertex3f(-0.5f, 0.5f,0);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            ObjectRenderEnd();
        }

        void ogl3_driver::drawMesh(mesh *m, const math::vec3f pos, const math::vec3f rot) const noexcept
        {
            ObjectRenderBegin();
                glColor4f(255,255,255,255);
                glTranslatef(pos.x,pos.y,pos.z);
                glRotatef(rot.x,rot.y,rot.z);
                glScalef(mat->getScale().x,mat->getScale().y,mat->getScale().z);

                ctx->testError(__LINE__, __FILE__);

                local_bind vao(m->getIdentifier());

                GLubyte *iptr = (GLubyte*)vao.ifNotBind(m->indices.data());
                GLubyte *vptr = (GLubyte*)vao.ifNotBind(m->vertices.data());

                ctx->testError(__LINE__, __FILE__);

                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_NORMAL_ARRAY);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);

                assert(m->indices.size() <= m->vertices.size()*3);

                glVertexPointer(3, GL_FLOAT, sizeof(math::vertex), vptr + offsetof(math::vertex, Pos));
                glNormalPointer(GL_FLOAT, sizeof(math::vertex), vptr + offsetof(math::vertex, Normal));
                glTexCoordPointer(2, GL_FLOAT, sizeof(math::vertex), vptr + offsetof(math::vertex, Coord));
                glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(math::vertex), vptr + offsetof(math::vertex, Color));

                glDrawElements(ogl3_render_mode[mat->getMode()], m->indices.size()*3, GL_UNSIGNED_INT, iptr);

                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                glDisableClientState(GL_NORMAL_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);

                ctx->testError(__LINE__, __FILE__);

            ObjectRenderEnd();
        }

        void ogl3_driver::setActiveMaterial(std::shared_ptr<material> i) noexcept
        {
            ctx->testError(__LINE__, __FILE__);
            static void(*_glState[2])(GLenum) = {&glDisable, &glEnable};

            if(mat)
            {
                if(mat->effect)
                    mat->effect->unbind();

                int start = i ? i->Texture.size() : 0;
                for(int stage = start; stage<mat->Texture.size(); ++stage)
                {
                    glActiveTexture(GL_TEXTURE0_ARB+stage);
                    if(mat->Texture[stage])
                        mat->Texture[stage]->unbind();
                }
            }

            ctx->testError(__LINE__, __FILE__);

            if(i)
            {
                _glState[bool(i->ant & ral_polygone)](GL_POLYGON_SMOOTH);
                _glState[bool(i->ant & ral_line)](GL_LINE_SMOOTH);
                _glState[bool(i->mat & rmt_solid)](GL_DEPTH_TEST);
                _glState[bool(i->mat & (rmt_add | rmt_sub))](GL_BLEND);
                _glState[bool(i->mat & rmt_lighting)](GL_LIGHTING);
                _glState[bool(i->mat & rmt_fog)](GL_FOG);
                _glState[bool(i->fac != rfc_off)](GL_CULL_FACE);

                glShadeModel(i->shd & rsd_flat ? GL_FLAT : GL_SMOOTH);

                if(!mat || mat->psize != i->psize)
                {
                    // deprecated & performance cost
                    glPointSize(i->psize);
                    glLineWidth(i->psize);
                }

                glPolygonMode(GL_FRONT_AND_BACK, i->wire ? GL_LINE : GL_FILL);

                /////////////////////////////////////////

                static const GLenum _wire[] = {
                    GL_FILL, GL_LINE
                };

                static const GLenum _cull[] = {
                    0, GL_BACK,
                    GL_FRONT, 0,
                    GL_FRONT_AND_BACK
                };

                //if(!mat || mat->wire != i->wire)
                //    glPolygonMode(_cull[i->fac], _wire[i->wire]);

                if(i->fac != rfc_off && (!mat || mat->fac != i->fac))
                    glCullFace(_cull[i->fac]);

                /////////////////////////////////////////

                if(!mat || mat->mat != i->mat)
                {
                    if(i->mat == rmt_solid)
                         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    else if(i->mat == rmt_add)
                         glBlendFunc(GL_ONE, GL_ONE);
                    else if(i->mat == rmt_sub)
                         glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ZERO);
                    else
                         glBlendFunc(GL_ONE, GL_ZERO);
                }

                /////////////////////////////////////////
                ctx->testError(__LINE__, __FILE__);
                /////////////////////////////////////////

                if(i->effect)
                    i->effect->bind();
                else
                {
                    int stage = 0;
                    if(mat)
                    {
                        int end = std::min(mat->Texture.size(), i->Texture.size());
                        for(; stage<end; ++stage)
                        {
                            if(i->Texture[stage] == mat->Texture[stage])
                                continue;

                            glActiveTextureARB(GL_TEXTURE0_ARB+stage);

                            if(i->Texture[stage])
                                i->Texture[stage]->bind();

                            glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);
                        }
                    }

                    ctx->testError(__LINE__, __FILE__);

                    for(; stage<i->Texture.size(); ++stage)
                    {
                        glActiveTextureARB(GL_TEXTURE0_ARB+stage);

                        if(i->Texture[stage])
                            i->Texture[stage]->bind();

                        glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);
                    }
                }
            }

            ctx->testError(__LINE__, __FILE__);
            mat = i;
        }

        std::shared_ptr<material> ogl3_driver::getActiveMaterial() const noexcept
        {
            return mat;
        }
    }
}
