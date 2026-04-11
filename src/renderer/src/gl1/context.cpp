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

#include "renderer/gl1.h"
#include "common/assert.h"
#include <glad/glad.h>

#ifdef PARANOID
#define CHECK_ERROR()                                                          \
    if (u32 error{glGetError()}; error != GL_NO_ERROR) {                       \
        PANIC("{}", getErrorMsg(error));                                       \
    }
#else
#define CHECK_ERROR()
#endif

static const char* getErrorMsg(u32 error_code) {
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
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
    );
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

GLContext::GLContext(SDL_Window* window) {
    setGLAttributes();
    ctx = SDL_GL_CreateContext(window);
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

void GLContext::begin(u32 mode) {
    glBegin(mode);
}

void GLContext::bindTexture(u32 target, u32 texture) {
    glBindTexture(target, texture);
    CHECK_ERROR();
}

void GLContext::color4f(float red, float green, float blue, float alpha) {
    glColor4f(red, green, blue, alpha);
}

void GLContext::enable(u32 cap) {
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

void GLContext::matrixMode(u32 mode) {
    glMatrixMode(mode);
    CHECK_ERROR();
}

void GLContext::ortho(
    double left,
    double right,
    double bottom,
    double top,
    double zNear,
    double zFar
) {
    glOrtho(left, right, bottom, top, zNear, zFar);
    CHECK_ERROR();
}

void GLContext::texCoord2f(float s, float t) {
    glTexCoord2f(s, t);
}

void GLContext::texImage2D(
    u32 target,
    i32 level,
    i32 internal_format,
    i32 width,
    i32 height,
    i32 border,
    u32 format,
    u32 type,
    const void* pixels
) {
    glTexImage2D(target, level, internal_format,
        width, height, border, format, type, pixels
    );
    CHECK_ERROR();
}

void GLContext::texParameterf(u32 target, u32 pname, float param) {
    glTexParameterf(target, pname, param);
    CHECK_ERROR();
}

void GLContext::vertex2f(float x, float y) {
    glVertex2f(x, y);
}

void GLContext::viewport(i32 x, i32 y, i32 width, i32 height) {
    glViewport(x, y, width, height);
    CHECK_ERROR();
}
