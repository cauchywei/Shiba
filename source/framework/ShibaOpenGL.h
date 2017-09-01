//
// Created by cauchywei on 2017/8/20.
//

#ifndef SHIBA_SHIBAOPENGL_H
#define SHIBA_SHIBAOPENGL_H

//#include <SFML/OpenGL.hpp>
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif


void _check_gl_error(const char *file, int line);

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)


#endif //SHIBA_SHIBAOPENGL_H
