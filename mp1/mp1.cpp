#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG inputImage;
  inputImage.readFromFile(inputFile);

  unsigned width = inputImage.width(), height = inputImage.height(),
           output_x = 0, output_y = 0;

  PNG outputImage(width, height);

  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      output_x = width - x - 1;
      output_y = height - y - 1;

      HSLAPixel * input_pixel = inputImage.getPixel(x, y);
      HSLAPixel * output_pixel = outputImage.getPixel(output_x, output_y);

      output_pixel->h = input_pixel->h;
      output_pixel->s = input_pixel->s;
      output_pixel->l = input_pixel->l;
      output_pixel->a = input_pixel->a;
    }
  }

  outputImage.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3

  return png;
}
