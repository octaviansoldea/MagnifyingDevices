#ifndef IMAGE_H
#define IMAGE_H

#include <filesystem>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

namespace fs = std::filesystem;

struct Image {
  Image(const fs::path & aPath = "");
  
  fs::path m_Path;
  
  cv::Mat m_ImageOpenCV;

  bool load();
  bool load(const fs::path & aPath);
  bool writeImage() const;
  bool writeImage(const fs::path & aPath) const;

  double m_Center[3] = {0.0, 0.0, 0.0};
  double m_Rotation[3][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
  };
  double m_Scale[3] = {1.0, 1.0, 1.0};
  
  void setTransform2D(double adbTX, double adbTY, double adbAngle);

  void updateOpenCVStructs();
  cv::Mat getTransformImageToWorld();
  void computePosition3D(double coordinates[3], int i, int j);
  void getColor(unsigned char rgb[3], double coordinates[3]);
   
  static double distance(Image & image1, Image & image2);
  static double distanceFromTo(Image & imageSrc, Image & imageDst);
private:
  
  void updateOpenCVScale();
  void updateOpenCVRotation();
  void updateOpenCVTranslation();
  
  cv::Mat m_OpenCVScale = cv::Mat::eye(4, 4, CV_64FC1);
  cv::Mat m_OpenCVRotation = cv::Mat::eye(4, 4, CV_64FC1);
  cv::Mat m_OpenCVCenter = cv::Mat::eye(4, 4, CV_64FC1);
  cv::Mat m_TransformImageToWorld = cv::Mat::eye(4, 4, CV_64FC1);
};



#endif //IMAGE_H
