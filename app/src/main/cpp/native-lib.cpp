/*
 * File: native-lib.cpp
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

#include <jni.h>
#include <string>
#include "Image.h"

extern "C" JNIEXPORT jfloatArray JNICALL
Java_com_pokoidev_androidsobelapp_MainActivity_sobelled(
        JNIEnv * env,
        jobject /* this */, jfloatArray components, jint width, jint height)
{
    int size = width * height * 3;

    // Create the jni type for the return data
    jfloatArray result;
    result = env->NewFloatArray(size);

    // Convert the jni type collection to a C++ pointer
    float * colors = env->GetFloatArrayElements(components, 0);

    // Create the image with the given data
    Image image (width, height, colors);

    // Apply the sobel effect
    image.sobel_colour();

    // Extract the data from the sobelled image
    float * fill = new float [size];
    image.copy_colour_components(fill);

    // Copy the return data into the jni float array
    env->SetFloatArrayRegion(result, 0, size, fill);

    delete fill;
    return result;
}
