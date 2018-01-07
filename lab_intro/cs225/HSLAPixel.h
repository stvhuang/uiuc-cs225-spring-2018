/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#ifndef CS225_HSLAPIXEL_H_
#define CS225_HSLAPIXEL_H_

#include <iostream>
#include <sstream>

namespace cs225 {
class HSLAPixel {
  public:
    HSLAPixel();
    HSLAPixel(double hue, double saturation, double luminance);
    HSLAPixel(double hue, double saturation, double luminance, double alpha);

    double h;  // Hue
    double s;  // Saturation
    double l;  // Luminance
    double a;  // Alpha

  private:
};
}  // namespace cs225

#endif
