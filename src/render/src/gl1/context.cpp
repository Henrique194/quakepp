/*
 * Copyright (C) Henrique Barateli, <henriquejb194@gmail.com>, et al.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "render/gl1.h"
#include "common/assert.h"
#include <glad/glad.h>

#ifdef PARANOID
#define CHECK_ERROR()                                                          \
    if (GLenum error{glGetError()}; error != GL_NO_ERROR) {                    \
        PANIC("{}", getErrorMsg(error));                                       \
    }
#else
#define CHECK_ERROR()
#endif

static const char* getErrorMsg(GLenum error_code) {
    switch (error_code) {
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_STACK_OVERFLOW:
            return "Stack overflow";
        case GL_STACK_UNDERFLOW:
            return "Stack underflow";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        default:
            return "Unknown error";
    }
}

static void setGLAttributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

GLContext::GLContext(SDL_Window* sdl_window) {
    setGLAttributes();
    ctx = SDL_GL_CreateContext(sdl_window);
    if (!ctx) {
        PANIC("Couldn't create GL context: {}", SDL_GetError());
    }
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        PANIC("Couldn't load GL functions");
    }
}

GLContext::~GLContext() {
    SDL_GL_DeleteContext(ctx);
}

void GLContext::begin(GLenum mode) {
    glBegin(mode);
}

void GLContext::bindTexture(GLenum target, GLuint texture) {
    glBindTexture(target, texture);
    CHECK_ERROR();
}

void GLContext::color4f(
    GLfloat red,
    GLfloat green,
    GLfloat blue,
    GLfloat alpha
) {
    glColor4f(red, green, blue, alpha);
}

void GLContext::enable(GLenum cap) {
    glEnable(cap);
    CHECK_ERROR();
}

void GLContext::end() {
    glEnd();
    CHECK_ERROR();
}

void GLContext::loadIdentity() {
    glLoadIdentity();
    CHECK_ERROR();
}

void GLContext::matrixMode(GLenum mode) {
    glMatrixMode(mode);
    CHECK_ERROR();
}

void GLContext::ortho(
    GLdouble left,
    GLdouble right,
    GLdouble bottom,
    GLdouble top,
    GLdouble zNear,
    GLdouble zFar
) {
    glOrtho(left, right, bottom, top, zNear, zFar);
    CHECK_ERROR();
}

void GLContext::texCoord2f(GLfloat s, GLfloat t) {
    glTexCoord2f(s, t);
}

void GLContext::texImage2D(
    GLenum target,
    GLint level,
    GLint internal_format,
    GLsizei width,
    GLsizei height,
    GLint border,
    GLenum format,
    GLenum type,
    const void* pixels
) {
    glTexImage2D(target, level, internal_format,
        width, height, border, format, type, pixels);
    CHECK_ERROR();
}

void GLContext::texParameterf(GLenum target, GLenum pname, GLfloat param) {
    glTexParameterf(target, pname, param);
    CHECK_ERROR();
}

void GLContext::vertex2f(GLfloat x, GLfloat y) {
    glVertex2f(x, y);
}

void GLContext::viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
    CHECK_ERROR();
}
