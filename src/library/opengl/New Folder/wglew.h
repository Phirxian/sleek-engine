/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: This software was created using the
** OpenGL(R) version 1.2.1 Sample Implementation published by SGI, but has
** not been independently verified as being compliant with the OpenGL(R)
** version 1.2.1 Specification.
*/

/*
** Copyright (C) 2002, Lev Povalahev
** All rights reserved.
** 
** Redistribution and use in source and binary forms, with or without modification, 
** are permitted provided that the following conditions are met:
** 
** * Redistributions of source code must retain the above copyright notice, 
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice, 
**   this list of conditions and the following disclaimer in the documentation 
**   and/or other materials provided with the distribution.
** * The name of the authors may be used to endorse or promote products 
**   derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
** IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
** INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
** BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
** OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
** THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
** The OpenGL Extension Wrangler Library
** Copyright (C) 2002 Milan Ikits
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef __wglew_h__
#define __wglew_h__

#ifdef __wglext_h_
#error wglext.h included before wglew.h
#endif

#define __wglext_h_

#ifdef _WIN32

#if !defined(APIENTRY) && !defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

/*
 * GLEW_STATIC needs to be set when including the
 * source directly in the project.  
 * GLEW_BUILD is set when building the dll version.
 */
#ifdef GLEW_STATIC
#define GLEW_EXPORT
#else
#ifdef GLEW_BUILD
#define GLEW_EXPORT __declspec(dllexport)
#else
#define GLEW_EXPORT __declspec(dllimport)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ARB extensions */
#define WGL_ARB_buffer_region 1
#define WGL_ARB_extensions_string 1
#define WGL_ARB_make_current_read 1
#define WGL_ARB_multisample 1
#define WGL_ARB_pbuffer 1
#define WGL_ARB_pixel_format 1
#define WGL_ARB_render_texture 1
/* multi-vendor extensions */
#define WGL_EXT_depth_float 1
#define WGL_EXT_display_color_table 1
#define WGL_EXT_extensions_string 1
#define WGL_EXT_make_current_read 1
#define WGL_EXT_multisample 1
#define WGL_EXT_swap_control 1
#define WGL_EXT_pixel_format 1
#define WGL_EXT_pbuffer 1
/* vendor-specific extensions */
#define WGL_I3D_digital_video_control 1
#define WGL_I3D_gamma 1
#define WGL_I3D_genlock 1
#define WGL_I3D_image_buffer 1 
#define WGL_I3D_swap_frame_lock 1
#define WGL_I3D_swap_frame_usage 1
#define WGL_OML_sync_control 1
/* ATI extensions */
#define WGL_ATI_pixel_format_float 1
/* NVIDIA extensions */
#define WGL_NV_float_buffer 1
#define WGL_NV_render_depth_texture 1
#define WGL_NV_render_texture_rectangle 1
#define WGL_NV_vertex_array_range 1

/* ---------------------------- ARB_buffer_region ------------------------- */

#ifdef WGL_ARB_buffer_region

#define WGL_FRONT_COLOR_BUFFER_BIT_ARB                          0x00000001
#define WGL_BACK_COLOR_BUFFER_BIT_ARB                           0x00000002
#define WGL_DEPTH_BUFFER_BIT_ARB                                0x00000004
#define WGL_STENCIL_BUFFER_BIT_ARB                              0x00000008

typedef HANDLE (APIENTRY * wglCreateBufferRegionARBPROC) (HDC hDC, int iLayerPlane, UINT uType);
typedef VOID (APIENTRY * wglDeleteBufferRegionARBPROC) (HANDLE hRegion);
typedef BOOL (APIENTRY * wglSaveBufferRegionARBPROC) (HANDLE hRegion, int x, int y, int width, int height);
typedef BOOL (APIENTRY * wglRestoreBufferRegionARBPROC) (HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);

extern GLEW_EXPORT wglCreateBufferRegionARBPROC wglCreateBufferRegionARB;
extern GLEW_EXPORT wglDeleteBufferRegionARBPROC wglDeleteBufferRegionARB;
extern GLEW_EXPORT wglSaveBufferRegionARBPROC wglSaveBufferRegionARB;
extern GLEW_EXPORT wglRestoreBufferRegionARBPROC wglRestoreBufferRegionARB;

#endif /* WGL_ARB_buffer_region */

/* -------------------------- ARB_extensions_string ----------------------- */

#ifdef WGL_ARB_extensions_string

typedef const char* (APIENTRY * wglGetExtensionsStringARBPROC) (HDC hdc);

extern GLEW_EXPORT wglGetExtensionsStringARBPROC wglGetExtensionsStringARB;

#endif /* WGL_ARB_extensions_string */

/* -------------------------- ARB_make_current_read ----------------------- */

#ifdef WGL_ARB_make_current_read

#define ERROR_INVALID_PIXEL_TYPE_ARB                            0x2043
#define ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB	                0x2054

typedef BOOL (APIENTRY * wglMakeContextCurrentARBPROC) (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
typedef HDC (APIENTRY * wglGetCurrentReadDCARBPROC) (void);

extern GLEW_EXPORT wglMakeContextCurrentARBPROC wglMakeContextCurrentARB;
extern GLEW_EXPORT wglGetCurrentReadDCARBPROC wglGetCurrentReadDCARB;

#endif /* WGL_ARB_make_current_read */

/* ----------------------------- ARB_multisample -------------------------- */

#ifdef WGL_ARB_multisample

#define WGL_SAMPLE_BUFFERS_ARB                                  0x2041
#define WGL_SAMPLES_ARB                                         0x2042

#endif /* WGL_ARB_multisample */

/* ------------------------------- ARB_pbuffer ---------------------------- */

#ifdef WGL_ARB_pbuffer

#define WGL_DRAW_TO_PBUFFER_ARB                                 0x202D
#define WGL_MAX_PBUFFER_PIXELS_ARB                              0x202E
#define WGL_MAX_PBUFFER_WIDTH_ARB                               0x202F
#define WGL_MAX_PBUFFER_HEIGHT_ARB                              0x2030
#define WGL_PBUFFER_LARGEST_ARB                                 0x2033
#define WGL_PBUFFER_WIDTH_ARB                                   0x2034
#define WGL_PBUFFER_HEIGHT_ARB                                  0x2035
#define WGL_PBUFFER_LOST_ARB                                    0x2036

DECLARE_HANDLE(HPBUFFERARB);

typedef HPBUFFERARB (APIENTRY * wglCreatePbufferARBPROC) (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
typedef HDC (APIENTRY * wglGetPbufferDCARBPROC) (HPBUFFERARB hPbuffer);
typedef int (APIENTRY * wglReleasePbufferDCARBPROC) (HPBUFFERARB hPbuffer, HDC hDC);
typedef BOOL (APIENTRY * wglDestroyPbufferARBPROC) (HPBUFFERARB hPbuffer);
typedef BOOL (APIENTRY * wglQueryPbufferARBPROC) (HPBUFFERARB hPbuffer, int iAttribute, int *piValue);

extern GLEW_EXPORT wglCreatePbufferARBPROC wglCreatePbufferARB;
extern GLEW_EXPORT wglGetPbufferDCARBPROC wglGetPbufferDCARB;
extern GLEW_EXPORT wglReleasePbufferDCARBPROC wglReleasePbufferDCARB;
extern GLEW_EXPORT wglDestroyPbufferARBPROC wglDestroyPbufferARB;
extern GLEW_EXPORT wglQueryPbufferARBPROC wglQueryPbufferARB;

#endif /* WGL_ARB_pbuffer */

/* ---------------------------- ARB_pixel_format -------------------------- */

#ifdef WGL_ARB_pixel_format

#define WGL_NUMBER_PIXEL_FORMATS_ARB                            0x2000
#define WGL_DRAW_TO_WINDOW_ARB                                  0x2001
#define WGL_DRAW_TO_BITMAP_ARB                                  0x2002
#define WGL_ACCELERATION_ARB                                    0x2003
#define WGL_NEED_PALETTE_ARB                                    0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB                             0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB                              0x2006
#define WGL_SWAP_METHOD_ARB                                     0x2007
#define WGL_NUMBER_OVERLAYS_ARB                                 0x2008
#define WGL_NUMBER_UNDERLAYS_ARB                                0x2009
#define WGL_TRANSPARENT_ARB                                     0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB                           0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB                         0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB                          0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB                         0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB                         0x203B
#define WGL_SHARE_DEPTH_ARB                                     0x200C
#define WGL_SHARE_STENCIL_ARB                                   0x200D
#define WGL_SHARE_ACCUM_ARB                                     0x200E
#define WGL_SUPPORT_GDI_ARB                                     0x200F
#define WGL_SUPPORT_OPENGL_ARB                                  0x2010
#define WGL_DOUBLE_BUFFER_ARB                                   0x2011
#define WGL_STEREO_ARB                                          0x2012
#define WGL_PIXEL_TYPE_ARB                                      0x2013
#define WGL_COLOR_BITS_ARB                                      0x2014
#define WGL_RED_BITS_ARB                                        0x2015
#define WGL_RED_SHIFT_ARB                                       0x2016
#define WGL_GREEN_BITS_ARB                                      0x2017
#define WGL_GREEN_SHIFT_ARB                                     0x2018
#define WGL_BLUE_BITS_ARB                                       0x2019
#define WGL_BLUE_SHIFT_ARB                                      0x201A
#define WGL_ALPHA_BITS_ARB                                      0x201B
#define WGL_ALPHA_SHIFT_ARB                                     0x201C
#define WGL_ACCUM_BITS_ARB                                      0x201D
#define WGL_ACCUM_RED_BITS_ARB                                  0x201E
#define WGL_ACCUM_GREEN_BITS_ARB                                0x201F
#define WGL_ACCUM_BLUE_BITS_ARB                                 0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB                                0x2021
#define WGL_DEPTH_BITS_ARB                                      0x2022
#define WGL_STENCIL_BITS_ARB                                    0x2023
#define WGL_AUX_BUFFERS_ARB                                     0x2024
#define WGL_NO_ACCELERATION_ARB                                 0x2025
#define WGL_GENERIC_ACCELERATION_ARB                            0x2026
#define WGL_FULL_ACCELERATION_ARB                               0x2027
#define WGL_SWAP_EXCHANGE_ARB                                   0x2028
#define WGL_SWAP_COPY_ARB                                       0x2029
#define WGL_SWAP_UNDEFINED_ARB                                  0x202A
#define WGL_TYPE_RGBA_ARB                                       0x202B
#define WGL_TYPE_COLORINDEX_ARB                                 0x202C

typedef BOOL (APIENTRY * wglGetPixelFormatAttribivARBPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
typedef BOOL (APIENTRY * wglGetPixelFormatAttribfvARBPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
typedef BOOL (APIENTRY * wglChoosePixelFormatARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

extern GLEW_EXPORT wglGetPixelFormatAttribivARBPROC wglGetPixelFormatAttribivARB;
extern GLEW_EXPORT wglGetPixelFormatAttribfvARBPROC wglGetPixelFormatAttribfvARB;
extern GLEW_EXPORT wglChoosePixelFormatARBPROC wglChoosePixelFormatARB;

#endif /* WGL_ARB_pixel_format */

/* --------------------------- ARB_render_texture ------------------------- */

#ifdef WGL_ARB_render_texture

#define WGL_BIND_TO_TEXTURE_RGB_ARB                             0x2070
#define WGL_BIND_TO_TEXTURE_RGBA_ARB                            0x2071
#define WGL_TEXTURE_FORMAT_ARB                                  0x2072
#define WGL_TEXTURE_TARGET_ARB                                  0x2073
#define WGL_MIPMAP_TEXTURE_ARB                                  0x2074
#define WGL_TEXTURE_RGB_ARB                                     0x2075
#define WGL_TEXTURE_RGBA_ARB                                    0x2076
#define WGL_NO_TEXTURE_ARB                                      0x2077
#define WGL_TEXTURE_CUBE_MAP_ARB                                0x2078
#define WGL_TEXTURE_1D_ARB                                      0x2079
#define WGL_TEXTURE_2D_ARB                                      0x207A
#define WGL_NO_TEXTURE_ARB                                      0x2077
#define WGL_MIPMAP_LEVEL_ARB                                    0x207B
#define WGL_CUBE_MAP_FACE_ARB                                   0x207C
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB                     0x207D
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB                     0x207E
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB                     0x207F
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB                     0x2080
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB                     0x2081
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB                     0x2082
#define WGL_FRONT_LEFT_ARB                                      0x2083
#define WGL_FRONT_RIGHT_ARB                                     0x2084
#define WGL_BACK_LEFT_ARB                                       0x2085
#define WGL_BACK_RIGHT_ARB                                      0x2086
#define WGL_AUX0_ARB                                            0x2087
#define WGL_AUX1_ARB                                            0x2088
#define WGL_AUX2_ARB                                            0x2089
#define WGL_AUX3_ARB                                            0x208A
#define WGL_AUX4_ARB                                            0x208B
#define WGL_AUX5_ARB                                            0x208C
#define WGL_AUX6_ARB                                            0x208D
#define WGL_AUX7_ARB                                            0x208E
#define WGL_AUX8_ARB                                            0x208F
#define WGL_AUX9_ARB                                            0x2090

typedef BOOL (APIENTRY * wglBindTexImageARBPROC) (HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (APIENTRY * wglReleaseTexImageARBPROC) (HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (APIENTRY * wglSetPbufferAttribARBPROC) (HPBUFFERARB hPbuffer, const int *piAttribList);

extern GLEW_EXPORT wglBindTexImageARBPROC wglBindTexImageARB;
extern GLEW_EXPORT wglReleaseTexImageARBPROC wglReleaseTexImageARB;
extern GLEW_EXPORT wglSetPbufferAttribARBPROC wglSetPbufferAttribARB;

#endif /* WGL_ARB_render_texture */

/* ----------------------------- EXT_depth_float -------------------------- */

#ifdef WGL_EXT_depth_float

#define WGL_DEPTH_FLOAT_EXT                                     0x2040

#endif /* WGL_EXT_depth_float */

/* ------------------------- EXT_display_color_table ---------------------- */

#ifdef WGL_EXT_display_color_table

typedef GLboolean (APIENTRY * wglCreateDisplayColorTableEXTPROC) (GLushort id);
typedef GLboolean (APIENTRY * wglLoadDisplayColorTableEXTPROC) (const GLushort *table, GLuint length);
typedef GLboolean (APIENTRY * wglBindDisplayColorTableEXTPROC) (GLushort id);
typedef void (APIENTRY * wglDestroyDisplayColorTableEXTPROC) (GLushort id);

extern GLEW_EXPORT wglCreateDisplayColorTableEXTPROC wglCreateDisplayColorTableEXT;
extern GLEW_EXPORT wglLoadDisplayColorTableEXTPROC wglLoadDisplayColorTableEXT;
extern GLEW_EXPORT wglBindDisplayColorTableEXTPROC wglBindDisplayColorTableEXT;
extern GLEW_EXPORT wglDestroyDisplayColorTableEXTPROC wglDestroyDisplayColorTableEXT;

#endif /* WGL_EXT_display_color_table */

/* -------------------------- EXT_extensions_string ----------------------- */

#ifdef WGL_EXT_extensions_string

typedef const char* (APIENTRY * wglGetExtensionsStringEXTPROC) ();

extern GLEW_EXPORT wglGetExtensionsStringEXTPROC wglGetExtensionsStringEXT;

#endif /* WGL_EXT_extensions_string */

/* -------------------------- EXT_make_current_read ----------------------- */

#ifdef WGL_EXT_make_current_read

#define ERROR_INVALID_PIXEL_TYPE_EXT                            0x2043

typedef BOOL (APIENTRY * wglMakeContextCurrentEXTPROC) (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
typedef HDC (APIENTRY * wglGetCurrentReadDCEXTPROC) (void);

extern GLEW_EXPORT wglMakeContextCurrentEXTPROC wglMakeContextCurrentEXT;
extern GLEW_EXPORT wglGetCurrentReadDCEXTPROC wglGetCurrentReadDCEXT;

#endif /* WGL_EXT_make_current_read */

/* ----------------------------- EXT_multisample -------------------------- */

#ifdef WGL_EXT_multisample

#define WGL_SAMPLE_BUFFERS_EXT                                  0x2041
#define WGL_SAMPLES_EXT                                         0x2042

#endif /* WGL_EXT_multisample */

/* ----------------------------- EXT_pixel_format ------------------------- */

#ifdef WGL_EXT_pixel_format

#define WGL_NUMBER_PIXEL_FORMATS_EXT                            0x2000
#define WGL_DRAW_TO_WINDOW_EXT                                  0x2001
#define WGL_DRAW_TO_BITMAP_EXT                                  0x2002
#define WGL_ACCELERATION_EXT                                    0x2003
#define WGL_NEED_PALETTE_EXT                                    0x2004
#define WGL_NEED_SYSTEM_PALETTE_EXT                             0x2005
#define WGL_SWAP_LAYER_BUFFERS_EXT                              0x2006
#define WGL_SWAP_METHOD_EXT                                     0x2007
#define WGL_NUMBER_OVERLAYS_EXT                                 0x2008
#define WGL_NUMBER_UNDERLAYS_EXT                                0x2009
#define WGL_TRANSPARENT_EXT                                     0x200A
#define WGL_TRANSPARENT_VALUE_EXT                               0x200B
#define WGL_SHARE_DEPTH_EXT                                     0x200C
#define WGL_SHARE_STENCIL_EXT                                   0x200D
#define WGL_SHARE_ACCUM_EXT                                     0x200E
#define WGL_SUPPORT_GDI_EXT                                     0x200F
#define WGL_SUPPORT_OPENGL_EXT                                  0x2010
#define WGL_DOUBLE_BUFFER_EXT                                   0x2011
#define WGL_STEREO_EXT                                          0x2012
#define WGL_PIXEL_TYPE_EXT                                      0x2013
#define WGL_COLOR_BITS_EXT                                      0x2014
#define WGL_RED_BITS_EXT                                        0x2015
#define WGL_RED_SHIFT_EXT                                       0x2016
#define WGL_GREEN_BITS_EXT                                      0x2017
#define WGL_GREEN_SHIFT_EXT                                     0x2018
#define WGL_BLUE_BITS_EXT                                       0x2019
#define WGL_BLUE_SHIFT_EXT                                      0x201A
#define WGL_ALPHA_BITS_EXT                                      0x201B
#define WGL_ALPHA_SHIFT_EXT                                     0x201C
#define WGL_ACCUM_BITS_EXT                                      0x201D
#define WGL_ACCUM_RED_BITS_EXT                                  0x201E
#define WGL_ACCUM_GREEN_BITS_EXT                                0x201F
#define WGL_ACCUM_BLUE_BITS_EXT                                 0x2020
#define WGL_ACCUM_ALPHA_BITS_EXT                                0x2021
#define WGL_DEPTH_BITS_EXT                                      0x2022
#define WGL_STENCIL_BITS_EXT                                    0x2023
#define WGL_AUX_BUFFERS_EXT                                     0x2024
#define WGL_NO_ACCELERATION_EXT                                 0x2025
#define WGL_GENERIC_ACCELERATION_EXT                            0x2026
#define WGL_FULL_ACCELERATION_EXT                               0x2027
#define WGL_SWAP_EXCHANGE_EXT                                   0x2028
#define WGL_SWAP_COPY_EXT                                       0x2029
#define WGL_SWAP_UNDEFINED_EXT                                  0x202A
#define WGL_TYPE_RGBA_EXT                                       0x202B
#define WGL_TYPE_COLORINDEX_EXT                                 0x202C

typedef BOOL (APIENTRY * wglGetPixelFormatAttribivEXTPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, int *piValues);
typedef BOOL (APIENTRY * wglGetPixelFormatAttribfvEXTPROC) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, FLOAT *pfValues);
typedef BOOL (APIENTRY * wglChoosePixelFormatEXTPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

extern GLEW_EXPORT wglGetPixelFormatAttribivEXTPROC wglGetPixelFormatAttribivEXT;
extern GLEW_EXPORT wglGetPixelFormatAttribfvEXTPROC wglGetPixelFormatAttribfvEXT;
extern GLEW_EXPORT wglChoosePixelFormatEXTPROC wglChoosePixelFormatEXT;

#endif /* WGL_EXT_pixel_format */

/* ------------------------------- EXT_pbuffer ---------------------------- */

#ifdef WGL_EXT_pbuffer

#define WGL_DRAW_TO_PBUFFER_EXT                                 0x202D
#define WGL_MAX_PBUFFER_PIXELS_EXT                              0x202E
#define WGL_MAX_PBUFFER_WIDTH_EXT                               0x202F
#define WGL_MAX_PBUFFER_HEIGHT_EXT                              0x2030
#define WGL_OPTIMAL_PBUFFER_WIDTH_EXT                           0x2031
#define WGL_OPTIMAL_PBUFFER_HEIGHT_EXT                          0x2032
#define WGL_PBUFFER_LARGEST_EXT                                 0x2033
#define WGL_PBUFFER_WIDTH_EXT                                   0x2034
#define WGL_PBUFFER_HEIGHT_EXT                                  0x2035

DECLARE_HANDLE(HPBUFFEREXT);

typedef HPBUFFEREXT (APIENTRY * wglCreatePbufferEXTPROC) (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
typedef HDC (APIENTRY * wglGetPbufferDCEXTPROC) (HPBUFFEREXT hPbuffer);
typedef int (APIENTRY * wglReleasePbufferDCEXTPROC) (HPBUFFEREXT hPbuffer, HDC hDC);
typedef BOOL (APIENTRY * wglDestroyPbufferEXTPROC) (HPBUFFEREXT hPbuffer);
typedef BOOL (APIENTRY * wglQueryPbufferEXTPROC) (HPBUFFEREXT hPbuffer, int iAttribute, int *piValue);

extern GLEW_EXPORT wglCreatePbufferEXTPROC wglCreatePbufferEXT;
extern GLEW_EXPORT wglGetPbufferDCEXTPROC wglGetPbufferDCEXT;
extern GLEW_EXPORT wglReleasePbufferDCEXTPROC wglReleasePbufferDCEXT;
extern GLEW_EXPORT wglDestroyPbufferEXTPROC wglDestroyPbufferEXT;
extern GLEW_EXPORT wglQueryPbufferEXTPROC wglQueryPbufferEXT;

#endif /* WGL_EXT_pbuffer */

/* ---------------------------- EXT_swap_control -------------------------- */

#ifdef WGL_EXT_swap_control

typedef BOOL (APIENTRY * wglSwapIntervalEXTPROC) (int interval);
typedef int (APIENTRY * wglGetSwapIntervalEXTPROC) (void);

extern GLEW_EXPORT wglSwapIntervalEXTPROC wglSwapIntervalEXT;
extern GLEW_EXPORT wglGetSwapIntervalEXTPROC wglGetSwapIntervalEXT;

#endif /* WGL_EXT_swap_control */

/* ------------------------ I3D_digital_video_control --------------------- */

#ifdef WGL_I3D_digital_video_control

#define WGL_DIGITAL_VIDEO_CURSOR_ALPHA_FRAMEBUFFER_I3D          0x2050
#define WGL_DIGITAL_VIDEO_CURSOR_ALPHA_VALUE_I3D                0x2051
#define WGL_DIGITAL_VIDEO_CURSOR_INCLUDED_I3D                   0x2052
#define WGL_DIGITAL_VIDEO_GAMMA_CORRECTED_I3D                   0x2053

typedef BOOL (APIENTRY * wglGetDigitalVideoParametersI3DPROC) (HDC hDC, int iAttribute, int *piValue);
typedef BOOL (APIENTRY * wglSetDigitalVideoParametersI3DPROC) (HDC hDC, int iAttribute, const int *piValue);

extern GLEW_EXPORT wglGetDigitalVideoParametersI3DPROC wglGetDigitalVideoParametersI3D;
extern GLEW_EXPORT wglSetDigitalVideoParametersI3DPROC wglSetDigitalVideoParametersI3D;

#endif /* WGL_I3D_digital_video_control */

/* -------------------------------- I3D_gamma ----------------------------- */

#ifdef WGL_I3D_gamma

#define WGL_GAMMA_TABLE_SIZE_I3D                                0x204E
#define WGL_GAMMA_EXCLUDE_DESKTOP_I3D                           0x204F

typedef BOOL (APIENTRY * wglGetGammaTableParametersI3DPROC) (HDC hDC, int iAttribute, int *piValue);
typedef BOOL (APIENTRY * wglSetGammaTableParametersI3DPROC) (HDC hDC, int iAttribute, const int *piValue);
typedef BOOL (APIENTRY * wglGetGammaTableI3DPROC) (HDC hDC, int iEntries, USHORT *puRed, USHORT *puGreen, USHORT *puBlue);
typedef BOOL (APIENTRY * wglSetGammaTableI3DPROC) (HDC hDC, int iEntries, const USHORT *puRed, const USHORT *puGreen, const USHORT *puBlue);

extern GLEW_EXPORT wglGetGammaTableParametersI3DPROC wglGetGammaTableParametersI3D;
extern GLEW_EXPORT wglSetGammaTableParametersI3DPROC wglSetGammaTableParametersI3D;
extern GLEW_EXPORT wglGetGammaTableI3DPROC wglGetGammaTableI3D;
extern GLEW_EXPORT wglSetGammaTableI3DPROC wglSetGammaTableI3D;

#endif /* WGL_I3D_gamma */

/* ------------------------------- I3D_genlock ---------------------------- */

#ifdef WGL_I3D_genlock

#define WGL_GENLOCK_SOURCE_MULTIVIEW_I3D                        0x2044
#define WGL_GENLOCK_SOURCE_EXTENAL_SYNC_I3D                     0x2045
#define WGL_GENLOCK_SOURCE_EXTENAL_FIELD_I3D                    0x2046
#define WGL_GENLOCK_SOURCE_EXTENAL_TTL_I3D                      0x2047
#define WGL_GENLOCK_SOURCE_DIGITAL_SYNC_I3D                     0x2048
#define WGL_GENLOCK_SOURCE_DIGITAL_FIELD_I3D                    0x2049
#define WGL_GENLOCK_SOURCE_EDGE_FALLING_I3D                     0x204A
#define WGL_GENLOCK_SOURCE_EDGE_RISING_I3D                      0x204B
#define WGL_GENLOCK_SOURCE_EDGE_BOTH_I3D                        0x204C

typedef BOOL (APIENTRY * wglEnableGenlockI3DPROC) (HDC hDC);
typedef BOOL (APIENTRY * wglDisableGenlockI3DPROC) (HDC hDC);
typedef BOOL (APIENTRY * wglIsEnabledGenlockI3DPROC) (HDC hDC, BOOL *pFlag);
typedef BOOL (APIENTRY * wglGenlockSourceI3DPROC) (HDC hDC, UINT uSource);
typedef BOOL (APIENTRY * wglGetGenlockSourceI3DPROC) (HDC hDC, UINT *uSource);
typedef BOOL (APIENTRY * wglGenlockSourceEdgeI3DPROC) (HDC hDC, UINT uEdge);
typedef BOOL (APIENTRY * wglGetGenlockSourceEdgeI3DPROC) (HDC hDC, UINT *uEdge);
typedef BOOL (APIENTRY * wglGenlockSampleRateI3DPROC) (HDC hDC, UINT uRate);
typedef BOOL (APIENTRY * wglGetGenlockSampleRateI3DPROC) (HDC hDC, UINT *uRate);
typedef BOOL (APIENTRY * wglGenlockSourceDelayI3DPROC) (HDC hDC, UINT uDelay);
typedef BOOL (APIENTRY * wglGetGenlockSourceDelayI3DPROC) (HDC hDC, UINT *uDelay);
typedef BOOL (APIENTRY * wglQueryGenlockMaxSourceDelayI3DPROC) (HDC hDC, UINT *uMaxLineDelay, UINT *uMaxPixelDelay);

extern GLEW_EXPORT wglEnableGenlockI3DPROC wglEnableGenlockI3D;
extern GLEW_EXPORT wglDisableGenlockI3DPROC wglDisableGenlockI3D;
extern GLEW_EXPORT wglIsEnabledGenlockI3DPROC wglIsEnabledGenlockI3D;
extern GLEW_EXPORT wglGenlockSourceI3DPROC wglGenlockSourceI3D;
extern GLEW_EXPORT wglGetGenlockSourceI3DPROC wglGetGenlockSourceI3D;
extern GLEW_EXPORT wglGenlockSourceEdgeI3DPROC wglGenlockSourceEdgeI3D;
extern GLEW_EXPORT wglGetGenlockSourceEdgeI3DPROC wglGetGenlockSourceEdgeI3D;
extern GLEW_EXPORT wglGenlockSampleRateI3DPROC wglGenlockSampleRateI3D;
extern GLEW_EXPORT wglGetGenlockSampleRateI3DPROC wglGetGenlockSampleRateI3D;
extern GLEW_EXPORT wglGenlockSourceDelayI3DPROC wglGenlockSourceDelayI3D;
extern GLEW_EXPORT wglGetGenlockSourceDelayI3DPROC wglGetGenlockSourceDelayI3D;
extern GLEW_EXPORT wglQueryGenlockMaxSourceDelayI3DPROC wglQueryGenlockMaxSourceDelayI3D;

#endif /* WGL_I3D_genlock */

/* ---------------------------- I3D_image_buffer -------------------------- */

#ifdef WGL_I3D_image_buffer

#define WGL_IMAGE_BUFFER_MIN_ACCESS_I3D                         0x00000001
#define WGL_IMAGE_BUFFER_LOCK_I3D                               0x00000002

typedef LPVOID (APIENTRY * wglCreateImageBufferI3DPROC) (HDC hDC, DWORD dwSize, UINT uFlags);
typedef BOOL (APIENTRY * wglDestroyImageBufferI3DPROC) (HDC hDC, LPVOID pAddress);
typedef BOOL (APIENTRY * wglAssociateImageBufferEventsI3DPROC) (HDC hDC, const HANDLE *pEvent, const LPVOID *pAddress, const DWORD *pSize, UINT count);
typedef BOOL (APIENTRY * wglReleaseImageBufferEventsI3DPROC) (HDC hDC, const LPVOID *pAddress, UINT count);

extern GLEW_EXPORT wglCreateImageBufferI3DPROC wglCreateImageBufferI3D;
extern GLEW_EXPORT wglDestroyImageBufferI3DPROC wglDestroyImageBufferI3D;
extern GLEW_EXPORT wglAssociateImageBufferEventsI3DPROC wglAssociateImageBufferEventsI3D; 
extern GLEW_EXPORT wglReleaseImageBufferEventsI3DPROC wglReleaseImageBufferEventsI3D;

#endif /* WGL_I3D_image_buffer */

/* --------------------------- I3D_swap_frame_lock ------------------------ */

#ifdef WGL_I3D_swap_frame_lock

typedef BOOL (APIENTRY * wglEnableFrameLockI3DPROC) (void);
typedef BOOL (APIENTRY * wglDisableFrameLockI3DPROC) (void);
typedef BOOL (APIENTRY * wglIsEnabledFrameLockI3DPROC) (BOOL *pFlag);
typedef BOOL (APIENTRY * wglQueryFrameLockMasterI3DPROC) (BOOL *pFlag);

extern GLEW_EXPORT wglEnableFrameLockI3DPROC wglEnableFrameLockI3D;
extern GLEW_EXPORT wglDisableFrameLockI3DPROC wglDisableFrameLockI3D;
extern GLEW_EXPORT wglIsEnabledFrameLockI3DPROC wglIsEnabledFrameLockI3D;
extern GLEW_EXPORT wglQueryFrameLockMasterI3DPROC wglQueryFrameLockMasterI3D;

#endif /* WGL_I3D_swap_frame_lock */

/* -------------------------- I3D_swap_frame_usage ------------------------ */

#ifdef WGL_I3D_swap_frame_usage

typedef BOOL (APIENTRY * wglGetFrameUsageI3DPROC) (float *pUsage);
typedef BOOL (APIENTRY * wglBeginFrameTrackingI3DPROC) (void);
typedef BOOL (APIENTRY * wglEndFrameTrackingI3DPROC) (void);
typedef BOOL (APIENTRY * wglQueryFrameTrackingI3DPROC) (DWORD *pFrameCount, DWORD *pMissedFrames, float *pLastMissedUsage);

extern GLEW_EXPORT wglGetFrameUsageI3DPROC wglGetFrameUsageI3D;
extern GLEW_EXPORT wglBeginFrameTrackingI3DPROC wglBeginFrameTrackingI3D;
extern GLEW_EXPORT wglEndFrameTrackingI3DPROC wglEndFrameTrackingI3D;
extern GLEW_EXPORT wglQueryFrameTrackingI3DPROC wglQueryFrameTrackingI3D;

#endif /* WGL_I3D_swap_frame_usage */

/* ---------------------------- OML_sync_control -------------------------- */

#ifdef WGL_OML_sync_control

typedef BOOL (APIENTRY * wglGetSyncValuesOMLPROC) (HDC hdc, INT64 *ust, INT64 *msc, INT64 *sbc);
typedef BOOL (APIENTRY * wglGetMscRateOMLPROC) (HDC hdc, INT32 *numerator, INT32 *denominator);
typedef INT64 (APIENTRY * wglSwapBuffersMscOMLPROC) (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder);
typedef INT64 (APIENTRY * wglSwapLayerBuffersMscOMLPROC) (HDC hdc, int fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder);
typedef BOOL (APIENTRY * wglWaitForMscOMLPROC) (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 *ust, INT64 *msc, INT64 *sbc);
typedef BOOL (APIENTRY * wglWaitForSbcOMLPROC) (HDC hdc, INT64 target_sbc, INT64 *ust, INT64 *msc, INT64 *sbc);

extern GLEW_EXPORT wglGetSyncValuesOMLPROC wglGetSyncValuesOML;
extern GLEW_EXPORT wglGetMscRateOMLPROC wglGetMscRateOML;
extern GLEW_EXPORT wglSwapBuffersMscOMLPROC wglSwapBuffersMscOML;
extern GLEW_EXPORT wglSwapLayerBuffersMscOMLPROC wglSwapLayerBuffersMscOML;
extern GLEW_EXPORT wglWaitForMscOMLPROC wglWaitForMscOML;
extern GLEW_EXPORT wglWaitForSbcOMLPROC wglWaitForSbcOML;

#endif /* WGL_OML_sync_control */

/* ------------------------- ATI_pixel_format_float ----------------------- */

#ifdef WGL_ATI_pixel_format_float

#define WGL_TYPE_RGBA_FLOAT_ATI                                 0x21A0
#define GL_TYPE_RGBA_FLOAT_ATI                                  0x8820
#define GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI                      0x8835

#endif /* WGL_ATI_pixel_format_float */

/* ---------------------------- NV_float_buffer --------------------------- */

#ifdef WGL_NV_float_buffer

#define WGL_FLOAT_COMPONENTS_NV                                 0x20B0
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV                0x20B1
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV               0x20B2
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV              0x20B3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV             0x20B4
#define WGL_TEXTURE_FLOAT_R_NV                                  0x20B5
#define WGL_TEXTURE_FLOAT_RG_NV                                 0x20B6
#define WGL_TEXTURE_FLOAT_RGB_NV                                0x20B7
#define WGL_TEXTURE_FLOAT_RGBA_NV                               0x20B8

#endif /* WGL_NV_float_buffer */

/* ------------------------- NV_render_depth_texture ---------------------- */

#ifdef WGL_NV_render_depth_texture

#define WGL_BIND_TO_TEXTURE_DEPTH_NV                            0x20A3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_DEPTH_NV                  0x20A4
#define WGL_DEPTH_TEXTURE_FORMAT_NV                             0x20A5
#define WGL_TEXTURE_DEPTH_COMPONENT_NV                          0x20A6
#define WGL_NO_TEXTURE_ARB                                      0x2077
#define WGL_DEPTH_COMPONENT_NV                                  0x20A7

#endif /* WGL_NV_render_depth_texture */

/* ----------------------- NV_render_texture_rectangle -------------------- */

#ifdef WGL_NV_render_texture_rectangle 

#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGB_NV                    0x20A0
#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGBA_NV                   0x20A1
#define WGL_TEXTURE_RECTANGLE_NV                                0x20A2

#endif /* WGL_NV_render_texture_rectangle */

/* ------------------------- NV_vertex_array_range ------------------------ */

#ifdef WGL_NV_vertex_array_range

typedef void * (APIENTRY * wglAllocateMemoryNVPROC) (GLsizei size, GLfloat readFrequency, GLfloat writeFrequency, GLfloat priority);
typedef void (APIENTRY * wglFreeMemoryNVPROC) (void *pointer);

extern GLEW_EXPORT wglAllocateMemoryNVPROC wglAllocateMemoryNV;
extern GLEW_EXPORT wglFreeMemoryNVPROC wglFreeMemoryNV;

#endif /* WGL_NV_vertex_array_range */

/* ------------------------------------------------------------------------ */

struct WGLEW
{
  unsigned int ARB_buffer_region : 1;
  unsigned int ARB_extensions_string : 1;
  unsigned int ARB_make_current_read : 1;
  unsigned int ARB_multisample : 1;
  unsigned int ARB_pbuffer : 1;
  unsigned int ARB_pixel_format : 1;
  unsigned int ARB_render_texture : 1;

  unsigned int EXT_depth_float : 1;
  unsigned int EXT_display_color_table : 1;
  unsigned int EXT_extensions_string : 1;
  unsigned int EXT_make_current_read : 1;
  unsigned int EXT_multisample : 1;
  unsigned int EXT_pixel_format : 1;
  unsigned int EXT_pbuffer : 1;
  unsigned int EXT_swap_control : 1;

  unsigned int I3D_digital_video_control : 1;
  unsigned int I3D_gamma : 1;
  unsigned int I3D_genlock : 1;
  unsigned int I3D_image_buffer : 1;
  unsigned int I3D_swap_frame_lock : 1;
  unsigned int I3D_swap_frame_usage : 1;
  unsigned int OML_sync_control : 1;

  unsigned int ATI_pixel_format_float : 1;

  unsigned int NV_float_buffer : 1;
  unsigned int NV_render_depth_texture : 1;
  unsigned int NV_render_texture_rectangle : 1;
  unsigned int NV_vertex_array_range : 1;
};

extern GLEW_EXPORT struct WGLEW wglew;

#ifdef __cplusplus
}
#endif

#undef GLEW_EXPORT

#endif /* _WIN32 */

#endif /* __wglew_h__ */
