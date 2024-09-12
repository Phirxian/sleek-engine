cmake_minimum_required(VERSION 3.5)
project(SleekThink)

SET(CMAKE_CXX_FLAGS_RELEASE "-O6 -ffast-math -Os")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -pg -fno-inline-functions -fno-inline ")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g2 -pg -fno-inline-functions -fno-inline")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_USE_PTHREADS_INIT true)
set(CMAKE_USE_PTHREADS_INIT ON)

###############################################################################
################################ dependencies #################################
###############################################################################

if( NOT cmake_build_type_tolower STREQUAL "release" )
  add_definitions(-DDEBUG)
endif()

include(CheckCXXCompilerFlag)
if (NOT MSVC)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG(-std=c++0x COMPILER_SUPPORTS_CXX0X)
  if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
  endif()
endif()

string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
add_definitions("-DGL_GLEXT_LEGACY")
add_definitions("-DGLEW_STATICY")
add_definitions("-DGL3_PROTOTYPES")
add_definitions("-DGLX_GLXEXT_LEGACY")
add_definitions("-DGLM_FORCE_PRECISION_MEDIUMP_FLOAT")
add_definitions("-DGLM_FORCE_PRECISION_MEDIUMP_DOUBLE")
add_definitions("-DGLM_FORCE_PRECISION_MEDIUMP_INT")
add_definitions("-DGLM_FORCE_PRECISION_MEDIUMP_UINT")

# Opengl
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

#devices
if (UNIX)
find_package(X11 REQUIRED)
endif (UNIX)

if (WIN32)
  add_definitions("-Dwin_device_support")
endif (WIN32)

find_package(SDL)
find_package(SDL2)
find_package(glfw3)

#images
find_package(PNG)
find_package(TIFF)
find_package(JPEG)


include_directories("src/app")
include_directories("src/sleek")
include_directories("src/library")

###############################################################################
################################ project ext ##################################
###############################################################################

file(GLOB_RECURSE sleek_ext src/library/*.cpp src/library/*.c src/*.h)
add_library(sleek-ext STATIC ${sleek_ext})

###############################################################################
################################ project lib ##################################
###############################################################################

file(GLOB_RECURSE sleek_engine src/sleek/*.cpp src/sleek/*.c src/*.h)

add_library(sleek-engine STATIC ${sleek_engine})
target_include_directories(sleek-engine PUBLIC ${PNG_INCLUDE_DIR})
target_include_directories(sleek-engine PUBLIC ${TIFF_INCLUDE_DIR})
target_include_directories(sleek-engine PUBLIC ${JPEG_INCLUDE_DIR})
target_include_directories(sleek-engine PUBLIC ${FREETYPE_INCLUDE_DIR_ft2build})

set(
  ALL_LIBS
  ${OPENGL_LIBRARY}
  ${GLUT_LIBRARY}
  ${GLEW_LIBRARY}
  freetype
  Threads::Threads
  -lstdc++fs -lzip
  -fopenmp
)

if(X11_FOUND)
  add_definitions("-Dx11_device_support")
  list(APPEND ALL_LIBS ${X11_LIBRARIES})
  list(APPEND ALL_LIBS -lXxf86vm)
endif(X11_FOUND)

if(SDL_FOUND)
  add_definitions("-Dsdl_device_support")
endif(SDL_FOUND)

if(SDL2_FOUND)
  add_definitions("-Dsdl2_device_support")
  list(APPEND ALL_LIBS ${SDL2_LIBRARIES})
endif(SDL2_FOUND)

if(glfw3_FOUND)
  add_definitions("-Dglfw3_device_support")
  list(APPEND ALL_LIBS glfw)
endif(glfw3_FOUND)

if(PNG_FOUND)
  add_definitions("-Dtexture_loader_png_support")
  list(APPEND ALL_LIBS ${PNG_LIBRARIES})
endif(TIFF_FOUND)

if(TIFF_FOUND)
  add_definitions("-Dtexture_loader_tiff_support")
  list(APPEND ALL_LIBS ${TIFF_LIBRARIES})
endif(TIFF_FOUND)

if(JPEG_FOUND)
  add_definitions("-Dtexture_loader_jpeg_support")
  list(APPEND ALL_LIBS ${JPEG_LIBRARIES})
endif(TIFF_FOUND)

###############################################################################
################################ project app ##################################
###############################################################################

file(GLOB example_dirs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/src/examples" "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/*")

foreach(example ${example_dirs})
    # Ensure we're dealing with a directory, not a file
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/${example}")
        # Collect all .cpp and .c files for this example
        file(GLOB_RECURSE example_sources 
            "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/${example}/*.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/${example}/*.c"
        )
        
        # Add the main.cpp file explicitly
        list(APPEND example_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/${example}/main.cpp")
        
        # Create the target name
        set(target_name "example_${example}")
        
        # Add the executable
        add_executable(${target_name} ${example_sources})
        
        # Add include directories
        target_include_directories(${target_name} PUBLIC 
            "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/${example}"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/sleek"
        )
        
        # Link libraries
        target_link_libraries(${target_name} PRIVATE sleek-engine sleek-ext ${ALL_LIBS})
    endif()
endforeach()