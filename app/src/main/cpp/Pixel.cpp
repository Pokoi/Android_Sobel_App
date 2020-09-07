/*
 * File: Pixel.cpp
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

#include "Pixel.h"

void Pixel::convert_luv_to_rgb()
{
    float Xr = 0.33f;
    float Yr = 0.33f;
    float Zr = 0.33f;
    float usr = 4 * Xr / (Xr + 15 * Yr + 2 * Zr);
    float vsr = 9 * Yr / (Xr + 15 * Yr + 3 * Zr);

    float u_ = luv_components.u / (13 * luv_components.l) + usr;
    float v_ = luv_components.v / (13 * luv_components.l) + vsr;
    float Y = pow(((luv_components.l + 16) / 116), 3);
    float X = (-9 * Y * u_) / (u_ - 4) * v_ - u_ * v_;
    float Z = (9 * Y - 15 * v_ * Y - v_ * X) / 3 * v_;

    float r = (3.063218f) * X + (-1.393325f) * Y + (-0.475802f) * Z;
    float g = (-0.969243f) * X + (1.875966f) * Y + (0.041555f) * Z;
    float b = (0.067871f) * X + (-0.228834f) * Y + (1.069251f) * Z;

    rgb_components.red = r < 0.f ? 0.f : r > 1.f ? 1.f : r;
    rgb_components.green = g < 0.f ? 0.f : g > 1.f ? 1.f : g;
    rgb_components.blue = b < 0.f ? 0.f : b > 1.f ? 1.f : b;
}

float Pixel::clamp(float value, float min, float max)
{
    return value < min ? min : value > max ? max : value;
}

void Pixel::convert_rgb_to_luv()
{
    if (rgb_components.red == 0 && rgb_components.green == 0 && rgb_components.blue == 0)
    {
        luv_components.l = luv_components.u = luv_components.v = 0.f;
    }

    else
    {
        float buffer[3];
        convert_rgb_to_xyz(buffer);
        convert_xyz_to_luv(buffer);
    }
}

void Pixel::convert_rgb_to_xyz(float* buffer)
{
    buffer[0] = (0.430574f) * rgb_components.red + (0.341550f) * rgb_components.green + (0.178325f) * rgb_components.blue;
    buffer[1] = (0.222015f) * rgb_components.red + (0.706655f) * rgb_components.green + (0.071330f) * rgb_components.blue;
    buffer[2] = (0.020183f) * rgb_components.red + (0.129553f) * rgb_components.green + (0.939180f) * rgb_components.blue;
}

void Pixel::convert_xyz_to_rgb(float* buffer)
{
    float r = (3.063218f) * buffer[0] + (-1.393325f) * buffer[1] + (-0.475802f) * buffer[2];
    float g = (-0.969243f) * buffer[0] + (1.875966f) * buffer[1] + (0.041555f) * buffer[2];
    float b = (0.067871f) * buffer[0] + (-0.228834f) * buffer[1] + (1.069251f) * buffer[2];

    rgb_components.red   = clamp(r, 0.f, 1.f);
    rgb_components.green = clamp(g, 0.f, 1.f);;
    rgb_components.blue  = clamp(b, 0.f, 1.f);;
}