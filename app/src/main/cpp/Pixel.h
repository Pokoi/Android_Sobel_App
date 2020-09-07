/*
 * File: Pixel.hpp
 * File Created: August 7th 2020
 * ––––––––––––––––––––––––
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * ––––––––––––––––––––––––
 * MIT License
 *
 * Copyright (c) 2020 Pokoidev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ANDROIDSOBELAPP_PIXEL_H
#define ANDROIDSOBELAPP_PIXEL_H

#include <math.h>
#include <algorithm>

class Pixel {
public:

    struct RGB
    {
        float red;
        float green;
        float blue;

        RGB()
                :
                red(0.f),
                green(0.f),
                blue(0.f)
        {}

        RGB(
                float r,
                float g,
                float b
        ) :
                red(r),
                green(g),
                blue(b)
        {}

        RGB(
                size_t r,
                size_t g,
                size_t b
        ) :
                red(((float)r) / 255.f),
                green(((float)g) / 255.f),
                blue(((float)b) / 255.f)
        {}

    } rgb_components;

    struct LUV
    {
        float l;
        float u;
        float v;

        LUV()
                :
                l(0.f),
                u(0.f),
                v(0.f)
        {}

        LUV(
                float l,
                float u,
                float v
        ) :
                l(l),
                u(u),
                v(v)
        {}

    } luv_components;

    Pixel()
    {}

    /**
    @brief Generates the luv components in base of rgb values
    */
    void convert_rgb_to_luv();

    /**
    @brief Converts the rgb componentes into a xyz color space. New values are stored in the given buffer
    @param buffer The buffer where store the converted values. Must have size 3 or greater.
    */
    void convert_rgb_to_xyz(float* buffer);


    /**
    @brief Converts the given xyz values into a rgb color space. New values are stored in the rgb_components field
    @param buffer The buffer where store the converted values. Must have size 3 or greater.
    */
    void convert_xyz_to_rgb(float* buffer);

    /**
    @brief Converts the given xyz values into a xyz protanopia simulation values. New values are stored in the given buffer
    @param buffer The buffer where store the converted values. Must have size 3 or greater.
    */
    void convert_xyz_to_luv(float* buffer);

    /**
    @brief Generates the rgb components in base of luv values
    */
    void convert_luv_to_rgb();

    /**
    @brief Clamps a value between 2 values
    @param value The vale to clamp
    @param min The min value
    @param max The max value
    */
    float clamp(float value, float min, float max);

};


#endif //ANDROIDSOBELAPP_PIXEL_H
