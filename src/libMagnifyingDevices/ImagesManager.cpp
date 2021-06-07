#include <filesystem>
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "ImagesManager.h"

using namespace std;
using namespace cv;

ImagesManager::ImagesManager(const fs::path & aPath) {
  init(aPath);
}

bool ImagesManager::init(const fs::path & aPath) {
  for (const auto& entry : fs::directory_iterator(aPath)) {
    if (entry.is_regular_file()) {
      Mat image;
      if(readImage(image, entry.path())) {
        add(image);
      }
    }
  }
  return(true);
}

bool ImagesManager::get(Mat & aImage, size_t index) {
  if(index > this->m_Images.size()) {
    return(false);
  }
  aImage = m_Images[index];
  return(true);
}

void ImagesManager::add(const Mat & aImage) {
  m_Images.push_back(aImage);
}
  
bool ImagesManager::readImage(cv::Mat & aImage, const fs::path & aPath) {
  aImage = imread(aPath, IMREAD_COLOR);
  if(aImage.empty())
  {
      std::cout << "Could not read the image: " << aPath << std::endl;
      return(false);
  }
  return(true);
}

bool ImagesManager::writeImage(const fs::path & aPath, const Mat & aImage) {
  bool bOk = imwrite(aPath, aImage);
  return(bOk);
}


