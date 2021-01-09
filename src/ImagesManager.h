#include <filesystem>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

namespace fs = std::filesystem;

struct ImagesManager {
  ImagesManager(const fs::path & aPath);
  
  
  bool init(const std::filesystem::path & aPath);
  
  bool get(cv::Mat & aImage, size_t index);
  void add(const cv::Mat & aImage);
  
  static bool readImage(cv::Mat & aImage, const fs::path & aPath);
  static bool writeImage(const fs::path & aPath, const cv::Mat & aImage);

private:
  std::vector<cv::Mat> m_Images;
};
