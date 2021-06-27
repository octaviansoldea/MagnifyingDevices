#include <filesystem>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#ifndef IMAGESMANAGER_H
#define IMAGESMANAGER_H

#include <opencv2/highgui.hpp>

#include "Image.h"

namespace fs = std::filesystem;

struct ImagesManager {
  
  bool init(const std::filesystem::path & aPath);
  
  Image & get(size_t index);
  void add(const Image & aImage);

  size_t size() const;
  
private:
  std::vector<Image> m_Images;
};

#endif //IMAGESMANAGER_H
