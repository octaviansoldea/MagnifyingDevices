#include <iostream>
#include <limits>
#include <math.h>
#include <string>

#include "Algorithms.h"

#include "ImagesManager.h"

using namespace std;

const double dbOneDegree = 0.5 / M_PI;

void computeAlignment2D(Image * apImage, const Image & aImageTarget) {
  double distance = std::numeric_limits<double>::max();
  Image imageMartor;
  for(int nTX = -1; nTX <= 1; nTX++) {
    double dbTX = 1.0 * nTX;
    for(int nTY = -1; nTY <= 1; nTY++) {
      double dbTY = 1.0 * nTY;
      for(int indexAngle = -1; indexAngle <= 1; indexAngle++) {
        cout << "nTX = " << nTX << " nTY = " << nTY << " indexAngle = " << indexAngle << endl;
        double dbRotationAngle = dbOneDegree * indexAngle;
        apImage->setTransform2D(dbTX, dbTY, dbRotationAngle);
        Image image = *apImage;
        double distanceFocus = Image::distance(image, *apImage);
        if(distanceFocus < distance) {
          distance = distanceFocus;
          imageMartor = image;
        }
      }
    }
  }
  memcpy(apImage->m_Center, imageMartor.m_Center, sizeof(double) * 3);
  for(size_t index = 0; index < 3; index++) {
    memcpy(apImage->m_Rotation[index], imageMartor.m_Rotation[index], sizeof(double) * 3);
  }
  memcpy(apImage->m_Scale, imageMartor.m_Scale, sizeof(double) * 3);
}

void computeAlignment2D(
  ImagesManager * apImagesManager,
  size_t indexTarget) {
  if(indexTarget >= apImagesManager->size()) {
    string strError =
      string("indexTarget ") +
      std::to_string((long unsigned)index) +
      " > " +
      to_string(apImagesManager->size());
    throw std::out_of_range(strError);
  }
  const Image & imageTarget = apImagesManager->get(indexTarget);
  for(size_t index = 0; index != apImagesManager->size(); index++) {
    Image & image = apImagesManager->get(index);
    if(index != indexTarget) {
      computeAlignment2D(&image, imageTarget);
    }
  }
}
