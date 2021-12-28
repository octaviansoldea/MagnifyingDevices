#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Image.h"

using namespace std;
using namespace cv;


Image::Image(const fs::path & aPath) : m_Path(aPath) {
}

bool Image::load() {
  return(load(m_Path));
}

bool Image::load(const fs::path & aPath) {
  m_ImageOpenCV = Mat();
  
  m_ImageOpenCV = imread(aPath, IMREAD_COLOR);
  if(m_ImageOpenCV.empty())
  {
      std::cout << "Could not read the image: " << aPath << std::endl;
      return(false);
  }
  return(true);
}

bool Image::writeImage() const {
  return(writeImage(m_Path));
}

bool Image::writeImage(const fs::path & aPath) const {
  bool bOk = imwrite(aPath, m_ImageOpenCV);
  return(bOk);
}

void Image::setTransform2D(double adbTX, double adbTY, double adbAngle) {
  m_Center[0] = adbTX;
  m_Center[1] = adbTY;
  double dbCos = cos(adbAngle);
  double dbSin = sin(adbAngle);
  m_Rotation[0][0] = dbCos;
  m_Rotation[0][1] = dbSin;
  m_Rotation[1][0] = - dbSin;
  m_Rotation[1][1] = dbCos;
  
  updateOpenCVStructs();
}

void Image::updateOpenCVStructs() {
  updateOpenCVScale();
  updateOpenCVRotation();
  updateOpenCVTranslation();
  
  m_TransformImageToWorld = Mat::eye(4, 4, CV_64FC1);
  m_TransformImageToWorld = m_OpenCVCenter * m_OpenCVRotation * m_OpenCVScale;
}

cv::Mat Image::getTransformImageToWorld() {
  return m_TransformImageToWorld;
}

void Image::computePosition3D(double coordinates[3], int i, int j) {
  Mat pointIn(4, 1, CV_64FC1);
  pointIn.at<double>(0,0) = i;
  pointIn.at<double>(1,0) = j;
  pointIn.at<double>(2,0) = 0;
  pointIn.at<double>(3,0) = 1;
  
  Mat pointOut = m_TransformImageToWorld * pointIn;
  int idx;
  for(idx = 0; idx < 3; idx++) {
    coordinates[idx] = pointOut.at<double>(idx, 0);
  }
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void Image::getColor(unsigned char rgb[3], double coordinates[3]) {
  
  Mat pointIn(4, 1, CV_64FC1);
  int idx;
  for(idx = 0; idx < 3; idx++) {
    pointIn.at<double>(idx,0) = idx;
  }
  pointIn.at<double>(3,0) = 1.0;
  
  //project on this image
  Mat pointDiff(4, 1, CV_64FC1);
  pointDiff = pointIn - m_OpenCVCenter;
  
  Mat pointInImage = m_OpenCVRotation * pointDiff;
  
  Mat transformWorldToImage = m_TransformImageToWorld.inv();
  
  Mat pointOut = transformWorldToImage * pointInImage;
  
  double x = pointOut.at<double>(0);
  double y = pointOut.at<double>(1);

  double floor_x = floor(x);
  double floor_y = floor(y);
  double ceil_x = ceil(x);
  double ceil_y = ceil(y);

  //string ty =  type2str( m_ImageOpenCV.type() );
  unsigned char rgbCorners[2][2][3];
  for(idx = 0; idx < 3; idx++) {
    rgbCorners[0][0][idx] = m_ImageOpenCV.at<cv::Vec3b>(floor_x,floor_y)[idx];
    rgbCorners[0][1][idx] = m_ImageOpenCV.at<cv::Vec3b>(floor_x,ceil_y)[idx];
    rgbCorners[1][0][idx] = m_ImageOpenCV.at<cv::Vec3b>(ceil_x,floor_y)[idx];
    rgbCorners[1][1][idx] = m_ImageOpenCV.at<cv::Vec3b>(ceil_x,ceil_y)[idx];
  }
  
  for(idx = 0; idx < 3; idx++) {
    unsigned short sum = 0;
    int i, j;
    for(i = 0; i < 2; i++) {
      for(j = 0; j < 2; j++) {
        sum += rgbCorners[i][i][idx];
      }
    }
    rgb[idx] = (unsigned char)((float)sum / 4.0);
  }
    
}

double Image::distanceFromTo(Image & imageSrc, Image & imageDst) {
  double distance = 0.0;
  int rowsSrc = imageSrc.m_ImageOpenCV.rows;
  int colsSrc = imageSrc.m_ImageOpenCV.cols;
  int i, j;
  double coordinates[3];
  unsigned char rgbSrc[3], rgbDst[3];
  
  Mat transformSrc = imageSrc.getTransformImageToWorld();
  Mat transformDst = imageDst.getTransformImageToWorld();
  
  for(i = 0; i < rowsSrc; i++) {
    for(j = 0; j < colsSrc; j++) {
      imageSrc.computePosition3D(coordinates, i, j);
      imageDst.getColor(rgbDst, coordinates);
    }
  }
  
  return 0.0;
}

double Image::distance(Image & image1, Image & image2) {
  double distance12 = Image::distanceFromTo(image1, image2);
  double distance21 = Image::distanceFromTo(image2, image1);
  
  double distance = distance12 + distance21;
  return(distance);
}

void Image::updateOpenCVScale() {
  m_OpenCVScale = Mat::eye(4, 4, CV_64FC1);
  int idx;
  for(idx = 0; idx < 3; idx++) {
    m_OpenCVScale.at<double>(idx, idx) = m_Scale[idx];
  }
}

void Image::updateOpenCVRotation() {
  m_OpenCVRotation = Mat::eye(4, 4, CV_64FC1);
  int i, j;
  for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
      m_OpenCVRotation.at<double>(i, i) = m_Rotation[i][j];
    }
  }
}

void Image::updateOpenCVTranslation() {
  m_OpenCVCenter = Mat::eye(4, 4, CV_64FC1);
  int idx;
  for(idx = 0; idx < 3; idx++) {
    m_OpenCVCenter.at<double>(idx,3) = m_Center[idx];
  }
}
