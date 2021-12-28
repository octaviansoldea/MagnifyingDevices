#include <filesystem>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Algorithms.h"
#include "ImagesManager.h"

using namespace cv;
using namespace std;

int main0()
{
  ImagesManager imagesManager;
  imagesManager.init("/Users/octavian/Octavian/MagnifyingDevices/data/");
  
    std::string image_path = samples::findFile("/Users/octavian/Octavian/MagnifyingDevices/data/lena.jpg");
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
        imwrite("/Users/octavian/Octavian/MagnifyingDevices/data/out.jpg", img);
    }
    return 0;
}

int main1()
{
  string strDirInput = fs::current_path() /= "../data/sceneBooks/video_split";
  
  Image image1(strDirInput + "/sceneBooks0001.jpg");
  if(image1.load() == false) {
    return(1);
  }
  
  Image image2(strDirInput + "/sceneBooks0002.jpg");
  if(image2.load() == false) {
    return(1);
  }
  
  return 1;
}

int main(int argc, const char * argv[])
{
  cerr << "Arguments = " << argv[1] << endl;
  
  if(string(argv[1]) == "0") {
    return main0();
  } else {
    return main1();
  }
  
  return 0;
}
