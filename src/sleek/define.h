#pragma once

#include "compile.h"

#define GLM_Precision glm::precision::mediump

typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void		    GLvoid;
typedef signed char	    GLbyte;		/* 1-byte signed */
typedef short		    GLshort;	/* 2-byte signed */
typedef int		        GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int		        GLsizei;	/* 4-byte signed */
typedef float		    GLfloat;	/* single precision float */
typedef float		    GLclampf;	/* single precision float in [0,1] */
typedef double		    GLdouble;	/* double precision float */
typedef double		    GLclampd;	/* double precision float in [0,1] */

namespace sleek
{
    static constexpr float PI = 3.14159265f;
    static constexpr float DegToRad = PI/180.f;
    static constexpr float RadToDeg = 180.f/PI;
    static constexpr float RECIPROCAL_PI = 1.0/PI;

    static constexpr const char *version = "0.6";
    static constexpr const char *engine_name = "SleekThink";
    static constexpr const char *engine_auth = "Jehan-Antoine Vayssade";

    static constexpr const char *licence = "Creative common";
    static constexpr const char *licence_attribute = "by-nc-sa";

    typedef unsigned char  u8;
    typedef unsigned short u16;
    typedef unsigned int   u32;
    typedef unsigned long  u64;

    typedef signed char  s8;
    typedef signed short s16;
    typedef signed int   s32;
    typedef signed long  s64;

    typedef float  f32;
    typedef double f64;
}
