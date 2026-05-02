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

#include "gl1.h"
#include "common/assert.h"
#include "fs/fs.h"
#include <SDL_stdinc.h>

Image* GL1Renderer::findImage(const char* name, ImageType type) {
    // FIXME: Replace linear search with hashmaps!
    for (auto& image : images) {
        if (!SDL_strcmp(image.name, name)) {
            image.reg_seq = reg_seq;
            return &image;
        }
    }
    return loadImage(name, type);
}

Image* GL1Renderer::loadImage(const char* name, ImageType type) {
    images.push_back(Image{});
    Image* img{&images.back()};

    // FIXME: switch to std::string!
    if (SDL_strlen(name) > sizeof(img->name)) {
        PANIC("Image name \"{}\" is too long", name);
    }
    auto qpic{file_sys->loadPicture(name)};
    if (!qpic) {
        PANIC("Failed to load image \"{}\"", name);
    }
    SDL_strlcpy(img->name, name, MAX_QPATH);
    img->width = qpic->width;
    img->height = qpic->height;
    img->type = type;
    img->reg_seq = reg_seq;
    gl.genTextures(1, &img->tex_num);
    img->sl = 0;
    img->sh = 1;
    img->tl = 0;
    img->th = 1;

    uploadImage(img, qpic->pixels.data());

    return img;
}

void GL1Renderer::bindImage(Image* img) {
    if (current_tex == img->tex_num) {
        return;
    }
    current_tex = img->tex_num;
    gl.bindTexture(GL_TEXTURE_2D, img->tex_num);
}

bool GL1Renderer::hasMipMap(Image* img) {
    switch (img->type) {
        case ImageType::Pic:
        case ImageType::Sky:
            return false;
        default:
            return true;
    }
}
