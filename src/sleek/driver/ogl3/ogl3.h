#define GL_GLEXT_LEGACY 1
#define GLEW_STATIC 1
#define GL3_PROTOTYPES 1

//#include <opengl/gl.h>
//#include <opengl/gl3.h>
#include <opengl/GLee.h>
//#include <opengl/glew.h>

#include <opengl/GLTool.h>


#if defined __linux
    #include <GL/glx.h>
#elif defined WIN32 || WIN64
    #include <windows.h>
#endif
