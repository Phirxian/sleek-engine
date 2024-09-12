#include "GLTool.h"

#include <iostream>

void glRotatef(GLfloat x, GLfloat y, GLfloat z)
{
    glRotatef(x,1,0,0);
    glRotatef(y,0,1,0);
    glRotatef(z,0,0,1);
}
void glQuad()
{
    glNormal3f(0,0,0);
    glTexCoord3i(0,0,0); glVertex3f(0,0,0);
    glTexCoord3i(1,0,0); glVertex3f(1,0,0);
    glTexCoord3i(1,1,0); glVertex3f(1,1,0);
    glTexCoord3i(0,1,0); glVertex3f(0,1,0);
}
void glQuadCenter()
{
    glNormal3f(0,0,0);
    glTexCoord3i(0,1,0); glVertex3f(-0.5f,-0.5f,0);
    glTexCoord3i(1,1,0); glVertex3f( 0.5f,-0.5f,0);
    glTexCoord3i(1,0,0); glVertex3f( 0.5f, 0.5f,0);
    glTexCoord3i(0,0,0); glVertex3f(-0.5f, 0.5f,0);
}
void glCubeCenter()
{
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.f);					// Normal Pointing Towards Viewer
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);	// Point 1 (Front)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);	// Point 2 (Front)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);	// Point 3 (Front)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);	// Point 4 (Front)
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// Point 1 (Back)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);	// Point 2 (Back)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);	// Point 3 (Back)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);	// Point 4 (Back)
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);	// Point 1 (Top)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  0.5f);	// Point 2 (Top)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,  0.5f,  0.5f);	// Point 3 (Top)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);	// Point 4 (Top)
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// Point 1 (Bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -0.5f);	// Point 2 (Bottom)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);	// Point 3 (Bottom)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);	// Point 4 (Bottom)
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);	// Point 1 (Right)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);	// Point 2 (Right)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);	// Point 3 (Right)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);	// Point 4 (Right)
    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// Point 1 (Left)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);	// Point 2 (Left)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);	// Point 3 (Left)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);	// Point 4 (Left)
}

const char* GLErrorString(GLenum errorCode)
{
    static const struct {
        GLenum code;
        const char *string;
    } errors[]= {
        {GL_NO_ERROR,          "no error"},
        {GL_INVALID_ENUM,      "invalid enumerant"},
        {GL_INVALID_VALUE,     "invalid value"},
        {GL_INVALID_OPERATION, "invalid operation"},
        {GL_STACK_OVERFLOW,    "stack overflow"},
        {GL_STACK_UNDERFLOW,   "stack underflow"},
        {GL_OUT_OF_MEMORY,     "out of memory"},
        {0,                    nullptr }
    };

    int i;

    for(i=0; errors[i].string; i++)
        if(errors[i].code == errorCode)
            return errors[i].string;

    return nullptr;
}


bool glCheckError_(int line, const std::string &file) noexcept
{
    GLenum er;

    while((er = glGetError()) != GL_NO_ERROR)
        // SOURCE_PATH_SIZE
        std::cerr << file << ":" << line << " >> GL: " << GLErrorString(er) << std::endl;

    return er != GL_NO_ERROR;
}
