#include <iostream>
#include <string>

#include "ImagesManager.h"

using namespace cv;
using namespace std;

int main(int argc, char * argv[])
{
  if (argc != 1)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    //std::cerr << " <Input Directory>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }
  
  string strDirInput = fs::current_path() /= "../../../data/sceneBooks/video_split";
  
  ImagesManager imagesManager(strDirInput);
  

  return 0;
}

