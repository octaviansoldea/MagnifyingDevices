#include <exception>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "ImagesManager.h"

using namespace std;
using namespace cv;

bool ImagesManager::init(const fs::path & aPath) {
  for (const auto& entry : fs::directory_iterator(aPath)) {
    if (entry.is_regular_file()) {
      Image image(entry.path());
      if(image.load(Image::Modalities::OPENCV) == false) {
        return(false);
      }
      m_Images.push_back(image);
    }
  }
  return(true);
}

Image & ImagesManager::get(size_t index) {
  if(index > this->m_Images.size()) {
    string strError =
      string("Index ") +
      to_string(index) +
      " > " +
      to_string(this->m_Images.size());
    throw std::out_of_range(strError);
  }
  return(m_Images[index]);
}

void ImagesManager::add(const Image & aImage) {
  m_Images.push_back(aImage);
}

size_t ImagesManager::size() const {
  return(m_Images.size());
}
