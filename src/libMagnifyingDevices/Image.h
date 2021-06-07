#include <filesystem>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "itkImage.h"
#include "itkImageFileReader.h"

namespace fs = std::filesystem;

struct Image {
  fs::path & m_Path;
  
  double m_Center[3];
  double m_Orientation[3][3];
  
  cv::Mat m_ImageOpenCV;
  
  static constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;
  
  ImageType m_ImageITK;

};
