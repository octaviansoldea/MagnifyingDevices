#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Image.h"

using namespace std;
using namespace cv;


Image::Image(const fs::path & aPath) : m_Path(aPath) {
  
}

bool Image::load(Modalities aModalities) {
  return(load(aModalities, m_Path));
}

bool Image::load(Modalities aModalities, const fs::path & aPath) {
  if(aModalities != Modalities::OPENCV) {
    return false;
  }
  m_ImageOpenCV = Mat();
  
  m_ImageOpenCV = imread(aPath, IMREAD_COLOR);
  if(m_ImageOpenCV.empty())
  {
      std::cout << "Could not read the image: " << aPath << std::endl;
      return(false);
  }
  return(true);
}

bool Image::writeImage(Modalities aModalities) const {
  return(writeImage(aModalities, m_Path));
}

bool Image::writeImage(Modalities aModalities, const fs::path & aPath) const {
  if(aModalities != Modalities::OPENCV) {
    return false;
  }
  bool bOk = imwrite(aPath, m_ImageOpenCV);
  return(bOk);
}

void Image::setTransform2D(double adbTX, double adbTY, double adbAngle) {
  this->m_Center[0] = adbTX;
  this->m_Center[1] = adbTX;
  //m_Orientation[0][0] =
}

double Image::distance(const Image & image1, const Image & image2) {
  return(0);
}
