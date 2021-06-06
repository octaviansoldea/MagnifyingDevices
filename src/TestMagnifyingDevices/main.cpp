#include <filesystem>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "ImagesManager.h"

using namespace cv;
int main_()
{
  ImagesManager imagesManager("/Users/octavian/Octavian/MagnifyingDevices/data/");
  
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


#include "itkImage.h"
#include "itkImageFileReader.h"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  ImageType::Pointer image = reader->GetOutput();

  return EXIT_SUCCESS;
}


