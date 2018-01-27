#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cstdlib>

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
  double myHue = 160.0;
  double hue = 0.0;
  unsigned y_end = 0;
  int height_starts[9] = {   0,  200,  360,  460,  540,  590, 630, 662,  700};
  int hue_mod[9] =       { 200,  160,  100,   80,   50,   40,  32,  16,    8};
  double hue_times[9] =  {32.0, 24.0, 18.0, 16.0, 12.0, 10.0, 9.0, 5.0, 2.75};

  for (int n = 0; n < 9; n++) {
    for (unsigned x = 0; x < width; x++) {
      if (n == 8) {
        y_end = height;
      } else {
        y_end = height_starts[n+1];
      }
      for (unsigned y = height_starts[n]; y < y_end; y++) {
        hue = myHue + (x / hue_mod[n]) * hue_times[n];
        HSLAPixel &pixel = *png.getPixel(x, y);
        pixel.h = hue;
        pixel.s = 1.0;
        pixel.l = 0.5;
      }
    }
  }

  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel &pixel = *png.getPixel(x, y);
      double r = (((double) rand() / (RAND_MAX)) + 1) * 20.0;
      pixel.h += r;
      if (pixel.h > 360.0) {
        pixel.h = 360.0;
      }
    }
  }

  return png;
}
