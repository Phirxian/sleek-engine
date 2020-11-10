cmake_minimum_required(VERSION 3.0)
project(SleekThink)

SET(CMAKE_CXX_FLAGS_RELEASE "-O6 -ffast-math -Os")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -pg -fno-inline-functions -fno-inline ")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g2 -pg -fno-inline-functions -fno-inline")

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

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(TIFF REQUIRED)
find_package(JPEG REQUIRED)
find_package(Threads REQUIRED)
find_package(GLUT REQUIRED)

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

###############################################################################
################################ project app ##################################
###############################################################################

file(GLOB_RECURSE application  src/app/*.cpp src/app/*.c src/*.h)

add_executable(main-app src/app/main.cpp ${application})
target_include_directories(main-app PUBLIC src/app/)
target_include_directories(main-app PUBLIC src/sleek/)

target_link_libraries(
    main-app sleek-engine sleek-ext
    ${JPEG_LIBRARIES} ${PNG_LIBRARIES} ${TIFF_LIBRARIES}
    ${X11_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY}
    Threads::Threads -lstdc++fs -lXxf86vm -lzip
)
