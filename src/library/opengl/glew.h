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
** * The name of the author may be used to endorse or promote products
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

#ifndef __glew_h__
#define __glew_h__

#if defined(__gl_h_) || defined(__GL_H__)
#error gl.h included before glew.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error glext.h included before glew.h
#endif
#if defined(__gl_ATI_h_)
#error glATI.h included before glew.h
#endif

#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gl_ATI_h_

#ifdef _WIN32

/*
 * GLEW does not include <windows.h> to avoid name space pollution.
 * GL needs APIENTRY and WINGDIAPI, GLU needs CALLBACK and wchar_t
 * defined properly.
 */
/* <windef.h> */
#ifndef APIENTRY
#define GLEW_APIENTRY_DEFINED
#if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define APIENTRY __stdcall
#else
#define APIENTRY
#endif
#endif
/* <winnt.h> */
#ifndef CALLBACK
#if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
#define CALLBACK __stdcall
#else
#define CALLBACK
#endif
#endif
/* <wingdi.h> and <winnt.h> */
#ifndef WINGDIAPI
#define GLEW_WINGDIAPI_DEFINED
#define WINGDIAPI __declspec(dllimport)
#endif
/* <ctype.h> */
//#ifndef _WCHAR_T_DEFINED
//typedef unsigned short wchar_t;
//#define _WCHAR_T_DEFINED
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

#else /* _UNIX */

#define APIENTRY
#define GLEW_EXPORT

#endif /* _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

/* core OpenGL */
#define GL_VERSION_1_1 1
#define GL_VERSION_1_2 1
#define GL_VERSION_1_3 1
#define GL_VERSION_1_4 1

/* ARB extensions */
#define GL_ARB_depth_texture 1 /* (1.4) */
#define GL_ARB_fragment_program 1
#define GL_ARB_imaging 1 /* (1.2) */
#define GL_ARB_matrix_palette 1
#define GL_ARB_multisample 1 /* (1.3) */
#define GL_ARB_multitexture 1 /* (1.3) */
#define GL_ARB_point_parameters 1 /* (1.4) */
#define GL_ARB_shadow 1 /* (1.4) */
#define GL_ARB_shadow_ambient 1
#define GL_ARB_texture_border_clamp 1 /* (1.3) */
#define GL_ARB_texture_compression 1 /* (1.3) */
#define GL_ARB_texture_cube_map 1 /* (1.3) */
#define GL_ARB_texture_env_add 1 /* (1.3) */
#define GL_ARB_texture_env_combine 1 /* (1.3) */
#define GL_ARB_texture_env_crossbar 1 /* (1.3) */
#define GL_ARB_texture_env_dot3 1 /* (1.3) */
#define GL_ARB_texture_mirrored_repeat 1 /* (1.4) */
#define GL_ARB_transpose_matrix 1 /* (1.3) */
#define GL_ARB_vertex_blend 1
#define GL_ARB_vertex_program 1
#define GL_ARB_window_pos 1 /* (1.4) */

/* multi-vendor extensions */
#define GL_EXT_abgr 1
#define GL_EXT_bgra 1 /* (1.2) */
#define GL_EXT_blend_color 1 /* (1.2) */
#define GL_EXT_blend_func_separate 1 /* (1.4) */
#define GL_EXT_blend_minmax 1 /* (1.2) */
#define GL_EXT_blend_subtract 1 /* (1.4) */
#define GL_EXT_clip_volume_hint 1
#define GL_EXT_compiled_vertex_array 1
#define GL_EXT_draw_range_elements 1 /* (1.2) */
#define GL_EXT_cull_vertex 1
#define GL_EXT_fog_coord 1 /* (1.4) */
#define GL_EXT_multi_draw_arrays 1 /* (1.4) */
#define GL_EXT_packed_pixels 1 /* (1.2) */
#define GL_EXT_point_parameters 1 /* (1.4) */
#define GL_EXT_secondary_color 1 /* (1.4) */
#define GL_EXT_separate_specular_color 1 /* (1.2) */
#define GL_EXT_shadow_funcs 1 /* ??? */
#define GL_EXT_stencil_two_side 1
#define GL_EXT_stencil_wrap 1 /* (1.4) */
#define GL_EXT_texture_compression_s3tc 1
#define GL_EXT_texture_filter_anisotropic 1
#define GL_EXT_texture_lod_bias 1 /* (1.4) */
#define GL_EXT_texture_rectangle 1
#define GL_EXT_vertex_shader 1
#define GL_EXT_vertex_weighting 1

/* vendor-specific extensions */
#define GL_SGIS_generate_mipmap 1
#define GL_SGIS_texture_lod 1
#define GL_SGIX_depth_texture 1 /* (1.4) */
#define GL_SGIX_shadow 1

#define GL_HP_occlusion_test 1
#define GL_S3_s3tc 1
#define GL_WIN_swap_hint 1

/* ATI extensions */
#define GL_ATI_draw_buffers 1
#define GL_ATI_element_array 1
#define GL_ATI_envmap_bumpmap 1
#define GL_ATI_fragment_shader 1
#define GL_ATI_map_object_buffer 1
#define GL_ATI_mapped_texture 1
#define GL_ATI_pn_triangles 1
#define GL_ATI_point_cull_mode 1
#define GL_ATI_separate_stencil 1
#define GL_ATI_text_fragment_shader 1
#define GL_ATI_texture_float 1
#define GL_ATI_texture_mirror_once 1
#define GL_ATI_timestamp 1
#define GL_ATI_vertex_array_object 1
#define GL_ATI_vertex_attrib_array_object 1
#define GL_ATI_vertex_streams 1
#define GL_ATIX_point_sprites 1
#define GL_ATIX_texture_env_combine3 1
#define GL_ATIX_texture_env_route 1
#define GL_ATIX_vertex_shader_output_point_size 1

/* NVIDIA extensions */
#define GL_NV_blend_square 1
#define GL_NV_copy_depth_to_color 1
#define GL_NV_depth_clamp 1
#define GL_NV_element_array 1
#define GL_NV_evaluators 1
#define GL_NV_fence 1
#define GL_NV_fog_distance 1
#define GL_NV_float_buffer 1
#define GL_NV_fragment_program 1
#define GL_NV_light_max_exponent 1
#define GL_NV_multisample_filter_hint 1
#define GL_NV_occlusion_query 1
#define GL_NV_packed_depth_stencil 1
#define GL_NV_pixel_data_range 1
#define GL_NV_point_sprite 1
#define GL_NV_primitive_restart 1
#define GL_NV_register_combiners 1
#define GL_NV_register_combiners2 1
#define GL_NV_texgen_reflection 1
#define GL_NV_texture_compression_vtc 1
#define GL_NV_texture_env_combine4 1
#define GL_NV_texture_rectangle 1
#define GL_NV_texture_shader 1
#define GL_NV_texture_shader2 1
#define GL_NV_texture_shader3 1
#define GL_NV_vertex_array_range 1
#define GL_NV_vertex_array_range2 1
#define GL_NV_vertex_program 1
#define GL_NV_vertex_program1_1 1
#define GL_NV_vertex_program2 1

/* ------------------------------ OpenGL 1.1 ------------------------------ */

#ifdef GL_VERSION_1_1

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

#define GL_VERSION_1_1                                          1
#define GL_ACCUM                                                0x0100
#define GL_LOAD                                                 0x0101
#define GL_RETURN                                               0x0102
#define GL_MULT                                                 0x0103
#define GL_ADD                                                  0x0104
#define GL_NEVER                                                0x0200
#define GL_LESS                                                 0x0201
#define GL_EQUAL                                                0x0202
#define GL_LEQUAL                                               0x0203
#define GL_GREATER                                              0x0204
#define GL_NOTEQUAL                                             0x0205
#define GL_GEQUAL                                               0x0206
#define GL_ALWAYS                                               0x0207
#define GL_CURRENT_BIT                                          0x00000001
#define GL_POINT_BIT                                            0x00000002
#define GL_LINE_BIT                                             0x00000004
#define GL_POLYGON_BIT                                          0x00000008
#define GL_POLYGON_STIPPLE_BIT                                  0x00000010
#define GL_PIXEL_MODE_BIT                                       0x00000020
#define GL_LIGHTING_BIT                                         0x00000040
#define GL_FOG_BIT                                              0x00000080
#define GL_DEPTH_BUFFER_BIT                                     0x00000100
#define GL_ACCUM_BUFFER_BIT                                     0x00000200
#define GL_STENCIL_BUFFER_BIT                                   0x00000400
#define GL_VIEWPORT_BIT                                         0x00000800
#define GL_TRANSFORM_BIT                                        0x00001000
#define GL_ENABLE_BIT                                           0x00002000
#define GL_COLOR_BUFFER_BIT                                     0x00004000
#define GL_HINT_BIT                                             0x00008000
#define GL_EVAL_BIT                                             0x00010000
#define GL_LIST_BIT                                             0x00020000
#define GL_TEXTURE_BIT                                          0x00040000
#define GL_SCISSOR_BIT                                          0x00080000
#define GL_ALL_ATTRIB_BITS                                      0x000fffff
#define GL_POINTS                                               0x0000
#define GL_LINES                                                0x0001
#define GL_LINE_LOOP                                            0x0002
#define GL_LINE_STRIP                                           0x0003
#define GL_TRIANGLES                                            0x0004
#define GL_TRIANGLE_STRIP                                       0x0005
#define GL_TRIANGLE_FAN                                         0x0006
#define GL_QUADS                                                0x0007
#define GL_QUAD_STRIP                                           0x0008
#define GL_POLYGON                                              0x0009
#define GL_ZERO                                                 0
#define GL_ONE                                                  1
#define GL_SRC_COLOR                                            0x0300
#define GL_ONE_MINUS_SRC_COLOR                                  0x0301
#define GL_SRC_ALPHA                                            0x0302
#define GL_ONE_MINUS_SRC_ALPHA                                  0x0303
#define GL_DST_ALPHA                                            0x0304
#define GL_ONE_MINUS_DST_ALPHA                                  0x0305
#define GL_DST_COLOR                                            0x0306
#define GL_ONE_MINUS_DST_COLOR                                  0x0307
#define GL_SRC_ALPHA_SATURATE                                   0x0308
#define GL_TRUE                                                 1
#define GL_FALSE                                                0
#define GL_CLIP_PLANE0                                          0x3000
#define GL_CLIP_PLANE1                                          0x3001
#define GL_CLIP_PLANE2                                          0x3002
#define GL_CLIP_PLANE3                                          0x3003
#define GL_CLIP_PLANE4                                          0x3004
#define GL_CLIP_PLANE5                                          0x3005
#define GL_BYTE                                                 0x1400
#define GL_UNSIGNED_BYTE                                        0x1401
#define GL_SHORT                                                0x1402
#define GL_UNSIGNED_SHORT                                       0x1403
#define GL_INT                                                  0x1404
#define GL_UNSIGNED_INT                                         0x1405
#define GL_FLOAT                                                0x1406
#define GL_2_BYTES                                              0x1407
#define GL_3_BYTES                                              0x1408
#define GL_4_BYTES                                              0x1409
#define GL_DOUBLE                                               0x140A
#define GL_NONE                                                 0
#define GL_FRONT_LEFT                                           0x0400
#define GL_FRONT_RIGHT                                          0x0401
#define GL_BACK_LEFT                                            0x0402
#define GL_BACK_RIGHT                                           0x0403
#define GL_FRONT                                                0x0404
#define GL_BACK                                                 0x0405
#define GL_LEFT                                                 0x0406
#define GL_RIGHT                                                0x0407
#define GL_FRONT_AND_BACK                                       0x0408
#define GL_AUX0                                                 0x0409
#define GL_AUX1                                                 0x040A
#define GL_AUX2                                                 0x040B
#define GL_AUX3                                                 0x040C
#define GL_NO_ERROR                                             0
#define GL_INVALID_ENUM                                         0x0500
#define GL_INVALID_VALUE                                        0x0501
#define GL_INVALID_OPERATION                                    0x0502
#define GL_STACK_OVERFLOW                                       0x0503
#define GL_STACK_UNDERFLOW                                      0x0504
#define GL_OUT_OF_MEMORY                                        0x0505
#define GL_2D                                                   0x0600
#define GL_3D                                                   0x0601
#define GL_3D_COLOR                                             0x0602
#define GL_3D_COLOR_TEXTURE                                     0x0603
#define GL_4D_COLOR_TEXTURE                                     0x0604
#define GL_PASS_THROUGH_TOKEN                                   0x0700
#define GL_POINT_TOKEN                                          0x0701
#define GL_LINE_TOKEN                                           0x0702
#define GL_POLYGON_TOKEN                                        0x0703
#define GL_BITMAP_TOKEN                                         0x0704
#define GL_DRAW_PIXEL_TOKEN                                     0x0705
#define GL_COPY_PIXEL_TOKEN                                     0x0706
#define GL_LINE_RESET_TOKEN                                     0x0707
#define GL_EXP                                                  0x0800
#define GL_EXP2                                                 0x0801
#define GL_CW                                                   0x0900
#define GL_CCW                                                  0x0901
#define GL_COEFF                                                0x0A00
#define GL_ORDER                                                0x0A01
#define GL_DOMAIN                                               0x0A02
#define GL_CURRENT_COLOR                                        0x0B00
#define GL_CURRENT_INDEX                                        0x0B01
#define GL_CURRENT_NORMAL                                       0x0B02
#define GL_CURRENT_TEXTURE_COORDS                               0x0B03
#define GL_CURRENT_RASTER_COLOR                                 0x0B04
#define GL_CURRENT_RASTER_INDEX                                 0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS                        0x0B06
#define GL_CURRENT_RASTER_POSITION                              0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID                        0x0B08
#define GL_CURRENT_RASTER_DISTANCE                              0x0B09
#define GL_POINT_SMOOTH                                         0x0B10
#define GL_POINT_SIZE                                           0x0B11
#define GL_POINT_SIZE_RANGE                                     0x0B12
#define GL_POINT_SIZE_GRANULARITY                               0x0B13
#define GL_LINE_SMOOTH                                          0x0B20
#define GL_LINE_WIDTH                                           0x0B21
#define GL_LINE_WIDTH_RANGE                                     0x0B22
#define GL_LINE_WIDTH_GRANULARITY                               0x0B23
#define GL_LINE_STIPPLE                                         0x0B24
#define GL_LINE_STIPPLE_PATTERN                                 0x0B25
#define GL_LINE_STIPPLE_REPEAT                                  0x0B26
#define GL_LIST_MODE                                            0x0B30
#define GL_MAX_LIST_NESTING                                     0x0B31
#define GL_LIST_BASE                                            0x0B32
#define GL_LIST_INDEX                                           0x0B33
#define GL_POLYGON_MODE                                         0x0B40
#define GL_POLYGON_SMOOTH                                       0x0B41
#define GL_POLYGON_STIPPLE                                      0x0B42
#define GL_EDGE_FLAG                                            0x0B43
#define GL_CULL_FACE                                            0x0B44
#define GL_CULL_FACE_MODE                                       0x0B45
#define GL_FRONT_FACE                                           0x0B46
#define GL_LIGHTING                                             0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER                             0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE                                 0x0B52
#define GL_LIGHT_MODEL_AMBIENT                                  0x0B53
#define GL_SHADE_MODEL                                          0x0B54
#define GL_COLOR_MATERIAL_FACE                                  0x0B55
#define GL_COLOR_MATERIAL_PARAMETER                             0x0B56
#define GL_COLOR_MATERIAL                                       0x0B57
#define GL_FOG                                                  0x0B60
#define GL_FOG_INDEX                                            0x0B61
#define GL_FOG_DENSITY                                          0x0B62
#define GL_FOG_START                                            0x0B63
#define GL_FOG_END                                              0x0B64
#define GL_FOG_MODE                                             0x0B65
#define GL_FOG_COLOR                                            0x0B66
#define GL_DEPTH_RANGE                                          0x0B70
#define GL_DEPTH_TEST                                           0x0B71
#define GL_DEPTH_WRITEMASK                                      0x0B72
#define GL_DEPTH_CLEAR_VALUE                                    0x0B73
#define GL_DEPTH_FUNC                                           0x0B74
#define GL_ACCUM_CLEAR_VALUE                                    0x0B80
#define GL_STENCIL_TEST                                         0x0B90
#define GL_STENCIL_CLEAR_VALUE                                  0x0B91
#define GL_STENCIL_FUNC                                         0x0B92
#define GL_STENCIL_VALUE_MASK                                   0x0B93
#define GL_STENCIL_FAIL                                         0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL                              0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS                              0x0B96
#define GL_STENCIL_REF                                          0x0B97
#define GL_STENCIL_WRITEMASK                                    0x0B98
#define GL_MATRIX_MODE                                          0x0BA0
#define GL_NORMALIZE                                            0x0BA1
#define GL_VIEWPORT                                             0x0BA2
#define GL_MODELVIEW_STACK_DEPTH                                0x0BA3
#define GL_PROJECTION_STACK_DEPTH                               0x0BA4
#define GL_TEXTURE_STACK_DEPTH                                  0x0BA5
#define GL_MODELVIEW_MATRIX                                     0x0BA6
#define GL_PROJECTION_MATRIX                                    0x0BA7
#define GL_TEXTURE_MATRIX                                       0x0BA8
#define GL_ATTRIB_STACK_DEPTH                                   0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH                            0x0BB1
#define GL_ALPHA_TEST                                           0x0BC0
#define GL_ALPHA_TEST_FUNC                                      0x0BC1
#define GL_ALPHA_TEST_REF                                       0x0BC2
#define GL_DITHER                                               0x0BD0
#define GL_BLEND_DST                                            0x0BE0
#define GL_BLEND_SRC                                            0x0BE1
#define GL_BLEND                                                0x0BE2
#define GL_LOGIC_OP_MODE                                        0x0BF0
#define GL_INDEX_LOGIC_OP                                       0x0BF1
#define GL_COLOR_LOGIC_OP                                       0x0BF2
#define GL_AUX_BUFFERS                                          0x0C00
#define GL_DRAW_BUFFER                                          0x0C01
#define GL_READ_BUFFER                                          0x0C02
#define GL_SCISSOR_BOX                                          0x0C10
#define GL_SCISSOR_TEST                                         0x0C11
#define GL_INDEX_CLEAR_VALUE                                    0x0C20
#define GL_INDEX_WRITEMASK                                      0x0C21
#define GL_COLOR_CLEAR_VALUE                                    0x0C22
#define GL_COLOR_WRITEMASK                                      0x0C23
#define GL_INDEX_MODE                                           0x0C30
#define GL_RGBA_MODE                                            0x0C31
#define GL_DOUBLEBUFFER                                         0x0C32
#define GL_STEREO                                               0x0C33
#define GL_RENDER_MODE                                          0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT                          0x0C50
#define GL_POINT_SMOOTH_HINT                                    0x0C51
#define GL_LINE_SMOOTH_HINT                                     0x0C52
#define GL_POLYGON_SMOOTH_HINT                                  0x0C53
#define GL_FOG_HINT                                             0x0C54
#define GL_TEXTURE_GEN_S                                        0x0C60
#define GL_TEXTURE_GEN_T                                        0x0C61
#define GL_TEXTURE_GEN_R                                        0x0C62
#define GL_TEXTURE_GEN_Q                                        0x0C63
#define GL_PIXEL_MAP_I_TO_I                                     0x0C70
#define GL_PIXEL_MAP_S_TO_S                                     0x0C71
#define GL_PIXEL_MAP_I_TO_R                                     0x0C72
#define GL_PIXEL_MAP_I_TO_G                                     0x0C73
#define GL_PIXEL_MAP_I_TO_B                                     0x0C74
#define GL_PIXEL_MAP_I_TO_A                                     0x0C75
#define GL_PIXEL_MAP_R_TO_R                                     0x0C76
#define GL_PIXEL_MAP_G_TO_G                                     0x0C77
#define GL_PIXEL_MAP_B_TO_B                                     0x0C78
#define GL_PIXEL_MAP_A_TO_A                                     0x0C79
#define GL_PIXEL_MAP_I_TO_I_SIZE                                0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE                                0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE                                0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE                                0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE                                0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE                                0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE                                0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE                                0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE                                0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE                                0x0CB9
#define GL_UNPACK_SWAP_BYTES                                    0x0CF0
#define GL_UNPACK_LSB_FIRST                                     0x0CF1
#define GL_UNPACK_ROW_LENGTH                                    0x0CF2
#define GL_UNPACK_SKIP_ROWS                                     0x0CF3
#define GL_UNPACK_SKIP_PIXELS                                   0x0CF4
#define GL_UNPACK_ALIGNMENT                                     0x0CF5
#define GL_PACK_SWAP_BYTES                                      0x0D00
#define GL_PACK_LSB_FIRST                                       0x0D01
#define GL_PACK_ROW_LENGTH                                      0x0D02
#define GL_PACK_SKIP_ROWS                                       0x0D03
#define GL_PACK_SKIP_PIXELS                                     0x0D04
#define GL_PACK_ALIGNMENT                                       0x0D05
#define GL_MAP_COLOR                                            0x0D10
#define GL_MAP_STENCIL                                          0x0D11
#define GL_INDEX_SHIFT                                          0x0D12
#define GL_INDEX_OFFSET                                         0x0D13
#define GL_RED_SCALE                                            0x0D14
#define GL_RED_BIAS                                             0x0D15
#define GL_ZOOM_X                                               0x0D16
#define GL_ZOOM_Y                                               0x0D17
#define GL_GREEN_SCALE                                          0x0D18
#define GL_GREEN_BIAS                                           0x0D19
#define GL_BLUE_SCALE                                           0x0D1A
#define GL_BLUE_BIAS                                            0x0D1B
#define GL_ALPHA_SCALE                                          0x0D1C
#define GL_ALPHA_BIAS                                           0x0D1D
#define GL_DEPTH_SCALE                                          0x0D1E
#define GL_DEPTH_BIAS                                           0x0D1F
#define GL_MAX_EVAL_ORDER                                       0x0D30
#define GL_MAX_LIGHTS                                           0x0D31
#define GL_MAX_CLIP_PLANES                                      0x0D32
#define GL_MAX_TEXTURE_SIZE                                     0x0D33
#define GL_MAX_PIXEL_MAP_TABLE                                  0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH                               0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH                            0x0D36
#define GL_MAX_NAME_STACK_DEPTH                                 0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH                           0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH                              0x0D39
#define GL_MAX_VIEWPORT_DIMS                                    0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH                        0x0D3B
#define GL_SUBPIXEL_BITS                                        0x0D50
#define GL_INDEX_BITS                                           0x0D51
#define GL_RED_BITS                                             0x0D52
#define GL_GREEN_BITS                                           0x0D53
#define GL_BLUE_BITS                                            0x0D54
#define GL_ALPHA_BITS                                           0x0D55
#define GL_DEPTH_BITS                                           0x0D56
#define GL_STENCIL_BITS                                         0x0D57
#define GL_ACCUM_RED_BITS                                       0x0D58
#define GL_ACCUM_GREEN_BITS                                     0x0D59
#define GL_ACCUM_BLUE_BITS                                      0x0D5A
#define GL_ACCUM_ALPHA_BITS                                     0x0D5B
#define GL_NAME_STACK_DEPTH                                     0x0D70
#define GL_AUTO_NORMAL                                          0x0D80
#define GL_MAP1_COLOR_4                                         0x0D90
#define GL_MAP1_INDEX                                           0x0D91
#define GL_MAP1_NORMAL                                          0x0D92
#define GL_MAP1_TEXTURE_COORD_1                                 0x0D93
#define GL_MAP1_TEXTURE_COORD_2                                 0x0D94
#define GL_MAP1_TEXTURE_COORD_3                                 0x0D95
#define GL_MAP1_TEXTURE_COORD_4                                 0x0D96
#define GL_MAP1_VERTEX_3                                        0x0D97
#define GL_MAP1_VERTEX_4                                        0x0D98
#define GL_MAP2_COLOR_4                                         0x0DB0
#define GL_MAP2_INDEX                                           0x0DB1
#define GL_MAP2_NORMAL                                          0x0DB2
#define GL_MAP2_TEXTURE_COORD_1                                 0x0DB3
#define GL_MAP2_TEXTURE_COORD_2                                 0x0DB4
#define GL_MAP2_TEXTURE_COORD_3                                 0x0DB5
#define GL_MAP2_TEXTURE_COORD_4                                 0x0DB6
#define GL_MAP2_VERTEX_3                                        0x0DB7
#define GL_MAP2_VERTEX_4                                        0x0DB8
#define GL_MAP1_GRID_DOMAIN                                     0x0DD0
#define GL_MAP1_GRID_SEGMENTS                                   0x0DD1
#define GL_MAP2_GRID_DOMAIN                                     0x0DD2
#define GL_MAP2_GRID_SEGMENTS                                   0x0DD3
#define GL_TEXTURE_1D                                           0x0DE0
#define GL_TEXTURE_2D                                           0x0DE1
#define GL_FEEDBACK_BUFFER_POINTER                              0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE                                 0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE                                 0x0DF2
#define GL_SELECTION_BUFFER_POINTER                             0x0DF3
#define GL_SELECTION_BUFFER_SIZE                                0x0DF4
#define GL_TEXTURE_WIDTH                                        0x1000
#define GL_TEXTURE_HEIGHT                                       0x1001
#define GL_TEXTURE_INTERNAL_FORMAT                              0x1003
#define GL_TEXTURE_BORDER_COLOR                                 0x1004
#define GL_TEXTURE_BORDER                                       0x1005
#define GL_DONT_CARE                                            0x1100
#define GL_FASTEST                                              0x1101
#define GL_NICEST                                               0x1102
#define GL_LIGHT0                                               0x4000
#define GL_LIGHT1                                               0x4001
#define GL_LIGHT2                                               0x4002
#define GL_LIGHT3                                               0x4003
#define GL_LIGHT4                                               0x4004
#define GL_LIGHT5                                               0x4005
#define GL_LIGHT6                                               0x4006
#define GL_LIGHT7                                               0x4007
#define GL_AMBIENT                                              0x1200
#define GL_DIFFUSE                                              0x1201
#define GL_SPECULAR                                             0x1202
#define GL_POSITION                                             0x1203
#define GL_SPOT_DIRECTION                                       0x1204
#define GL_SPOT_EXPONENT                                        0x1205
#define GL_SPOT_CUTOFF                                          0x1206
#define GL_CONSTANT_ATTENUATION                                 0x1207
#define GL_LINEAR_ATTENUATION                                   0x1208
#define GL_QUADRATIC_ATTENUATION                                0x1209
#define GL_COMPILE                                              0x1300
#define GL_COMPILE_AND_EXECUTE                                  0x1301
#define GL_CLEAR                                                0x1500
#define GL_AND                                                  0x1501
#define GL_AND_REVERSE                                          0x1502
#define GL_COPY                                                 0x1503
#define GL_AND_INVERTED                                         0x1504
#define GL_NOOP                                                 0x1505
#define GL_XOR                                                  0x1506
#define GL_OR                                                   0x1507
#define GL_NOR                                                  0x1508
#define GL_EQUIV                                                0x1509
#define GL_INVERT                                               0x150A
#define GL_OR_REVERSE                                           0x150B
#define GL_COPY_INVERTED                                        0x150C
#define GL_OR_INVERTED                                          0x150D
#define GL_NAND                                                 0x150E
#define GL_SET                                                  0x150F
#define GL_EMISSION                                             0x1600
#define GL_SHININESS                                            0x1601
#define GL_AMBIENT_AND_DIFFUSE                                  0x1602
#define GL_COLOR_INDEXES                                        0x1603
#define GL_MODELVIEW                                            0x1700
#define GL_PROJECTION                                           0x1701
#define GL_TEXTURE                                              0x1702
#define GL_COLOR                                                0x1800
#define GL_DEPTH                                                0x1801
#define GL_STENCIL                                              0x1802
#define GL_COLOR_INDEX                                          0x1900
#define GL_STENCIL_INDEX                                        0x1901
#define GL_DEPTH_COMPONENT                                      0x1902
#define GL_RED                                                  0x1903
#define GL_GREEN                                                0x1904
#define GL_BLUE                                                 0x1905
#define GL_ALPHA                                                0x1906
#define GL_RGB                                                  0x1907
#define GL_RGBA                                                 0x1908
#define GL_LUMINANCE                                            0x1909
#define GL_LUMINANCE_ALPHA                                      0x190A
#define GL_BITMAP                                               0x1A00
#define GL_POINT                                                0x1B00
#define GL_LINE                                                 0x1B01
#define GL_FILL                                                 0x1B02
#define GL_RENDER                                               0x1C00
#define GL_FEEDBACK                                             0x1C01
#define GL_SELECT                                               0x1C02
#define GL_FLAT                                                 0x1D00
#define GL_SMOOTH                                               0x1D01
#define GL_KEEP                                                 0x1E00
#define GL_REPLACE                                              0x1E01
#define GL_INCR                                                 0x1E02
#define GL_DECR                                                 0x1E03
#define GL_VENDOR                                               0x1F00
#define GL_RENDERER                                             0x1F01
#define GL_VERSION                                              0x1F02
#define GL_EXTENSIONS                                           0x1F03
#define GL_S                                                    0x2000
#define GL_T                                                    0x2001
#define GL_R                                                    0x2002
#define GL_Q                                                    0x2003
#define GL_MODULATE                                             0x2100
#define GL_DECAL                                                0x2101
#define GL_TEXTURE_ENV_MODE                                     0x2200
#define GL_TEXTURE_ENV_COLOR                                    0x2201
#define GL_TEXTURE_ENV                                          0x2300
#define GL_EYE_LINEAR                                           0x2400
#define GL_OBJECT_LINEAR                                        0x2401
#define GL_SPHERE_MAP                                           0x2402
#define GL_TEXTURE_GEN_MODE                                     0x2500
#define GL_OBJECT_PLANE                                         0x2501
#define GL_EYE_PLANE                                            0x2502
#define GL_NEAREST                                              0x2600
#define GL_LINEAR                                               0x2601
#define GL_NEAREST_MIPMAP_NEAREST                               0x2700
#define GL_LINEAR_MIPMAP_NEAREST                                0x2701
#define GL_NEAREST_MIPMAP_LINEAR                                0x2702
#define GL_LINEAR_MIPMAP_LINEAR                                 0x2703
#define GL_TEXTURE_MAG_FILTER                                   0x2800
#define GL_TEXTURE_MIN_FILTER                                   0x2801
#define GL_TEXTURE_WRAP_S                                       0x2802
#define GL_TEXTURE_WRAP_T                                       0x2803
#define GL_CLAMP                                                0x2900
#define GL_REPEAT                                               0x2901
#define GL_CLIENT_PIXEL_STORE_BIT                               0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT                              0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS                               0xffffffff
#define GL_POLYGON_OFFSET_FACTOR                                0x8038
#define GL_POLYGON_OFFSET_UNITS                                 0x2A00
#define GL_POLYGON_OFFSET_POINT                                 0x2A01
#define GL_POLYGON_OFFSET_LINE                                  0x2A02
#define GL_POLYGON_OFFSET_FILL                                  0x8037
#define GL_ALPHA4                                               0x803B
#define GL_ALPHA8                                               0x803C
#define GL_ALPHA12                                              0x803D
#define GL_ALPHA16                                              0x803E
#define GL_LUMINANCE4                                           0x803F
#define GL_LUMINANCE8                                           0x8040
#define GL_LUMINANCE12                                          0x8041
#define GL_LUMINANCE16                                          0x8042
#define GL_LUMINANCE4_ALPHA4                                    0x8043
#define GL_LUMINANCE6_ALPHA2                                    0x8044
#define GL_LUMINANCE8_ALPHA8                                    0x8045
#define GL_LUMINANCE12_ALPHA4                                   0x8046
#define GL_LUMINANCE12_ALPHA12                                  0x8047
#define GL_LUMINANCE16_ALPHA16                                  0x8048
#define GL_INTENSITY                                            0x8049
#define GL_INTENSITY4                                           0x804A
#define GL_INTENSITY8                                           0x804B
#define GL_INTENSITY12                                          0x804C
#define GL_INTENSITY16                                          0x804D
#define GL_R3_G3_B2                                             0x2A10
#define GL_RGB4                                                 0x804F
#define GL_RGB5                                                 0x8050
#define GL_RGB8                                                 0x8051
#define GL_RGB10                                                0x8052
#define GL_RGB12                                                0x8053
#define GL_RGB16                                                0x8054
#define GL_RGBA2                                                0x8055
#define GL_RGBA4                                                0x8056
#define GL_RGB5_A1                                              0x8057
#define GL_RGBA8                                                0x8058
#define GL_RGB10_A2                                             0x8059
#define GL_RGBA12                                               0x805A
#define GL_RGBA16                                               0x805B
#define GL_TEXTURE_RED_SIZE                                     0x805C
#define GL_TEXTURE_GREEN_SIZE                                   0x805D
#define GL_TEXTURE_BLUE_SIZE                                    0x805E
#define GL_TEXTURE_ALPHA_SIZE                                   0x805F
#define GL_TEXTURE_LUMINANCE_SIZE                               0x8060
#define GL_TEXTURE_INTENSITY_SIZE                               0x8061
#define GL_PROXY_TEXTURE_1D                                     0x8063
#define GL_PROXY_TEXTURE_2D                                     0x8064
#define GL_TEXTURE_PRIORITY                                     0x8066
#define GL_TEXTURE_RESIDENT                                     0x8067
#define GL_TEXTURE_BINDING_1D                                   0x8068
#define GL_TEXTURE_BINDING_2D                                   0x8069
#define GL_VERTEX_ARRAY                                         0x8074
#define GL_NORMAL_ARRAY                                         0x8075
#define GL_COLOR_ARRAY                                          0x8076
#define GL_INDEX_ARRAY                                          0x8077
#define GL_TEXTURE_COORD_ARRAY                                  0x8078
#define GL_EDGE_FLAG_ARRAY                                      0x8079
#define GL_VERTEX_ARRAY_SIZE                                    0x807A
#define GL_VERTEX_ARRAY_TYPE                                    0x807B
#define GL_VERTEX_ARRAY_STRIDE                                  0x807C
#define GL_NORMAL_ARRAY_TYPE                                    0x807E
#define GL_NORMAL_ARRAY_STRIDE                                  0x807F
#define GL_COLOR_ARRAY_SIZE                                     0x8081
#define GL_COLOR_ARRAY_TYPE                                     0x8082
#define GL_COLOR_ARRAY_STRIDE                                   0x8083
#define GL_INDEX_ARRAY_TYPE                                     0x8085
#define GL_INDEX_ARRAY_STRIDE                                   0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE                             0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE                             0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE                           0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE                               0x808C
#define GL_VERTEX_ARRAY_POINTER                                 0x808E
#define GL_NORMAL_ARRAY_POINTER                                 0x808F
#define GL_COLOR_ARRAY_POINTER                                  0x8090
#define GL_INDEX_ARRAY_POINTER                                  0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER                          0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER                              0x8093
#define GL_V2F                                                  0x2A20
#define GL_V3F                                                  0x2A21
#define GL_C4UB_V2F                                             0x2A22
#define GL_C4UB_V3F                                             0x2A23
#define GL_C3F_V3F                                              0x2A24
#define GL_N3F_V3F                                              0x2A25
#define GL_C4F_N3F_V3F                                          0x2A26
#define GL_T2F_V3F                                              0x2A27
#define GL_T4F_V4F                                              0x2A28
#define GL_T2F_C4UB_V3F                                         0x2A29
#define GL_T2F_C3F_V3F                                          0x2A2A
#define GL_T2F_N3F_V3F                                          0x2A2B
#define GL_T2F_C4F_N3F_V3F                                      0x2A2C
#define GL_T4F_C4F_N3F_V4F                                      0x2A2D
#define GL_LOGIC_OP GL_INDEX_LOGIC_OP
#define GL_TEXTURE_COMPONENTS GL_TEXTURE_INTERNAL_FORMAT
#define GL_COLOR_INDEX1_EXT                                     0x80E2
#define GL_COLOR_INDEX2_EXT                                     0x80E3
#define GL_COLOR_INDEX4_EXT                                     0x80E4
#define GL_COLOR_INDEX8_EXT                                     0x80E5
#define GL_COLOR_INDEX12_EXT                                    0x80E6
#define GL_COLOR_INDEX16_EXT                                    0x80E7

extern void APIENTRY glAccum (GLenum op, GLfloat value);
extern void APIENTRY glAlphaFunc (GLenum func, GLclampf ref);
extern GLboolean APIENTRY glAreTexturesResident (GLsizei n, const GLuint *textures, GLboolean *residences);
extern void APIENTRY glArrayElement (GLint i);
extern void APIENTRY glBegin (GLenum mode);
extern void APIENTRY glBindTexture (GLenum target, GLuint texture);
extern void APIENTRY glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
extern void APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
extern void APIENTRY glCallList (GLuint list);
extern void APIENTRY glCallLists (GLsizei n, GLenum type, const GLvoid *lists);
extern void APIENTRY glClear (GLbitfield mask);
extern void APIENTRY glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern void APIENTRY glClearDepth (GLclampd depth);
extern void APIENTRY glClearIndex (GLfloat c);
extern void APIENTRY glClearStencil (GLint s);
extern void APIENTRY glClipPlane (GLenum plane, const GLdouble *equation);
extern void APIENTRY glColor3b (GLbyte red, GLbyte green, GLbyte blue);
extern void APIENTRY glColor3bv (const GLbyte *v);
extern void APIENTRY glColor3d (GLdouble red, GLdouble green, GLdouble blue);
extern void APIENTRY glColor3dv (const GLdouble *v);
extern void APIENTRY glColor3f (GLfloat red, GLfloat green, GLfloat blue);
extern void APIENTRY glColor3fv (const GLfloat *v);
extern void APIENTRY glColor3i (GLint red, GLint green, GLint blue);
extern void APIENTRY glColor3iv (const GLint *v);
extern void APIENTRY glColor3s (GLshort red, GLshort green, GLshort blue);
extern void APIENTRY glColor3sv (const GLshort *v);
extern void APIENTRY glColor3ub (GLubyte red, GLubyte green, GLubyte blue);
extern void APIENTRY glColor3ubv (const GLubyte *v);
extern void APIENTRY glColor3ui (GLuint red, GLuint green, GLuint blue);
extern void APIENTRY glColor3uiv (const GLuint *v);
extern void APIENTRY glColor3us (GLushort red, GLushort green, GLushort blue);
extern void APIENTRY glColor3usv (const GLushort *v);
extern void APIENTRY glColor4b (GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
extern void APIENTRY glColor4bv (const GLbyte *v);
extern void APIENTRY glColor4d (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
extern void APIENTRY glColor4dv (const GLdouble *v);
extern void APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void APIENTRY glColor4fv (const GLfloat *v);
extern void APIENTRY glColor4i (GLint red, GLint green, GLint blue, GLint alpha);
extern void APIENTRY glColor4iv (const GLint *v);
extern void APIENTRY glColor4s (GLshort red, GLshort green, GLshort blue, GLshort alpha);
extern void APIENTRY glColor4sv (const GLshort *v);
extern void APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
extern void APIENTRY glColor4ubv (const GLubyte *v);
extern void APIENTRY glColor4ui (GLuint red, GLuint green, GLuint blue, GLuint alpha);
extern void APIENTRY glColor4uiv (const GLuint *v);
extern void APIENTRY glColor4us (GLushort red, GLushort green, GLushort blue, GLushort alpha);
extern void APIENTRY glColor4usv (const GLushort *v);
extern void APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
extern void APIENTRY glColorMaterial (GLenum face, GLenum mode);
extern void APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void APIENTRY glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
extern void APIENTRY glCopyTexImage1D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
extern void APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
extern void APIENTRY glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
extern void APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void APIENTRY glCullFace (GLenum mode);
extern void APIENTRY glDeleteLists (GLuint list, GLsizei range);
extern void APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures);
extern void APIENTRY glDepthFunc (GLenum func);
extern void APIENTRY glDepthMask (GLboolean flag);
extern void APIENTRY glDepthRange (GLclampd zNear, GLclampd zFar);
extern void APIENTRY glDisable (GLenum cap);
extern void APIENTRY glDisableClientState (GLenum array);
extern void APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count);
extern void APIENTRY glDrawBuffer (GLenum mode);
extern void APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
extern void APIENTRY glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern void APIENTRY glEdgeFlag (GLboolean flag);
extern void APIENTRY glEdgeFlagPointer (GLsizei stride, const GLvoid *pointer);
extern void APIENTRY glEdgeFlagv (const GLboolean *flag);
extern void APIENTRY glEnable (GLenum cap);
extern void APIENTRY glEnableClientState (GLenum array);
extern void APIENTRY glEnd (void);
extern void APIENTRY glEndList (void);
extern void APIENTRY glEvalCoord1d (GLdouble u);
extern void APIENTRY glEvalCoord1dv (const GLdouble *u);
extern void APIENTRY glEvalCoord1f (GLfloat u);
extern void APIENTRY glEvalCoord1fv (const GLfloat *u);
extern void APIENTRY glEvalCoord2d (GLdouble u, GLdouble v);
extern void APIENTRY glEvalCoord2dv (const GLdouble *u);
extern void APIENTRY glEvalCoord2f (GLfloat u, GLfloat v);
extern void APIENTRY glEvalCoord2fv (const GLfloat *u);
extern void APIENTRY glEvalMesh1 (GLenum mode, GLint i1, GLint i2);
extern void APIENTRY glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
extern void APIENTRY glEvalPoint1 (GLint i);
extern void APIENTRY glEvalPoint2 (GLint i, GLint j);
extern void APIENTRY glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer);
extern void APIENTRY glFinish (void);
extern void APIENTRY glFlush (void);
extern void APIENTRY glFogf (GLenum pname, GLfloat param);
extern void APIENTRY glFogfv (GLenum pname, const GLfloat *params);
extern void APIENTRY glFogi (GLenum pname, GLint param);
extern void APIENTRY glFogiv (GLenum pname, const GLint *params);
extern void APIENTRY glFrontFace (GLenum mode);
extern void APIENTRY glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern GLuint APIENTRY glGenLists (GLsizei range);
extern void APIENTRY glGenTextures (GLsizei n, GLuint *textures);
extern void APIENTRY glGetBooleanv (GLenum pname, GLboolean *params);
extern void APIENTRY glGetClipPlane (GLenum plane, GLdouble *equation);
extern void APIENTRY glGetDoublev (GLenum pname, GLdouble *params);
extern GLenum APIENTRY glGetError (void);
extern void APIENTRY glGetFloatv (GLenum pname, GLfloat *params);
extern void APIENTRY glGetIntegerv (GLenum pname, GLint *params);
extern void APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
extern void APIENTRY glGetLightiv (GLenum light, GLenum pname, GLint *params);
extern void APIENTRY glGetMapdv (GLenum target, GLenum query, GLdouble *v);
extern void APIENTRY glGetMapfv (GLenum target, GLenum query, GLfloat *v);
extern void APIENTRY glGetMapiv (GLenum target, GLenum query, GLint *v);
extern void APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
extern void APIENTRY glGetMaterialiv (GLenum face, GLenum pname, GLint *params);
extern void APIENTRY glGetPixelMapfv (GLenum map, GLfloat *values);
extern void APIENTRY glGetPixelMapuiv (GLenum map, GLuint *values);
extern void APIENTRY glGetPixelMapusv (GLenum map, GLushort *values);
extern void APIENTRY glGetPointerv (GLenum pname, GLvoid* *params);
extern void APIENTRY glGetPolygonStipple (GLubyte *mask);
extern const GLubyte * APIENTRY glGetString (GLenum name);
extern void APIENTRY glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
extern void APIENTRY glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
extern void APIENTRY glGetTexGendv (GLenum coord, GLenum pname, GLdouble *params);
extern void APIENTRY glGetTexGenfv (GLenum coord, GLenum pname, GLfloat *params);
extern void APIENTRY glGetTexGeniv (GLenum coord, GLenum pname, GLint *params);
extern void APIENTRY glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
extern void APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
extern void APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
extern void APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
extern void APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
extern void APIENTRY glHint (GLenum target, GLenum mode);
extern void APIENTRY glIndexMask (GLuint mask);
extern void APIENTRY glIndexPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
extern void APIENTRY glIndexd (GLdouble c);
extern void APIENTRY glIndexdv (const GLdouble *c);
extern void APIENTRY glIndexf (GLfloat c);
extern void APIENTRY glIndexfv (const GLfloat *c);
extern void APIENTRY glIndexi (GLint c);
extern void APIENTRY glIndexiv (const GLint *c);
extern void APIENTRY glIndexs (GLshort c);
extern void APIENTRY glIndexsv (const GLshort *c);
extern void APIENTRY glIndexub (GLubyte c);
extern void APIENTRY glIndexubv (const GLubyte *c);
extern void APIENTRY glInitNames (void);
extern void APIENTRY glInterleavedArrays (GLenum format, GLsizei stride, const GLvoid *pointer);
extern GLboolean APIENTRY glIsEnabled (GLenum cap);
extern GLboolean APIENTRY glIsList (GLuint list);
extern GLboolean APIENTRY glIsTexture (GLuint texture);
extern void APIENTRY glLightModelf (GLenum pname, GLfloat param);
extern void APIENTRY glLightModelfv (GLenum pname, const GLfloat *params);
extern void APIENTRY glLightModeli (GLenum pname, GLint param);
extern void APIENTRY glLightModeliv (GLenum pname, const GLint *params);
extern void APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
extern void APIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params);
extern void APIENTRY glLighti (GLenum light, GLenum pname, GLint param);
extern void APIENTRY glLightiv (GLenum light, GLenum pname, const GLint *params);
extern void APIENTRY glLineStipple (GLint factor, GLushort pattern);
extern void APIENTRY glLineWidth (GLfloat width);
extern void APIENTRY glListBase (GLuint base);
extern void APIENTRY glLoadIdentity (void);
extern void APIENTRY glLoadMatrixd (const GLdouble *m);
extern void APIENTRY glLoadMatrixf (const GLfloat *m);
extern void APIENTRY glLoadName (GLuint name);
extern void APIENTRY glLogicOp (GLenum opcode);
extern void APIENTRY glMap1d (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
extern void APIENTRY glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
extern void APIENTRY glMap2d (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
extern void APIENTRY glMap2f (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
extern void APIENTRY glMapGrid1d (GLint un, GLdouble u1, GLdouble u2);
extern void APIENTRY glMapGrid1f (GLint un, GLfloat u1, GLfloat u2);
extern void APIENTRY glMapGrid2d (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
extern void APIENTRY glMapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
extern void APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
extern void APIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
extern void APIENTRY glMateriali (GLenum face, GLenum pname, GLint param);
extern void APIENTRY glMaterialiv (GLenum face, GLenum pname, const GLint *params);
extern void APIENTRY glMatrixMode (GLenum mode);
extern void APIENTRY glMultMatrixd (const GLdouble *m);
extern void APIENTRY glMultMatrixf (const GLfloat *m);
extern void APIENTRY glNewList (GLuint list, GLenum mode);
extern void APIENTRY glNormal3b (GLbyte nx, GLbyte ny, GLbyte nz);
extern void APIENTRY glNormal3bv (const GLbyte *v);
extern void APIENTRY glNormal3d (GLdouble nx, GLdouble ny, GLdouble nz);
extern void APIENTRY glNormal3dv (const GLdouble *v);
extern void APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
extern void APIENTRY glNormal3fv (const GLfloat *v);
extern void APIENTRY glNormal3i (GLint nx, GLint ny, GLint nz);
extern void APIENTRY glNormal3iv (const GLint *v);
extern void APIENTRY glNormal3s (GLshort nx, GLshort ny, GLshort nz);
extern void APIENTRY glNormal3sv (const GLshort *v);
extern void APIENTRY glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
extern void APIENTRY glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void APIENTRY glPassThrough (GLfloat token);
extern void APIENTRY glPixelMapfv (GLenum map, GLsizei mapsize, const GLfloat *values);
extern void APIENTRY glPixelMapuiv (GLenum map, GLsizei mapsize, const GLuint *values);
extern void APIENTRY glPixelMapusv (GLenum map, GLsizei mapsize, const GLushort *values);
extern void APIENTRY glPixelStoref (GLenum pname, GLfloat param);
extern void APIENTRY glPixelStorei (GLenum pname, GLint param);
extern void APIENTRY glPixelTransferf (GLenum pname, GLfloat param);
extern void APIENTRY glPixelTransferi (GLenum pname, GLint param);
extern void APIENTRY glPixelZoom (GLfloat xfactor, GLfloat yfactor);
extern void APIENTRY glPointSize (GLfloat size);
extern void APIENTRY glPolygonMode (GLenum face, GLenum mode);
extern void APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
extern void APIENTRY glPolygonStipple (const GLubyte *mask);
extern void APIENTRY glPopAttrib (void);
extern void APIENTRY glPopClientAttrib (void);
extern void APIENTRY glPopMatrix (void);
extern void APIENTRY glPopName (void);
extern void APIENTRY glPrioritizeTextures (GLsizei n, const GLuint *textures, const GLclampf *priorities);
extern void APIENTRY glPushAttrib (GLbitfield mask);
extern void APIENTRY glPushClientAttrib (GLbitfield mask);
extern void APIENTRY glPushMatrix (void);
extern void APIENTRY glPushName (GLuint name);
extern void APIENTRY glRasterPos2d (GLdouble x, GLdouble y);
extern void APIENTRY glRasterPos2dv (const GLdouble *v);
extern void APIENTRY glRasterPos2f (GLfloat x, GLfloat y);
extern void APIENTRY glRasterPos2fv (const GLfloat *v);
extern void APIENTRY glRasterPos2i (GLint x, GLint y);
extern void APIENTRY glRasterPos2iv (const GLint *v);
extern void APIENTRY glRasterPos2s (GLshort x, GLshort y);
extern void APIENTRY glRasterPos2sv (const GLshort *v);
extern void APIENTRY glRasterPos3d (GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glRasterPos3dv (const GLdouble *v);
extern void APIENTRY glRasterPos3f (GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glRasterPos3fv (const GLfloat *v);
extern void APIENTRY glRasterPos3i (GLint x, GLint y, GLint z);
extern void APIENTRY glRasterPos3iv (const GLint *v);
extern void APIENTRY glRasterPos3s (GLshort x, GLshort y, GLshort z);
extern void APIENTRY glRasterPos3sv (const GLshort *v);
extern void APIENTRY glRasterPos4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void APIENTRY glRasterPos4dv (const GLdouble *v);
extern void APIENTRY glRasterPos4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void APIENTRY glRasterPos4fv (const GLfloat *v);
extern void APIENTRY glRasterPos4i (GLint x, GLint y, GLint z, GLint w);
extern void APIENTRY glRasterPos4iv (const GLint *v);
extern void APIENTRY glRasterPos4s (GLshort x, GLshort y, GLshort z, GLshort w);
extern void APIENTRY glRasterPos4sv (const GLshort *v);
extern void APIENTRY glReadBuffer (GLenum mode);
extern void APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
extern void APIENTRY glRectd (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
extern void APIENTRY glRectdv (const GLdouble *v1, const GLdouble *v2);
extern void APIENTRY glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
extern void APIENTRY glRectfv (const GLfloat *v1, const GLfloat *v2);
extern void APIENTRY glRecti (GLint x1, GLint y1, GLint x2, GLint y2);
extern void APIENTRY glRectiv (const GLint *v1, const GLint *v2);
extern void APIENTRY glRects (GLshort x1, GLshort y1, GLshort x2, GLshort y2);
extern void APIENTRY glRectsv (const GLshort *v1, const GLshort *v2);
extern GLint APIENTRY glRenderMode (GLenum mode);
extern void APIENTRY glRotated (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glScaled (GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
extern void APIENTRY glSelectBuffer (GLsizei size, GLuint *buffer);
extern void APIENTRY glShadeModel (GLenum mode);
extern void APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
extern void APIENTRY glStencilMask (GLuint mask);
extern void APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
extern void APIENTRY glTexCoord1d (GLdouble s);
extern void APIENTRY glTexCoord1dv (const GLdouble *v);
extern void APIENTRY glTexCoord1f (GLfloat s);
extern void APIENTRY glTexCoord1fv (const GLfloat *v);
extern void APIENTRY glTexCoord1i (GLint s);
extern void APIENTRY glTexCoord1iv (const GLint *v);
extern void APIENTRY glTexCoord1s (GLshort s);
extern void APIENTRY glTexCoord1sv (const GLshort *v);
extern void APIENTRY glTexCoord2d (GLdouble s, GLdouble t);
extern void APIENTRY glTexCoord2dv (const GLdouble *v);
extern void APIENTRY glTexCoord2f (GLfloat s, GLfloat t);
extern void APIENTRY glTexCoord2fv (const GLfloat *v);
extern void APIENTRY glTexCoord2i (GLint s, GLint t);
extern void APIENTRY glTexCoord2iv (const GLint *v);
extern void APIENTRY glTexCoord2s (GLshort s, GLshort t);
extern void APIENTRY glTexCoord2sv (const GLshort *v);
extern void APIENTRY glTexCoord3d (GLdouble s, GLdouble t, GLdouble r);
extern void APIENTRY glTexCoord3dv (const GLdouble *v);
extern void APIENTRY glTexCoord3f (GLfloat s, GLfloat t, GLfloat r);
extern void APIENTRY glTexCoord3fv (const GLfloat *v);
extern void APIENTRY glTexCoord3i (GLint s, GLint t, GLint r);
extern void APIENTRY glTexCoord3iv (const GLint *v);
extern void APIENTRY glTexCoord3s (GLshort s, GLshort t, GLshort r);
extern void APIENTRY glTexCoord3sv (const GLshort *v);
extern void APIENTRY glTexCoord4d (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
extern void APIENTRY glTexCoord4dv (const GLdouble *v);
extern void APIENTRY glTexCoord4f (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
extern void APIENTRY glTexCoord4fv (const GLfloat *v);
extern void APIENTRY glTexCoord4i (GLint s, GLint t, GLint r, GLint q);
extern void APIENTRY glTexCoord4iv (const GLint *v);
extern void APIENTRY glTexCoord4s (GLshort s, GLshort t, GLshort r, GLshort q);
extern void APIENTRY glTexCoord4sv (const GLshort *v);
extern void APIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param);
extern void APIENTRY glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
extern void APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param);
extern void APIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params);
extern void APIENTRY glTexGend (GLenum coord, GLenum pname, GLdouble param);
extern void APIENTRY glTexGendv (GLenum coord, GLenum pname, const GLdouble *params);
extern void APIENTRY glTexGenf (GLenum coord, GLenum pname, GLfloat param);
extern void APIENTRY glTexGenfv (GLenum coord, GLenum pname, const GLfloat *params);
extern void APIENTRY glTexGeni (GLenum coord, GLenum pname, GLint param);
extern void APIENTRY glTexGeniv (GLenum coord, GLenum pname, const GLint *params);
extern void APIENTRY glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
extern void APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
extern void APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
extern void APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
extern void APIENTRY glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
extern void APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern void APIENTRY glTranslated (GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glVertex2d (GLdouble x, GLdouble y);
extern void APIENTRY glVertex2dv (const GLdouble *v);
extern void APIENTRY glVertex2f (GLfloat x, GLfloat y);
extern void APIENTRY glVertex2fv (const GLfloat *v);
extern void APIENTRY glVertex2i (GLint x, GLint y);
extern void APIENTRY glVertex2iv (const GLint *v);
extern void APIENTRY glVertex2s (GLshort x, GLshort y);
extern void APIENTRY glVertex2sv (const GLshort *v);
extern void APIENTRY glVertex3d (GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glVertex3dv (const GLdouble *v);
extern void APIENTRY glVertex3f (GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glVertex3fv (const GLfloat *v);
extern void APIENTRY glVertex3i (GLint x, GLint y, GLint z);
extern void APIENTRY glVertex3iv (const GLint *v);
extern void APIENTRY glVertex3s (GLshort x, GLshort y, GLshort z);
extern void APIENTRY glVertex3sv (const GLshort *v);
extern void APIENTRY glVertex4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void APIENTRY glVertex4dv (const GLdouble *v);
extern void APIENTRY glVertex4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void APIENTRY glVertex4fv (const GLfloat *v);
extern void APIENTRY glVertex4i (GLint x, GLint y, GLint z, GLint w);
extern void APIENTRY glVertex4iv (const GLint *v);
extern void APIENTRY glVertex4s (GLshort x, GLshort y, GLshort z, GLshort w);
extern void APIENTRY glVertex4sv (const GLshort *v);
extern void APIENTRY glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);

#endif /* GL_VERSION_1_1 */

/* this is where we can safely include GLU */
#include <GL/glu.h>

/* ------------------------------ OpenGL 1.2 ------------------------------ */

#ifdef GL_VERSION_1_2

#define GL_UNSIGNED_BYTE_3_3_2                                  0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4                               0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1                               0x8034
#define GL_UNSIGNED_INT_8_8_8_8                                 0x8035
#define GL_UNSIGNED_INT_10_10_10_2                              0x8036
#define GL_RESCALE_NORMAL                                       0x803A
#define GL_UNSIGNED_BYTE_2_3_3_REV                              0x8362
#define GL_UNSIGNED_SHORT_5_6_5                                 0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV                             0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                           0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV                             0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV                          0x8368
#define GL_BGR                                                  0x80E0
#define GL_BGRA                                                 0x80E1
#define GL_MAX_ELEMENTS_VERTICES                                0x80E8
#define GL_MAX_ELEMENTS_INDICES                                 0x80E9
#define GL_CLAMP_TO_EDGE                                        0x812F
#define GL_TEXTURE_MIN_LOD                                      0x813A
#define GL_TEXTURE_MAX_LOD                                      0x813B
#define GL_TEXTURE_BASE_LEVEL                                   0x813C
#define GL_TEXTURE_MAX_LEVEL                                    0x813D
#define GL_LIGHT_MODEL_COLOR_CONTROL                            0x81F8
#define GL_SINGLE_COLOR                                         0x81F9
#define GL_SEPARATE_SPECULAR_COLOR                              0x81FA
#define GL_SMOOTH_POINT_SIZE_RANGE                              0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY                        0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE                              0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY                        0x0B23
#define GL_ALIASED_POINT_SIZE_RANGE                             0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE                             0x846E
#define GL_PACK_SKIP_IMAGES                                     0x806B
#define GL_PACK_IMAGE_HEIGHT                                    0x806C
#define GL_UNPACK_SKIP_IMAGES                                   0x806D
#define GL_UNPACK_IMAGE_HEIGHT                                  0x806E
#define GL_TEXTURE_3D                                           0x806F
#define GL_PROXY_TEXTURE_3D                                     0x8070
#define GL_TEXTURE_DEPTH                                        0x8071
#define GL_TEXTURE_WRAP_R                                       0x8072
#define GL_MAX_3D_TEXTURE_SIZE                                  0x8073
#define GL_TEXTURE_BINDING_3D                                   0x806A

typedef void (APIENTRY * glDrawRangeElementsPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
typedef void (APIENTRY * glTexImage3DPROC) (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRY * glTexSubImage3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRY * glCopyTexSubImage3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

extern GLEW_EXPORT glDrawRangeElementsPROC glDrawRangeElements;
extern GLEW_EXPORT glTexImage3DPROC glTexImage3D;
extern GLEW_EXPORT glTexSubImage3DPROC glTexSubImage3D;
extern GLEW_EXPORT glCopyTexSubImage3DPROC glCopyTexSubImage3D;

#endif /* GL_VERSION_1_2 */

/* ------------------------------ OpenGL 1.3 ------------------------------ */

#ifdef GL_VERSION_1_3

#define GL_TEXTURE0                                             0x84C0
#define GL_TEXTURE1                                             0x84C1
#define GL_TEXTURE2                                             0x84C2
#define GL_TEXTURE3                                             0x84C3
#define GL_TEXTURE4                                             0x84C4
#define GL_TEXTURE5                                             0x84C5
#define GL_TEXTURE6                                             0x84C6
#define GL_TEXTURE7                                             0x84C7
#define GL_TEXTURE8                                             0x84C8
#define GL_TEXTURE9                                             0x84C9
#define GL_TEXTURE10                                            0x84CA
#define GL_TEXTURE11                                            0x84CB
#define GL_TEXTURE12                                            0x84CC
#define GL_TEXTURE13                                            0x84CD
#define GL_TEXTURE14                                            0x84CE
#define GL_TEXTURE15                                            0x84CF
#define GL_TEXTURE16                                            0x84D0
#define GL_TEXTURE17                                            0x84D1
#define GL_TEXTURE18                                            0x84D2
#define GL_TEXTURE19                                            0x84D3
#define GL_TEXTURE20                                            0x84D4
#define GL_TEXTURE21                                            0x84D5
#define GL_TEXTURE22                                            0x84D6
#define GL_TEXTURE23                                            0x84D7
#define GL_TEXTURE24                                            0x84D8
#define GL_TEXTURE25                                            0x84D9
#define GL_TEXTURE26                                            0x84DA
#define GL_TEXTURE27                                            0x84DB
#define GL_TEXTURE28                                            0x84DC
#define GL_TEXTURE29                                            0x84DD
#define GL_TEXTURE30                                            0x84DE
#define GL_TEXTURE31                                            0x84DF
#define GL_ACTIVE_TEXTURE                                       0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE                                0x84E1
#define GL_MAX_TEXTURE_UNITS                                    0x84E2

#define GL_NORMAL_MAP                                           0x8511
#define GL_REFLECTION_MAP                                       0x8512
#define GL_TEXTURE_CUBE_MAP                                     0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP                             0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X                          0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X                          0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y                          0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                          0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z                          0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                          0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP                               0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE                            0x851C

#define GL_COMPRESSED_ALPHA                                     0x84E9
#define GL_COMPRESSED_LUMINANCE                                 0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA                           0x84EB
#define GL_COMPRESSED_INTENSITY                                 0x84EC
#define GL_COMPRESSED_RGB                                       0x84ED
#define GL_COMPRESSED_RGBA                                      0x84EE
#define GL_TEXTURE_COMPRESSION_HINT                             0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE                        0x86A0
#define GL_TEXTURE_COMPRESSED                                   0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS                       0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS                           0x86A3

#define GL_MULTISAMPLE                                          0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE                             0x809E
#define GL_SAMPLE_ALPHA_TO_ONE                                  0x809F
#define GL_SAMPLE_COVERAGE                                      0x80A0
#define GL_SAMPLE_BUFFERS                                       0x80A8
#define GL_SAMPLES                                              0x80A9
#define GL_SAMPLE_COVERAGE_VALUE                                0x80AA
#define GL_SAMPLE_COVERAGE_INVERT                               0x80AB
#define GL_MULTISAMPLE_BIT                                      0x20000000

#define GL_TRANSPOSE_MODELVIEW_MATRIX                           0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX                          0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX                             0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX                               0x84E6

#define GL_COMBINE                                              0x8570
#define GL_COMBINE_RGB                                          0x8571
#define GL_COMBINE_ALPHA                                        0x8572
#define GL_SOURCE0_RGB                                          0x8580
#define GL_SOURCE1_RGB                                          0x8581
#define GL_SOURCE2_RGB                                          0x8582
#define GL_SOURCE0_ALPHA                                        0x8588
#define GL_SOURCE1_ALPHA                                        0x8589
#define GL_SOURCE2_ALPHA                                        0x858A
#define GL_OPERAND0_RGB                                         0x8590
#define GL_OPERAND1_RGB                                         0x8591
#define GL_OPERAND2_RGB                                         0x8592
#define GL_OPERAND0_ALPHA                                       0x8598
#define GL_OPERAND1_ALPHA                                       0x8599
#define GL_OPERAND2_ALPHA                                       0x859A
#define GL_RGB_SCALE                                            0x8573
#define GL_ADD_SIGNED                                           0x8574
#define GL_INTERPOLATE                                          0x8575
#define GL_SUBTRACT                                             0x84E7
#define GL_CONSTANT                                             0x8576
#define GL_PRIMARY_COLOR                                        0x8577
#define GL_PREVIOUS                                             0x8578
#define GL_DOT3_RGB                                             0x86AE
#define GL_DOT3_RGBA                                            0x86AF
#define GL_CLAMP_TO_BORDER                                      0x812D

typedef void (APIENTRY * glActiveTexturePROC) (GLenum texture);
typedef void (APIENTRY * glClientActiveTexturePROC) (GLenum texture);
typedef void (APIENTRY * glCompressedTexImage1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexImage2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexImage3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexSubImage1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexSubImage2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexSubImage3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glGetCompressedTexImagePROC) (GLenum target, GLint lod, GLvoid *img);
typedef void (APIENTRY * glMultiTexCoord1dPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * glMultiTexCoord1dvPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord1fPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * glMultiTexCoord1fvPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord1iPROC) (GLenum target, GLint s);
typedef void (APIENTRY * glMultiTexCoord1ivPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord1sPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * glMultiTexCoord1svPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * glMultiTexCoord2dPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * glMultiTexCoord2dvPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord2fPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * glMultiTexCoord2fvPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord2iPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * glMultiTexCoord2ivPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord2sPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * glMultiTexCoord2svPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * glMultiTexCoord3dPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * glMultiTexCoord3dvPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord3fPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * glMultiTexCoord3fvPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord3iPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * glMultiTexCoord3ivPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord3sPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * glMultiTexCoord3svPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * glMultiTexCoord4dPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * glMultiTexCoord4dvPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord4fPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * glMultiTexCoord4fvPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord4iPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * glMultiTexCoord4ivPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord4sPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * glMultiTexCoord4svPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * glLoadTransposeMatrixdPROC) (const GLdouble m[16]);
typedef void (APIENTRY * glLoadTransposeMatrixfPROC) (const GLfloat m[16]);
typedef void (APIENTRY * glMultTransposeMatrixdPROC) (const GLdouble m[16]);
typedef void (APIENTRY * glMultTransposeMatrixfPROC) (const GLfloat m[16]);
typedef void (APIENTRY * glSampleCoveragePROC) (GLclampf value, GLboolean invert);

extern GLEW_EXPORT glActiveTexturePROC glActiveTexture;
extern GLEW_EXPORT glClientActiveTexturePROC glClientActiveTexture;
extern GLEW_EXPORT glMultiTexCoord1dPROC glMultiTexCoord1d;
extern GLEW_EXPORT glMultiTexCoord1dvPROC glMultiTexCoord1dv;
extern GLEW_EXPORT glMultiTexCoord1fPROC glMultiTexCoord1f;
extern GLEW_EXPORT glMultiTexCoord1fvPROC glMultiTexCoord1fv;
extern GLEW_EXPORT glMultiTexCoord1iPROC glMultiTexCoord1i;
extern GLEW_EXPORT glMultiTexCoord1ivPROC glMultiTexCoord1iv;
extern GLEW_EXPORT glMultiTexCoord1sPROC glMultiTexCoord1s;
extern GLEW_EXPORT glMultiTexCoord1svPROC glMultiTexCoord1sv;
extern GLEW_EXPORT glMultiTexCoord2dPROC glMultiTexCoord2d;
extern GLEW_EXPORT glMultiTexCoord2dvPROC glMultiTexCoord2dv;
extern GLEW_EXPORT glMultiTexCoord2fPROC glMultiTexCoord2f;
extern GLEW_EXPORT glMultiTexCoord2fvPROC glMultiTexCoord2fv;
extern GLEW_EXPORT glMultiTexCoord2iPROC glMultiTexCoord2i;
extern GLEW_EXPORT glMultiTexCoord2ivPROC glMultiTexCoord2iv;
extern GLEW_EXPORT glMultiTexCoord2sPROC glMultiTexCoord2s;
extern GLEW_EXPORT glMultiTexCoord2svPROC glMultiTexCoord2sv;
extern GLEW_EXPORT glMultiTexCoord3dPROC glMultiTexCoord3d;
extern GLEW_EXPORT glMultiTexCoord3dvPROC glMultiTexCoord3dv;
extern GLEW_EXPORT glMultiTexCoord3fPROC glMultiTexCoord3f;
extern GLEW_EXPORT glMultiTexCoord3fvPROC glMultiTexCoord3fv;
extern GLEW_EXPORT glMultiTexCoord3iPROC glMultiTexCoord3i;
extern GLEW_EXPORT glMultiTexCoord3ivPROC glMultiTexCoord3iv;
extern GLEW_EXPORT glMultiTexCoord3sPROC glMultiTexCoord3s;
extern GLEW_EXPORT glMultiTexCoord3svPROC glMultiTexCoord3sv;
extern GLEW_EXPORT glMultiTexCoord4dPROC glMultiTexCoord4d;
extern GLEW_EXPORT glMultiTexCoord4dvPROC glMultiTexCoord4dv;
extern GLEW_EXPORT glMultiTexCoord4fPROC glMultiTexCoord4f;
extern GLEW_EXPORT glMultiTexCoord4fvPROC glMultiTexCoord4fv;
extern GLEW_EXPORT glMultiTexCoord4iPROC glMultiTexCoord4i;
extern GLEW_EXPORT glMultiTexCoord4ivPROC glMultiTexCoord4iv;
extern GLEW_EXPORT glMultiTexCoord4sPROC glMultiTexCoord4s;
extern GLEW_EXPORT glMultiTexCoord4svPROC glMultiTexCoord4sv;
extern GLEW_EXPORT glLoadTransposeMatrixfPROC glLoadTransposeMatrixf;
extern GLEW_EXPORT glLoadTransposeMatrixdPROC glLoadTransposeMatrixd;
extern GLEW_EXPORT glMultTransposeMatrixfPROC glMultTransposeMatrixf;
extern GLEW_EXPORT glMultTransposeMatrixdPROC glMultTransposeMatrixd;
extern GLEW_EXPORT glCompressedTexImage3DPROC glCompressedTexImage3D;
extern GLEW_EXPORT glCompressedTexImage2DPROC glCompressedTexImage2D;
extern GLEW_EXPORT glCompressedTexImage1DPROC glCompressedTexImage1D;
extern GLEW_EXPORT glCompressedTexSubImage3DPROC glCompressedTexSubImage3D;
extern GLEW_EXPORT glCompressedTexSubImage2DPROC glCompressedTexSubImage2D;
extern GLEW_EXPORT glCompressedTexSubImage1DPROC glCompressedTexSubImage1D;
extern GLEW_EXPORT glGetCompressedTexImagePROC glGetCompressedTexImage;
extern GLEW_EXPORT glSampleCoveragePROC glSampleCoverage;

#endif /* GL_VERSION_1_3 */

/* ------------------------------ OpenGL 1.4 ------------------------------ */

#ifdef GL_VERSION_1_4

#ifndef GL_ARB_imaging
#define GL_BLEND_EQUATION                                       0x8009
#define GL_MIN                                                  0x8007
#define GL_MAX                                                  0x8008
#define GL_FUNC_ADD                                             0x8006
#define GL_FUNC_SUBTRACT                                        0x800A
#define GL_FUNC_REVERSE_SUBTRACT                                0x800B
#define GL_BLEND_COLOR                                          0x8005
#define GL_CONSTANT_COLOR                                       0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR                             0x8002
#define GL_CONSTANT_ALPHA                                       0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA                             0x8004
#endif /* GL_ARB_imaging */

#define GL_GENERATE_MIPMAP                                      0x8191
#define GL_GENERATE_MIPMAP_HINT                                 0x8192
#define GL_DEPTH_COMPONENT16                                    0x81A5
#define GL_DEPTH_COMPONENT24                                    0x81A6
#define GL_DEPTH_COMPONENT32                                    0x81A7
#define GL_TEXTURE_DEPTH_SIZE                                   0x884A
#define GL_DEPTH_TEXTURE_MODE                                   0x884B
#define GL_TEXTURE_COMPARE_MODE                                 0x884C
#define GL_TEXTURE_COMPARE_FUNC                                 0x884D
#define GL_COMPARE_R_TO_TEXTURE                                 0x884E
#define GL_FOG_COORDINATE_SOURCE                                0x8450
#define GL_FOG_COORDINATE                                       0x8451
#define GL_FRAGMENT_DEPTH                                       0x8452
#define GL_CURRENT_FOG_COORDINATE                               0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE                            0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE                          0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER                         0x8456
#define GL_FOG_COORDINATE_ARRAY                                 0x8457
#define GL_POINT_SIZE_MIN                                       0x8126
#define GL_POINT_SIZE_MAX                                       0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE                            0x8128
#define GL_POINT_DISTANCE_ATTENUATION                           0x8129
#define GL_COLOR_SUM                                            0x8458
#define GL_CURRENT_SECONDARY_COLOR                              0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE                           0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE                           0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE                         0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER                        0x845D
#define GL_SECONDARY_COLOR_ARRAY                                0x845E
#define GL_BLEND_DST_RGB                                        0x80C8
#define GL_BLEND_SRC_RGB                                        0x80C9
#define GL_BLEND_DST_ALPHA                                      0x80CA
#define GL_BLEND_SRC_ALPHA                                      0x80CB
#define GL_INCR_WRAP                                            0x8507
#define GL_DECR_WRAP                                            0x8508
#define GL_TEXTURE_FILTER_CONTROL                               0x8500
#define GL_TEXTURE_LOD_BIAS                                     0x8501
#define GL_MAX_TEXTURE_LOD_BIAS                                 0x84FD
#define GL_MIRRORED_REPEAT                                      0x8370

#ifndef GL_ARB_imaging
typedef void (APIENTRY * glBlendEquationPROC) (GLenum mode);
typedef void (APIENTRY * glBlendColorPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
#endif /* GL_ARB_imaging */
typedef void (APIENTRY * glFogCoordfPROC) (GLfloat coord);
typedef void (APIENTRY * glFogCoordfvPROC) (const GLfloat *coord);
typedef void (APIENTRY * glFogCoorddPROC) (GLdouble coord);
typedef void (APIENTRY * glFogCoorddvPROC) (const GLdouble *coord);
typedef void (APIENTRY * glFogCoordPointerPROC) (GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * glMultiDrawArraysPROC) (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount);
typedef void (APIENTRY * glMultiDrawElementsPROC) (GLenum mode, GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount);
typedef void (APIENTRY * glPointParameterfPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * glPointParameterfvPROC) (GLenum pname, GLfloat *params);
typedef void (APIENTRY * glSecondaryColor3bPROC) (GLbyte red, GLbyte green, GLbyte blue);
typedef void (APIENTRY * glSecondaryColor3bvPROC) (const GLbyte *v);
typedef void (APIENTRY * glSecondaryColor3dPROC) (GLdouble red, GLdouble green, GLdouble blue);
typedef void (APIENTRY * glSecondaryColor3dvPROC) (const GLdouble *v);
typedef void (APIENTRY * glSecondaryColor3fPROC) (GLfloat red, GLfloat green, GLfloat blue);
typedef void (APIENTRY * glSecondaryColor3fvPROC) (const GLfloat *v);
typedef void (APIENTRY * glSecondaryColor3iPROC) (GLint red, GLint green, GLint blue);
typedef void (APIENTRY * glSecondaryColor3ivPROC) (const GLint *v);
typedef void (APIENTRY * glSecondaryColor3sPROC) (GLshort red, GLshort green, GLshort blue);
typedef void (APIENTRY * glSecondaryColor3svPROC) (const GLshort *v);
typedef void (APIENTRY * glSecondaryColor3ubPROC) (GLubyte red, GLubyte green, GLubyte blue);
typedef void (APIENTRY * glSecondaryColor3ubvPROC) (const GLubyte *v);
typedef void (APIENTRY * glSecondaryColor3uiPROC) (GLuint red, GLuint green, GLuint blue);
typedef void (APIENTRY * glSecondaryColor3uivPROC) (const GLuint *v);
typedef void (APIENTRY * glSecondaryColor3usPROC) (GLushort red, GLushort green, GLushort blue);
typedef void (APIENTRY * glSecondaryColor3usvPROC) (const GLushort *v);
typedef void (APIENTRY * glSecondaryColorPointerPROC) (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);
typedef void (APIENTRY * glBlendFuncSeparatePROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (APIENTRY * glWindowPos2dPROC) (GLdouble x, GLdouble y);
typedef void (APIENTRY * glWindowPos2fPROC) (GLfloat x, GLfloat y);
typedef void (APIENTRY * glWindowPos2iPROC) (GLint x, GLint y);
typedef void (APIENTRY * glWindowPos2sPROC) (GLshort x, GLshort y);
typedef void (APIENTRY * glWindowPos2dvPROC) (const GLdouble *p);
typedef void (APIENTRY * glWindowPos2fvPROC) (const GLfloat *p);
typedef void (APIENTRY * glWindowPos2ivPROC) (const GLint *p);
typedef void (APIENTRY * glWindowPos2svPROC) (const GLshort *p);
typedef void (APIENTRY * glWindowPos3dPROC) (GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * glWindowPos3fPROC) (GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * glWindowPos3iPROC) (GLint x, GLint y, GLint z);
typedef void (APIENTRY * glWindowPos3sPROC) (GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * glWindowPos3dvPROC) (const GLdouble *p);
typedef void (APIENTRY * glWindowPos3fvPROC) (const GLfloat *p);
typedef void (APIENTRY * glWindowPos3ivPROC) (const GLint *p);
typedef void (APIENTRY * glWindowPos3svPROC) (const GLshort *p);

#ifndef GL_ARB_imaging
extern GLEW_EXPORT glBlendColorPROC glBlendColor;
extern GLEW_EXPORT glBlendEquationPROC glBlendEquation;
#endif /* GL_ARB_imaging */
extern GLEW_EXPORT glFogCoordfPROC glFogCoordf;
extern GLEW_EXPORT glFogCoordfvPROC glFogCoordfv;
extern GLEW_EXPORT glFogCoorddPROC glFogCoordd;
extern GLEW_EXPORT glFogCoorddvPROC glFogCoorddv;
extern GLEW_EXPORT glFogCoordPointerPROC glFogCoordPointer;
extern GLEW_EXPORT glMultiDrawArraysPROC glMultiDrawArrays;
extern GLEW_EXPORT glMultiDrawElementsPROC glMultiDrawElements;
extern GLEW_EXPORT glPointParameterfPROC glPointParameterf;
extern GLEW_EXPORT glPointParameterfvPROC glPointParameterfv;
extern GLEW_EXPORT glSecondaryColor3bPROC glSecondaryColor3b;
extern GLEW_EXPORT glSecondaryColor3bvPROC glSecondaryColor3bv;
extern GLEW_EXPORT glSecondaryColor3dPROC glSecondaryColor3d;
extern GLEW_EXPORT glSecondaryColor3dvPROC glSecondaryColor3dv;
extern GLEW_EXPORT glSecondaryColor3fPROC glSecondaryColor3f;
extern GLEW_EXPORT glSecondaryColor3fvPROC glSecondaryColor3fv;
extern GLEW_EXPORT glSecondaryColor3iPROC glSecondaryColor3i;
extern GLEW_EXPORT glSecondaryColor3ivPROC glSecondaryColor3iv;
extern GLEW_EXPORT glSecondaryColor3sPROC glSecondaryColor3s;
extern GLEW_EXPORT glSecondaryColor3svPROC glSecondaryColor3sv;
extern GLEW_EXPORT glSecondaryColor3ubPROC glSecondaryColor3ub;
extern GLEW_EXPORT glSecondaryColor3ubvPROC glSecondaryColor3ubv;
extern GLEW_EXPORT glSecondaryColor3uiPROC glSecondaryColor3ui;
extern GLEW_EXPORT glSecondaryColor3uivPROC glSecondaryColor3uiv;
extern GLEW_EXPORT glSecondaryColor3usPROC glSecondaryColor3us;
extern GLEW_EXPORT glSecondaryColor3usvPROC glSecondaryColor3usv;
extern GLEW_EXPORT glSecondaryColorPointerPROC glSecondaryColorPointer;
extern GLEW_EXPORT glBlendFuncSeparatePROC glBlendFuncSeparate;
extern GLEW_EXPORT glWindowPos2dPROC glWindowPos2d;
extern GLEW_EXPORT glWindowPos2fPROC glWindowPos2f;
extern GLEW_EXPORT glWindowPos2iPROC glWindowPos2i;
extern GLEW_EXPORT glWindowPos2sPROC glWindowPos2s;
extern GLEW_EXPORT glWindowPos2dvPROC glWindowPos2dv;
extern GLEW_EXPORT glWindowPos2fvPROC glWindowPos2fv;
extern GLEW_EXPORT glWindowPos2ivPROC glWindowPos2iv;
extern GLEW_EXPORT glWindowPos2svPROC glWindowPos2sv;
extern GLEW_EXPORT glWindowPos3dPROC glWindowPos3d;
extern GLEW_EXPORT glWindowPos3fPROC glWindowPos3f;
extern GLEW_EXPORT glWindowPos3iPROC glWindowPos3i;
extern GLEW_EXPORT glWindowPos3sPROC glWindowPos3s;
extern GLEW_EXPORT glWindowPos3dvPROC glWindowPos3dv;
extern GLEW_EXPORT glWindowPos3fvPROC glWindowPos3fv;
extern GLEW_EXPORT glWindowPos3ivPROC glWindowPos3iv;
extern GLEW_EXPORT glWindowPos3svPROC glWindowPos3sv;

#endif /* GL_VERSION_1_4 */

/* --------------------------- ARB_depth_texture -------------------------- */

#ifdef GL_ARB_depth_texture

#define GL_DEPTH_COMPONENT16_ARB                                0x81A5
#define GL_DEPTH_COMPONENT24_ARB                                0x81A6
#define GL_DEPTH_COMPONENT32_ARB                                0x81A7
#define GL_TEXTURE_DEPTH_SIZE_ARB                               0x884A
#define GL_DEPTH_TEXTURE_MODE_ARB                               0x884B

#endif /* GL_ARB_depth_texture */

/* -------------------------- ARB_fragment_program ------------------------ */

#ifdef GL_ARB_fragment_program

#define GL_FRAGMENT_PROGRAM_ARB                                 0x8804
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB                         0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB                         0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB                         0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB                  0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB                  0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB                  0x880A
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB                     0x880B
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB                     0x880C
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB                     0x880D
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB              0x880E
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB              0x880F
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB              0x8810
#define GL_MAX_TEXTURE_COORDS_ARB                               0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB                          0x8872

#endif /* GL_ARB_fragment_program */

/* ------------------------------ ARB_imaging ----------------------------- */

#ifdef GL_ARB_imaging

#define GL_CONSTANT_COLOR                                       0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR                             0x8002
#define GL_CONSTANT_ALPHA                                       0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA                             0x8004
#define GL_BLEND_COLOR                                          0x8005
#define GL_FUNC_ADD                                             0x8006
#define GL_MIN                                                  0x8007
#define GL_MAX                                                  0x8008
#define GL_BLEND_EQUATION                                       0x8009
#define GL_FUNC_SUBTRACT                                        0x800A
#define GL_FUNC_REVERSE_SUBTRACT                                0x800B
#define GL_CONVOLUTION_1D                                       0x8010
#define GL_CONVOLUTION_2D                                       0x8011
#define GL_SEPARABLE_2D                                         0x8012
#define GL_CONVOLUTION_BORDER_MODE                              0x8013
#define GL_CONVOLUTION_FILTER_SCALE                             0x8014
#define GL_CONVOLUTION_FILTER_BIAS                              0x8015
#define GL_REDUCE                                               0x8016
#define GL_CONVOLUTION_FORMAT                                   0x8017
#define GL_CONVOLUTION_WIDTH                                    0x8018
#define GL_CONVOLUTION_HEIGHT                                   0x8019
#define GL_MAX_CONVOLUTION_WIDTH                                0x801A
#define GL_MAX_CONVOLUTION_HEIGHT                               0x801B
#define GL_POST_CONVOLUTION_RED_SCALE                           0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE                         0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE                          0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE                         0x801F
#define GL_POST_CONVOLUTION_RED_BIAS                            0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS                          0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS                           0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS                          0x8023
#define GL_HISTOGRAM                                            0x8024
#define GL_PROXY_HISTOGRAM                                      0x8025
#define GL_HISTOGRAM_WIDTH                                      0x8026
#define GL_HISTOGRAM_FORMAT                                     0x8027
#define GL_HISTOGRAM_RED_SIZE                                   0x8028
#define GL_HISTOGRAM_GREEN_SIZE                                 0x8029
#define GL_HISTOGRAM_BLUE_SIZE                                  0x802A
#define GL_HISTOGRAM_ALPHA_SIZE                                 0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE                             0x802C
#define GL_HISTOGRAM_SINK                                       0x802D
#define GL_MINMAX                                               0x802E
#define GL_MINMAX_FORMAT                                        0x802F
#define GL_MINMAX_SINK                                          0x8030
#define GL_TABLE_TOO_LARGE                                      0x8031
#define GL_COLOR_MATRIX                                         0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH                             0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH                         0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE                          0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE                        0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE                         0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE                        0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS                           0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS                         0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS                          0x80BA
#define GL_POST_COLOR_MATIX_ALPHA_BIAS                          0x80BB
#define GL_COLOR_TABLE                                          0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE                         0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE                        0x80D2
#define GL_PROXY_COLOR_TABLE                                    0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE                   0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE                  0x80D5
#define GL_COLOR_TABLE_SCALE                                    0x80D6
#define GL_COLOR_TABLE_BIAS                                     0x80D7
#define GL_COLOR_TABLE_FORMAT                                   0x80D8
#define GL_COLOR_TABLE_WIDTH                                    0x80D9
#define GL_COLOR_TABLE_RED_SIZE                                 0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE                               0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE                                0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE                               0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE                           0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE                           0x80DF
#define GL_IGNORE_BORDER                                        0x8150
#define GL_CONSTANT_BORDER                                      0x8151
#define GL_WRAP_BORDER                                          0x8152
#define GL_REPLICATE_BORDER                                     0x8153
#define GL_CONVOLUTION_BORDER_COLOR                             0x8154

typedef void (APIENTRY * glColorTablePROC) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (APIENTRY * glColorSubTablePROC) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
typedef void (APIENTRY * glColorTableParameterivPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRY * glColorTableParameterfvPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * glCopyColorSubTablePROC) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * glCopyColorTablePROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * glGetColorTablePROC) (GLenum target, GLenum format, GLenum type, GLvoid *table);
typedef void (APIENTRY * glGetColorTableParameterfvPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetColorTableParameterivPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * glBlendEquationPROC) (GLenum mode);
typedef void (APIENTRY * glBlendColorPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (APIENTRY * glHistogramPROC) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
typedef void (APIENTRY * glResetHistogramPROC) (GLenum target);
typedef void (APIENTRY * glGetHistogramPROC) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
typedef void (APIENTRY * glGetHistogramParameterfvPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetHistogramParameterivPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * glMinmaxPROC) (GLenum target, GLenum internalformat, GLboolean sink);
typedef void (APIENTRY * glResetMinmaxPROC) (GLenum target);
typedef void (APIENTRY * glGetMinmaxPROC) (GLenum target, GLboolean reset, GLenum format, GLenum types, GLvoid *values);
typedef void (APIENTRY * glGetMinmaxParameterfvPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetMinmaxParameterivPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * glConvolutionFilter1DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
typedef void (APIENTRY * glConvolutionFilter2DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
typedef void (APIENTRY * glConvolutionParameterfPROC) (GLenum target, GLenum pname, GLfloat params);
typedef void (APIENTRY * glConvolutionParameterfvPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * glConvolutionParameteriPROC) (GLenum target, GLenum pname, GLint params);
typedef void (APIENTRY * glConvolutionParameterivPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRY * glCopyConvolutionFilter1DPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * glCopyConvolutionFilter2DPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY * glGetConvolutionFilterPROC) (GLenum target, GLenum format, GLenum type, GLvoid *image);
typedef void (APIENTRY * glGetConvolutionParameterfvPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetConvolutionParameterivPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * glSeparableFilter2DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
typedef void (APIENTRY * glGetSeparableFilterPROC) (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);

extern GLEW_EXPORT glBlendColorPROC glBlendColor;
extern GLEW_EXPORT glBlendEquationPROC glBlendEquation;
extern GLEW_EXPORT glColorTablePROC glColorTable;
extern GLEW_EXPORT glColorTableParameterfvPROC glColorTableParameterfv;
extern GLEW_EXPORT glColorTableParameterivPROC glColorTableParameteriv;
extern GLEW_EXPORT glCopyColorTablePROC glCopyColorTable;
extern GLEW_EXPORT glGetColorTablePROC glGetColorTable;
extern GLEW_EXPORT glGetColorTableParameterfvPROC glGetColorTableParameterfv;
extern GLEW_EXPORT glGetColorTableParameterivPROC glGetColorTableParameteriv;
extern GLEW_EXPORT glColorSubTablePROC glColorSubTable;
extern GLEW_EXPORT glCopyColorSubTablePROC glCopyColorSubTable;
extern GLEW_EXPORT glConvolutionFilter1DPROC glConvolutionFilter1D;
extern GLEW_EXPORT glConvolutionFilter2DPROC glConvolutionFilter2D;
extern GLEW_EXPORT glConvolutionParameterfPROC glConvolutionParameterf;
extern GLEW_EXPORT glConvolutionParameterfvPROC glConvolutionParameterfv;
extern GLEW_EXPORT glConvolutionParameteriPROC glConvolutionParameteri;
extern GLEW_EXPORT glConvolutionParameterivPROC glConvolutionParameteriv;
extern GLEW_EXPORT glCopyConvolutionFilter1DPROC glCopyConvolutionFilter1D;
extern GLEW_EXPORT glCopyConvolutionFilter2DPROC glCopyConvolutionFilter2D;
extern GLEW_EXPORT glGetConvolutionFilterPROC glGetConvolutionFilter;
extern GLEW_EXPORT glGetConvolutionParameterfvPROC glGetConvolutionParameterfv;
extern GLEW_EXPORT glGetConvolutionParameterivPROC glGetConvolutionParameteriv;
extern GLEW_EXPORT glGetSeparableFilterPROC glGetSeparableFilter;
extern GLEW_EXPORT glSeparableFilter2DPROC glSeparableFilter2D;
extern GLEW_EXPORT glGetHistogramPROC glGetHistogram;
extern GLEW_EXPORT glGetHistogramParameterfvPROC glGetHistogramParameterfv;
extern GLEW_EXPORT glGetHistogramParameterivPROC glGetHistogramParameteriv;
extern GLEW_EXPORT glGetMinmaxPROC glGetMinmax;
extern GLEW_EXPORT glGetMinmaxParameterfvPROC glGetMinmaxParameterfv;
extern GLEW_EXPORT glGetMinmaxParameterivPROC glGetMinmaxParameteriv;
extern GLEW_EXPORT glHistogramPROC glHistogram;
extern GLEW_EXPORT glMinmaxPROC glMinmax;
extern GLEW_EXPORT glResetHistogramPROC glResetHistogram;
extern GLEW_EXPORT glResetMinmaxPROC glResetMinmax;

#endif /* GL_ARB_imaging */

/* -------------------------- ARB_matrix_palette -------------------------- */

#ifdef GL_ARB_matrix_palette

#define GL_MATRIX_PALETTE_ARB                                   0x8840
#define GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB                   0x8841
#define GL_MAX_PALETTE_MATRICES_ARB                             0x8842
#define GL_CURRENT_PALETTE_MATRIX_ARB                           0x8843
#define GL_MATRIX_INDEX_ARRAY_ARB                               0x8844
#define GL_CURRENT_MATRIX_INDEX_ARB                             0x8845
#define GL_MATRIX_INDEX_ARRAY_SIZE_ARB                          0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_ARB                          0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_ARB                        0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_ARB                       0x8849

typedef void (APIENTRY * glCurrentPaletteMatrixARBPROC) (GLint index);
typedef void (APIENTRY * glMatrixIndexubvARBPROC) (GLint size, GLubyte *indices);
typedef void (APIENTRY * glMatrixIndexusvARBPROC) (GLint size, GLushort *indices);
typedef void (APIENTRY * glMatrixIndexuivARBPROC) (GLint size, GLuint *indices);
typedef void (APIENTRY * glMatrixIndexPointerARBPROC) (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);

extern GLEW_EXPORT glCurrentPaletteMatrixARBPROC glCurrentPaletteMatrixARB;
extern GLEW_EXPORT glMatrixIndexubvARBPROC glMatrixIndexubvARB;
extern GLEW_EXPORT glMatrixIndexusvARBPROC glMatrixIndexusvARB;
extern GLEW_EXPORT glMatrixIndexuivARBPROC glMatrixIndexuivARB;
extern GLEW_EXPORT glMatrixIndexPointerARBPROC glMatrixIndexPointerARB;

#endif /* GL_ARB_matrix_palette */

/* ---------------------------- ARB_multisample --------------------------- */

#ifdef GL_ARB_multisample

#define GL_MULTISAMPLE_ARB                                      0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE_ARB                         0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_ARB                              0x809F
#define GL_SAMPLE_COVERAGE_ARB                                  0x80A0
#define GL_SAMPLE_BUFFERS_ARB                                   0x80A8
#define GL_SAMPLES_ARB                                          0x80A9
#define GL_SAMPLE_COVERAGE_VALUE_ARB                            0x80AA
#define GL_SAMPLE_COVERAGE_INVERT_ARB                           0x80AB
#define GL_MULTISAMPLE_BIT_ARB                                  0x20000000

typedef void (APIENTRY * glSampleCoverageARBPROC) (GLclampf value, GLboolean invert);

extern GLEW_EXPORT glSampleCoverageARBPROC glSampleCoverageARB;

#endif /* GL_ARB_multisample */

/* --------------------------- ARB_multitexture --------------------------- */

#ifdef GL_ARB_multitexture

#define GL_TEXTURE0_ARB                                         0x84C0
#define GL_TEXTURE1_ARB                                         0x84C1
#define GL_TEXTURE2_ARB                                         0x84C2
#define GL_TEXTURE3_ARB                                         0x84C3
#define GL_TEXTURE4_ARB                                         0x84C4
#define GL_TEXTURE5_ARB                                         0x84C5
#define GL_TEXTURE6_ARB                                         0x84C6
#define GL_TEXTURE7_ARB                                         0x84C7
#define GL_TEXTURE8_ARB                                         0x84C8
#define GL_TEXTURE9_ARB                                         0x84C9
#define GL_TEXTURE10_ARB                                        0x84CA
#define GL_TEXTURE11_ARB                                        0x84CB
#define GL_TEXTURE12_ARB                                        0x84CC
#define GL_TEXTURE13_ARB                                        0x84CD
#define GL_TEXTURE14_ARB                                        0x84CE
#define GL_TEXTURE15_ARB                                        0x84CF
#define GL_TEXTURE16_ARB                                        0x84D0
#define GL_TEXTURE17_ARB                                        0x84D1
#define GL_TEXTURE18_ARB                                        0x84D2
#define GL_TEXTURE19_ARB                                        0x84D3
#define GL_TEXTURE20_ARB                                        0x84D4
#define GL_TEXTURE21_ARB                                        0x84D5
#define GL_TEXTURE22_ARB                                        0x84D6
#define GL_TEXTURE23_ARB                                        0x84D7
#define GL_TEXTURE24_ARB                                        0x84D8
#define GL_TEXTURE25_ARB                                        0x84D9
#define GL_TEXTURE26_ARB                                        0x84DA
#define GL_TEXTURE27_ARB                                        0x84DB
#define GL_TEXTURE28_ARB                                        0x84DC
#define GL_TEXTURE29_ARB                                        0x84DD
#define GL_TEXTURE30_ARB                                        0x84DE
#define GL_TEXTURE31_ARB                                        0x84DF
#define GL_ACTIVE_TEXTURE_ARB                                   0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB                            0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB                                0x84E2

typedef void (APIENTRY * glActiveTextureARBPROC) (GLenum texture);
typedef void (APIENTRY * glClientActiveTextureARBPROC) (GLenum texture);
typedef void (APIENTRY * glMultiTexCoord1dARBPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * glMultiTexCoord1dvARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord1fARBPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * glMultiTexCoord1fvARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord1iARBPROC) (GLenum target, GLint s);
typedef void (APIENTRY * glMultiTexCoord1ivARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord1sARBPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * glMultiTexCoord1svARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * glMultiTexCoord2dARBPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * glMultiTexCoord2dvARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord2fARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * glMultiTexCoord2fvARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord2iARBPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * glMultiTexCoord2ivARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord2sARBPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * glMultiTexCoord2svARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * glMultiTexCoord3dARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * glMultiTexCoord3dvARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord3fARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * glMultiTexCoord3fvARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord3iARBPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * glMultiTexCoord3ivARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord3sARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * glMultiTexCoord3svARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * glMultiTexCoord4dARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * glMultiTexCoord4dvARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * glMultiTexCoord4fARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * glMultiTexCoord4fvARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * glMultiTexCoord4iARBPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * glMultiTexCoord4ivARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * glMultiTexCoord4sARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * glMultiTexCoord4svARBPROC) (GLenum target, const GLshort *v);

extern GLEW_EXPORT glActiveTextureARBPROC glActiveTextureARB;
extern GLEW_EXPORT glClientActiveTextureARBPROC glClientActiveTextureARB;
extern GLEW_EXPORT glMultiTexCoord1dARBPROC glMultiTexCoord1dARB;
extern GLEW_EXPORT glMultiTexCoord1dvARBPROC glMultiTexCoord1dvARB;
extern GLEW_EXPORT glMultiTexCoord1fARBPROC glMultiTexCoord1fARB;
extern GLEW_EXPORT glMultiTexCoord1fvARBPROC glMultiTexCoord1fvARB;
extern GLEW_EXPORT glMultiTexCoord1iARBPROC glMultiTexCoord1iARB;
extern GLEW_EXPORT glMultiTexCoord1ivARBPROC glMultiTexCoord1ivARB;
extern GLEW_EXPORT glMultiTexCoord1sARBPROC glMultiTexCoord1sARB;
extern GLEW_EXPORT glMultiTexCoord1svARBPROC glMultiTexCoord1svARB;
extern GLEW_EXPORT glMultiTexCoord2dARBPROC glMultiTexCoord2dARB;
extern GLEW_EXPORT glMultiTexCoord2dvARBPROC glMultiTexCoord2dvARB;
extern GLEW_EXPORT glMultiTexCoord2fARBPROC glMultiTexCoord2fARB;
extern GLEW_EXPORT glMultiTexCoord2fvARBPROC glMultiTexCoord2fvARB;
extern GLEW_EXPORT glMultiTexCoord2iARBPROC glMultiTexCoord2iARB;
extern GLEW_EXPORT glMultiTexCoord2ivARBPROC glMultiTexCoord2ivARB;
extern GLEW_EXPORT glMultiTexCoord2sARBPROC glMultiTexCoord2sARB;
extern GLEW_EXPORT glMultiTexCoord2svARBPROC glMultiTexCoord2svARB;
extern GLEW_EXPORT glMultiTexCoord3dARBPROC glMultiTexCoord3dARB;
extern GLEW_EXPORT glMultiTexCoord3dvARBPROC glMultiTexCoord3dvARB;
extern GLEW_EXPORT glMultiTexCoord3fARBPROC glMultiTexCoord3fARB;
extern GLEW_EXPORT glMultiTexCoord3fvARBPROC glMultiTexCoord3fvARB;
extern GLEW_EXPORT glMultiTexCoord3iARBPROC glMultiTexCoord3iARB;
extern GLEW_EXPORT glMultiTexCoord3ivARBPROC glMultiTexCoord3ivARB;
extern GLEW_EXPORT glMultiTexCoord3sARBPROC glMultiTexCoord3sARB;
extern GLEW_EXPORT glMultiTexCoord3svARBPROC glMultiTexCoord3svARB;
extern GLEW_EXPORT glMultiTexCoord4dARBPROC glMultiTexCoord4dARB;
extern GLEW_EXPORT glMultiTexCoord4dvARBPROC glMultiTexCoord4dvARB;
extern GLEW_EXPORT glMultiTexCoord4fARBPROC glMultiTexCoord4fARB;
extern GLEW_EXPORT glMultiTexCoord4fvARBPROC glMultiTexCoord4fvARB;
extern GLEW_EXPORT glMultiTexCoord4iARBPROC glMultiTexCoord4iARB;
extern GLEW_EXPORT glMultiTexCoord4ivARBPROC glMultiTexCoord4ivARB;
extern GLEW_EXPORT glMultiTexCoord4sARBPROC glMultiTexCoord4sARB;
extern GLEW_EXPORT glMultiTexCoord4svARBPROC glMultiTexCoord4svARB;

#endif /* GL_ARB_multitexture */

/* ------------------------- ARB_point_parameters ------------------------- */

#ifdef GL_ARB_point_parameters

#define GL_POINT_SIZE_MIN_ARB                                   0x8126
#define GL_POINT_SIZE_MAX_ARB                                   0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB                        0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB                       0x8129

typedef void (APIENTRY * glPointParameterfARBPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * glPointParameterfvARBPROC) (GLenum pname, GLfloat *params);

extern GLEW_EXPORT glPointParameterfARBPROC glPointParameterfARB;
extern GLEW_EXPORT glPointParameterfvARBPROC glPointParameterfvARB;

#endif /* GL_ARB_point_parameters */

/* ------------------------------ ARB_shadow ------------------------------ */

#ifdef GL_ARB_shadow

#define GL_TEXTURE_COMPARE_MODE_ARB                             0x884C
#define GL_TEXTURE_COMPARE_FUNC_ARB                             0x884D
#define GL_COMPARE_R_TO_TEXTURE_ARB                             0x884E

#endif /* GL_ARB_shadow */

/* -------------------------- ARB_shadow_ambient -------------------------- */

#ifdef GL_ARB_shadow_ambient

#define GL_TEXTURE_COMPARE_FAIL_VALUE_ARB                       0x80BF

#endif /* GL_ARB_shadow_ambient */

/* ----------------------- ARB_texture_border_clamp ----------------------- */

#ifdef GL_ARB_texture_border_clamp

#define GL_CLAMP_TO_BORDER_ARB                                  0x812D

#endif /* GL_ARB_texture_border_clamp */

/* ------------------------ ARB_texture_compression ----------------------- */

#ifdef GL_ARB_texture_compression

#define GL_COMPRESSED_ALPHA_ARB                                 0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB                             0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB                       0x84EB
#define GL_COMPRESSED_INTENSITY_ARB                             0x84EC
#define GL_COMPRESSED_RGB_ARB                                   0x84ED
#define GL_COMPRESSED_RGBA_ARB                                  0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB                         0x84EF
#define GL_TEXTURE_IMAGE_SIZE_ARB                               0x86A0
#define GL_TEXTURE_COMPRESSED_ARB                               0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB                   0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB                       0x86A3

typedef void (APIENTRY * glCompressedTexImage1DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexImage2DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexImage3DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexSubImage1DARBPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexSubImage2DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glCompressedTexSubImage3DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * glGetCompressedTexImageARBPROC) (GLenum target, GLint lod, GLvoid *img);

extern GLEW_EXPORT glCompressedTexImage3DARBPROC glCompressedTexImage3DARB;
extern GLEW_EXPORT glCompressedTexImage2DARBPROC glCompressedTexImage2DARB;
extern GLEW_EXPORT glCompressedTexImage1DARBPROC glCompressedTexImage1DARB;
extern GLEW_EXPORT glCompressedTexSubImage3DARBPROC glCompressedTexSubImage3DARB;
extern GLEW_EXPORT glCompressedTexSubImage2DARBPROC glCompressedTexSubImage2DARB;
extern GLEW_EXPORT glCompressedTexSubImage1DARBPROC glCompressedTexSubImage1DARB;
extern GLEW_EXPORT glGetCompressedTexImageARBPROC glGetCompressedTexImageARB;

#endif /* GL_ARB_texture_compression */

/* ------------------------- ARB_texture_cube_map ------------------------- */

#ifdef GL_ARB_texture_cube_map

#define GL_NORMAL_MAP_ARB                                       0x8511
#define GL_REFLECTION_MAP_ARB                                   0x8512
#define GL_TEXTURE_CUBE_MAP_ARB                                 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB                         0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB                      0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB                      0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB                      0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB                      0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB                      0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB                      0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB                           0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB                        0x851C

#endif /* GL_ARB_texture_cube_map */

/* -------------------------- ARB_texture_env_add ------------------------- */

/* ------------------------ ARB_texture_env_combine ----------------------- */

#ifdef GL_ARB_texture_env_combine

#define GL_COMBINE_ARB                                          0x8570
#define GL_COMBINE_RGB_ARB                                      0x8571
#define GL_COMBINE_ALPHA_ARB                                    0x8572
#define GL_RGB_SCALE_ARB                                        0x8573
#define GL_ADD_SIGNED_ARB                                       0x8574
#define GL_INTERPOLATE_ARB                                      0x8575
#define GL_CONSTANT_ARB                                         0x8576
#define GL_PRIMARY_COLOR_ARB                                    0x8577
#define GL_PREVIOUS_ARB                                         0x8578
#define GL_SOURCE0_RGB_ARB                                      0x8580
#define GL_SOURCE1_RGB_ARB                                      0x8581
#define GL_SOURCE2_RGB_ARB                                      0x8582
#define GL_SOURCE0_ALPHA_ARB                                    0x8588
#define GL_SOURCE1_ALPHA_ARB                                    0x8589
#define GL_SOURCE2_ALPHA_ARB                                    0x858A
#define GL_OPERAND0_RGB_ARB                                     0x8590
#define GL_OPERAND1_RGB_ARB                                     0x8591
#define GL_OPERAND2_RGB_ARB                                     0x8592
#define GL_OPERAND0_ALPHA_ARB                                   0x8598
#define GL_OPERAND1_ALPHA_ARB                                   0x8599
#define GL_OPERAND2_ALPHA_ARB                                   0x859A

#endif /* GL_ARB_texture_env_combine */

/* ----------------------- ARB_texture_env_crossbar ----------------------- */

/* ------------------------- ARB_texture_env_dot3 ------------------------- */

#ifdef GL_ARB_texture_env_dot3

#define GL_DOT3_RGB_ARB                                         0x86AE
#define GL_DOT3_RGBA_ARB                                        0x86AF

#endif /* GL_ARB_texture_env_dot3 */

/* ---------------------- ARB_texture_mirrored_repeat --------------------- */

#ifdef GL_ARB_texture_mirrored_repeat

#define GL_MIRRORED_REPEAT_ARB                                  0x8370

#endif /* GL_ARB_texture_mirrored_repeat */

/* ------------------------- ARB_transpose_matrix ------------------------- */

#ifdef GL_ARB_transpose_matrix

#define GL_TRANSPOSE_MODELVIEW_MATRIX_ARB                       0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX_ARB                      0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX_ARB                         0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX_ARB                           0x84E6

typedef void (APIENTRY * glLoadTransposeMatrixdARBPROC) (const GLdouble m[16]);
typedef void (APIENTRY * glLoadTransposeMatrixfARBPROC) (const GLfloat m[16]);
typedef void (APIENTRY * glMultTransposeMatrixdARBPROC) (const GLdouble m[16]);
typedef void (APIENTRY * glMultTransposeMatrixfARBPROC) (const GLfloat m[16]);

extern GLEW_EXPORT glLoadTransposeMatrixfARBPROC glLoadTransposeMatrixfARB;
extern GLEW_EXPORT glLoadTransposeMatrixdARBPROC glLoadTransposeMatrixdARB;
extern GLEW_EXPORT glMultTransposeMatrixfARBPROC glMultTransposeMatrixfARB;
extern GLEW_EXPORT glMultTransposeMatrixdARBPROC glMultTransposeMatrixdARB;

#endif /* GL_ARB_transpose_matrix */

/* --------------------------- ARB_vertex_blend --------------------------- */

#ifdef GL_ARB_vertex_blend

#define GL_MAX_VERTEX_UNITS_ARB                                 0x86A4
#define GL_ACTIVE_VERTEX_UNITS_ARB                              0x86A5
#define GL_WEIGHT_SUM_UNITY_ARB                                 0x86A6
#define GL_VERTEX_BLEND_ARB                                     0x86A7
#define GL_CURRENT_WEIGHT_ARB                                   0x86A8
#define GL_WEIGHT_ARRAY_TYPE_ARB                                0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_ARB                              0x86AA
#define GL_WEIGHT_ARRAY_SIZE_ARB                                0x86AB
#define GL_WEIGHT_ARRAY_POINTER_ARB                             0x86AC
#define GL_WEIGHT_ARRAY_ARB                                     0x86AD
#define GL_MODELVIEW0_ARB                                       0x1700
#define GL_MODELVIEW1_ARB                                       0x850A
#define GL_MODELVIEW2_ARB                                       0x8722
#define GL_MODELVIEW3_ARB                                       0x8723
#define GL_MODELVIEW4_ARB                                       0x8724
#define GL_MODELVIEW5_ARB                                       0x8725
#define GL_MODELVIEW6_ARB                                       0x8726
#define GL_MODELVIEW7_ARB                                       0x8727
#define GL_MODELVIEW8_ARB                                       0x8728
#define GL_MODELVIEW9_ARB                                       0x8729
#define GL_MODELVIEW10_ARB                                      0x872A
#define GL_MODELVIEW11_ARB                                      0x872B
#define GL_MODELVIEW12_ARB                                      0x872C
#define GL_MODELVIEW13_ARB                                      0x872D
#define GL_MODELVIEW14_ARB                                      0x872E
#define GL_MODELVIEW15_ARB                                      0x872F
#define GL_MODELVIEW16_ARB                                      0x8730
#define GL_MODELVIEW17_ARB                                      0x8731
#define GL_MODELVIEW18_ARB                                      0x8732
#define GL_MODELVIEW19_ARB                                      0x8733
#define GL_MODELVIEW20_ARB                                      0x8734
#define GL_MODELVIEW21_ARB                                      0x8735
#define GL_MODELVIEW22_ARB                                      0x8736
#define GL_MODELVIEW23_ARB                                      0x8737
#define GL_MODELVIEW24_ARB                                      0x8738
#define GL_MODELVIEW25_ARB                                      0x8739
#define GL_MODELVIEW26_ARB                                      0x873A
#define GL_MODELVIEW27_ARB                                      0x873B
#define GL_MODELVIEW28_ARB                                      0x873C
#define GL_MODELVIEW29_ARB                                      0x873D
#define GL_MODELVIEW30_ARB                                      0x873E
#define GL_MODELVIEW31_ARB                                      0x873F

typedef void (APIENTRY * glWeightbvARBPROC) (GLint size, GLbyte *weights);
typedef void (APIENTRY * glWeightsvARBPROC) (GLint size, GLshort *weights);
typedef void (APIENTRY * glWeightivARBPROC) (GLint size, GLint *weights);
typedef void (APIENTRY * glWeightfvARBPROC) (GLint size, GLfloat *weights);
typedef void (APIENTRY * glWeightdvARBPROC) (GLint size, GLdouble *weights);
typedef void (APIENTRY * glWeightubvARBPROC) (GLint size, GLubyte *weights);
typedef void (APIENTRY * glWeightusvARBPROC) (GLint size, GLushort *weights);
typedef void (APIENTRY * glWeightuivARBPROC) (GLint size, GLuint *weights);
typedef void (APIENTRY * glWeightPointerARBPROC) (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);
typedef void (APIENTRY * glVertexBlendARBPROC) (GLint count);

extern GLEW_EXPORT glWeightbvARBPROC glWeightbvARB;
extern GLEW_EXPORT glWeightsvARBPROC glWeightsvARB;
extern GLEW_EXPORT glWeightivARBPROC glWeightivARB;
extern GLEW_EXPORT glWeightfvARBPROC glWeightfvARB;
extern GLEW_EXPORT glWeightdvARBPROC glWeightdvARB;
extern GLEW_EXPORT glWeightubvARBPROC glWeightubvARB;
extern GLEW_EXPORT glWeightusvARBPROC glWeightusvARB;
extern GLEW_EXPORT glWeightuivARBPROC glWeightuivARB;
extern GLEW_EXPORT glWeightPointerARBPROC glWeightPointerARB;
extern GLEW_EXPORT glVertexBlendARBPROC glVertexBlendARB;

#endif /* GL_ARB_vertex_blend */

/* -------------------------- ARB_vertex_program -------------------------- */

#ifdef GL_ARB_vertex_program

#define GL_VERTEX_PROGRAM_ARB                                   0x8620
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB                        0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB                          0x8643
#define GL_COLOR_SUM_ARB                                        0x8458
#define GL_PROGRAM_FORMAT_ASCII_ARB                             0x8875
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB                      0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB                         0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB                       0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB                         0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB                   0x886A
#define GL_CURRENT_VERTEX_ATTRIB_ARB                            0x8626
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB                      0x8645
#define GL_PROGRAM_LENGTH_ARB                                   0x8627
#define GL_PROGRAM_FORMAT_ARB                                   0x8876
#define GL_PROGRAM_BINDING_ARB                                  0x8677
#define GL_PROGRAM_INSTRUCTIONS_ARB                             0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB                         0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB                      0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB                  0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB                              0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB                          0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB                       0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB                   0x88A7
#define GL_PROGRAM_PARAMETERS_ARB                               0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB                           0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB                        0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB                    0x88AB
#define GL_PROGRAM_ATTRIBS_ARB                                  0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB                              0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB                           0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB                       0x88AF
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB                        0x88B0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB                    0x88B1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB                 0x88B2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB             0x88B3
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB                     0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB                       0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB                      0x88B6
#define GL_PROGRAM_STRING_ARB                                   0x8628
#define GL_PROGRAM_ERROR_POSITION_ARB                           0x864B
#define GL_CURRENT_MATRIX_ARB                                   0x8641
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB                         0x88B7
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB                       0x8640
#define GL_MAX_VERTEX_ATTRIBS_ARB                               0x8869
#define GL_MAX_PROGRAM_MATRICES_ARB                             0x862F
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB                   0x862E
#define GL_PROGRAM_ERROR_STRING_ARB                             0x8874
#define GL_MATRIX0_ARB                                          0x88C0
#define GL_MATRIX1_ARB                                          0x88C1
#define GL_MATRIX2_ARB                                          0x88C2
#define GL_MATRIX3_ARB                                          0x88C3
#define GL_MATRIX4_ARB                                          0x88C4
#define GL_MATRIX5_ARB                                          0x88C5
#define GL_MATRIX6_ARB                                          0x88C6
#define GL_MATRIX7_ARB                                          0x88C7
#define GL_MATRIX8_ARB                                          0x88C8
#define GL_MATRIX9_ARB                                          0x88C9
#define GL_MATRIX10_ARB                                         0x88CA
#define GL_MATRIX11_ARB                                         0x88CB
#define GL_MATRIX12_ARB                                         0x88CC
#define GL_MATRIX13_ARB                                         0x88CD
#define GL_MATRIX14_ARB                                         0x88CE
#define GL_MATRIX15_ARB                                         0x88CF
#define GL_MATRIX16_ARB                                         0x88D0
#define GL_MATRIX17_ARB                                         0x88D1
#define GL_MATRIX18_ARB                                         0x88D2
#define GL_MATRIX19_ARB                                         0x88D3
#define GL_MATRIX20_ARB                                         0x88D4
#define GL_MATRIX21_ARB                                         0x88D5
#define GL_MATRIX22_ARB                                         0x88D6
#define GL_MATRIX23_ARB                                         0x88D7
#define GL_MATRIX24_ARB                                         0x88D8
#define GL_MATRIX25_ARB                                         0x88D9
#define GL_MATRIX26_ARB                                         0x88DA
#define GL_MATRIX27_ARB                                         0x88DB
#define GL_MATRIX28_ARB                                         0x88DC
#define GL_MATRIX29_ARB                                         0x88DD
#define GL_MATRIX30_ARB                                         0x88DE
#define GL_MATRIX31_ARB                                         0x88DF

typedef void (APIENTRY * glVertexAttrib1sARBPROC) (GLuint index, GLshort x);
typedef void (APIENTRY * glVertexAttrib1fARBPROC) (GLuint index, GLfloat x);
typedef void (APIENTRY * glVertexAttrib1dARBPROC) (GLuint index, GLdouble x);
typedef void (APIENTRY * glVertexAttrib2sARBPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRY * glVertexAttrib2fARBPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRY * glVertexAttrib2dARBPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRY * glVertexAttrib3sARBPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * glVertexAttrib3fARBPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * glVertexAttrib3dARBPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * glVertexAttrib4sARBPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRY * glVertexAttrib4fARBPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glVertexAttrib4dARBPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glVertexAttrib4NubARBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRY * glVertexAttrib1svARBPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib1fvARBPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib1dvARBPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib2svARBPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib2fvARBPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib2dvARBPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib3svARBPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib3fvARBPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib3dvARBPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib4bvARBPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRY * glVertexAttrib4svARBPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib4ivARBPROC) (GLuint index, const GLint *v);
typedef void (APIENTRY * glVertexAttrib4ubvARBPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRY * glVertexAttrib4usvARBPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRY * glVertexAttrib4uivARBPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRY * glVertexAttrib4fvARBPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib4dvARBPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib4NbvARBPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRY * glVertexAttrib4NsvARBPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib4NivARBPROC) (GLuint index, const GLint *v);
typedef void (APIENTRY * glVertexAttrib4NubvARBPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRY * glVertexAttrib4NusvARBPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRY * glVertexAttrib4NuivARBPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRY * glVertexAttribPointerARBPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * glEnableVertexAttribArrayARBPROC) (GLuint index);
typedef void (APIENTRY * glDisableVertexAttribArrayARBPROC) (GLuint index);
typedef void (APIENTRY * glProgramStringARBPROC) (GLenum target, GLenum format, GLsizei len, const GLvoid *string);
typedef void (APIENTRY * glBindProgramARBPROC) (GLenum target, GLuint program);
typedef void (APIENTRY * glDeleteProgramsARBPROC) (GLsizei n, const GLuint *programs);
typedef void (APIENTRY * glGenProgramsARBPROC) (GLsizei n, GLuint *programs);
typedef void (APIENTRY * glProgramEnvParameter4dARBPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glProgramEnvParameter4dvARBPROC) (GLenum target, GLuint index, const GLdouble *params);
typedef void (APIENTRY * glProgramEnvParameter4fARBPROC) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glProgramEnvParameter4fvARBPROC) (GLenum target, GLuint index, const GLfloat *params);
typedef void (APIENTRY * glProgramLocalParameter4dARBPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glProgramLocalParameter4dvARBPROC) (GLenum target, GLuint index, const GLdouble *params);
typedef void (APIENTRY * glProgramLocalParameter4fARBPROC) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glProgramLocalParameter4fvARBPROC) (GLenum target, GLuint index, const GLfloat *params);
typedef void (APIENTRY * glGetProgramEnvParameterdvARBPROC) (GLenum target, GLuint index, GLdouble *params);
typedef void (APIENTRY * glGetProgramEnvParameterfvARBPROC) (GLenum target, GLuint index, GLfloat *params);
typedef void (APIENTRY * glGetProgramLocalParameterdvARBPROC) (GLenum target, GLuint index, GLdouble *params);
typedef void (APIENTRY * glGetProgramLocalParameterfvARBPROC) (GLenum target, GLuint index, GLfloat *params);
typedef void (APIENTRY * glGetProgramivARBPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetProgramStringARBPROC) (GLenum target, GLenum pname, GLvoid *string);
typedef void (APIENTRY * glGetVertexAttribdvARBPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRY * glGetVertexAttribfvARBPROC) (GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetVertexAttribivARBPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetVertexAttribPointervARBPROC) (GLuint index, GLenum pname, GLvoid **pointer);
typedef GLboolean (APIENTRY * glIsProgramARBPROC) (GLuint program);

extern GLEW_EXPORT glVertexAttrib1sARBPROC glVertexAttrib1sARB;
extern GLEW_EXPORT glVertexAttrib1fARBPROC glVertexAttrib1fARB;
extern GLEW_EXPORT glVertexAttrib1dARBPROC glVertexAttrib1dARB;
extern GLEW_EXPORT glVertexAttrib2sARBPROC glVertexAttrib2sARB;
extern GLEW_EXPORT glVertexAttrib2fARBPROC glVertexAttrib2fARB;
extern GLEW_EXPORT glVertexAttrib2dARBPROC glVertexAttrib2dARB;
extern GLEW_EXPORT glVertexAttrib3sARBPROC glVertexAttrib3sARB;
extern GLEW_EXPORT glVertexAttrib3fARBPROC glVertexAttrib3fARB;
extern GLEW_EXPORT glVertexAttrib3dARBPROC glVertexAttrib3dARB;
extern GLEW_EXPORT glVertexAttrib4sARBPROC glVertexAttrib4sARB;
extern GLEW_EXPORT glVertexAttrib4fARBPROC glVertexAttrib4fARB;
extern GLEW_EXPORT glVertexAttrib4dARBPROC glVertexAttrib4dARB;
extern GLEW_EXPORT glVertexAttrib4NubARBPROC glVertexAttrib4NubARB;
extern GLEW_EXPORT glVertexAttrib1svARBPROC glVertexAttrib1svARB;
extern GLEW_EXPORT glVertexAttrib1fvARBPROC glVertexAttrib1fvARB;
extern GLEW_EXPORT glVertexAttrib1dvARBPROC glVertexAttrib1dvARB;
extern GLEW_EXPORT glVertexAttrib2svARBPROC glVertexAttrib2svARB;
extern GLEW_EXPORT glVertexAttrib2fvARBPROC glVertexAttrib2fvARB;
extern GLEW_EXPORT glVertexAttrib2dvARBPROC glVertexAttrib2dvARB;
extern GLEW_EXPORT glVertexAttrib3svARBPROC glVertexAttrib3svARB;
extern GLEW_EXPORT glVertexAttrib3fvARBPROC glVertexAttrib3fvARB;
extern GLEW_EXPORT glVertexAttrib3dvARBPROC glVertexAttrib3dvARB;
extern GLEW_EXPORT glVertexAttrib4bvARBPROC glVertexAttrib4bvARB;
extern GLEW_EXPORT glVertexAttrib4svARBPROC glVertexAttrib4svARB;
extern GLEW_EXPORT glVertexAttrib4ivARBPROC glVertexAttrib4ivARB;
extern GLEW_EXPORT glVertexAttrib4ubvARBPROC glVertexAttrib4ubvARB;
extern GLEW_EXPORT glVertexAttrib4usvARBPROC glVertexAttrib4usvARB;
extern GLEW_EXPORT glVertexAttrib4uivARBPROC glVertexAttrib4uivARB;
extern GLEW_EXPORT glVertexAttrib4fvARBPROC glVertexAttrib4fvARB;
extern GLEW_EXPORT glVertexAttrib4dvARBPROC glVertexAttrib4dvARB;
extern GLEW_EXPORT glVertexAttrib4NbvARBPROC glVertexAttrib4NbvARB;
extern GLEW_EXPORT glVertexAttrib4NsvARBPROC glVertexAttrib4NsvARB;
extern GLEW_EXPORT glVertexAttrib4NivARBPROC glVertexAttrib4NivARB;
extern GLEW_EXPORT glVertexAttrib4NubvARBPROC glVertexAttrib4NubvARB;
extern GLEW_EXPORT glVertexAttrib4NusvARBPROC glVertexAttrib4NusvARB;
extern GLEW_EXPORT glVertexAttrib4NuivARBPROC glVertexAttrib4NuivARB;
extern GLEW_EXPORT glVertexAttribPointerARBPROC glVertexAttribPointerARB;
extern GLEW_EXPORT glEnableVertexAttribArrayARBPROC glEnableVertexAttribArrayARB;
extern GLEW_EXPORT glDisableVertexAttribArrayARBPROC glDisableVertexAttribArrayARB;
extern GLEW_EXPORT glProgramStringARBPROC glProgramStringARB;
extern GLEW_EXPORT glBindProgramARBPROC glBindProgramARB;
extern GLEW_EXPORT glDeleteProgramsARBPROC glDeleteProgramsARB;
extern GLEW_EXPORT glGenProgramsARBPROC glGenProgramsARB;
extern GLEW_EXPORT glProgramEnvParameter4dARBPROC glProgramEnvParameter4dARB;
extern GLEW_EXPORT glProgramEnvParameter4dvARBPROC glProgramEnvParameter4dvARB;
extern GLEW_EXPORT glProgramEnvParameter4fARBPROC glProgramEnvParameter4fARB;
extern GLEW_EXPORT glProgramEnvParameter4fvARBPROC glProgramEnvParameter4fvARB;
extern GLEW_EXPORT glProgramLocalParameter4dARBPROC glProgramLocalParameter4dARB;
extern GLEW_EXPORT glProgramLocalParameter4dvARBPROC glProgramLocalParameter4dvARB;
extern GLEW_EXPORT glProgramLocalParameter4fARBPROC glProgramLocalParameter4fARB;
extern GLEW_EXPORT glProgramLocalParameter4fvARBPROC glProgramLocalParameter4fvARB;
extern GLEW_EXPORT glGetProgramEnvParameterdvARBPROC glGetProgramEnvParameterdvARB;
extern GLEW_EXPORT glGetProgramEnvParameterfvARBPROC glGetProgramEnvParameterfvARB;
extern GLEW_EXPORT glGetProgramLocalParameterdvARBPROC glGetProgramLocalParameterdvARB;
extern GLEW_EXPORT glGetProgramLocalParameterfvARBPROC glGetProgramLocalParameterfvARB;
extern GLEW_EXPORT glGetProgramivARBPROC glGetProgramivARB;
extern GLEW_EXPORT glGetProgramStringARBPROC glGetProgramStringARB;
extern GLEW_EXPORT glGetVertexAttribdvARBPROC glGetVertexAttribdvARB;
extern GLEW_EXPORT glGetVertexAttribfvARBPROC glGetVertexAttribfvARB;
extern GLEW_EXPORT glGetVertexAttribivARBPROC glGetVertexAttribivARB;
extern GLEW_EXPORT glGetVertexAttribPointervARBPROC glGetVertexAttribPointervARB;
extern GLEW_EXPORT glIsProgramARBPROC glIsProgramARB;

#endif /* GL_ARB_vertex_program */

/* ---------------------------- ARB_window_pos ---------------------------- */

#ifdef GL_ARB_window_pos

typedef void (APIENTRY * glWindowPos2dARBPROC) (GLdouble x, GLdouble y);
typedef void (APIENTRY * glWindowPos2fARBPROC) (GLfloat x, GLfloat y);
typedef void (APIENTRY * glWindowPos2iARBPROC) (GLint x, GLint y);
typedef void (APIENTRY * glWindowPos2sARBPROC) (GLshort x, GLshort y);
typedef void (APIENTRY * glWindowPos2dvARBPROC) (const GLdouble *p);
typedef void (APIENTRY * glWindowPos2fvARBPROC) (const GLfloat *p);
typedef void (APIENTRY * glWindowPos2ivARBPROC) (const GLint *p);
typedef void (APIENTRY * glWindowPos2svARBPROC) (const GLshort *p);
typedef void (APIENTRY * glWindowPos3dARBPROC) (GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * glWindowPos3fARBPROC) (GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * glWindowPos3iARBPROC) (GLint x, GLint y, GLint z);
typedef void (APIENTRY * glWindowPos3sARBPROC) (GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * glWindowPos3dvARBPROC) (const GLdouble *p);
typedef void (APIENTRY * glWindowPos3fvARBPROC) (const GLfloat *p);
typedef void (APIENTRY * glWindowPos3ivARBPROC) (const GLint *p);
typedef void (APIENTRY * glWindowPos3svARBPROC) (const GLshort *p);

extern GLEW_EXPORT glWindowPos2dARBPROC glWindowPos2dARB;
extern GLEW_EXPORT glWindowPos2fARBPROC glWindowPos2fARB;
extern GLEW_EXPORT glWindowPos2iARBPROC glWindowPos2iARB;
extern GLEW_EXPORT glWindowPos2sARBPROC glWindowPos2sARB;
extern GLEW_EXPORT glWindowPos2dvARBPROC glWindowPos2dvARB;
extern GLEW_EXPORT glWindowPos2fvARBPROC glWindowPos2fvARB;
extern GLEW_EXPORT glWindowPos2ivARBPROC glWindowPos2ivARB;
extern GLEW_EXPORT glWindowPos2svARBPROC glWindowPos2svARB;
extern GLEW_EXPORT glWindowPos3dARBPROC glWindowPos3dARB;
extern GLEW_EXPORT glWindowPos3fARBPROC glWindowPos3fARB;
extern GLEW_EXPORT glWindowPos3iARBPROC glWindowPos3iARB;
extern GLEW_EXPORT glWindowPos3sARBPROC glWindowPos3sARB;
extern GLEW_EXPORT glWindowPos3dvARBPROC glWindowPos3dvARB;
extern GLEW_EXPORT glWindowPos3fvARBPROC glWindowPos3fvARB;
extern GLEW_EXPORT glWindowPos3ivARBPROC glWindowPos3ivARB;
extern GLEW_EXPORT glWindowPos3svARBPROC glWindowPos3svARB;

#endif /* GL_ARB_window_pos */

/* ------------------------------- EXT_abgr ------------------------------- */

#ifdef GL_EXT_abgr

#define GL_ABGR_EXT                                             0x8000

#endif /* GL_EXT_abgr */

/* ------------------------------- EXT_bgra ------------------------------- */

#ifdef GL_EXT_bgra

#define GL_BGR_EXT                                              0x80E0
#define GL_BGRA_EXT                                             0x80E1

#endif /* GL_EXT_bgra */

/* --------------------------- EXT_blend_color ---------------------------- */

#ifdef GL_EXT_blend_color

#define GL_CONSTANT_COLOR_EXT                                   0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT                         0x8002
#define GL_CONSTANT_ALPHA_EXT                                   0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT                         0x8004
#define GL_BLEND_COLOR_EXT                                      0x8005

typedef void (APIENTRY * glBlendColorEXTPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

extern GLEW_EXPORT glBlendColorEXTPROC glBlendColorEXT;

#endif /* GL_EXT_blend_color */

/* ------------------------ EXT_blend_func_separate ----------------------- */

#ifdef GL_EXT_blend_func_separate

#define GL_BLEND_DST_RGB_EXT                                    0x80C8
#define GL_BLEND_SRC_RGB_EXT                                    0x80C9
#define GL_BLEND_DST_ALPHA_EXT                                  0x80CA
#define GL_BLEND_SRC_ALPHA_EXT                                  0x80CB

typedef void (APIENTRY * glBlendFuncSeparateEXTPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);

extern GLEW_EXPORT glBlendFuncSeparateEXTPROC glBlendFuncSeparateEXT;

#endif /* GL_EXT_blend_func_separate */

/* --------------------------- EXT_blend_minmax --------------------------- */

#ifdef GL_EXT_blend_minmax

#define GL_FUNC_ADD_EXT                                         0x8006
#define GL_MIN_EXT                                              0x8007
#define GL_MAX_EXT                                              0x8008
#define GL_BLEND_EQUATION_EXT                                   0x8009

typedef void (APIENTRY * glBlendEquationEXTPROC) (GLenum mode);

extern GLEW_EXPORT glBlendEquationEXTPROC glBlendEquationEXT;

#endif /* GL_EXT_blend_minmax */

/* ------------------------- EXT_blend_subtract --------------------------- */

#ifdef GL_EXT_blend_subtract

#define GL_FUNC_SUBTRACT_EXT                                    0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT                            0x800B

#endif /* GL_EXT_blend_subtract */

/* -------------------------- EXT_clip_volume_hint ------------------------ */

#ifdef GL_EXT_clip_volume_hint

#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT                        0x80F0

#endif /* GL_EXT_clip_volume_hint */

/* ----------------------- EXT_compiled_vertex_array ---------------------- */

#ifdef GL_EXT_compiled_vertex_array

#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT                         0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT                         0x81A9

typedef void (APIENTRY * glLockArraysEXTPROC) (GLint first, GLsizei count);
typedef void (APIENTRY * glUnlockArraysEXTPROC) (void);

extern GLEW_EXPORT glLockArraysEXTPROC glLockArraysEXT;
extern GLEW_EXPORT glUnlockArraysEXTPROC glUnlockArraysEXT;

#endif /* GL_EXT_compiled_vertex_array */

/* ---------------------------- EXT_cull_vertex --------------------------- */

#ifdef GL_EXT_cull_vertex

typedef void (APIENTRY * glCullParameterfvEXTPROC) (GLenum pname, GLfloat *params);
typedef void (APIENTRY * glCullParameterdvEXTPROC) (GLenum pname, GLdouble *params);

extern GLEW_EXPORT glCullParameterfvEXTPROC glCullParameterfvEXT;
extern GLEW_EXPORT glCullParameterdvEXTPROC glCullParameterdvEXT;

#define GL_CULL_VERTEX_EXT                                      0x81AA
#define GL_CULL_VERTEX_EYE_POSITION_EXT                         0x81AB
#define GL_CULL_VERTEX_OBJECT_POSITION_EXT                      0x81AC

#endif /* GL_EXT_cull_vertex */

/* ------------------------ EXT_draw_range_elements ----------------------- */

#ifdef GL_EXT_draw_range_elements

typedef void (APIENTRY * glDrawRangeElementsEXTPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

extern GLEW_EXPORT glDrawRangeElementsEXTPROC glDrawRangeElementsEXT;

#define GL_MAX_ELEMENTS_VERTICES_EXT                            0x80E8
#define GL_MAX_ELEMENTS_INDICES_EXT                             0x80E9

#endif /* GL_EXT_draw_range_elements */

/* ----------------------------- EXT_fog_coord ---------------------------- */

#ifdef GL_EXT_fog_coord

#define GL_FOG_COORDINATE_SOURCE_EXT                            0x8450
#define GL_FOG_COORDINATE_EXT                                   0x8451
#define GL_FRAGMENT_DEPTH_EXT                                   0x8452
#define GL_CURRENT_FOG_COORDINATE_EXT                           0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT                        0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT                      0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT                     0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT                             0x8457

typedef void (APIENTRY * glFogCoordfEXTPROC) (GLfloat coord);
typedef void (APIENTRY * glFogCoordfvEXTPROC) (const GLfloat *coord);
typedef void (APIENTRY * glFogCoorddEXTPROC) (GLdouble coord);
typedef void (APIENTRY * glFogCoorddvEXTPROC) (const GLdouble *coord);
typedef void (APIENTRY * glFogCoordPointerEXTPROC) (GLenum type, GLsizei stride, const GLvoid *pointer);

extern GLEW_EXPORT glFogCoordfEXTPROC glFogCoordfEXT;
extern GLEW_EXPORT glFogCoordfvEXTPROC glFogCoordfvEXT;
extern GLEW_EXPORT glFogCoorddEXTPROC glFogCoorddEXT;
extern GLEW_EXPORT glFogCoorddvEXTPROC glFogCoorddvEXT;
extern GLEW_EXPORT glFogCoordPointerEXTPROC glFogCoordPointerEXT;

#endif /* GL_EXT_fog_coord */

/* ------------------------- EXT_multi_draw_arrays ------------------------ */

#ifdef GL_EXT_multi_draw_arrays

typedef void (APIENTRY * glMultiDrawArraysEXTPROC) (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount);
typedef void (APIENTRY * glMultiDrawElementsEXTPROC) (GLenum mode, GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount);

extern GLEW_EXPORT glMultiDrawArraysEXTPROC glMultiDrawArraysEXT;
extern GLEW_EXPORT glMultiDrawElementsEXTPROC glMultiDrawElementsEXT;

#endif /* GL_EXT_multi_draw_arrays */

/* --------------------------- EXT_packed_pixels -------------------------- */

#ifdef GL_EXT_packed_pixels

#define GL_UNSIGNED_BYTE_3_3_2_EXT                              0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT                           0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT                           0x8034
#define GL_UNSIGNED_INT_8_8_8_8_EXT                             0x8035
#define GL_UNSIGNED_INT_10_10_10_2_EXT                          0x8036

#endif /* GL_EXT_packed_pixels */

/* ------------------------- EXT_point_parameters ------------------------- */

#ifdef GL_EXT_point_parameters

#define GL_POINT_SIZE_MIN_EXT                                   0x8126
#define GL_POINT_SIZE_MAX_EXT                                   0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT                        0x8128
#define GL_DISTANCE_ATTENUATION_EXT                             0x8129

typedef void (APIENTRY * glPointParameterfEXTPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * glPointParameterfvEXTPROC) (GLenum pname, const GLfloat *params);

extern GLEW_EXPORT glPointParameterfEXTPROC glPointParameterfEXT;
extern GLEW_EXPORT glPointParameterfvEXTPROC glPointParameterfvEXT;

#endif /* GL_EXT_point_parameters */

/* -------------------------- EXT_secondary_color ------------------------- */

#ifdef GL_EXT_secondary_color

#define GL_COLOR_SUM_EXT                                        0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT                          0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT                       0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT                       0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT                     0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT                    0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT                            0x845E

typedef void (APIENTRY * glSecondaryColor3bEXTPROC) (GLbyte red, GLbyte green, GLbyte blue);
typedef void (APIENTRY * glSecondaryColor3bvEXTPROC) (const GLbyte *v);
typedef void (APIENTRY * glSecondaryColor3dEXTPROC) (GLdouble red, GLdouble green, GLdouble blue);
typedef void (APIENTRY * glSecondaryColor3dvEXTPROC) (const GLdouble *v);
typedef void (APIENTRY * glSecondaryColor3fEXTPROC) (GLfloat red, GLfloat green, GLfloat blue);
typedef void (APIENTRY * glSecondaryColor3fvEXTPROC) (const GLfloat *v);
typedef void (APIENTRY * glSecondaryColor3iEXTPROC) (GLint red, GLint green, GLint blue);
typedef void (APIENTRY * glSecondaryColor3ivEXTPROC) (const GLint *v);
typedef void (APIENTRY * glSecondaryColor3sEXTPROC) (GLshort red, GLshort green, GLshort blue);
typedef void (APIENTRY * glSecondaryColor3svEXTPROC) (const GLshort *v);
typedef void (APIENTRY * glSecondaryColor3ubEXTPROC) (GLubyte red, GLubyte green, GLubyte blue);
typedef void (APIENTRY * glSecondaryColor3ubvEXTPROC) (const GLubyte *v);
typedef void (APIENTRY * glSecondaryColor3uiEXTPROC) (GLuint red, GLuint green, GLuint blue);
typedef void (APIENTRY * glSecondaryColor3uivEXTPROC) (const GLuint *v);
typedef void (APIENTRY * glSecondaryColor3usEXTPROC) (GLushort red, GLushort green, GLushort blue);
typedef void (APIENTRY * glSecondaryColor3usvEXTPROC) (const GLushort *v);
typedef void (APIENTRY * glSecondaryColorPointerEXTPROC) (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);

extern GLEW_EXPORT glSecondaryColor3bEXTPROC glSecondaryColor3bEXT;
extern GLEW_EXPORT glSecondaryColor3bvEXTPROC glSecondaryColor3bvEXT;
extern GLEW_EXPORT glSecondaryColor3dEXTPROC glSecondaryColor3dEXT;
extern GLEW_EXPORT glSecondaryColor3dvEXTPROC glSecondaryColor3dvEXT;
extern GLEW_EXPORT glSecondaryColor3fEXTPROC glSecondaryColor3fEXT;
extern GLEW_EXPORT glSecondaryColor3fvEXTPROC glSecondaryColor3fvEXT;
extern GLEW_EXPORT glSecondaryColor3iEXTPROC glSecondaryColor3iEXT;
extern GLEW_EXPORT glSecondaryColor3ivEXTPROC glSecondaryColor3ivEXT;
extern GLEW_EXPORT glSecondaryColor3sEXTPROC glSecondaryColor3sEXT;
extern GLEW_EXPORT glSecondaryColor3svEXTPROC glSecondaryColor3svEXT;
extern GLEW_EXPORT glSecondaryColor3ubEXTPROC glSecondaryColor3ubEXT;
extern GLEW_EXPORT glSecondaryColor3ubvEXTPROC glSecondaryColor3ubvEXT;
extern GLEW_EXPORT glSecondaryColor3uiEXTPROC glSecondaryColor3uiEXT;
extern GLEW_EXPORT glSecondaryColor3uivEXTPROC glSecondaryColor3uivEXT;
extern GLEW_EXPORT glSecondaryColor3usEXTPROC glSecondaryColor3usEXT;
extern GLEW_EXPORT glSecondaryColor3usvEXTPROC glSecondaryColor3usvEXT;
extern GLEW_EXPORT glSecondaryColorPointerEXTPROC glSecondaryColorPointerEXT;

#endif /* GL_EXT_secondary_color */

/* ---------------------- EXT_separate_specular_color --------------------- */

#ifdef GL_EXT_separate_specular_color

#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT                        0x81F8
#define GL_SINGLE_COLOR_EXT                                     0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT                          0x81FA

#endif /* GL_EXT_separate_specular_color */

/* --------------------------- EXT_shadow_funcs --------------------------- */

/* ------------------------- EXT_stencil_two_side ------------------------- */

#ifdef GL_EXT_stencil_two_side

typedef void (APIENTRY * glActiveStencilFaceEXTPROC) (GLenum face);

extern GLEW_EXPORT glActiveStencilFaceEXTPROC glActiveStencilFaceEXT;

#define GL_STENCIL_TEST_TWO_SIDE_EXT                            0x8910
#define GL_ACTIVE_STENCIL_FACE_EXT                              0x8911

#endif /* GL_EXT_stencil_two_side */

/* --------------------------- EXT_stencil_wrap --------------------------- */

#ifdef GL_EXT_stencil_wrap

#define GL_INCR_WRAP_EXT                                        0x8507
#define GL_DECR_WRAP_EXT                                        0x8508

#endif /* GL_EXT_stencil_wrap */

/* --------------------- EXT_texture_compression_s3tc --------------------- */

#ifdef GL_EXT_texture_compression_s3tc

#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                         0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                        0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                        0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                        0x83F3

#endif /* GL_EXT_texture_compression_s3tc */

/* ------------------------ EXT_texture_env_combine ----------------------- */

#ifdef GL_EXT_texture_env_combine

#define GL_COMBINE_EXT                                          0x8570
#define GL_COMBINE_RGB_EXT                                      0x8571
#define GL_COMBINE_ALPHA_EXT                                    0x8572
#define GL_RGB_SCALE_EXT                                        0x8573
#define GL_ADD_SIGNED_EXT                                       0x8574
#define GL_INTERPOLATE_EXT                                      0x8575
#define GL_CONSTANT_EXT                                         0x8576
#define GL_PRIMARY_COLOR_EXT                                    0x8577
#define GL_PREVIOUS_EXT                                         0x8578
#define GL_SOURCE0_RGB_EXT                                      0x8580
#define GL_SOURCE1_RGB_EXT                                      0x8581
#define GL_SOURCE2_RGB_EXT                                      0x8582
#define GL_SOURCE0_ALPHA_EXT                                    0x8588
#define GL_SOURCE1_ALPHA_EXT                                    0x8589
#define GL_SOURCE2_ALPHA_EXT                                    0x858A
#define GL_OPERAND0_RGB_EXT                                     0x8590
#define GL_OPERAND1_RGB_EXT                                     0x8591
#define GL_OPERAND2_RGB_EXT                                     0x8592
#define GL_OPERAND0_ALPHA_EXT                                   0x8598
#define GL_OPERAND1_ALPHA_EXT                                   0x8599
#define GL_OPERAND2_ALPHA_EXT                                   0x859A

#endif /* GL_EXT_texture_env_combine */

/* -------------------- EXT_texture_filter_anisotropic -------------------- */

#ifdef GL_EXT_texture_filter_anisotropic

#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF

#endif /* GL_EXT_texture_filter_anisotropic */

/* ------------------------- EXT_texture_lod_bias ------------------------- */

#ifdef GL_EXT_texture_lod_bias

#define GL_TEXTURE_FILTER_CONTROL_EXT                           0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                                 0x8501
#define GL_MAX_TEXTURE_LOD_BIAS_EXT                             0x84FD

#endif /* GL_EXT_texture_lod_bias */

/* ------------------------- EXT_texture_rectangle ------------------------ */

#ifdef GL_EXT_texture_rectangle

#define GL_TEXTURE_RECTANGLE_EXT                                0x85B3
#define GL_TEXTURE_BINDING_RECTANGLE_EXT                        0x85B4
#define GL_PROXY_TEXTURE_RECTANGLE_EXT                          0x85B5
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_EXT                       0x85B6

#endif /* GL_EXT_texture_rectangle */

/* --------------------------- EXT_vertex_shader -------------------------- */

#ifdef GL_EXT_vertex_shader

#define GL_VERTEX_SHADER_EXT                                    0x8780
#define GL_VERTEX_SHADER_BINDING_EXT                            0x8781
#define GL_OP_INDEX_EXT                                         0x8782
#define GL_OP_NEGATE_EXT                                        0x8783
#define GL_OP_DOT3_EXT                                          0x8784
#define GL_OP_DOT4_EXT                                          0x8785
#define GL_OP_MUL_EXT                                           0x8786
#define GL_OP_ADD_EXT                                           0x8787
#define GL_OP_MADD_EXT                                          0x8788
#define GL_OP_FRAC_EXT                                          0x8789
#define GL_OP_MAX_EXT                                           0x878A
#define GL_OP_MIN_EXT                                           0x878B
#define GL_OP_SET_GE_EXT                                        0x878C
#define GL_OP_SET_LT_EXT                                        0x878D
#define GL_OP_CLAMP_EXT                                         0x878E
#define GL_OP_FLOOR_EXT                                         0x878F
#define GL_OP_ROUND_EXT                                         0x8790
#define GL_OP_EXP_BASE_2_EXT                                    0x8791
#define GL_OP_LOG_BASE_2_EXT                                    0x8792
#define GL_OP_POWER_EXT                                         0x8793
#define GL_OP_RECIP_EXT                                         0x8794
#define GL_OP_RECIP_SQRT_EXT                                    0x8795
#define GL_OP_SUB_EXT                                           0x8796
#define GL_OP_CROSS_PRODUCT_EXT                                 0x8797
#define GL_OP_MULTIPLY_MATRIX_EXT                               0x8798
#define GL_OP_MOV_EXT                                           0x8799
#define GL_OUTPUT_VERTEX_EXT                                    0x879A
#define GL_OUTPUT_COLOR0_EXT                                    0x879B
#define GL_OUTPUT_COLOR1_EXT                                    0x879C
#define GL_OUTPUT_TEXTURE_COORD0_EXT                            0x879D
#define GL_OUTPUT_TEXTURE_COORD1_EXT                            0x879E
#define GL_OUTPUT_TEXTURE_COORD2_EXT                            0x879F
#define GL_OUTPUT_TEXTURE_COORD3_EXT                            0x87A0
#define GL_OUTPUT_TEXTURE_COORD4_EXT                            0x87A1
#define GL_OUTPUT_TEXTURE_COORD5_EXT                            0x87A2
#define GL_OUTPUT_TEXTURE_COORD6_EXT                            0x87A3
#define GL_OUTPUT_TEXTURE_COORD7_EXT                            0x87A4
#define GL_OUTPUT_TEXTURE_COORD8_EXT                            0x87A5
#define GL_OUTPUT_TEXTURE_COORD9_EXT                            0x87A6
#define GL_OUTPUT_TEXTURE_COORD10_EXT                           0x87A7
#define GL_OUTPUT_TEXTURE_COORD11_EXT                           0x87A8
#define GL_OUTPUT_TEXTURE_COORD12_EXT                           0x87A9
#define GL_OUTPUT_TEXTURE_COORD13_EXT                           0x87AA
#define GL_OUTPUT_TEXTURE_COORD14_EXT                           0x87AB
#define GL_OUTPUT_TEXTURE_COORD15_EXT                           0x87AC
#define GL_OUTPUT_TEXTURE_COORD16_EXT                           0x87AD
#define GL_OUTPUT_TEXTURE_COORD17_EXT                           0x87AE
#define GL_OUTPUT_TEXTURE_COORD18_EXT                           0x87AF
#define GL_OUTPUT_TEXTURE_COORD19_EXT                           0x87B0
#define GL_OUTPUT_TEXTURE_COORD20_EXT                           0x87B1
#define GL_OUTPUT_TEXTURE_COORD21_EXT                           0x87B2
#define GL_OUTPUT_TEXTURE_COORD22_EXT                           0x87B3
#define GL_OUTPUT_TEXTURE_COORD23_EXT                           0x87B4
#define GL_OUTPUT_TEXTURE_COORD24_EXT                           0x87B5
#define GL_OUTPUT_TEXTURE_COORD25_EXT                           0x87B6
#define GL_OUTPUT_TEXTURE_COORD26_EXT                           0x87B7
#define GL_OUTPUT_TEXTURE_COORD27_EXT                           0x87B8
#define GL_OUTPUT_TEXTURE_COORD28_EXT                           0x87B9
#define GL_OUTPUT_TEXTURE_COORD29_EXT                           0x87BA
#define GL_OUTPUT_TEXTURE_COORD30_EXT                           0x87BB
#define GL_OUTPUT_TEXTURE_COORD31_EXT                           0x87BC
#define GL_OUTPUT_FOG_EXT                                       0x87BD
#define GL_SCALAR_EXT                                           0x87BE
#define GL_VECTOR_EXT                                           0x87BF
#define GL_MATRIX_EXT                                           0x87C0
#define GL_VARIANT_EXT                                          0x87C1
#define GL_INVARIANT_EXT                                        0x87C2
#define GL_LOCAL_CONSTANT_EXT                                   0x87C3
#define GL_LOCAL_EXT                                            0x87C4
#define GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT                   0x87C5
#define GL_MAX_VERTEX_SHADER_VARIANTS_EXT                       0x87C6
#define GL_MAX_VERTEX_SHADER_INVARIANTS_EXT                     0x87C7
#define GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT                0x87C8
#define GL_MAX_VERTEX_SHADER_LOCALS_EXT                         0x87C9
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT         0x87CA
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT             0x87CB
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT           0x87CC
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT      0x87CD
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT               0x87CE
#define GL_VERTEX_SHADER_INSTRUCTIONS_EXT                       0x87CF
#define GL_VERTEX_SHADER_VARIANTS_EXT                           0x87D0
#define GL_VERTEX_SHADER_INVARIANTS_EXT                         0x87D1
#define GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT                    0x87D2
#define GL_VERTEX_SHADER_LOCALS_EXT                             0x87D3
#define GL_VERTEX_SHADER_OPTIMIZED_EXT                          0x87D4
#define GL_X_EXT                                                0x87D5
#define GL_Y_EXT                                                0x87D6
#define GL_Z_EXT                                                0x87D7
#define GL_W_EXT                                                0x87D8
#define GL_NEGATIVE_X_EXT                                       0x87D9
#define GL_NEGATIVE_Y_EXT                                       0x87DA
#define GL_NEGATIVE_Z_EXT                                       0x87DB
#define GL_NEGATIVE_W_EXT                                       0x87DC
#define GL_ZERO_EXT                                             0x87DD
#define GL_ONE_EXT                                              0x87DE
#define GL_NEGATIVE_ONE_EXT                                     0x87DF
#define GL_NORMALIZED_RANGE_EXT                                 0x87E0
#define GL_FULL_RANGE_EXT                                       0x87E1
#define GL_CURRENT_VERTEX_EXT                                   0x87E2
#define GL_MVP_MATRIX_EXT                                       0x87E3
#define GL_VARIANT_VALUE_EXT                                    0x87E4
#define GL_VARIANT_DATATYPE_EXT                                 0x87E5
#define GL_VARIANT_ARRAY_STRIDE_EXT                             0x87E6
#define GL_VARIANT_ARRAY_TYPE_EXT                               0x87E7
#define GL_VARIANT_ARRAY_EXT                                    0x87E8
#define GL_VARIANT_ARRAY_POINTER_EXT                            0x87E9
#define GL_INVARIANT_VALUE_EXT                                  0x87EA
#define GL_INVARIANT_DATATYPE_EXT                               0x87EB
#define GL_LOCAL_CONSTANT_VALUE_EXT                             0x87EC
#define GL_LOCAL_CONSTANT_DATATYPE_EXT                          0x87ED

typedef void (APIENTRY * glBeginVertexShaderEXTPROC) ();
typedef void (APIENTRY * glEndVertexShaderEXTPROC) ();
typedef void (APIENTRY * glBindVertexShaderEXTPROC) (GLuint id);
typedef GLuint (APIENTRY * glGenVertexShadersEXTPROC) (GLuint range);
typedef void (APIENTRY * glDeleteVertexShaderEXTPROC) (GLuint id);
typedef void (APIENTRY * glShaderOp1EXTPROC) (GLenum op, GLuint res, GLuint arg1);
typedef void (APIENTRY * glShaderOp2EXTPROC) (GLenum op, GLuint res, GLuint arg1, GLuint arg2);
typedef void (APIENTRY * glShaderOp3EXTPROC) (GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3);
typedef void (APIENTRY * glSwizzleEXTPROC) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (APIENTRY * glWriteMaskEXTPROC) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (APIENTRY * glInsertComponentEXTPROC) (GLuint res, GLuint src, GLuint num);
typedef void (APIENTRY * glExtractComponentEXTPROC) (GLuint res, GLuint src, GLuint num);
typedef GLuint (APIENTRY * glGenSymbolsEXTPROC) (GLenum dataType, GLenum storageType, GLenum range, GLuint components);
typedef void (APIENTRY * glSetInvariantEXTPROC) (GLuint id, GLenum type, GLvoid *addr);
typedef void (APIENTRY * glSetLocalConstantEXTPROC) (GLuint id, GLenum type, GLvoid *addr);
typedef void (APIENTRY * glVariantbvEXTPROC) (GLuint id, GLbyte *addr);
typedef void (APIENTRY * glVariantsvEXTPROC) (GLuint id, GLshort *addr);
typedef void (APIENTRY * glVariantivEXTPROC) (GLuint id, GLint *addr);
typedef void (APIENTRY * glVariantfvEXTPROC) (GLuint id, GLfloat *addr);
typedef void (APIENTRY * glVariantdvEXTPROC) (GLuint id, GLdouble *addr);
typedef void (APIENTRY * glVariantubvEXTPROC) (GLuint id, GLubyte *addr);
typedef void (APIENTRY * glVariantusvEXTPROC) (GLuint id, GLushort *addr);
typedef void (APIENTRY * glVariantuivEXTPROC) (GLuint id, GLuint *addr);
typedef void (APIENTRY * glVariantPointerEXTPROC) (GLuint id, GLenum type, GLuint stride, GLvoid *addr);
typedef void (APIENTRY * glEnableVariantClientStateEXTPROC) (GLuint id);
typedef void (APIENTRY * glDisableVariantClientStateEXTPROC) (GLuint id);
typedef GLuint (APIENTRY * glBindLightParameterEXTPROC) (GLenum light, GLenum value);
typedef GLuint (APIENTRY * glBindMaterialParameterEXTPROC) (GLenum face, GLenum value);
typedef GLuint (APIENTRY * glBindTexGenParameterEXTPROC) (GLenum unit, GLenum coord, GLenum value);
typedef GLuint (APIENTRY * glBindTextureUnitParameterEXTPROC) (GLenum unit, GLenum value);
typedef GLuint (APIENTRY * glBindParameterEXTPROC) (GLenum value);
typedef GLboolean (APIENTRY * glIsVariantEnabledEXTPROC) (GLuint id, GLenum cap);
typedef void (APIENTRY * glGetVariantBooleanvEXTPROC) (GLuint id, GLenum value, GLboolean *data);
typedef void (APIENTRY * glGetVariantIntegervEXTPROC) (GLuint id, GLenum value, GLint *data);
typedef void (APIENTRY * glGetVariantFloatvEXTPROC) (GLuint id, GLenum value, GLfloat *data);
typedef void (APIENTRY * glGetVariantPointervEXTPROC) (GLuint id, GLenum value, GLvoid **data);
typedef void (APIENTRY * glGetInvariantBooleanvEXTPROC) (GLuint id, GLenum value, GLboolean *data);
typedef void (APIENTRY * glGetInvariantIntegervEXTPROC) (GLuint id, GLenum value, GLint *data);
typedef void (APIENTRY * glGetInvariantFloatvEXTPROC) (GLuint id, GLenum value, GLfloat *data);
typedef void (APIENTRY * glGetLocalConstantBooleanvEXTPROC) (GLuint id, GLenum value, GLboolean *data);
typedef void (APIENTRY * glGetLocalConstantIntegervEXTPROC) (GLuint id, GLenum value, GLint *data);
typedef void (APIENTRY * glGetLocalConstantFloatvEXTPROC) (GLuint id, GLenum value, GLfloat *data);

extern GLEW_EXPORT glBeginVertexShaderEXTPROC glBeginVertexShaderEXT;
extern GLEW_EXPORT glEndVertexShaderEXTPROC glEndVertexShaderEXT;
extern GLEW_EXPORT glBindVertexShaderEXTPROC glBindVertexShaderEXT;
extern GLEW_EXPORT glGenVertexShadersEXTPROC glGenVertexShadersEXT;
extern GLEW_EXPORT glDeleteVertexShaderEXTPROC glDeleteVertexShaderEXT;
extern GLEW_EXPORT glShaderOp1EXTPROC glShaderOp1EXT;
extern GLEW_EXPORT glShaderOp2EXTPROC glShaderOp2EXT;
extern GLEW_EXPORT glShaderOp3EXTPROC glShaderOp3EXT;
extern GLEW_EXPORT glSwizzleEXTPROC glSwizzleEXT;
extern GLEW_EXPORT glWriteMaskEXTPROC glWriteMaskEXT;
extern GLEW_EXPORT glInsertComponentEXTPROC glInsertComponentEXT;
extern GLEW_EXPORT glExtractComponentEXTPROC glExtractComponentEXT;
extern GLEW_EXPORT glGenSymbolsEXTPROC glGenSymbolsEXT;
extern GLEW_EXPORT glSetInvariantEXTPROC glSetInvariantEXT;
extern GLEW_EXPORT glSetLocalConstantEXTPROC glSetLocalConstantEXT;
extern GLEW_EXPORT glVariantbvEXTPROC glVariantbvEXT;
extern GLEW_EXPORT glVariantsvEXTPROC glVariantsvEXT;
extern GLEW_EXPORT glVariantivEXTPROC glVariantivEXT;
extern GLEW_EXPORT glVariantfvEXTPROC glVariantfvEXT;
extern GLEW_EXPORT glVariantdvEXTPROC glVariantdvEXT;
extern GLEW_EXPORT glVariantubvEXTPROC glVariantubvEXT;
extern GLEW_EXPORT glVariantusvEXTPROC glVariantusvEXT;
extern GLEW_EXPORT glVariantuivEXTPROC glVariantuivEXT;
extern GLEW_EXPORT glVariantPointerEXTPROC glVariantPointerEXT;
extern GLEW_EXPORT glEnableVariantClientStateEXTPROC glEnableVariantClientStateEXT;
extern GLEW_EXPORT glDisableVariantClientStateEXTPROC glDisableVariantClientStateEXT;
extern GLEW_EXPORT glBindLightParameterEXTPROC glBindLightParameterEXT;
extern GLEW_EXPORT glBindMaterialParameterEXTPROC glBindMaterialParameterEXT;
extern GLEW_EXPORT glBindTexGenParameterEXTPROC glBindTexGenParameterEXT;
extern GLEW_EXPORT glBindTextureUnitParameterEXTPROC glBindTextureUnitParameterEXT;
extern GLEW_EXPORT glBindParameterEXTPROC glBindParameterEXT;
extern GLEW_EXPORT glIsVariantEnabledEXTPROC glIsVariantEnabledEXT;
extern GLEW_EXPORT glGetVariantBooleanvEXTPROC glGetVariantBooleanvEXT;
extern GLEW_EXPORT glGetVariantIntegervEXTPROC glGetVariantIntegervEXT;
extern GLEW_EXPORT glGetVariantFloatvEXTPROC glGetVariantFloatvEXT;
extern GLEW_EXPORT glGetVariantPointervEXTPROC glGetVariantPointervEXT;
extern GLEW_EXPORT glGetInvariantBooleanvEXTPROC glGetInvariantBooleanvEXT;
extern GLEW_EXPORT glGetInvariantIntegervEXTPROC glGetInvariantIntegervEXT;
extern GLEW_EXPORT glGetInvariantFloatvEXTPROC glGetInvariantFloatvEXT;
extern GLEW_EXPORT glGetLocalConstantBooleanvEXTPROC glGetLocalConstantBooleanvEXT;
extern GLEW_EXPORT glGetLocalConstantIntegervEXTPROC glGetLocalConstantIntegervEXT;
extern GLEW_EXPORT glGetLocalConstantFloatvEXTPROC glGetLocalConstantFloatvEXT;

#endif /* GL_EXT_vertex_shader */

/* ------------------------- EXT_vertex_weighting ------------------------- */

#ifdef GL_EXT_vertex_weighting

#define GL_MODELVIEW0_STACK_DEPTH_EXT                           0x0BA3  /* alias to GL_MODELVIEW_STACK_DEPTH */
#define GL_MODELVIEW1_STACK_DEPTH_EXT                           0x8502
#define GL_MODELVIEW0_MATRIX_EXT                                0x0BA6  /* alias to GL_MODELVIEW_MATRIX */
#define GL_MODELVIEW1_MATRIX_EXT                                0x8506
#define GL_VERTEX_WEIGHTING_EXT                                 0x8509
#define GL_MODELVIEW0_EXT                                       0x1700  /* alias to GL_MODELVIEW */
#define GL_MODELVIEW1_EXT                                       0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT                            0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT                              0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT                         0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT                         0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT                       0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT                      0x8510

typedef void (APIENTRY * glVertexWeightfEXTPROC) (GLfloat weight);
typedef void (APIENTRY * glVertexWeightfvEXTPROC) (const GLfloat *weight);
typedef void (APIENTRY * glVertexWeightPointerEXTPROC) (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern GLEW_EXPORT glVertexWeightfEXTPROC glVertexWeightfEXT;
extern GLEW_EXPORT glVertexWeightfvEXTPROC glVertexWeightfvEXT;
extern GLEW_EXPORT glVertexWeightPointerEXTPROC glVertexWeightPointerEXT;

#endif /* GL_EXT_vertex_weighting */

/* ------------------------- SGIS_generate_mipmap ------------------------- */

#ifdef GL_SGIS_generate_mipmap

#define GL_GENERATE_MIPMAP_SGIS                                 0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS                            0x8192

#endif /* GL_SGIS_generate_mipmap */

/* --------------------------- SGIS_texture_lod --------------------------- */

#ifdef GL_SGIS_texture_lod

#define GL_TEXTURE_MIN_LOD_SGIS                                 0x813A
#define GL_TEXTURE_MAX_LOD_SGIS                                 0x813B
#define GL_TEXTURE_BASE_LEVEL_SGIS                              0x813C
#define GL_TEXTURE_MAX_LEVEL_SGIS                               0x813D

#endif /* GL_SGIS_texture_lod */

/* --------------------------- SGIX_depth_texture ------------------------- */

#ifdef GL_SGIX_depth_texture

#define GL_DEPTH_COMPONENT16_SGIX                               0x81A5
#define GL_DEPTH_COMPONENT24_SGIX                               0x81A6
#define GL_DEPTH_COMPONENT32_SGIX                               0x81A7

#endif /* GL_SGIX_depth_texture */

/* ------------------------------ SGIX_shadow ----------------------------- */

#ifdef GL_SGIX_shadow

#define GL_TEXTURE_COMPARE_SGIX                                 0x819A
#define GL_TEXTURE_COMPARE_OPERATOR_SGIX                        0x819B
#define GL_TEXTURE_LEQUAL_R_SGIX                                0x819C
#define GL_TEXTURE_GEQUAL_R_SGIX                                0x819D

#endif /* GL_SGIX_shadow */

/* --------------------------- HP_occlusion_test -------------------------- */

#ifdef GL_HP_occlusion_test

#define GL_OCCLUSION_TEST_HP                                    0x8165
#define GL_OCCLUSION_TEST_RESULT_HP                             0x8166

#endif /* GL_HP_occlusion_test */

/* -------------------------------- S3_s3tc ------------------------------- */

#ifdef GL_S3_s3tc

#define GL_RGB_S3TC                                             0x83A0
#define GL_RGB4_S3TC                                            0x83A1
#define GL_RGBA_S3TC                                            0x83A2
#define GL_RGBA4_S3TC                                           0x83A3

#endif /* S3_s3tc */

/* ------------------------------ WIN_swap_hint --------------------------- */

#ifdef GL_WIN_swap_hint

typedef void (APIENTRY * glAddSwapHintRectWinPROC) (GLint x, GLint y, GLsizei width, GLsizei height);

extern GLEW_EXPORT glAddSwapHintRectWinPROC glAddSwapHintRectWin;

#endif /* GL_WIN_swap_hint */

/* ---------------------------- ATI_draw_buffers -------------------------- */

#ifdef GL_ATI_draw_buffers

#define GL_MAX_DRAW_BUFFERS_ATI                                 0x8824
#define GL_DRAW_BUFFER0_ATI                                     0x8825
#define GL_DRAW_BUFFER1_ATI                                     0x8826
#define GL_DRAW_BUFFER2_ATI                                     0x8827
#define GL_DRAW_BUFFER3_ATI                                     0x8828
#define GL_DRAW_BUFFER4_ATI                                     0x8829
#define GL_DRAW_BUFFER5_ATI                                     0x882A
#define GL_DRAW_BUFFER6_ATI                                     0x882B
#define GL_DRAW_BUFFER7_ATI                                     0x882C
#define GL_DRAW_BUFFER8_ATI                                     0x882D
#define GL_DRAW_BUFFER9_ATI                                     0x882E
#define GL_DRAW_BUFFER10_ATI                                    0x882F
#define GL_DRAW_BUFFER11_ATI                                    0x8830
#define GL_DRAW_BUFFER12_ATI                                    0x8831
#define GL_DRAW_BUFFER13_ATI                                    0x8832
#define GL_DRAW_BUFFER14_ATI                                    0x8833
#define GL_DRAW_BUFFER15_ATI                                    0x8834

typedef void (APIENTRY * glDrawBuffersPROC) (GLsizei n, const GLenum *bufs);

extern GLEW_EXPORT glDrawBuffersPROC glDrawBuffers;

#endif /* GL_ATI_draw_buffers */

/* --------------------------- ATI_element_array -------------------------- */

#ifdef GL_ATI_element_array

#define GL_ELEMENT_ARRAY_ATI                                    0x8768
#define GL_ELEMENT_ARRAY_TYPE_ATI                               0x8769
#define GL_ELEMENT_ARRAY_POINTER_ATI                            0x876A

typedef void (APIENTRY * glElementPointerATIPROC) (GLenum type, const GLvoid *pointer);
typedef void (APIENTRY * glDrawElementArrayATIPROC) (GLenum mode, GLsizei count);
typedef void (APIENTRY * glDrawRangeElementArrayATIPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count);

extern GLEW_EXPORT glElementPointerATIPROC glElementPointerATI;
extern GLEW_EXPORT glDrawElementArrayATIPROC glDrawElementArrayATI;
extern GLEW_EXPORT glDrawRangeElementArrayATIPROC glDrawRangeElementArrayATI;

#endif /* GL_ATI_element_array */

/* -------------------------- ATI_envmap_bumpmap -------------------------- */

#ifdef GL_ATI_envmap_bumpmap

#define GL_BUMP_ROT_MATRIX_ATI                                  0x8775
#define GL_BUMP_ROT_MATRIX_SIZE_ATI                             0x8776
#define GL_BUMP_NUM_TEX_UNITS_ATI                               0x8777
#define GL_BUMP_TEX_UNITS_ATI                                   0x8778
#define GL_DUDV_ATI                                             0x8779
#define GL_DU8DV8_ATI                                           0x877A
#define GL_BUMP_ENVMAP_ATI                                      0x877B
#define GL_BUMP_TARGET_ATI                                      0x877C

typedef void (APIENTRY * glTexBumpParameterivATIPROC) (GLenum pname, GLint *param);
typedef void (APIENTRY * glTexBumpParameterfvATIPROC) (GLenum pname, GLfloat *param);
typedef void (APIENTRY * glGetTexBumpParameterivATIPROC) (GLenum pname, GLint *param);
typedef void (APIENTRY * glGetTexBumpParameterfvATIPROC) (GLenum pname, GLfloat *param);

extern GLEW_EXPORT glTexBumpParameterivATIPROC glTexBumpParameterivATI;
extern GLEW_EXPORT glTexBumpParameterfvATIPROC glTexBumpParameterfvATI;
extern GLEW_EXPORT glGetTexBumpParameterivATIPROC glGetTexBumpParameterivATI;
extern GLEW_EXPORT glGetTexBumpParameterfvATIPROC glGetTexBumpParameterfvATI;

#endif /* GL_ATI_envmap_bumpmap */

/* ------------------------- ATI_fragment_shader ------------------------- */

#ifdef GL_ATI_fragment_shader

#define GL_FRAGMENT_SHADER_ATI                                  0x8920
#define GL_REG_0_ATI                                            0x8921
#define GL_REG_1_ATI                                            0x8922
#define GL_REG_2_ATI                                            0x8923
#define GL_REG_3_ATI                                            0x8924
#define GL_REG_4_ATI                                            0x8925
#define GL_REG_5_ATI                                            0x8926
#define GL_REG_6_ATI                                            0x8927
#define GL_REG_7_ATI                                            0x8928
#define GL_REG_8_ATI                                            0x8929
#define GL_REG_9_ATI                                            0x892A
#define GL_REG_10_ATI                                           0x892B
#define GL_REG_11_ATI                                           0x892C
#define GL_REG_12_ATI                                           0x892D
#define GL_REG_13_ATI                                           0x892E
#define GL_REG_14_ATI                                           0x892F
#define GL_REG_15_ATI                                           0x8930
#define GL_REG_16_ATI                                           0x8931
#define GL_REG_17_ATI                                           0x8932
#define GL_REG_18_ATI                                           0x8933
#define GL_REG_19_ATI                                           0x8934
#define GL_REG_20_ATI                                           0x8935
#define GL_REG_21_ATI                                           0x8936
#define GL_REG_22_ATI                                           0x8937
#define GL_REG_23_ATI                                           0x8938
#define GL_REG_24_ATI                                           0x8939
#define GL_REG_25_ATI                                           0x893A
#define GL_REG_26_ATI                                           0x893B
#define GL_REG_27_ATI                                           0x893C
#define GL_REG_28_ATI                                           0x893D
#define GL_REG_29_ATI                                           0x893E
#define GL_REG_30_ATI                                           0x893F
#define GL_REG_31_ATI                                           0x8940
#define GL_CON_0_ATI                                            0x8941
#define GL_CON_1_ATI                                            0x8942
#define GL_CON_2_ATI                                            0x8943
#define GL_CON_3_ATI                                            0x8944
#define GL_CON_4_ATI                                            0x8945
#define GL_CON_5_ATI                                            0x8946
#define GL_CON_6_ATI                                            0x8947
#define GL_CON_7_ATI                                            0x8948
#define GL_CON_8_ATI                                            0x8949
#define GL_CON_9_ATI                                            0x894A
#define GL_CON_10_ATI                                           0x894B
#define GL_CON_11_ATI                                           0x894C
#define GL_CON_12_ATI                                           0x894D
#define GL_CON_13_ATI                                           0x894E
#define GL_CON_14_ATI                                           0x894F
#define GL_CON_15_ATI                                           0x8950
#define GL_CON_16_ATI                                           0x8951
#define GL_CON_17_ATI                                           0x8952
#define GL_CON_18_ATI                                           0x8953
#define GL_CON_19_ATI                                           0x8954
#define GL_CON_20_ATI                                           0x8955
#define GL_CON_21_ATI                                           0x8956
#define GL_CON_22_ATI                                           0x8957
#define GL_CON_23_ATI                                           0x8958
#define GL_CON_24_ATI                                           0x8959
#define GL_CON_25_ATI                                           0x895A
#define GL_CON_26_ATI                                           0x895B
#define GL_CON_27_ATI                                           0x895C
#define GL_CON_28_ATI                                           0x895D
#define GL_CON_29_ATI                                           0x895E
#define GL_CON_30_ATI                                           0x895F
#define GL_CON_31_ATI                                           0x8960
#define GL_MOV_ATI                                              0x8961
#define GL_ADD_ATI                                              0x8963
#define GL_MUL_ATI                                              0x8964
#define GL_SUB_ATI                                              0x8965
#define GL_DOT3_ATI                                             0x8966
#define GL_DOT4_ATI                                             0x8967
#define GL_MAD_ATI                                              0x8968
#define GL_LERP_ATI                                             0x8969
#define GL_CND_ATI                                              0x896A
#define GL_CND0_ATI                                             0x896B
#define GL_DOT2_ADD_ATI                                         0x896C
#define GL_SECONDARY_INTERPOLATOR_ATI                           0x896D
#define GL_NUM_FRAGMENT_REGISTERS_ATI                           0x896E
#define GL_NUM_FRAGMENT_CONSTANTS_ATI                           0x896F
#define GL_NUM_PASSES_ATI                                       0x8970
#define GL_NUM_INSTRUCTIONS_PER_PASS_ATI                        0x8971
#define GL_NUM_INSTRUCTIONS_TOTAL_ATI                           0x8972
#define GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI                0x8973
#define GL_NUM_LOOPBACK_COMPONENTS_ATI                          0x8974
#define GL_COLOR_ALPHA_PAIRING_ATI                              0x8975
#define GL_SWIZZLE_STR_ATI                                      0x8976
#define GL_SWIZZLE_STQ_ATI                                      0x8977
#define GL_SWIZZLE_STR_DR_ATI                                   0x8978
#define GL_SWIZZLE_STQ_DQ_ATI                                   0x8979
#define GL_SWIZZLE_STRQ_ATI                                     0x897A
#define GL_SWIZZLE_STRQ_DQ_ATI                                  0x897B
#define GL_RED_BIT_ATI                                          0x00000001
#define GL_GREEN_BIT_ATI                                        0x00000002
#define GL_BLUE_BIT_ATI                                         0x00000004
#define GL_2X_BIT_ATI                                           0x00000001
#define GL_4X_BIT_ATI                                           0x00000002
#define GL_8X_BIT_ATI                                           0x00000004
#define GL_HALF_BIT_ATI                                         0x00000008
#define GL_QUARTER_BIT_ATI                                      0x00000010
#define GL_EIGHTH_BIT_ATI                                       0x00000020
#define GL_SATURATE_BIT_ATI                                     0x00000040
#define GL_COMP_BIT_ATI                                         0x00000002
#define GL_NEGATE_BIT_ATI                                       0x00000004
#define GL_BIAS_BIT_ATI                                         0x00000008

typedef GLuint (APIENTRY * glGenFragmentShadersATIPROC) (GLuint range);
typedef void (APIENTRY * glBindFragmentShaderATIPROC) (GLuint id);
typedef void (APIENTRY * glDeleteFragmentShaderATIPROC) (GLuint id);
typedef void (APIENTRY * glBeginFragmentShaderATIPROC) (GLvoid);
typedef void (APIENTRY * glEndFragmentShaderATIPROC) (GLvoid);
typedef void (APIENTRY * glPassTexCoordATIPROC) (GLuint dst, GLuint coord, GLenum swizzle);
typedef void (APIENTRY * glSampleMapATIPROC) (GLuint dst, GLuint interp, GLenum swizzle);
typedef void (APIENTRY * glColorFragmentOp1ATIPROC) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (APIENTRY * glColorFragmentOp2ATIPROC) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (APIENTRY * glColorFragmentOp3ATIPROC) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (APIENTRY * glAlphaFragmentOp1ATIPROC) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (APIENTRY * glAlphaFragmentOp2ATIPROC) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (APIENTRY * glAlphaFragmentOp3ATIPROC) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (APIENTRY * glSetFragmentShaderConstantATIPROC) (GLuint dst, const GLfloat *value);

extern GLEW_EXPORT glGenFragmentShadersATIPROC glGenFragmentShadersATI;
extern GLEW_EXPORT glBindFragmentShaderATIPROC glBindFragmentShaderATI;
extern GLEW_EXPORT glDeleteFragmentShaderATIPROC glDeleteFragmentShaderATI;
extern GLEW_EXPORT glBeginFragmentShaderATIPROC glBeginFragmentShaderATI;
extern GLEW_EXPORT glEndFragmentShaderATIPROC glEndFragmentShaderATI;
extern GLEW_EXPORT glPassTexCoordATIPROC glPassTexCoordATI;
extern GLEW_EXPORT glSampleMapATIPROC glSampleMapATI;
extern GLEW_EXPORT glColorFragmentOp1ATIPROC glColorFragmentOp1ATI;
extern GLEW_EXPORT glColorFragmentOp2ATIPROC glColorFragmentOp2ATI;
extern GLEW_EXPORT glColorFragmentOp3ATIPROC glColorFragmentOp3ATI;
extern GLEW_EXPORT glAlphaFragmentOp1ATIPROC glAlphaFragmentOp1ATI;
extern GLEW_EXPORT glAlphaFragmentOp2ATIPROC glAlphaFragmentOp2ATI;
extern GLEW_EXPORT glAlphaFragmentOp3ATIPROC glAlphaFragmentOp3ATI;
extern GLEW_EXPORT glSetFragmentShaderConstantATIPROC glSetFragmentShaderConstantATI;

#endif /* GL_ATI_fragment_shader */

/* ------------------------- ATI_map_object_buffer ------------------------ */

#ifdef GL_ATI_map_object_buffer

typedef void *(APIENTRY * glMapObjectBufferATIPROC)(GLuint buffer);
typedef void (APIENTRY * glUnmapObjectBufferATIPROC)(GLuint buffer);

extern GLEW_EXPORT glMapObjectBufferATIPROC glMapObjectBufferATI;
extern GLEW_EXPORT glUnmapObjectBufferATIPROC glUnmapObjectBufferATI;

#endif /* GL_ATI_map_object_buffer */

/* -------------------------- ATI_mapped_texture -------------------------- */

#ifdef GL_ATI_mapped_texture

#define GL_MAPPED_TEXTURE_PIXEL_STRIDE_ATI                      0x8820
#define GL_MAPPED_TEXTURE_ROW_STRIDE_ATI                        0x8821
#define GL_MAPPED_TEXTURE_LAYER_STRIDE_ATI                      0x8822

typedef void (APIENTRY * glMapTexture3DPROC) (GLenum level, GLvoid **buffer);
typedef void (APIENTRY * glUnmapTexture3DPROC) (void);

extern GLEW_EXPORT glMapTexture3DPROC glMapTexture3D;
extern GLEW_EXPORT glUnmapTexture3DPROC glUnmapTexture3D;

#endif /* GL_ATI_mapped_texture */

/* --------------------------- ATI_pn_triangles --------------------------- */

#ifdef GL_ATI_pn_triangles

#define GL_PN_TRIANGLES_ATI                                     0x87F0
#define GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI               0x87F1
#define GL_PN_TRIANGLES_POINT_MODE_ATI                          0x87F2
#define GL_PN_TRIANGLES_NORMAL_MODE_ATI                         0x87F3
#define GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI                   0x87F4
#define GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI                   0x87F5
#define GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI                    0x87F6
#define GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI                  0x87F7
#define GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI               0x87F8

typedef void (APIENTRY * glPNTrianglesiATIPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * glPNTrianglesfATIPROC) (GLenum pname, GLfloat param);

extern GLEW_EXPORT glPNTrianglesiATIPROC glPNTrianglesiATI;
extern GLEW_EXPORT glPNTrianglesfATIPROC glPNTrianglesfATI;

#endif /* GL_ATI_pn_triangles */

/* -------------------------- ATI_point_cull_mode ------------------------- */

#ifdef GL_ATI_point_cull_mode

#define GL_POINT_CULL_MODE_ATI                                  0x60b3
#define GL_POINT_CULL_CENTER_ATI                                0x60b4
#define GL_POINT_CLIP_ATI                                       0x60b5

#endif /* GL_ATI_point_cull_mode */

/* -------------------------- ATI_separate_stencil ------------------------ */

#ifdef GL_ATI_separate_stencil

#define GL_STENCIL_BACK_FUNC_ATI                                0x8800
#define GL_STENCIL_BACK_FAIL_ATI                                0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL_ATI                     0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS_ATI                     0x8803

typedef void (APIENTRY * glStencilOpSeparateATIPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (APIENTRY * glStencilFuncSeparateATIPROC) (GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask);

extern GLEW_EXPORT glStencilOpSeparateATIPROC glStencilOpSeparateATI;
extern GLEW_EXPORT glStencilFuncSeparateATIPROC glStencilFuncSeparateATI;

#endif /* GL_ATI_separate_stencil */

/* ----------------------- ATI_text_fragment_shader ----------------------- */

#ifdef GL_ATI_text_fragment_shader

#define GL_TEXT_FRAGMENT_SHADER_ATI                             0x8200

#endif /* GL_ATI_text_fragment_shader */

/* --------------------------- ATI_texture_float -------------------------- */

#ifdef GL_ATI_texture_float

#define GL_RGBA_FLOAT32_ATI                                     0x8814
#define GL_RGB_FLOAT32_ATI                                      0x8815
#define GL_ALPHA_FLOAT32_ATI                                    0x8816
#define GL_INTENSITY_FLOAT32_ATI                                0x8817
#define GL_LUMINANCE_FLOAT32_ATI                                0x8818
#define GL_LUMINANCE_ALPHA_FLOAT32_ATI                          0x8819
#define GL_RGBA_FLOAT16_ATI                                     0x881A
#define GL_RGB_FLOAT16_ATI                                      0x881B
#define GL_ALPHA_FLOAT16_ATI                                    0x881C
#define GL_INTENSITY_FLOAT16_ATI                                0x881D
#define GL_LUMINANCE_FLOAT16_ATI                                0x881E
#define GL_LUMINANCE_ALPHA_FLOAT16_ATI                          0x881F

#endif /* GL_ATI_texture_float */

/* ------------------------ ATI_texture_mirror_once ----------------------- */

#ifdef GL_ATI_texture_mirror_once

#define GL_MIRROR_CLAMP_ATI                                     0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_ATI                             0x8743

#endif

/* ----------------------------- ATI_timestamp ---------------------------- */

#ifdef GL_ATI_timestamp

typedef void (APIENTRY * glNewTimeStampPROC) (GLvoid **);
typedef void (APIENTRY * glDeleteTimeStampPROC) (GLvoid *);
typedef void (APIENTRY * glSendTimeStampPROC) (GLvoid *);
typedef void (APIENTRY * glWaitTimeStampPROC) (GLvoid *);

extern GLEW_EXPORT glNewTimeStampPROC glNewTimeStamp;
extern GLEW_EXPORT glDeleteTimeStampPROC glDeleteTimeStamp;
extern GLEW_EXPORT glSendTimeStampPROC glSendTimeStamp;
extern GLEW_EXPORT glWaitTimeStampPROC glWaitTimeStamp;

#endif /* GL_ATI_timestamp */

/* ------------------------ ATI_vertex_array_object ----------------------- */

#ifdef GL_ATI_vertex_array_object

#define GL_EXTERN GLEW_EXPORT_ATI                                           0x8760
#define GL_DYNAMIC_ATI                                          0x8761
#define GL_PRESERVE_ATI                                         0x8762
#define GL_DISCARD_ATI                                          0x8763
#define GL_OBJECT_BUFFER_SIZE_ATI                               0x8764
#define GL_OBJECT_BUFFER_USAGE_ATI                              0x8765
#define GL_ARRAY_OBJECT_BUFFER_ATI                              0x8766
#define GL_ARRAY_OBJECT_OFFSET_ATI                              0x8767

typedef GLuint (APIENTRY * glNewObjectBufferATIPROC) (GLsizei size, const GLvoid *pointer, GLenum usage);
typedef GLboolean (APIENTRY * glIsObjectBufferATIPROC) (GLuint buffer);
typedef void (APIENTRY * glUpdateObjectBufferATIPROC) (GLuint buffer, GLuint offset, GLsizei size, const GLvoid *pointer, GLenum preserve);
typedef void (APIENTRY * glGetObjectBufferfvATIPROC) (GLuint buffer, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetObjectBufferivATIPROC) (GLuint buffer, GLenum pname, GLint *params);
typedef void (APIENTRY * glFreeObjectBufferATIPROC) (GLuint buffer);
typedef void (APIENTRY * glArrayObjectATIPROC) (GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (APIENTRY * glGetArrayObjectfvATIPROC) (GLenum array, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetArrayObjectivATIPROC) (GLenum array, GLenum pname, GLint *params);
typedef void (APIENTRY * glVariantArrayObjectATIPROC) (GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (APIENTRY * glGetVariantArrayObjectfvATIPROC) (GLuint id, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetVariantArrayObjectivATIPROC) (GLuint id, GLenum pname, GLint *params);

extern GLEW_EXPORT glNewObjectBufferATIPROC glNewObjectBufferATI;
extern GLEW_EXPORT glIsObjectBufferATIPROC glIsObjectBufferATI;
extern GLEW_EXPORT glUpdateObjectBufferATIPROC glUpdateObjectBufferATI;
extern GLEW_EXPORT glGetObjectBufferfvATIPROC glGetObjectBufferfvATI;
extern GLEW_EXPORT glGetObjectBufferivATIPROC glGetObjectBufferivATI;
extern GLEW_EXPORT glFreeObjectBufferATIPROC glFreeObjectBufferATI;
extern GLEW_EXPORT glArrayObjectATIPROC glArrayObjectATI;
extern GLEW_EXPORT glGetArrayObjectfvATIPROC glGetArrayObjectfvATI;
extern GLEW_EXPORT glGetArrayObjectivATIPROC glGetArrayObjectivATI;
extern GLEW_EXPORT glVariantArrayObjectATIPROC glVariantArrayObjectATI;
extern GLEW_EXPORT glGetVariantArrayObjectfvATIPROC glGetVariantArrayObjectfvATI;
extern GLEW_EXPORT glGetVariantArrayObjectivATIPROC glGetVariantArrayObjectivATI;

#endif /* GL_ATI_vertex_array_object */

/* -------------------- ATI_vertex_attrib_array_object -------------------- */

#ifdef GL_ATI_vertex_attrib_array_object

typedef void (APIENTRY * glVertexAttribArratObjectATIPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (APIENTRY * glGetVertexAttribArratObjectfvATIPROC)(GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetVertexAttrubAttatObjectivATIPROC)(GLuint index, GLenum pname, GLint *params);

extern GLEW_EXPORT glVertexAttribArratObjectATIPROC glVertexAttribArratObjectATI;
extern GLEW_EXPORT glGetVertexAttribArratObjectfvATIPROC glGetVertexAttribArratObjectfvATI;
extern GLEW_EXPORT glGetVertexAttrubAttatObjectivATIPROC glGetVertexAttrubAttatObjectivATI;

#endif /* GL_ATI_vertex_attrib_array_object */

/* -------------------------- ATI_vertex_streams -------------------------- */

#ifdef GL_ATI_vertex_streams

#define GL_MAX_VERTEX_STREAMS_ATI                               0x876B
#define GL_VERTEX_SOURCE_ATI                                    0x876C
#define GL_VERTEX_STREAM0_ATI                                   0x876D
#define GL_VERTEX_STREAM1_ATI                                   0x876E
#define GL_VERTEX_STREAM2_ATI                                   0x876F
#define GL_VERTEX_STREAM3_ATI                                   0x8770
#define GL_VERTEX_STREAM4_ATI                                   0x8771
#define GL_VERTEX_STREAM5_ATI                                   0x8772
#define GL_VERTEX_STREAM6_ATI                                   0x8773
#define GL_VERTEX_STREAM7_ATI                                   0x8774

typedef void (APIENTRY * glClientActiveVertexStreamATIPROC) (GLenum stream);
typedef void (APIENTRY * glVertexBlendEnviATIPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * glVertexBlendEnvfATIPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * glVertexStream2sATIPROC) (GLenum stream, GLshort x, GLshort y);
typedef void (APIENTRY * glVertexStream2svATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * glVertexStream2iATIPROC) (GLenum stream, GLint x, GLint y);
typedef void (APIENTRY * glVertexStream2ivATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * glVertexStream2fATIPROC) (GLenum stream, GLfloat x, GLfloat y);
typedef void (APIENTRY * glVertexStream2fvATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * glVertexStream2dATIPROC) (GLenum stream, GLdouble x, GLdouble y);
typedef void (APIENTRY * glVertexStream2dvATIPROC) (GLenum stream, const GLdouble *v);
typedef void (APIENTRY * glVertexStream3sATIPROC) (GLenum stream, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * glVertexStream3svATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * glVertexStream3iATIPROC) (GLenum stream, GLint x, GLint y, GLint z);
typedef void (APIENTRY * glVertexStream3ivATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * glVertexStream3fATIPROC) (GLenum stream, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * glVertexStream3fvATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * glVertexStream3dATIPROC) (GLenum stream, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * glVertexStream3dvATIPROC) (GLenum stream, const GLdouble *v);
typedef void (APIENTRY * glVertexStream4sATIPROC) (GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRY * glVertexStream4svATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * glVertexStream4iATIPROC) (GLenum stream, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRY * glVertexStream4ivATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * glVertexStream4fATIPROC) (GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glVertexStream4fvATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * glVertexStream4dATIPROC) (GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glVertexStream4dvATIPROC) (GLenum stream, const GLdouble *v);
typedef void (APIENTRY * glNormalStream3bATIPROC) (GLenum stream, GLbyte x, GLbyte y, GLbyte z);
typedef void (APIENTRY * glNormalStream3bvATIPROC) (GLenum stream, const GLbyte *v);
typedef void (APIENTRY * glNormalStream3sATIPROC) (GLenum stream, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * glNormalStream3svATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * glNormalStream3iATIPROC) (GLenum stream, GLint x, GLint y, GLint z);
typedef void (APIENTRY * glNormalStream3ivATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * glNormalStream3fATIPROC) (GLenum stream, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * glNormalStream3fvATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * glNormalStream3dATIPROC) (GLenum stream, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * glNormalStream3dvATIPROC) (GLenum stream, const GLdouble *v);

extern GLEW_EXPORT glClientActiveVertexStreamATIPROC glClientActiveVertexStreamATI;
extern GLEW_EXPORT glVertexBlendEnviATIPROC glVertexBlendEnviATI;
extern GLEW_EXPORT glVertexBlendEnvfATIPROC glVertexBlendEnvfATI;
extern GLEW_EXPORT glVertexStream2sATIPROC glVertexStream2sATI;
extern GLEW_EXPORT glVertexStream2svATIPROC glVertexStream2svATI;
extern GLEW_EXPORT glVertexStream2iATIPROC glVertexStream2iATI;
extern GLEW_EXPORT glVertexStream2ivATIPROC glVertexStream2ivATI;
extern GLEW_EXPORT glVertexStream2fATIPROC glVertexStream2fATI;
extern GLEW_EXPORT glVertexStream2fvATIPROC glVertexStream2fvATI;
extern GLEW_EXPORT glVertexStream2dATIPROC glVertexStream2dATI;
extern GLEW_EXPORT glVertexStream2dvATIPROC glVertexStream2dvATI;
extern GLEW_EXPORT glVertexStream3sATIPROC glVertexStream3sATI;
extern GLEW_EXPORT glVertexStream3svATIPROC glVertexStream3svATI;
extern GLEW_EXPORT glVertexStream3iATIPROC glVertexStream3iATI;
extern GLEW_EXPORT glVertexStream3ivATIPROC glVertexStream3ivATI;
extern GLEW_EXPORT glVertexStream3fATIPROC glVertexStream3fATI;
extern GLEW_EXPORT glVertexStream3fvATIPROC glVertexStream3fvATI;
extern GLEW_EXPORT glVertexStream3dATIPROC glVertexStream3dATI;
extern GLEW_EXPORT glVertexStream3dvATIPROC glVertexStream3dvATI;
extern GLEW_EXPORT glVertexStream4sATIPROC glVertexStream4sATI;
extern GLEW_EXPORT glVertexStream4svATIPROC glVertexStream4svATI;
extern GLEW_EXPORT glVertexStream4iATIPROC glVertexStream4iATI;
extern GLEW_EXPORT glVertexStream4ivATIPROC glVertexStream4ivATI;
extern GLEW_EXPORT glVertexStream4fATIPROC glVertexStream4fATI;
extern GLEW_EXPORT glVertexStream4fvATIPROC glVertexStream4fvATI;
extern GLEW_EXPORT glVertexStream4dATIPROC glVertexStream4dATI;
extern GLEW_EXPORT glVertexStream4dvATIPROC glVertexStream4dvATI;
extern GLEW_EXPORT glNormalStream3bATIPROC glNormalStream3bATI;
extern GLEW_EXPORT glNormalStream3bvATIPROC glNormalStream3bvATI;
extern GLEW_EXPORT glNormalStream3sATIPROC glNormalStream3sATI;
extern GLEW_EXPORT glNormalStream3svATIPROC glNormalStream3svATI;
extern GLEW_EXPORT glNormalStream3iATIPROC glNormalStream3iATI;
extern GLEW_EXPORT glNormalStream3ivATIPROC glNormalStream3ivATI;
extern GLEW_EXPORT glNormalStream3fATIPROC glNormalStream3fATI;
extern GLEW_EXPORT glNormalStream3fvATIPROC glNormalStream3fvATI;
extern GLEW_EXPORT glNormalStream3dATIPROC glNormalStream3dATI;
extern GLEW_EXPORT glNormalStream3dvATIPROC glNormalStream3dvATI;

#endif /* GL_ATI_vertex_streams */

/* -------------------------- ATIX_point_sprites -------------------------- */

#ifdef GL_ATIX_point_sprites

#define GL_TEXTURE_POINT_MODE_ATIX                              0x60b0
#define	GL_TEXTURE_POINT_ONE_COORD_ATIX                         0x60b1
#define	GL_TEXTURE_POINT_SPRITE_ATIX                            0x60b2
#define GL_POINT_SPRITE_CULL_MODE_ATIX                          0x60b3
#define GL_POINT_SPRITE_CULL_CENTER_ATIX                        0x60b4
#define GL_POINT_SPRITE_CULL_CLIP_ATIX                          0x60b5

#endif /* GL_ATIX_point_sprites */

/* ----------------------- ATIX_texture_env_combine3 ---------------------- */

#ifdef GL_ATIX_texture_env_combine3

#define GL_MODULATE_ADD_ATIX                                    0x8744
#define GL_MODULATE_SIGNED_ADD_ATIX                             0x8745
#define GL_MODULATE_SUBTRACT_ATIX                               0x8746

#endif /* GL_ATIX_texture_env_combine3 */

/* ------------------------ ATIX_texture_env_route ------------------------ */

#ifdef GL_ATIX_texture_env_route

#define GL_SECONDARY_COLOR_ATIX                                 0x8747
#define GL_TEXTURE_OUTPUT_RGB_ATIX                              0x8748
#define GL_TEXTURE_OUTPUT_ALPHA_ATIX                            0x8749

#endif /* GL_ATIX_texture_env_route */

/* ----------------- ATIX_vertex_shader_output_point_size ----------------- */

#ifdef GL_ATIX_vertex_shader_output_point_size

#define GL_OUTPUT_POINT_SIZE_ATIX                               0x610E

#endif /* GL_ATIX_vertex_shader_output_point_size */

/* ---------------------------- NV_blend_square --------------------------- */

/* ------------------------ NV_copy_depth_to_color ------------------------ */

#ifdef GL_NV_copy_depth_to_color

#define GL_DEPTH_STENCIL_TO_RGBA_NV                             0x886E
#define GL_DEPTH_STENCIL_TO_BGRA_NV                             0x886F

#endif /* GL_NV_copy_depth_to_color */

/* ---------------------------- NV_depth_clamp ---------------------------- */

#ifdef GL_NV_depth_clamp

#define GL_DEPTH_CLAMP_NV                                       0x864F

#endif /* GL_NV_depth_clamp */

/* --------------------------- NV_element_array --------------------------- */

#ifdef GL_NV_element_array

#define GL_ELEMENT_ARRAY_TYPE_NV                                0x8769
#define GL_ELEMENT_ARRAY_POINTER_NV                             0x876A

typedef void (APIENTRY * glElementPointerNVPROC) (GLenum type, const GLvoid *pointer);
typedef void (APIENTRY * glDrawElementArrayNVPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRY * glDrawRangeElementArrayNVPROC) (GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count);
typedef void (APIENTRY * glMultiDrawElementArrayNVPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (APIENTRY * glMultiDrawRangeElementArrayNVPROC) (GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount);

extern GLEW_EXPORT glElementPointerNVPROC glElementPointerNV;
extern GLEW_EXPORT glDrawElementArrayNVPROC glDrawElementArrayNV;
extern GLEW_EXPORT glDrawRangeElementArrayNVPROC glDrawRangeElementArrayNV;
extern GLEW_EXPORT glMultiDrawElementArrayNVPROC glMultiDrawElementArrayNV;
extern GLEW_EXPORT glMultiDrawRangeElementArrayNVPROC glMultiDrawRangeElementArrayNV;

#endif /* GL_NV_element_array */

/* ----------------------------- NV_evaluators ---------------------------- */

#ifdef GL_NV_evaluators

#define GL_EVAL_2D_NV                                           0x86C0
#define GL_EVAL_TRIANGULAR_2D_NV                                0x86C1
#define GL_MAP_TESSELLATION_NV                                  0x86C2
#define GL_MAP_ATTRIB_U_ORDER_NV                                0x86C3
#define GL_MAP_ATTRIB_V_ORDER_NV                                0x86C4
#define GL_EVAL_FRACTIONAL_TESSELLATION_NV                      0x86C5
#define GL_EVAL_VERTEX_ATTRIB0_NV                               0x86C6
#define GL_EVAL_VERTEX_ATTRIB1_NV                               0x86C7
#define GL_EVAL_VERTEX_ATTRIB2_NV                               0x86C8
#define GL_EVAL_VERTEX_ATTRIB3_NV                               0x86C9
#define GL_EVAL_VERTEX_ATTRIB4_NV                               0x86CA
#define GL_EVAL_VERTEX_ATTRIB5_NV                               0x86CB
#define GL_EVAL_VERTEX_ATTRIB6_NV                               0x86CC
#define GL_EVAL_VERTEX_ATTRIB7_NV                               0x86CD
#define GL_EVAL_VERTEX_ATTRIB8_NV                               0x86CE
#define GL_EVAL_VERTEX_ATTRIB9_NV                               0x86CF
#define GL_EVAL_VERTEX_ATTRIB10_NV                              0x86D0
#define GL_EVAL_VERTEX_ATTRIB11_NV                              0x86D1
#define GL_EVAL_VERTEX_ATTRIB12_NV                              0x86D2
#define GL_EVAL_VERTEX_ATTRIB13_NV                              0x86D3
#define GL_EVAL_VERTEX_ATTRIB14_NV                              0x86D4
#define GL_EVAL_VERTEX_ATTRIB15_NV                              0x86D5
#define GL_MAX_MAP_TESSELLATION_NV                              0x86D6
#define GL_MAX_RATIONAL_EVAL_ORDER_NV                           0x86D7

typedef void (APIENTRY * glMapControlPointsNVPROC) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid *points);
typedef void (APIENTRY * glMapParameterivNVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRY * glMapParameterfvNVPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * glGetMapControlPointsNVPROC) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid *points);
typedef void (APIENTRY * glGetMapParameterivNVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetMapParameterfvNVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetMapAttribParameterivNVPROC) (GLenum target, GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetMapAttribParameterfvNVPROC) (GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glEvalMapsNVPROC) (GLenum target, GLenum mode);

extern GLEW_EXPORT glMapControlPointsNVPROC glMapControlPointsNV;
extern GLEW_EXPORT glMapParameterivNVPROC glMapParameterivNV;
extern GLEW_EXPORT glMapParameterfvNVPROC glMapParameterfvNV;
extern GLEW_EXPORT glGetMapControlPointsNVPROC glGetMapControlPointsNV;
extern GLEW_EXPORT glGetMapParameterivNVPROC glGetMapParameterivNV;
extern GLEW_EXPORT glGetMapParameterfvNVPROC glGetMapParameterfvNV;
extern GLEW_EXPORT glGetMapAttribParameterivNVPROC glGetMapAttribParameterivNV;
extern GLEW_EXPORT glGetMapAttribParameterfvNVPROC glGetMapAttribParameterfvNV;
extern GLEW_EXPORT glEvalMapsNVPROC glEvalMapsNV;

#endif /* GL_NV_evaluators */

/* ------------------------------- NV_fence ------------------------------- */

#ifdef GL_NV_fence

#define GL_ALL_COMPLETED_NV                                     0x84F2
#define GL_FENCE_STATUS_NV                                      0x84F3
#define GL_FENCE_CONDITION_NV                                   0x84F4

typedef void (APIENTRY * glGenFencesNVPROC) (GLsizei n, GLuint *fences);
typedef void (APIENTRY * glDeleteFencesNVPROC) (GLsizei n, const GLuint *fences);
typedef void (APIENTRY * glSetFenceNVPROC) (GLuint fence, GLenum condition);
typedef GLboolean (APIENTRY * glTestFenceNVPROC) (GLuint fence);
typedef void (APIENTRY * glFinishFenceNVPROC) (GLuint fence);
typedef GLboolean (APIENTRY * glIsFenceNVPROC) (GLuint fence);
typedef void (APIENTRY * glGetFenceivNVPROC) (GLuint fence, GLenum pname, GLint *params);

extern GLEW_EXPORT glGenFencesNVPROC glGenFencesNV;
extern GLEW_EXPORT glDeleteFencesNVPROC glDeleteFencesNV;
extern GLEW_EXPORT glSetFenceNVPROC glSetFenceNV;
extern GLEW_EXPORT glTestFenceNVPROC glTestFenceNV;
extern GLEW_EXPORT glFinishFenceNVPROC glFinishFenceNV;
extern GLEW_EXPORT glIsFenceNVPROC glIsFenceNV;
extern GLEW_EXPORT glGetFenceivNVPROC glGetFenceivNV;

#endif /* GL_NV_fence */

/* ---------------------------- NV_float_buffer --------------------------- */

#ifdef GL_NV_float_buffer

#define GL_FLOAT_R_NV                                           0x8880
#define GL_FLOAT_RG_NV                                          0x8881
#define GL_FLOAT_RGB_NV                                         0x8882
#define GL_FLOAT_RGBA_NV                                        0x8883
#define GL_FLOAT_R32_NV                                         0x8885
#define GL_FLOAT_R16_NV                                         0x8884
#define GL_FLOAT_R32_NV                                         0x8885
#define GL_FLOAT_RG16_NV                                        0x8886
#define GL_FLOAT_RG32_NV                                        0x8887
#define GL_FLOAT_RGB16_NV                                       0x8888
#define GL_FLOAT_RGB32_NV                                       0x8889
#define GL_FLOAT_RGBA16_NV                                      0x888A
#define GL_FLOAT_RGBA32_NV                                      0x888B
#define GL_TEXTURE_FLOAT_COMPONENTS_NV                          0x888C
#define GL_FLOAT_CLEAR_COLOR_VALUE_NV                           0x888D
#define GL_FLOAT_RGBA_MODE_NV                                   0x888E

#endif /* GL_NV_float_buffer */

/* ---------------------------- NV_fog_distance --------------------------- */

#ifdef GL_NV_fog_distance

#define GL_FOG_DISTANCE_MODE_NV                                 0x855A
#define GL_EYE_RADIAL_NV                                        0x855B
#define GL_EYE_PLANE_ABSOLUTE_NV                                0x855C

#endif /* GL_NV_fog_distance */

/* -------------------------- NV_fragment_program ------------------------- */

#ifdef GL_NV_fragment_program

#define GL_FRAGMENT_PROGRAM_NV                                  0x8870
#define GL_MAX_TEXTURE_COORDS_NV                                0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_NV                           0x8872
#define GL_FRAGMENT_PROGRAM_BINDING_NV                          0x8873
#define GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV             0x8868
#define GL_PROGRAM_ERROR_STRING_NV                              0x8874

typedef void (APIENTRY * glProgramNamedParameter4fNVPROC) (GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glProgramNamedParameter4dNVPROC) (GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glProgramNamedParameter4fvNVPROC) (GLuint id, GLsizei len, const GLubyte *name, const GLfloat v[]);
typedef void (APIENTRY * glProgramNamedParameter4dvNVPROC) (GLuint id, GLsizei len, const GLubyte *name, const GLdouble v[]);
typedef void (APIENTRY * glGetProgramNamedParameterfvNVPROC) (GLuint id, GLsizei len, const GLubyte *name, GLfloat *params);
typedef void (APIENTRY * glGetProgramNamedParameterdvNVPROC) (GLuint id, GLsizei len, const GLubyte *name, GLdouble *params);

#ifndef GL_ARB_vertex_program
typedef void (APIENTRY * glProgramLocalParameter4dARBPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glProgramLocalParameter4dvARBPROC) (GLenum target, GLuint index, const GLdouble *params);
typedef void (APIENTRY * glProgramLocalParameter4fARBPROC) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glProgramLocalParameter4fvARBPROC) (GLenum target, GLuint index, const GLfloat *params);
typedef void (APIENTRY * glGetProgramLocalParameterdvARBPROC) (GLenum target, GLuint index, GLdouble *params);
typedef void (APIENTRY * glGetProgramLocalParameterfvARBPROC) (GLenum target, GLuint index, GLfloat *params);
#endif /* GL_ARB_vertex_program */

extern GLEW_EXPORT glProgramNamedParameter4fNVPROC glProgramNamedParameter4fNV;
extern GLEW_EXPORT glProgramNamedParameter4dNVPROC glProgramNamedParameter4dNV;
extern GLEW_EXPORT glProgramNamedParameter4fvNVPROC glProgramNamedParameter4fvNV;
extern GLEW_EXPORT glProgramNamedParameter4dvNVPROC glProgramNamedParameter4dvNV;
extern GLEW_EXPORT glGetProgramNamedParameterfvNVPROC glGetProgramNamedParameterfvNV;
extern GLEW_EXPORT glGetProgramNamedParameterdvNVPROC glGetProgramNamedParameterdvNV;

#ifndef GL_ARB_vertex_program
extern GLEW_EXPORT glProgramLocalParameter4dARBPROC glProgramLocalParameter4dARB;
extern GLEW_EXPORT glProgramLocalParameter4dvARBPROC glProgramLocalParameter4dvARB;
extern GLEW_EXPORT glProgramLocalParameter4fARBPROC glProgramLocalParameter4fARB;
extern GLEW_EXPORT glProgramLocalParameter4fvARBPROC glProgramLocalParameter4fvARB;
extern GLEW_EXPORT glGetProgramLocalParameterdvARBPROC glGetProgramLocalParameterdvARB;
extern GLEW_EXPORT glGetProgramLocalParameterfvARBPROC glGetProgramLocalParameterfvARB;
#endif /* GL_ARB_vertex_program */

#endif /* GL_NV_fragment_program */

/* ------------------------- NV_light_max_exponent ------------------------ */

#ifdef GL_NV_light_max_exponent

#define GL_MAX_SHININESS_NV                                     0x8504
#define GL_MAX_SPOT_EXPONENT_NV                                 0x8505

#endif /* GL_NV_light_max_exponent */

/* ----------------------- NV_multisample_filter_hint --------------------- */

#ifdef GL_NV_multisample_filter_hint

#define GL_MULTISAMPLE_FILTER_HINT_NV                           0x8534

#endif /* GL_NV_multisample_filter_hint */

/* -------------------------- NV_occlusion_query -------------------------- */

#ifdef GL_NV_occlusion_query

#ifndef GL_HP_occlusion_test
#define GL_OCCLUSION_TEST_HP                                    0x8165
#define GL_OCCLUSION_TEST_RESULT_HP                             0x8166
#endif /* GL_HP_occlusion_test */
#define GL_PIXEL_COUNTER_BITS_NV                                0x8864
#define GL_CURRENT_OCCLUSION_QUERY_ID_NV                        0x8865
#define GL_PIXEL_COUNT_NV                                       0x8866
#define GL_PIXEL_COUNT_AVAILABLE_NV                             0x8867

typedef void (APIENTRY * glGenOcclusionQueriesNVPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRY * glDeleteOcclusionQueriesNVPROC) (GLsizei n, const GLuint *ids);
typedef GLboolean (APIENTRY * glIsOcclusionQueryNVPROC) (GLuint id);
typedef void (APIENTRY * glBeginOcclusionQueryNVPROC) (GLuint id);
typedef void (APIENTRY * glEndOcclusionQueryNVPROC) (void);
typedef void (APIENTRY * glGetOcclusionQueryivNVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetOcclusionQueryuivNVPROC) (GLuint id, GLenum pname, GLuint *params);

extern GLEW_EXPORT glGenOcclusionQueriesNVPROC glGenOcclusionQueriesNV;
extern GLEW_EXPORT glDeleteOcclusionQueriesNVPROC glDeleteOcclusionQueriesNV;
extern GLEW_EXPORT glIsOcclusionQueryNVPROC glIsOcclusionQueryNV;
extern GLEW_EXPORT glBeginOcclusionQueryNVPROC glBeginOcclusionQueryNV;
extern GLEW_EXPORT glEndOcclusionQueryNVPROC glEndOcclusionQueryNV;
extern GLEW_EXPORT glGetOcclusionQueryivNVPROC glGetOcclusionQueryivNV;
extern GLEW_EXPORT glGetOcclusionQueryuivNVPROC glGetOcclusionQueryuivNV;

#endif /* GL_NV_occlusion_query */

/* ------------------------ NV_packed_depth_stencil ----------------------- */

#ifdef GL_NV_packed_depth_stencil

#define GL_DEPTH_STENCIL_NV                                     0x84F9
#define GL_UNSIGNED_INT_24_8_NV                                 0x84FA

#endif /* GL_NV_packed_depth_stencil */

/* -------------------------- NV_pixel_data_range ------------------------- */

#ifdef GL_NV_pixel_data_range

#define WRITE_PIXEL_DATA_RANGE_NV                               0x8878
#define READ_PIXEL_DATA_RANGE_NV                                0x8879
#define WRITE_PIXEL_DATA_RANGE_LENGTH_NV                        0x887A
#define READ_PIXEL_DATA_RANGE_LENGTH_NV                         0x887B
#define WRITE_PIXEL_DATA_RANGE_POINTER_NV                       0x887C
#define READ_PIXEL_DATA_RANGE_POINTER_NV                        0x887D

typedef void (APIENTRY * glPixelDataRangeNVPROC) (GLenum target, GLsizei length, GLvoid *pointer);
typedef void (APIENTRY * glFlushPixelDataRangeNVPROC) (GLenum target);

extern GLEW_EXPORT glPixelDataRangeNVPROC glPixelDataRangeNV;
extern GLEW_EXPORT glFlushPixelDataRangeNVPROC glFlushPixelDataRangeNV;

#endif /* GL_NV_pixel_data_range */

/* ---------------------------- NV_point_sprite --------------------------- */

#ifdef GL_NV_point_sprite

#define GL_POINT_SPRITE_NV                                      0x8861
#define GL_COORD_REPLACE_NV                                     0x8862
#define GL_POINT_SPRITE_R_MODE_NV                               0x8863

typedef void (APIENTRY * glPointParameteriNVPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * glPointParameterivNVPROC) (GLenum pname, const GLint *params);

extern GLEW_EXPORT glPointParameteriNVPROC glPointParameteriNV;
extern GLEW_EXPORT glPointParameterivNVPROC glPointParameterivNV;

#endif /* GL_NV_point_sprite */

/* ------------------------- NV_primitive_restart ------------------------- */

#ifdef GL_NV_primitive_restart

#define GL_PRIMITIVE_RESTART_NV                                 0x8558
#define GL_PRIMITIVE_RESTART_INDEX_NV                           0x8559

typedef void (APIENTRY * glPrimitiveRestartNVPROC) ();
typedef void (APIENTRY * glPrimitiveRestartIndexNVPROC) (GLuint index);

extern GLEW_EXPORT glPrimitiveRestartNVPROC glPrimitiveRestartNV;
extern GLEW_EXPORT glPrimitiveRestartIndexNVPROC glPrimitiveRestartIndexNV;

#endif /* GL_NV_primitive_restart */

/* ------------------------- NV_register_combiners ------------------------ */

#ifdef GL_NV_register_combiners

#define GL_REGISTER_COMBINERS_NV                                0x8522
#define GL_COMBINER0_NV                                         0x8550
#define GL_COMBINER1_NV                                         0x8551
#define GL_COMBINER2_NV                                         0x8552
#define GL_COMBINER3_NV                                         0x8553
#define GL_COMBINER4_NV                                         0x8554
#define GL_COMBINER5_NV                                         0x8555
#define GL_COMBINER6_NV                                         0x8556
#define GL_COMBINER7_NV                                         0x8557
#define GL_VARIABLE_A_NV                                        0x8523
#define GL_VARIABLE_B_NV                                        0x8524
#define GL_VARIABLE_C_NV                                        0x8525
#define GL_VARIABLE_D_NV                                        0x8526
#define GL_VARIABLE_E_NV                                        0x8527
#define GL_VARIABLE_F_NV                                        0x8528
#define GL_VARIABLE_G_NV                                        0x8529
#define GL_CONSTANT_COLOR0_NV                                   0x852A
#define GL_CONSTANT_COLOR1_NV                                   0x852B
#define GL_PRIMARY_COLOR_NV                                     0x852C
#define GL_SECONDARY_COLOR_NV                                   0x852D
#define GL_SPARE0_NV                                            0x852E
#define GL_SPARE1_NV                                            0x852F
#define GL_UNSIGNED_IDENTITY_NV                                 0x8536
#define GL_UNSIGNED_INVERT_NV                                   0x8537
#define GL_EXPAND_NORMAL_NV                                     0x8538
#define GL_EXPAND_NEGATE_NV                                     0x8539
#define GL_HALF_BIAS_NORMAL_NV                                  0x853A
#define GL_HALF_BIAS_NEGATE_NV                                  0x853B
#define GL_SIGNED_IDENTITY_NV                                   0x853C
#define GL_SIGNED_NEGATE_NV                                     0x853D
#define GL_E_TIMES_F_NV                                         0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV                       0x8532
#define GL_SCALE_BY_TWO_NV                                      0x853E
#define GL_SCALE_BY_FOUR_NV                                     0x853F
#define GL_SCALE_BY_ONE_HALF_NV                                 0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV                         0x8541
#define GL_DISCARD_NV                                           0x8530
#define GL_COMBINER_INPUT_NV                                    0x8542
#define GL_COMBINER_MAPPING_NV                                  0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV                          0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV                           0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV                           0x8546
#define GL_COMBINER_MUX_SUM_NV                                  0x8547
#define GL_COMBINER_SCALE_NV                                    0x8548
#define GL_COMBINER_BIAS_NV                                     0x8549
#define GL_COMBINER_AB_OUTPUT_NV                                0x854A
#define GL_COMBINER_CD_OUTPUT_NV                                0x854B
#define GL_COMBINER_SUM_OUTPUT_NV                               0x854C
#define GL_NUM_GENERAL_COMBINERS_NV                             0x854E
#define GL_COLOR_SUM_CLAMP_NV                                   0x854F
#define GL_MAX_GENERAL_COMBINERS_NV                             0x854D

typedef void (APIENTRY * glCombinerParameterfvNVPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRY * glCombinerParameterfNVPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * glCombinerParameterivNVPROC) (GLenum pname, const GLint *params);
typedef void (APIENTRY * glCombinerParameteriNVPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * glCombinerInputNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (APIENTRY * glCombinerOutputNVPROC) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
typedef void (APIENTRY * glFinalCombinerInputNVPROC) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (APIENTRY * glGetCombinerInputParameterfvNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetCombinerInputParameterivNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetCombinerOutputParameterfvNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetCombinerOutputParameterivNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetFinalCombinerInputParameterfvNVPROC) (GLenum variable, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetFinalCombinerInputParameterivNVPROC) (GLenum variable, GLenum pname, GLint *params);

extern GLEW_EXPORT glCombinerParameterfvNVPROC glCombinerParameterfvNV;
extern GLEW_EXPORT glCombinerParameterfNVPROC  glCombinerParameterfNV;
extern GLEW_EXPORT glCombinerParameterivNVPROC glCombinerParameterivNV;
extern GLEW_EXPORT glCombinerParameteriNVPROC glCombinerParameteriNV;
extern GLEW_EXPORT glCombinerInputNVPROC glCombinerInputNV;
extern GLEW_EXPORT glCombinerOutputNVPROC glCombinerOutputNV;
extern GLEW_EXPORT glFinalCombinerInputNVPROC glFinalCombinerInputNV;
extern GLEW_EXPORT glGetCombinerInputParameterfvNVPROC glGetCombinerInputParameterfvNV;
extern GLEW_EXPORT glGetCombinerInputParameterivNVPROC glGetCombinerInputParameterivNV;
extern GLEW_EXPORT glGetCombinerOutputParameterfvNVPROC glGetCombinerOutputParameterfvNV;
extern GLEW_EXPORT glGetCombinerOutputParameterivNVPROC glGetCombinerOutputParameterivNV;
extern GLEW_EXPORT glGetFinalCombinerInputParameterfvNVPROC glGetFinalCombinerInputParameterfvNV;
extern GLEW_EXPORT glGetFinalCombinerInputParameterivNVPROC glGetFinalCombinerInputParameterivNV;

#endif /* GL_NV_register_combiners */

/* ------------------------ NV_register_combiners2 ------------------------ */

#ifdef GL_NV_register_combiners2

#define GL_PER_STAGE_CONSTANTS_NV                               0x8535

typedef void (APIENTRY * glCombinerStageParameterfvNVPROC) (GLenum stage, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * glGetCombinerStageParameterfvNVPROC) (GLenum stage, GLenum pname, GLfloat *params);

extern GLEW_EXPORT glCombinerStageParameterfvNVPROC glCombinerStageParameterfvNV;
extern GLEW_EXPORT glGetCombinerStageParameterfvNVPROC glGetCombinerStageParameterfvNV;

#endif /* GL_NV_register_combiners2 */

/* ------------------------- NV_texgen_reflection ------------------------- */

#ifdef GL_NV_texgen_reflection

#define GL_NORMAL_MAP_NV                                        0x8511
#define GL_REFLECTION_MAP_NV                                    0x8512

#endif /* GL_NV_texgen_reflection */

/* ---------------------- NV_texture_compression_vtc ---------------------- */

/* ------------------------ NV_texture_env_combine4 ----------------------- */

#ifdef GL_NV_texture_env_combine4

#define GL_COMBINE4_NV                                          0x8503
#define GL_SOURCE3_RGB_NV                                       0x8583
#define GL_SOURCE3_ALPHA_NV                                     0x858B
#define GL_OPERAND3_RGB_NV                                      0x8593
#define GL_OPERAND3_ALPHA_NV                                    0x859B

#endif /* GL_NV_texture_env_combine */

/* ------------------------- NV_texture_rectangle ------------------------- */

#ifdef GL_NV_texture_rectangle

#define GL_TEXTURE_RECTANGLE_NV                                 0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_NV                         0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_NV                           0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_NV                        0x84F8

#endif /* GL_NV_texture_rectangle */

/* --------------------------- NV_texture_shader -------------------------- */

#ifdef GL_NV_texture_shader

#define GL_TEXTURE_SHADER_NV                                    0x86DE
#define GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV                 0x86D9
#define GL_SHADER_OPERATION_NV                                  0x86DF
#define GL_CULL_MODES_NV                                        0x86E0
#define GL_OFFSET_TEXTURE_MATRIX_NV                             0x86E1
#define GL_OFFSET_TEXTURE_SCALE_NV                              0x86E2
#define GL_OFFSET_TEXTURE_BIAS_NV                               0x86E3
#define GL_PREVIOUS_TEXTURE_INPUT_NV                            0x86E4
#define GL_CONST_EYE_NV                                         0x86E5
#define GL_SHADER_CONSISTENT_NV                                 0x86DD
#define GL_PASS_THROUGH_NV                                      0x86E6
#define GL_CULL_FRAGMENT_NV                                     0x86E7
#define GL_OFFSET_TEXTURE_2D_NV                                 0x86E8
#define GL_OFFSET_TEXTURE_RECTANGLE_NV                          0x864C
#define GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV                    0x864D
#define GL_DEPENDENT_AR_TEXTURE_2D_NV                           0x86E9
#define GL_DEPENDENT_GB_TEXTURE_2D_NV                           0x86EA
#define GL_DOT_PRODUCT_NV                                       0x86EC
#define GL_DOT_PRODUCT_DEPTH_REPLACE_NV                         0x86ED
#define GL_DOT_PRODUCT_TEXTURE_2D_NV                            0x86EE
#define GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV                     0x864E
#define GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV                      0x86F0
#define GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV                      0x86F1
#define GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV                      0x86F2
#define GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV            0x86F3
#define GL_HILO_NV                                              0x86F4
#define GL_DSDT_NV                                              0x86F5
#define GL_DSDT_MAG_NV                                          0x86F6
#define GL_DSDT_MAG_VIB_NV                                      0x86F7
#define GL_UNSIGNED_INT_S8_S8_8_8_NV                            0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV                        0x86DB
#define GL_SIGNED_RGBA_NV                                       0x86FB
#define GL_SIGNED_RGBA8_NV                                      0x86FC
#define GL_SIGNED_RGB_NV                                        0x86FE
#define GL_SIGNED_RGB8_NV                                       0x86FF
#define GL_SIGNED_LUMINANCE_NV                                  0x8701
#define GL_SIGNED_LUMINANCE8_NV                                 0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV                            0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV                          0x8704
#define GL_SIGNED_ALPHA_NV                                      0x8705
#define GL_SIGNED_ALPHA8_NV                                     0x8706
#define GL_SIGNED_INTENSITY_NV                                  0x8707
#define GL_SIGNED_INTENSITY8_NV                                 0x8708
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV                         0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV                       0x870D
#define GL_HILO16_NV                                            0x86F8
#define GL_SIGNED_HILO_NV                                       0x86F9
#define GL_SIGNED_HILO16_NV                                     0x86FA
#define GL_DSDT8_NV                                             0x8709
#define GL_DSDT8_MAG8_NV                                        0x870A
#define GL_DSDT_MAG_INTENSITY_NV                                0x86DC
#define GL_DSDT8_MAG8_INTENSITY8_NV                             0x870B
#define GL_HI_SCALE_NV                                          0x870E
#define GL_LO_SCALE_NV                                          0x870F
#define GL_DS_SCALE_NV                                          0x8710
#define GL_DT_SCALE_NV                                          0x8711
#define GL_MAGNITUDE_SCALE_NV                                   0x8712
#define GL_VIBRANCE_SCALE_NV                                    0x8713
#define GL_HI_BIAS_NV                                           0x8714
#define GL_LO_BIAS_NV                                           0x8715
#define GL_DS_BIAS_NV                                           0x8716
#define GL_DT_BIAS_NV                                           0x8717
#define GL_MAGNITUDE_BIAS_NV                                    0x8718
#define GL_VIBRANCE_BIAS_NV                                     0x8719
#define GL_TEXTURE_BORDER_VALUES_NV                             0x871A
#define GL_TEXTURE_HI_SIZE_NV                                   0x871B
#define GL_TEXTURE_LO_SIZE_NV                                   0x871C
#define GL_TEXTURE_DS_SIZE_NV                                   0x871D
#define GL_TEXTURE_DT_SIZE_NV                                   0x871E
#define GL_TEXTURE_MAG_SIZE_NV                                  0x871F

#endif /* GL_NV_texture_shader */

/* -------------------------- NV_texture_shader2 -------------------------- */

#ifdef GL_NV_texture_shader2

#define GL_DOT_PRODUCT_TEXTURE_3D_NV                            0x86EF
#define GL_HILO_NV                                              0x86F4
#define GL_DSDT_NV                                              0x86F5
#define GL_DSDT_MAG_NV                                          0x86F6
#define GL_DSDT_MAG_VIB_NV                                      0x86F7
#define GL_UNSIGNED_INT_S8_S8_8_8_NV                            0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV                        0x86DB
#define GL_SIGNED_RGBA_NV                                       0x86FB
#define GL_SIGNED_RGBA8_NV                                      0x86FC
#define GL_SIGNED_RGB_NV                                        0x86FE
#define GL_SIGNED_RGB8_NV                                       0x86FF
#define GL_SIGNED_LUMINANCE_NV                                  0x8701
#define GL_SIGNED_LUMINANCE8_NV                                 0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV                            0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV                          0x8704
#define GL_SIGNED_ALPHA_NV                                      0x8705
#define GL_SIGNED_ALPHA8_NV                                     0x8706
#define GL_SIGNED_INTENSITY_NV                                  0x8707
#define GL_SIGNED_INTENSITY8_NV                                 0x8708
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV                         0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV                       0x870D
#define GL_HILO16_NV                                            0x86F8
#define GL_SIGNED_HILO_NV                                       0x86F9
#define GL_SIGNED_HILO16_NV                                     0x86FA
#define GL_DSDT8_NV                                             0x8709
#define GL_DSDT8_MAG8_NV                                        0x870A
#define GL_DSDT_MAG_INTENSITY_NV                                0x86DC
#define GL_DSDT8_MAG8_INTENSITY8_NV                             0x870B

#endif /* GL_NV_texture_shader2 */

/* -------------------------- NV_texture_shader3 -------------------------- */

#ifdef GL_NV_texture_shader3

#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_NV                      0x8850
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV                0x8851
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV               0x8852
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV         0x8853
#define GL_OFFSET_HILO_TEXTURE_2D_NV                            0x8854
#define GL_OFFSET_HILO_TEXTURE_RECTANGLE_NV                     0x8855
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV                 0x8856
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV          0x8857
#define GL_DEPENDENT_HILO_TEXTURE_2D_NV                         0x8858
#define GL_DEPENDENT_RGB_TEXTURE_3D_NV                          0x8859
#define GL_DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV                    0x885A
#define GL_DOT_PRODUCT_PASS_THROUGH_NV                          0x885B
#define GL_DOT_PRODUCT_TEXTURE_1D_NV                            0x885C
#define GL_DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV                  0x885D
#define GL_HILO8_NV                                             0x885E
#define GL_SIGNED_HILO8_NV                                      0x885F
#define GL_FORCE_BLUE_TO_ONE_NV                                 0x8860

#endif /* GL_NV_texture_shader3 */

/* ------------------------- NV_vertex_array_range ------------------------ */

#ifdef GL_NV_vertex_array_range

#define GL_VERTEX_ARRAY_RANGE_NV                                0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_NV                         0x851E
#define GL_VERTEX_ARRAY_RANGE_VALID_NV                          0x851F
#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV                    0x8520
#define GL_VERTEX_ARRAY_RANGE_POINTER_NV                        0x8521

typedef void (APIENTRY * glFlushVertexArrayRangeNVPROC) (void);
typedef void (APIENTRY * glVertexArrayRangeNVPROC) (GLsizei size, const GLvoid *pointer);

extern GLEW_EXPORT glFlushVertexArrayRangeNVPROC glFlushVertexArrayRangeNV;
extern GLEW_EXPORT glVertexArrayRangeNVPROC glVertexArrayRangeNV;

#endif /* GL_NV_vertex_array_range */

/* ------------------------ NV_vertex_array_range2 ------------------------ */

#ifdef GL_NV_vertex_array_range2

#define GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV                  0x8533

#endif /* GL_NV_vertex_array_range2 */

/* --------------------------- NV_vertex_program -------------------------- */

#ifdef GL_NV_vertex_program

#define GL_VERTEX_PROGRAM_NV                                    0x8620
#define GL_VERTEX_PROGRAM_POINT_SIZE_NV                         0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_NV                           0x8643
#define GL_VERTEX_STATE_PROGRAM_NV                              0x8621
#define GL_ATTRIB_ARRAY_SIZE_NV                                 0x8623
#define GL_ATTRIB_ARRAY_STRIDE_NV                               0x8624
#define GL_ATTRIB_ARRAY_TYPE_NV                                 0x8625
#define GL_CURRENT_ATTRIB_NV                                    0x8626
#define GL_PROGRAM_PARAMETER_NV                                 0x8644
#define GL_ATTRIB_ARRAY_POINTER_NV                              0x8645
#define GL_PROGRAM_TARGET_NV                                    0x8646
#define GL_PROGRAM_LENGTH_NV                                    0x8627
#define GL_PROGRAM_RESIDENT_NV                                  0x8647
#define GL_PROGRAM_STRING_NV                                    0x8628
#define GL_TRACK_MATRIX_NV                                      0x8648
#define GL_TRACK_MATRIX_TRANSFORM_NV                            0x8649
#define GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV                      0x862E
#define GL_MAX_TRACK_MATRICES_NV                                0x862F
#define GL_CURRENT_MATRIX_STACK_DEPTH_NV                        0x8640
#define GL_CURRENT_MATRIX_NV                                    0x8641
#define GL_VERTEX_PROGRAM_BINDING_NV                            0x864A
#define GL_PROGRAM_ERROR_POSITION_NV                            0x864B
#define GL_MODELVIEW_PROJECTION_NV                              0x8629
#define GL_MATRIX0_NV                                           0x8630
#define GL_MATRIX1_NV                                           0x8631
#define GL_MATRIX2_NV                                           0x8632
#define GL_MATRIX3_NV                                           0x8633
#define GL_MATRIX4_NV                                           0x8634
#define GL_MATRIX5_NV                                           0x8635
#define GL_MATRIX6_NV                                           0x8636
#define GL_MATRIX7_NV                                           0x8637
#define GL_IDENTITY_NV                                          0x862A
#define GL_INVERSE_NV                                           0x862B
#define GL_TRANSPOSE_NV                                         0x862C
#define GL_INVERSE_TRANSPOSE_NV                                 0x862D
#define GL_VERTEX_ATTRIB_ARRAY0_NV                              0x8650
#define GL_VERTEX_ATTRIB_ARRAY1_NV                              0x8651
#define GL_VERTEX_ATTRIB_ARRAY2_NV                              0x8652
#define GL_VERTEX_ATTRIB_ARRAY3_NV                              0x8653
#define GL_VERTEX_ATTRIB_ARRAY4_NV                              0x8654
#define GL_VERTEX_ATTRIB_ARRAY5_NV                              0x8655
#define GL_VERTEX_ATTRIB_ARRAY6_NV                              0x8656
#define GL_VERTEX_ATTRIB_ARRAY7_NV                              0x8657
#define GL_VERTEX_ATTRIB_ARRAY8_NV                              0x8658
#define GL_VERTEX_ATTRIB_ARRAY9_NV                              0x8659
#define GL_VERTEX_ATTRIB_ARRAY10_NV                             0x865A
#define GL_VERTEX_ATTRIB_ARRAY11_NV                             0x865B
#define GL_VERTEX_ATTRIB_ARRAY12_NV                             0x865C
#define GL_VERTEX_ATTRIB_ARRAY13_NV                             0x865D
#define GL_VERTEX_ATTRIB_ARRAY14_NV                             0x865E
#define GL_VERTEX_ATTRIB_ARRAY15_NV                             0x865F
#define GL_MAP1_VERTEX_ATTRIB0_4_NV                             0x8660
#define GL_MAP1_VERTEX_ATTRIB1_4_NV                             0x8661
#define GL_MAP1_VERTEX_ATTRIB2_4_NV                             0x8662
#define GL_MAP1_VERTEX_ATTRIB3_4_NV                             0x8663
#define GL_MAP1_VERTEX_ATTRIB4_4_NV                             0x8664
#define GL_MAP1_VERTEX_ATTRIB5_4_NV                             0x8665
#define GL_MAP1_VERTEX_ATTRIB6_4_NV                             0x8666
#define GL_MAP1_VERTEX_ATTRIB7_4_NV                             0x8667
#define GL_MAP1_VERTEX_ATTRIB8_4_NV                             0x8668
#define GL_MAP1_VERTEX_ATTRIB9_4_NV                             0x8669
#define GL_MAP1_VERTEX_ATTRIB10_4_NV                            0x866A
#define GL_MAP1_VERTEX_ATTRIB11_4_NV                            0x866B
#define GL_MAP1_VERTEX_ATTRIB12_4_NV                            0x866C
#define GL_MAP1_VERTEX_ATTRIB13_4_NV                            0x866D
#define GL_MAP1_VERTEX_ATTRIB14_4_NV                            0x866E
#define GL_MAP1_VERTEX_ATTRIB15_4_NV                            0x866F
#define GL_MAP2_VERTEX_ATTRIB0_4_NV                             0x8670
#define GL_MAP2_VERTEX_ATTRIB1_4_NV                             0x8671
#define GL_MAP2_VERTEX_ATTRIB2_4_NV                             0x8672
#define GL_MAP2_VERTEX_ATTRIB3_4_NV                             0x8673
#define GL_MAP2_VERTEX_ATTRIB4_4_NV                             0x8674
#define GL_MAP2_VERTEX_ATTRIB5_4_NV                             0x8675
#define GL_MAP2_VERTEX_ATTRIB6_4_NV                             0x8676
#define GL_MAP2_VERTEX_ATTRIB7_4_NV                             0x8677
#define GL_MAP2_VERTEX_ATTRIB8_4_NV                             0x8678
#define GL_MAP2_VERTEX_ATTRIB9_4_NV                             0x8679
#define GL_MAP2_VERTEX_ATTRIB10_4_NV                            0x867A
#define GL_MAP2_VERTEX_ATTRIB11_4_NV                            0x867B
#define GL_MAP2_VERTEX_ATTRIB12_4_NV                            0x867C
#define GL_MAP2_VERTEX_ATTRIB13_4_NV                            0x867D
#define GL_MAP2_VERTEX_ATTRIB14_4_NV                            0x867E
#define GL_MAP2_VERTEX_ATTRIB15_4_NV                            0x867F

typedef void (APIENTRY * glBindProgramNVPROC) (GLenum target, GLuint id);
typedef void (APIENTRY * glDeleteProgramsNVPROC) (GLsizei n, const GLuint *ids);
typedef void (APIENTRY * glExecuteProgramNVPROC) (GLenum target, GLuint id, const GLfloat *params);
typedef void (APIENTRY * glGenProgramsNVPROC) (GLsizei n, GLuint *ids);
typedef GLboolean (APIENTRY * glAreProgramsResidentNVPROC) (GLsizei n, const GLuint *ids, GLboolean *residences);
typedef void (APIENTRY * glRequestResidentProgramsNVPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRY * glGetProgramParameterfvNVPROC) (GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetProgramParameterdvNVPROC) (GLenum target, GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRY * glGetProgramivNVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetProgramStringNVPROC) (GLuint id, GLenum pname, GLubyte *program);
typedef void (APIENTRY * glGetTrackMatrixivNVPROC) (GLenum target, GLuint address, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetVertexAttribdvNVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRY * glGetVertexAttribfvNVPROC) (GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * glGetVertexAttribivNVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRY * glGetVertexAttribPointervNVPROC) (GLuint index, GLenum pname, GLvoid **pointer);
typedef GLboolean (APIENTRY * glIsProgramNVPROC) (GLuint id);
typedef void (APIENTRY * glLoadProgramNVPROC) (GLenum target, GLuint id, GLsizei len, const GLubyte *program);
typedef void (APIENTRY * glProgramParameter4fNVPROC) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glProgramParameter4dNVPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glProgramParameter4dvNVPROC) (GLenum target, GLuint index, const GLdouble *params);
typedef void (APIENTRY * glProgramParameter4fvNVPROC) (GLenum target, GLuint index, const GLfloat *params);
typedef void (APIENTRY * glProgramParameters4dvNVPROC) (GLenum target, GLuint index, GLuint num, const GLdouble *params);
typedef void (APIENTRY * glProgramParameters4fvNVPROC) (GLenum target, GLuint index, GLuint num, const GLfloat *params);
typedef void (APIENTRY * glTrackMatrixNVPROC) (GLenum target, GLuint address, GLenum matrix, GLenum transform);
typedef void (APIENTRY * glVertexAttribPointerNVPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * glVertexAttrib1sNVPROC) (GLuint index, GLshort x);
typedef void (APIENTRY * glVertexAttrib1fNVPROC) (GLuint index, GLfloat x);
typedef void (APIENTRY * glVertexAttrib1dNVPROC) (GLuint index, GLdouble x);
typedef void (APIENTRY * glVertexAttrib2sNVPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRY * glVertexAttrib2fNVPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRY * glVertexAttrib2dNVPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRY * glVertexAttrib3sNVPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * glVertexAttrib3fNVPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * glVertexAttrib3dNVPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * glVertexAttrib4sNVPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRY * glVertexAttrib4fNVPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * glVertexAttrib4dNVPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * glVertexAttrib4ubNVPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRY * glVertexAttrib1svNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib1fvNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib1dvNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib2svNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib2fvNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib2dvNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib3svNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib3fvNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib3dvNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib4svNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * glVertexAttrib4fvNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * glVertexAttrib4dvNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * glVertexAttrib4ubvNVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRY * glVertexAttribs1svNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * glVertexAttribs1fvNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * glVertexAttribs1dvNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * glVertexAttribs2svNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * glVertexAttribs2fvNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * glVertexAttribs2dvNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * glVertexAttribs3svNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * glVertexAttribs3fvNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * glVertexAttribs3dvNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * glVertexAttribs4svNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * glVertexAttribs4fvNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * glVertexAttribs4dvNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * glVertexAttribs4ubvNVPROC) (GLuint index, GLsizei n, const GLubyte *v);

extern GLEW_EXPORT glBindProgramNVPROC glBindProgramNV;
extern GLEW_EXPORT glDeleteProgramsNVPROC glDeleteProgramsNV;
extern GLEW_EXPORT glExecuteProgramNVPROC glExecuteProgramNV;
extern GLEW_EXPORT glGenProgramsNVPROC glGenProgramsNV;
extern GLEW_EXPORT glAreProgramsResidentNVPROC glAreProgramsResidentNV;
extern GLEW_EXPORT glRequestResidentProgramsNVPROC glRequestResidentProgramsNV;
extern GLEW_EXPORT glGetProgramParameterfvNVPROC glGetProgramParameterfvNV;
extern GLEW_EXPORT glGetProgramParameterdvNVPROC glGetProgramParameterdvNV;
extern GLEW_EXPORT glGetProgramivNVPROC glGetProgramivNV;
extern GLEW_EXPORT glGetProgramStringNVPROC glGetProgramStringNV;
extern GLEW_EXPORT glGetTrackMatrixivNVPROC glGetTrackMatrixivNV;
extern GLEW_EXPORT glGetVertexAttribdvNVPROC glGetVertexAttribdvNV;
extern GLEW_EXPORT glGetVertexAttribfvNVPROC glGetVertexAttribfvNV;
extern GLEW_EXPORT glGetVertexAttribivNVPROC glGetVertexAttribivNV;
extern GLEW_EXPORT glGetVertexAttribPointervNVPROC glGetVertexAttribPointervNV;
extern GLEW_EXPORT glIsProgramNVPROC glIsProgramNV;
extern GLEW_EXPORT glLoadProgramNVPROC glLoadProgramNV;
extern GLEW_EXPORT glProgramParameter4fNVPROC glProgramParameter4fNV;
extern GLEW_EXPORT glProgramParameter4dNVPROC glProgramParameter4dNV;
extern GLEW_EXPORT glProgramParameter4dvNVPROC glProgramParameter4dvNV;
extern GLEW_EXPORT glProgramParameter4fvNVPROC glProgramParameter4fvNV;
extern GLEW_EXPORT glProgramParameters4dvNVPROC glProgramParameters4dvNV;
extern GLEW_EXPORT glProgramParameters4fvNVPROC glProgramParameters4fvNV;
extern GLEW_EXPORT glTrackMatrixNVPROC glTrackMatrixNV;
extern GLEW_EXPORT glVertexAttribPointerNVPROC glVertexAttribPointerNV;
extern GLEW_EXPORT glVertexAttrib1sNVPROC glVertexAttrib1sNV;
extern GLEW_EXPORT glVertexAttrib1fNVPROC glVertexAttrib1fNV;
extern GLEW_EXPORT glVertexAttrib1dNVPROC glVertexAttrib1dNV;
extern GLEW_EXPORT glVertexAttrib2sNVPROC glVertexAttrib2sNV;
extern GLEW_EXPORT glVertexAttrib2fNVPROC glVertexAttrib2fNV;
extern GLEW_EXPORT glVertexAttrib2dNVPROC glVertexAttrib2dNV;
extern GLEW_EXPORT glVertexAttrib3sNVPROC glVertexAttrib3sNV;
extern GLEW_EXPORT glVertexAttrib3fNVPROC glVertexAttrib3fNV;
extern GLEW_EXPORT glVertexAttrib3dNVPROC glVertexAttrib3dNV;
extern GLEW_EXPORT glVertexAttrib4sNVPROC glVertexAttrib4sNV;
extern GLEW_EXPORT glVertexAttrib4fNVPROC glVertexAttrib4fNV;
extern GLEW_EXPORT glVertexAttrib4dNVPROC glVertexAttrib4dNV;
extern GLEW_EXPORT glVertexAttrib4ubNVPROC glVertexAttrib4ubNV;
extern GLEW_EXPORT glVertexAttrib1svNVPROC glVertexAttrib1svNV;
extern GLEW_EXPORT glVertexAttrib1fvNVPROC glVertexAttrib1fvNV;
extern GLEW_EXPORT glVertexAttrib1dvNVPROC glVertexAttrib1dvNV;
extern GLEW_EXPORT glVertexAttrib2svNVPROC glVertexAttrib2svNV;
extern GLEW_EXPORT glVertexAttrib2fvNVPROC glVertexAttrib2fvNV;
extern GLEW_EXPORT glVertexAttrib2dvNVPROC glVertexAttrib2dvNV;
extern GLEW_EXPORT glVertexAttrib3svNVPROC glVertexAttrib3svNV;
extern GLEW_EXPORT glVertexAttrib3fvNVPROC glVertexAttrib3fvNV;
extern GLEW_EXPORT glVertexAttrib3dvNVPROC glVertexAttrib3dvNV;
extern GLEW_EXPORT glVertexAttrib4svNVPROC glVertexAttrib4svNV;
extern GLEW_EXPORT glVertexAttrib4fvNVPROC glVertexAttrib4fvNV;
extern GLEW_EXPORT glVertexAttrib4dvNVPROC glVertexAttrib4dvNV;
extern GLEW_EXPORT glVertexAttrib4ubvNVPROC glVertexAttrib4ubvNV;
extern GLEW_EXPORT glVertexAttribs1svNVPROC glVertexAttribs1svNV;
extern GLEW_EXPORT glVertexAttribs1fvNVPROC glVertexAttribs1fvNV;
extern GLEW_EXPORT glVertexAttribs1dvNVPROC glVertexAttribs1dvNV;
extern GLEW_EXPORT glVertexAttribs2svNVPROC glVertexAttribs2svNV;
extern GLEW_EXPORT glVertexAttribs2fvNVPROC glVertexAttribs2fvNV;
extern GLEW_EXPORT glVertexAttribs2dvNVPROC glVertexAttribs2dvNV;
extern GLEW_EXPORT glVertexAttribs3svNVPROC glVertexAttribs3svNV;
extern GLEW_EXPORT glVertexAttribs3fvNVPROC glVertexAttribs3fvNV;
extern GLEW_EXPORT glVertexAttribs3dvNVPROC glVertexAttribs3dvNV;
extern GLEW_EXPORT glVertexAttribs4svNVPROC glVertexAttribs4svNV;
extern GLEW_EXPORT glVertexAttribs4fvNVPROC glVertexAttribs4fvNV;
extern GLEW_EXPORT glVertexAttribs4dvNVPROC glVertexAttribs4dvNV;
extern GLEW_EXPORT glVertexAttribs4ubvNVPROC glVertexAttribs4ubvNV;

#endif /* GL_NV_vertex_program */

/* ------------------------- NV_vertex_program1_1 ------------------------- */

/* -------------------------- NV_vertex_program2 -------------------------- */

/* ------------------------------------------------------------------------ */

struct GLEW
{
  unsigned int GL_11 : 1;
  unsigned int GL_12 : 1;
  unsigned int GL_13 : 1;
  unsigned int GL_14 : 1;

  unsigned int ARB_depth_texture : 1;
  unsigned int ARB_fragment_program : 1;
  unsigned int ARB_imaging : 1;
  unsigned int ARB_matrix_palette : 1;
  unsigned int ARB_multisample : 1;
  unsigned int ARB_multitexture : 1;
  unsigned int ARB_point_parameters : 1;
  unsigned int ARB_shadow : 1;
  unsigned int ARB_shadow_ambient : 1;
  unsigned int ARB_texture_border_clamp : 1;
  unsigned int ARB_texture_compression : 1;
  unsigned int ARB_texture_cube_map : 1;
  unsigned int ARB_texture_env_add : 1;
  unsigned int ARB_texture_env_combine : 1;
  unsigned int ARB_texture_env_crossbar : 1;
  unsigned int ARB_texture_env_dot3 : 1;
  unsigned int ARB_texture_mirrored_repeat : 1;
  unsigned int ARB_transpose_matrix : 1;
  unsigned int ARB_vertex_blend : 1;
  unsigned int ARB_vertex_program : 1;
  unsigned int ARB_window_pos : 1;

  unsigned int EXT_abgr : 1;
  unsigned int EXT_bgra : 1;
  unsigned int EXT_blend_color : 1;
  unsigned int EXT_blend_minmax : 1;
  unsigned int EXT_blend_subtract : 1;
  unsigned int EXT_blend_func_separate : 1;
  unsigned int EXT_clip_volume_hint : 1;
  unsigned int EXT_compiled_vertex_array : 1;
  unsigned int EXT_cull_vertex : 1;
  unsigned int EXT_draw_range_elements : 1;
  unsigned int EXT_fog_coord : 1;
  unsigned int EXT_multi_draw_arrays : 1;
  unsigned int EXT_packed_pixels : 1;
  unsigned int EXT_point_parameters : 1;
  unsigned int EXT_secondary_color : 1;
  unsigned int EXT_separate_specular_color : 1;
  unsigned int EXT_shadow_funcs : 1;
  unsigned int EXT_stencil_two_side : 1;
  unsigned int EXT_stencil_wrap : 1;
  unsigned int EXT_texture_compression_s3tc : 1;
  unsigned int EXT_texture_env_combine : 1;
  unsigned int EXT_texture_filter_anisotropic : 1;
  unsigned int EXT_texture_lod_bias : 1;
  unsigned int EXT_texture_rectangle : 1;
  unsigned int EXT_vertex_shader : 1;
  unsigned int EXT_vertex_weighting : 1;

  unsigned int SGIS_generate_mipmap : 1;
  unsigned int SGIS_texture_lod : 1;
  unsigned int SGIX_depth_texture : 1;
  unsigned int SGIX_shadow : 1;

  unsigned int HP_occlusion_test : 1;
  unsigned int S3_s3tc : 1;
  unsigned int WIN_swap_hint : 1;

  unsigned int ATI_draw_buffers : 1;
  unsigned int ATI_element_array : 1;
  unsigned int ATI_envmap_bumpmap : 1;
  unsigned int ATI_fragment_shader : 1;
  unsigned int ATI_map_object_buffer : 1;
  unsigned int ATI_mapped_texture : 1;
  unsigned int ATI_pn_triangles : 1;
  unsigned int ATI_point_cull_mode : 1;
  unsigned int ATI_separate_stencil : 1;
  unsigned int ATI_text_fragment_shader : 1;
  unsigned int ATI_texture_float : 1;
  unsigned int ATI_texture_mirror_once : 1;
  unsigned int ATI_timestamp : 1;
  unsigned int ATI_vertex_array_object : 1;
  unsigned int ATI_vertex_attrib_array_object : 1;
  unsigned int ATI_vertex_streams : 1;
  unsigned int ATIX_point_sprites : 1;
  unsigned int ATIX_texture_env_combine3 : 1;
  unsigned int ATIX_texture_env_route : 1;
  unsigned int ATIX_vertex_shader_output_point_size : 1;

  unsigned int NV_blend_square : 1;
  unsigned int NV_copy_depth_to_color : 1;
  unsigned int NV_depth_clamp : 1;
  unsigned int NV_element_array : 1;
  unsigned int NV_evaluators : 1;
  unsigned int NV_fence : 1;
  unsigned int NV_float_buffer : 1;
  unsigned int NV_fog_distance : 1;
  unsigned int NV_fragment_program : 1;
  unsigned int NV_light_max_exponent : 1;
  unsigned int NV_multisample_filter_hint : 1;
  unsigned int NV_occlusion_query : 1;
  unsigned int NV_packed_depth_stencil : 1;
  unsigned int NV_pixel_data_range : 1;
  unsigned int NV_primitive_restart : 1;
  unsigned int NV_point_sprite : 1;
  unsigned int NV_register_combiners : 1;
  unsigned int NV_register_combiners2 : 1;
  unsigned int NV_texgen_reflection : 1;
  unsigned int NV_texture_compression_vtc : 1;
  unsigned int NV_texture_env_combine4 : 1;
  unsigned int NV_texture_rectangle : 1;
  unsigned int NV_texture_shader : 1;
  unsigned int NV_texture_shader2 : 1;
  unsigned int NV_texture_shader3 : 1;
  unsigned int NV_vertex_array_range : 1;
  unsigned int NV_vertex_array_range2 : 1;
  unsigned int NV_vertex_program : 1;
  unsigned int NV_vertex_program1_1 : 1;
  unsigned int NV_vertex_program2 : 1;
};

/* error codes */
#define GLEW_OK                         0
#define GLEW_ERROR_NO_GL_VERSION        1  /* missing GL version */
#define GLEW_ERROR_NO_EXTENSIONS_STRING 2  /* missing {ARB,EXT}_extensions_string */
#define GLEW_ERROR_GL_VERSION_10_ONLY   3  /* GL 1.1 and up are not supported */
#define GLEW_ERROR_GLX_VERSION_11_ONLY  4  /* GLX 1.2 and up are not supported */

extern GLEW_EXPORT struct GLEW glew;
extern GLEW_EXPORT GLboolean glewExperimental;
extern GLEW_EXPORT GLint glewInit ();
extern GLEW_EXPORT const char* glewGetErrorString (GLint error);

#ifdef __cplusplus
}
#endif

#ifdef GLEW_APIENTRY_DEFINED
#undef GLEW_APIENTRY_DEFINED
#undef APIENTRY
#endif

#ifdef GLEW_WINGDIAPI_DEFINED
#undef GLEW_WINGDIAPI_DEFINED
#undef WINGDIAPI
#endif

#undef GLEW_EXPORT

//#endif /* __glew_h__ */
