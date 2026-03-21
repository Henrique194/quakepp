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

static float gl_picmip = 0;
static float gl_max_size = 1024;
static int gl_solid_format = 3;
static int gl_alpha_format = 4;
static int gl_filter_min = GL_NEAREST;
static int gl_filter_max = GL_NEAREST;
static int texture_extension_number = 1;

static const u32 d_8to24table[256] = {
    4278190080, 4279176975, 4280229663, 4281282351, 4282335039, 4283124555,
    4284177243, 4285229931, 4286282619, 4287335307, 4288387995, 4289440683,
    4290493371, 4291546059, 4292598747, 4293651435, 4278651663, 4278914839,
    4278916895, 4279180071, 4279444271, 4279708471, 4279709503, 4279973707,
    4279974739, 4280238939, 4280240995, 4280243051, 4280244083, 4280508283,
    4280510339, 4280512399, 4279175947, 4279964435, 4280752923, 4281542439,
    4282330927, 4283119415, 4283907903, 4284958535, 4285747023, 4286536539,
    4287325027, 4288113515, 4288902003, 4289690491, 4290478979, 4291529611,
    4278190080, 4278191879, 4278192907, 4278194963, 4278197019, 4278199075,
    4278659883, 4278660911, 4278662967, 4278665023, 4278667079, 4278930251,
    4278932307, 4278934363, 4278936419, 4279200619, 4278190087, 4278190095,
    4278190103, 4278190111, 4278190119, 4278190127, 4278190135, 4278190143,
    4278190151, 4278190159, 4278190167, 4278190175, 4278190183, 4278190191,
    4278190199, 4278190207, 4278194963, 4278197019, 4278199075, 4278201135,
    4278202167, 4278204227, 4278664011, 4278666071, 4278667103, 4278930283,
    4279194487, 4279457667, 4279458699, 4279984023, 4280247203, 4280510383,
    4278653731, 4278916911, 4279181115, 4279444299, 4279708503, 4280233827,
    4280498035, 4281023359, 4281549711, 4281552799, 4281295791, 4281300927,
    4281044943, 4280789983, 4280273903, 4280022015, 4278191883, 4278194971,
    4279182123, 4279446327, 4279972679, 4280498003, 4281024355, 4281550703,
    4282340223, 4282867595, 4283657115, 4284447655, 4285237175, 4286288835,
    4287341523, 4288132067, 4288908203, 4288118687, 4287067027, 4286277515,
    4285487999, 4284699511, 4283911019, 4283121503, 4282595159, 4281806667,
    4281280323, 4280491831, 4279965483, 4279440163, 4278913815, 4278650639,
    4288639931, 4287589295, 4286799779, 4286011287, 4285222795, 4284435327,
    4283646835, 4283120491, 4282331999, 4281805651, 4281017159, 4280491835,
    4279965487, 4279440163, 4278913815, 4278650639, 4290495451, 4289180619,
    4288390079, 4287338415, 4286285731, 4285496215, 4284444551, 4283655035,
    4282865515, 4282075999, 4281548627, 4280759107, 4280232759, 4279705383,
    4279178011, 4278651663, 4286284655, 4285496167, 4284969823, 4284443479,
    4283917135, 4283390791, 4282864447, 4282338103, 4281811759, 4281285419,
    4280759075, 4280232735, 4279706391, 4279442191, 4278915851, 4278651655,
    4280022015, 4279754735, 4279487451, 4279220171, 4279216059, 4278949803,
    4278682523, 4278678411, 4278674299, 4278211435, 4278208347, 4278204235,
    4278201147, 4278198059, 4278193947, 4278191883, 4294901760, 4293856011,
    4292809491, 4291762971, 4290716451, 4289669931, 4288622383, 4287573807,
    4286525231, 4285476655, 4284428079, 4283378475, 4282327843, 4281277211,
    4280226579, 4279175947, 4278190123, 4278190139, 4278191947, 4278191967,
    4278194031, 4278654847, 4278656915, 4278921123, 4279186359, 4279978947,
    4281033679, 4282089435, 4283406307, 4284460007, 4286037999, 4287353847,
    4282088359, 4281834423, 4281844679, 4283950055, 4294950783, 4294961067,
    4294967255, 4278190183, 4278190219, 4278190259, 4278190295, 4278190335,
    4287886335, 4291295231, 4294967295, 5462943,
};

//
// Operates in place, quartering the size of the texture.
//
static void GL_MipMap(byte* in, int width, int height) {
    width <<= 2;
    height >>= 1;
    byte* out = in;
    for (int i = 0; i < height; i++, in += width) {
        for (int j = 0; j < width; j += 8, out += 4, in += 8) {
            out[0] = (in[0] + in[4] + in[width + 0] + in[width + 4]) >> 2;
            out[1] = (in[1] + in[5] + in[width + 1] + in[width + 5]) >> 2;
            out[2] = (in[2] + in[6] + in[width + 2] + in[width + 6]) >> 2;
            out[3] = (in[3] + in[7] + in[width + 3] + in[width + 7]) >> 2;
        }
    }
}

//
// Same as GL_Resample8BitTexture, but operates on RGBA pixels.
//
static void GL_ResampleTexture(
    const unsigned* in,
    int inwidth,
    int inheight,
    unsigned* out,
    int outwidth,
    int outheight
) {
    unsigned fracstep = inwidth * 0x10000 / outwidth;
    for (int i = 0; i < outheight; i++, out += outwidth) {
        const u32* inrow = in + inwidth * (i * inheight / outheight);
        u32 frac = fracstep >> 1;
        for (int j = 0; j < outwidth; j += 4) {
            out[j] = inrow[frac >> 16];
            frac += fracstep;
            out[j + 1] = inrow[frac >> 16];
            frac += fracstep;
            out[j + 2] = inrow[frac >> 16];
            frac += fracstep;
            out[j + 3] = inrow[frac >> 16];
            frac += fracstep;
        }
    }
}

static void GL_Upload32(
    const u32* data,
    int width,
    int height,
    bool mipmap,
    bool alpha
) {
    static u32 scaled[1024 * 512];

    int scaled_width = 1;
    int scaled_height = 1;
    while (scaled_width < width) {
        scaled_width <<= 1;
    }
    while (scaled_height < height) {
        scaled_height <<= 1;
    }
    scaled_width >>= (int) gl_picmip;
    scaled_height >>= (int) gl_picmip;
    if (scaled_width > (int) gl_max_size) {
        scaled_width = (int) gl_max_size;
    }
    if (scaled_height > (int) gl_max_size) {
        scaled_height = (int) gl_max_size;
    }
    if (scaled_width * scaled_height > sizeof(scaled) / 4) {
        PANIC("GL_LoadTexture: too big");
    }

    int samples = alpha ? gl_alpha_format : gl_solid_format;

    if (scaled_width == width && scaled_height == height) {
        if (!mipmap) {
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                samples,
                scaled_width,
                scaled_height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data
            );
            goto done;
        }
        memcpy(scaled, data, width * height * 4);
    } else {
        GL_ResampleTexture(
            data,
            width,
            height,
            scaled,
            scaled_width,
            scaled_height
        );
    }

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        samples,
        scaled_width,
        scaled_height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        scaled
    );
    if (mipmap) {
        int miplevel = 0;
        while (scaled_width > 1 || scaled_height > 1) {
            GL_MipMap((byte*) scaled, scaled_width, scaled_height);
            scaled_width >>= 1;
            scaled_height >>= 1;
            if (scaled_width < 1) {
                scaled_width = 1;
            }
            if (scaled_height < 1) {
                scaled_height = 1;
            }
            miplevel++;
            glTexImage2D(
                GL_TEXTURE_2D,
                miplevel,
                samples,
                scaled_width,
                scaled_height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                scaled
            );
        }
    }

done:

    if (mipmap) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter_min);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter_max);
    } else {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter_max);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter_max);
    }
}

static void GL_Upload8(const QPic* pic, bool mipmap, bool alpha) {
    static u32 trans[640 * 480]; // FIXME, temporary

    int s = pic->width * pic->height;
    if (alpha) {
        // If there are no transparent pixels, make it a
        // 3 component texture even if it was specified
        // as otherwise.
        bool has_alpha = false;
        for (int i = 0; i < s; i++) {
            int p = pic->data[i];
            if (p == 255) {
                has_alpha = true;
            }
            trans[i] = d_8to24table[p];
        }
        if (alpha && !has_alpha) {
            alpha = false;
        }
    } else {
        if (s & 3) {
            PANIC("GL_Upload8: s&3");
        }
        for (int i = 0; i < s; i += 4) {
            trans[i] = d_8to24table[pic->data[i]];
            trans[i + 1] = d_8to24table[pic->data[i + 1]];
            trans[i + 2] = d_8to24table[pic->data[i + 2]];
            trans[i + 3] = d_8to24table[pic->data[i + 3]];
        }
    }

    GL_Upload32(trans, pic->width, pic->height, mipmap, alpha);
}

int GL1Renderer::loadTexture(
    const char* identifier,
    const QPic* pic,
    bool mipmap,
    bool alpha
) {
    // see if the texture is already present.
    GLTexture* glt{findTexture(identifier, pic->width, pic->height)};
    if (glt) {
        return glt->texnum;
    }
    glt = &gltextures[numgltextures];
    numgltextures++;

    strcpy(glt->identifier, identifier);
    glt->texnum = texture_extension_number;
    glt->width = pic->width;
    glt->height = pic->height;
    glt->mipmap = mipmap;

    bindTexture(texture_extension_number);

    GL_Upload8(pic, mipmap, alpha);

    texture_extension_number++;

    return texture_extension_number - 1;
}

int GL1Renderer::loadPicTexture(QPic* pic) {
    return loadTexture("", pic, false, true);
}

void GL1Renderer::bindTexture(u32 tex) {
    if (current_tex == tex) {
        return;
    }
    current_tex = tex;
    glBindTexture(GL_TEXTURE_2D, (GLuint) tex);
}

GLTexture* GL1Renderer::findTexture(
    const char* identifier,
    int width,
    int height
) {
    if (!identifier[0]) {
        return nullptr;
    }
    for (int i = 0; i < numgltextures; i++) {
        const GLTexture* glt{&gltextures[i]};
        if (strcmp(identifier, glt->identifier)) {
            continue;
        }
        if (width != glt->width || height != glt->height) {
            PANIC("Cache Mismatch");
        }
        return &gltextures[i];
    }
    return nullptr;
}
