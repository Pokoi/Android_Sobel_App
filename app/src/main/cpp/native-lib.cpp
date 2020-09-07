#include <jni.h>
#include <string>
#include "Image.h"


extern "C" JNIEXPORT jintArray JNICALL
Java_com_pokoidev_androidsobelapp_MainActivity_sobelled(
        JNIEnv *env,
        jobject /* this */, jintArray components, jint width, jint height)
{
    int size = width * height * 3;

    // Create the native java type for the return data
    jintArray result;
    result = (*env).NewIntArray(size);

    // Create the image with the given data
    Image image (width, height, reinterpret_cast<int *>(components));

    // Apply the sobel effect
    image.sobel_colour();

    // Extract the data from the sobelled image
    jint fill[size];
    for (int i = 0; i < image.get_pixels().size(); ++i)
    {
        fill[i] = image.get_pixel(i).rgb_components.red;
        fill[i] = image.get_pixel(i).rgb_components.green;
        fill[i] = image.get_pixel(i).rgb_components.blue;
    }

    (*env)->SetIntArrayRegion(env, result, 0, size, fill);
    return result;
}
