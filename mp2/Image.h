/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */


#ifndef IMAGE_H_
#define IMAGE_H_

#include "cs225/PNG.h"

namespace cs225 {
class Image : public PNG {
public:
  Image();
  Image(unsigned width, unsigned height);
  void lighten();
  void lighten(double amount);
  void darken();
  void darken(double amount);
  void saturate();
  void saturate(double amount);
  void desaturate();
  void desaturate(double amount);
  void grayscale();
  void rotateColor(double degrees);
  void illinify();
  void scale(double factor);
  void scale(unsigned w, unsigned h);
};
} // namespace cs225

#endif
