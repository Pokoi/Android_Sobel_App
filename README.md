# Android_Sobel_App
An application for mobile devices to apply sobel effect to images

![alt text](https://github.com/Pokoi/Android_Sobel_App/blob/master/examples/original.jpeg "Original preview") 
![alt text](https://github.com/Pokoi/Android_Sobel_App/blob/master/examples/sobel.jpeg "Sobel preview")  


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

The project is developed in Android Studio environment using Java and C++ with the JNI connection. [Android Studio](https://developer.android.com/studio) must be installed to compile the project. Unity version used in the development process was 4.0.1.

The min sdk version to run the app in 26. 

No aditional libraries are needed.


### Installing

If you don`t have git in your machine you can follow the steps given in the [git site](https://git-scm.com/).  

Once you have git installed, you can download the repo by command line typing the following line:

```
git clone https://github.com/Pokoi/Android_Sobel_App.git
```

And that's it. No more steps are needed.


## Data model explanation

The C++ backend includes the following classes:    
:art: *Pixel*: A class with the color information of a pixel.    
:art: *Image*: The class that manages all the image creation and image transformation actions.   


## Supported features

:one: Load images from device gallery   
:two: Apply sobel filter to loaded image  
:three: See a preview of the applied filter  
:four: Save the image into the device gallery  


## Built With

:computer: [Android Studio](https://developer.android.com/studio) 

## Authors

* **Jesús Fermín Villar Ramírez `Pokoidev'** - *Project development* - [GitHub profile](https://github.com/Pokoi)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
