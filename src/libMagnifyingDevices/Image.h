#ifndef IMAGE_H
#define IMAGE_H

#include <filesystem>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "itkImage.h"
#include "itkImageFileReader.h"

namespace fs = std::filesystem;

struct Image {
  Image(const fs::path & aPath = "");
  
  fs::path m_Path;
  
  enum class Modalities {
    NO_MODALITY = 0x0,
    OPENCV = 0x1,
    ITK = 0x2
  };
  Modalities m_Modalities = Modalities::NO_MODALITY;
  
  cv::Mat m_ImageOpenCV;
  
  static constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;
  
  ImageType::Pointer m_pImageITK;
  
  bool load(Modalities aModalities);
  bool load(Modalities aModalities, const fs::path & aPath);
  bool writeImage(Modalities aModalities) const;
  bool writeImage(Modalities aModalities, const fs::path & aPath) const;

  double m_Center[3] = {0.0, 0.0, 0.0};
  double m_Orientation[3][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
  };
  double m_Scales[3] = {1.0, 1.0, 1.0};
  
  void setTransform2D(double adbTX, double adbTY, double adbAngle);
  
  static double distance(const Image & image1, const Image & image2);
  
};



#endif //IMAGE_H
