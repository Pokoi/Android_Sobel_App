/*
 * File: Image.cpp
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

#include "Image.h"
#include <math.h>


Image::Image(
                std::uint16_t width,
                std::uint16_t height,
                int components []
            ) :
                width(width),
                height(height),
                pixels(width* height)
{
    for(int i = 0, component_iterator = 0; i < pixels.size(); ++i)
    {
         pixels[i].rgb_components.red   = components[component_iterator];
         pixels[i].rgb_components.green = components[++component_iterator];
         pixels[i].rgb_components.blue  = components[++component_iterator];
    }
}

Pixel& Image::get_pixel(uint16_t index)
{
    return pixels[index];
}

Pixel& Image::get_pixel(uint16_t x, uint16_t y)
{
    return pixels[y * width + x];
}

void Image::set_pixel(uint16_t x, uint16_t y, Pixel& pixel)
{
    pixels[y * width + x] = pixel;
}

void Image::sobel_colour()
{
    int end = width * height;
    int iterator = 0;

    // set the start in the second row and the end in the previous of the last row
    // This avoid extra conditional operations and the lost of information is not relevant
    iterator += width + 1;
    end -= (width + 1);

    std::vector<float> buffer(width * height);

    float min = 1.f;
    float max = 0.f;


    while (iterator < end)
    {
        float horizontal_edge   = colour_difference(pixels[iterator - 1], pixels[iterator + 1]);
        float diagonal_1_edge   = colour_difference(pixels[iterator - width - 1], pixels[iterator + width + 1]);
        float diagonal_2_edge   = colour_difference(pixels[iterator - width + 1], pixels[iterator + width - 1]);
        float vertical_edge     = colour_difference(pixels[iterator - width], pixels[iterator + width]);


        float val = horizontal_edge + diagonal_1_edge + diagonal_2_edge + vertical_edge;
        if (val != 0)
        {
            int i = 0;
        }
        buffer[iterator] = val;

        max = val > max ? val : max;
        min = val < min ? val : min;

        ++iterator;
    }

    iterator = 0;

    while (iterator < buffer.size())
    {
        buffer[iterator] = ((buffer[iterator] - min) / max - min);

        pixels[iterator].rgb_components.red = 1.f - buffer[iterator];
        pixels[iterator].rgb_components.green = 1.f - buffer[iterator];
        pixels[iterator].rgb_components.blue = 1.f - buffer[iterator];

        ++iterator;
    }
}

float Image::colour_difference(Pixel& first, Pixel& second)
{
    first.convert_rgb_to_luv();
    second.convert_rgb_to_luv();

    return
            pow(second.luv_components.l - first.luv_components.l, 2.f) +
            pow(second.luv_components.u - first.luv_components.u, 2.f) +
            pow(second.luv_components.v - first.luv_components.v, 2.f);

}


