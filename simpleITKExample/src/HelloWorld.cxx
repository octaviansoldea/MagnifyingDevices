#include "itkImage.h"
#include <iostream>
  
int main_()
{
  using ImageType = itk::Image< unsigned short, 3 >;
  
  ImageType::Pointer image = ImageType::New();
  
  std::cout << "ITK Hello World !" << std::endl;
  
  return EXIT_SUCCESS;
}

#include "itkImage.h"
#include "itkImageFileReader.h"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  ImageType::Pointer image = reader->GetOutput();

  return EXIT_SUCCESS;
}


