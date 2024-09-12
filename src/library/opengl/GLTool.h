#include <opengl/GLee.h>

#include <string>

void glRotatef(GLfloat x, GLfloat y, GLfloat z);
void glQuad();
void glQuadCenter();
void glCubeCenter();

const char* GLErrorString(GLenum errorCode);

bool glCheckError_(int line, const std::string &file) noexcept;

#define glCheckError() glCheckError(__FILE__, __LINE__) 