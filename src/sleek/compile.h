#if defined __linux
    //#define x11_device_support
#elif defined WIN32 || WIN64
    #include <windows.h>
    #include <stdio.h>
    #include <time.h>
    //#define win_device_support
    //! maybe never
    //! #define d3d_context_support
#endif

//! globally managed by cmake
//#define sdl_device_support
//#define sdl2_device_support
//#define gtk3_device_support
//#define glfw3_device_support

#define gui_support

#define std_filesystem_support
#define mem_filesystem_support
//#define zip_filesystem_support

#define mesh_loader_3ds_support
#define mesh_loader_txt_support
#define mesh_loader_obj_support

//! need external loader
//#define texture_loader_png_support
//#define texture_loader_jpeg_support
//#define texture_loader_tiff_support
#define texture_loader_bmp_support
#define texture_loader_pgm_support
#define texture_loader_tga_support
#define texture_loader_blp_support
#define texture_loader_pcx_support
//#define video_reader_support
//#define video_reader_audio_support

#define reserved_texture 4
#define gui_frame_userdata 2
#define shader_userdata 4
#define material_userdata 4
