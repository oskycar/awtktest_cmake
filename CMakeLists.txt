cmake_minimum_required(VERSION 3.12)
project(awtktest_cmake)

set(CMAKE_CXX_STANDARD 11)

#程序中用到的RES_ROOT宏定义
add_definitions(-DRES_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/../awtk.git/demos")

#设置awtk库根路径，后面设置头文件搜索路径会用到
set(TK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../awtk.git")

add_executable(awtktest_cmake main.cpp)

#配置sdl库
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(awtktest_cmake ${SDL2_LIBRARIES})


#配置APPLE平台库

#查找framework库，找到后会定义名称FRAMEWORK_${fwname}
macro(FIND_OSX_FRAMEWORK fwname)
    find_library(FRAMEWORK_${fwname}
            NAMES ${fwname}
            PATHS ${CMAKE_OSX_SYSROOT}/System/Library
            PATH_SUFFIXES Frameworks
            NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(FIND_OSX_FRAMEWORK)

if(APPLE)
    FIND_OSX_FRAMEWORK(Cocoa)
    FIND_OSX_FRAMEWORK(QuartzCore)
    FIND_OSX_FRAMEWORK(OpenGL)
    FIND_OSX_FRAMEWORK(Metal)
    FIND_OSX_FRAMEWORK(MetalKit)

    set(depend_apple_libs
            ${depend_apple_libs}
            ${FRAMEWORK_Cocoa}
            ${FRAMEWORK_QuartzCore}
            ${FRAMEWORK_OpenGL}
            ${FRAMEWORK_Metal}
            ${FRAMEWORK_MetalKit}
            )
    target_link_libraries(awtktest_cmake ${depend_apple_libs})
endif(APPLE)

target_include_directories(awtktest_cmake
        PRIVATE
         ${TK_ROOT}
         ${TK_ROOT}/src
         ${TK_ROOT}/3rd
         ${TK_ROOT}/src/ext_widgets
         ${TK_ROOT}/3rd/pixman
         ${TK_ROOT}/3rd/pixman/pixman
         ${TK_ROOT}/3rd/cairo/cairo
         ${TK_ROOT}/3rd/bgfx/bgfx/include
         ${TK_ROOT}/3rd/bgfx/bx/include
         ${TK_ROOT}/3rd/bgfx/bimg/include
         ${TK_ROOT}/3rd/agge
         ${TK_ROOT}/3rd/agg/include
         ${TK_ROOT}/3rd/nanovg
         ${TK_ROOT}/3rd/nanovg/gl
         ${TK_ROOT}/3rd/nanovg/base
         ${TK_ROOT}/3rd/nanovg/agge
         ${TK_ROOT}/3rd/nanovg/bgfx
         ${TK_ROOT}/3rd/SDL/src
         ${TK_ROOT}/3rd/SDL/include
         ${TK_ROOT}/3rd/agge/src
         ${TK_ROOT}/3rd/agge/include
         ${TK_ROOT}/3rd/gpinyin/include
         ${TK_ROOT}/3rd/libunibreak
         ${TK_ROOT}/tools)




#配置awtk编译出来的静态库
set(AWTK_LIB_PATH "${TK_ROOT}/lib")

add_library(libassets STATIC IMPORTED)
set_target_properties(libassets PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libassets.a)

add_library(libawtk STATIC IMPORTED)
set_target_properties(libawtk PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libawtk.a)

add_library(libcommon STATIC IMPORTED)
set_target_properties(libcommon PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libcommon.a)

add_library(libfont_gen STATIC IMPORTED)
set_target_properties(libfont_gen PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libfont_gen.a)

add_library(libglad STATIC IMPORTED)
set_target_properties(libglad PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libglad.a)

add_library(libgpinyin STATIC IMPORTED)
set_target_properties(libgpinyin PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libgpinyin.a)

add_library(libimage_gen STATIC IMPORTED)
set_target_properties(libimage_gen PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libimage_gen.a)

add_library(liblinebreak STATIC IMPORTED)
set_target_properties(liblinebreak PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/liblinebreak.a)

add_library(libnanovg STATIC IMPORTED)
set_target_properties(libnanovg PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libnanovg.a)

add_library(libstr_gen STATIC IMPORTED)
set_target_properties(libstr_gen PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libstr_gen.a)

add_library(libtheme_gen STATIC IMPORTED)
set_target_properties(libtheme_gen PROPERTIES IMPORTED_LOCATION ${AWTK_LIB_PATH}/libtheme_gen.a)

target_link_libraries(awtktest_cmake
        libassets
        libawtk
        libcommon
        libfont_gen
        libglad
        libgpinyin
        libimage_gen
        liblinebreak
        libnanovg
        libstr_gen
        libtheme_gen  )



