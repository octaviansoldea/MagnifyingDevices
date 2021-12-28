#include <iostream>
#include <string>

#include "ImagesManager.h"
#include "Algorithms.h"

using namespace cv;
using namespace std;

int main(int argc, char * argv[])
{
  if (argc != 1)
  {
    cerr << "Usage: " << std::endl;
    cerr << argv[0];
    std::cerr << " <Input Directory>";
    cerr << std::endl;
    return EXIT_FAILURE;
  }
  
  string strDirInput = fs::current_path() /= "../../../data/sceneBooks/video_split";
  
  ImagesManager imagesManager;
  imagesManager.init(strDirInput);
  
  try {
    computeAlignment2D(&imagesManager, 0);
  } catch (const std::exception& e) {
    cerr << "Could not access image: " << e.what() << endl;
    return(false);
  }
  
  return 0;
}

