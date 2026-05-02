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

void GL1Renderer::uploadImage(Image* img, byte* data) {
    // FIXME: Replace this with std::vector!
    static u32 trans[640*480];
    i32 size{img->width * img->height};
    for (i32 i = 0; i < size; i++) {
        byte pix{data[i]};
        trans[i] = d_8to24table[pix];
    }
    bindImage(img);
    uploadImage32bit(img, trans);
}

void GL1Renderer::uploadImage32bit(Image* img, u32* data) {
    static u32 scaled[1024*512];
    i32 w{img->width};
    i32 h{img->height};
    i32 scaled_w;
    i32 scaled_h;
    getScaledSize(w, h, scaled_w, scaled_h);
    if (scaled_w * scaled_h > sizeof(scaled) / 4) {
        PANIC("too big");
    }
    bool mipmap{hasMipMap(img)};
    i32 format{getTexFormat(img, (byte*)data)};
    if (scaled_w == w && scaled_h == h) {
        // No resize needed.
        if (!mipmap) {
            uploadTex(0, format, w, h, data);
            setTexFilter(mipmap);
            return;
        }
        memcpy(scaled, data, w * h * 4);
    } else {
        // Resize needed.
        resampleTex(data, w, h, scaled, scaled_w, scaled_h);
    }
    uploadTex(0, format, scaled_w, scaled_h, scaled);
    if (mipmap) {
        genMipMaps(format, scaled_w, scaled_h, (byte*)scaled);
    }
    setTexFilter(mipmap);
}

void GL1Renderer::getScaledSize(i32 w, i32 h, i32& scaled_w, i32& scaled_h) const {
    scaled_w = 1;
    scaled_h = 1;
    while (scaled_w < w) {
        scaled_w <<= 1;
    }
    while (scaled_h < h) {
        scaled_h <<= 1;
    }
    scaled_w >>= (i32) gl_picmip;
    scaled_h >>= (i32) gl_picmip;
    if (scaled_w > (i32) gl_max_size) {
        scaled_w = (i32) gl_max_size;
    }
    if (scaled_h > (i32) gl_max_size) {
        scaled_h = (i32) gl_max_size;
    }
}


i32 GL1Renderer::getTexFormat(Image* img, const byte* data) const {
    // Scan the texture for any non-255 alpha.
    i32 c{img->width * img->height};
    data += 3;
    for (i32 i = 0; i < c; i++, data += 4) {
        if (*data != 255) {
            return alpha_format;
        }
    }
    return solid_format;
}

void GL1Renderer::setTexFilter(bool mipmap) {
    float max = filter_max;
    float min = (mipmap ? filter_min : filter_max);
    gl.texParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    gl.texParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
}

void GL1Renderer::resampleTex(
    const u32* in, i32 in_w, i32 in_h,
    u32* out, i32 out_w, i32 out_h
) {
    u32 frac_step = in_w * 0x10000 / out_w;
    for (i32 i = 0; i < out_h; i++, out += out_w) {
        const u32* in_row = in + in_w * (i * in_h / out_h);
        u32 frac = frac_step >> 1;
        for (i32 j = 0; j < out_w; j += 4) {
            out[j] = in_row[frac >> 16];
            frac += frac_step;
            out[j + 1] = in_row[frac >> 16];
            frac += frac_step;
            out[j + 2] = in_row[frac >> 16];
            frac += frac_step;
            out[j + 3] = in_row[frac >> 16];
            frac += frac_step;
        }
    }
}

void GL1Renderer::uploadTex(i32 level, i32 format, i32 w, i32 h, const void* data) {
    gl.texImage2D(GL_TEXTURE_2D, level, format, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}


void GL1Renderer::genMipMaps(i32 format, i32 w, i32 h, byte* data) {
    i32 mip_level{0};
    while (w > 1 || h > 1) {
        genMipMap(w, h, data);
        w >>= 1;
        h >>= 1;
        if (w < 1) {
            w = 1;
        }
        if (h < 1) {
            h = 1;
        }
        mip_level++;
        uploadTex(mip_level, format, w, h, data);
    }
}

void GL1Renderer::genMipMap(i32 w, i32 h, byte* in) {
    w <<= 2;
    h >>= 1;
    byte* out = in;
    for (i32 i = 0; i < h; i++, in += w) {
        for (i32 j = 0; j < w; j += 8, out += 4, in += 8) {
            out[0] = (in[0] + in[4] + in[w + 0] + in[w + 4]) >> 2;
            out[1] = (in[1] + in[5] + in[w + 1] + in[w + 5]) >> 2;
            out[2] = (in[2] + in[6] + in[w + 2] + in[w + 6]) >> 2;
            out[3] = (in[3] + in[7] + in[w + 3] + in[w + 7]) >> 2;
        }
    }
}
