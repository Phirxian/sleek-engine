#include <opengl/GLTool.h>

#ifdef __glad_h_
#define GL_FOG_HINT 0x0C54
#define GL_PERSPECTIVE_CORRECTION_HINT 0x0C50
#define GL_POINT_SMOOTH_HINT 0x0C51
#define glMatrixPop glMatrixPopEXT
#define glMatrixPush glMatrixPushEXT
#define glColor4ub glColorP4ui
#define GL_PROJECTION 0x1701
#define GL_MODELVIEW 0x1700
#endif

#if defined __linux
    #include <GL/glx.h>
#elif defined WIN32 || WIN64
    #include <windows.h>
#endif
