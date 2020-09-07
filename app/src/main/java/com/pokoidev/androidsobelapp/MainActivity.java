package com.pokoidev.androidsobelapp;

import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private static final int GALLERY_REQUEST_CODE = 123;
    private static final int PERMISSIONS_REQUEST_CODE = 1995;

    //Catched layout elements
    ImageView image_display;
    ImageView sobelled_display;
    Button load_button;
    Button sobel_button;
    Button export_button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        check_permisses();

        // Layout initialization
        {
            image_display = findViewById(R.id.image_display);
            load_button = findViewById(R.id.load_button);
            sobel_button = findViewById(R.id.sobel_button);
            export_button = findViewById(R.id.export_button);
        }

        // Onclick listeners
        {
            load_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Intent intent = new Intent();
                    intent.setType("image/*");
                    intent.setAction(Intent.ACTION_GET_CONTENT);
                    startActivityForResult(Intent.createChooser(intent, "Select an image to load"), GALLERY_REQUEST_CODE);
                }
            });

            sobel_button.setOnClickListener(new View.OnClickListener() {
                @RequiresApi(api = Build.VERSION_CODES.Q)
                @Override
                public void onClick(View v) {

                    image_display.invalidate();
                    Bitmap bitmap = ((BitmapDrawable) image_display.getDrawable()).getBitmap();

                    int width = bitmap.getWidth();
                    int height = bitmap.getHeight();

                    float[] components = extractDataFromBitmap(bitmap);
                    float[] sobelled = sobelled(components, width, height);

                    Bitmap bitmap_sobelled = constructBitmapFromArray(sobelled, width, height);
                    image_display.setImageBitmap(bitmap_sobelled);
                    image_display.invalidate();
                }
            });

            export_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {

                    image_display.invalidate();
                    Bitmap bitmap = ((BitmapDrawable) image_display.getDrawable()).getBitmap();
                    MediaStore.Images.Media.insertImage(getContentResolver(), bitmap, "Sobeled image", "");
                }
            });
        }
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        // When the image has been picked from the gallery.
        if(requestCode == GALLERY_REQUEST_CODE && resultCode == RESULT_OK && data != null)
        {
            Uri image = data.getData();
            image_display.setImageURI(image);
            image_display.invalidate();
        }
    }

    /**
     * @brief The native method for the transformations
     * @param components The colour components of the image to transform
     * @param width The width of the image
     * @param height The height of the image
     * @return The colour components of the sobelled image
     */
    public native float [] sobelled(float[] components, int width, int height);

    /**
     @brief Extract the pixel data from a Bitmap
     @param bitmap The bitmap with the info to extract
     @return A collection with all the values
     */
    public float[] extractDataFromBitmap(Bitmap bitmap)
    {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int size = width * height * 3 ;
        float [] components = new float [size];

        for(int i = 0, x = 0, y = 0; i < size; i+=3)
        {
            int color = bitmap.getPixel(x,y);

            components[i]   = Color.red(color) ;
            components[i+1] = Color.green(color);
            components[i+2] = Color.blue(color);

            ++x;
            if(x >= width)
            {
                x = 0;
                ++y;
            }
        }

        return components;
    }

    /**
     @brief Constructs a Bitmap from a collection of colour components
     @param components The colour components of the image
     @param width The bitmap width
     @param height The bitmap height
     @return The created bitmap
     */
    @RequiresApi(api = Build.VERSION_CODES.O)
    public Bitmap constructBitmapFromArray(float[] components, int width, int height)
    {
        // Create the bitmap
        Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        int size = width * height;

        // Assign the bitmap values
        for(int i = 0, x = 0, y = 0; i < size; ++i)
        {
            int color = (255 & 0xff) << 24 | ((int) (255 * (components[i * 3 ])) & 0xff) << 16 | ((int) (255 * (components[i * 3 + 1])) & 0xff) << 8 | ((int) (255 * (components[i*3+2])) & 0xff);
            bitmap.setPixel(x, y, color);

            ++x;
            if(x >= width)
            {
                x = 0;
                ++y;
            }
        }

        return bitmap;
    }

    /**
     @brief Check for the needed permisses
    */
    public void check_permisses()
    {
        String[] appPermisions = {Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE};

        List<String> listPermissionsNeeded = new ArrayList<>();

        for (String perm : appPermisions) {
            if (ContextCompat.checkSelfPermission(this, perm) != PackageManager.PERMISSION_GRANTED) {
                listPermissionsNeeded.add(perm);
            }
        }

        if (!listPermissionsNeeded.isEmpty()) {
            ActivityCompat.requestPermissions(this, listPermissionsNeeded.toArray(new String[listPermissionsNeeded.size()]), PERMISSIONS_REQUEST_CODE);
        }
    }

    
}
