#include <filesystem>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "ImagesManager.h"

using namespace cv;
int main()
{
  ImagesManager imagesManager("/Users/octavian/Octavian/MagnifyingDevices/data/");
  
    std::string image_path = samples::findFile("/Users/octavian/Octavian/MagnifyingDevices/data/lena.png");
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("/Users/octavian/Octavian/MagnifyingDevices/data/out.png", img);
    }
    return 0;
}
