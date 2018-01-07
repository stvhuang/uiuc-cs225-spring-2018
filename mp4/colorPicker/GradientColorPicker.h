#ifndef GradientColorPicker_H
#define GradientColorPicker_H

#include "../Point.h"
#include "../cs225/HSLAPixel.h"
#include "ColorPicker.h"

using namespace cs225;

/**
 * A color picker class using gradient color picking algorithm
 */
class GradientColorPicker : public ColorPicker {
  public:
    GradientColorPicker(HSLAPixel color1, HSLAPixel color2, Point center,
                        unsigned radius);
    HSLAPixel getColor(unsigned x, unsigned y);

  private:
    HSLAPixel color1;
    HSLAPixel color2;
    Point center;
    unsigned radius;
};

#endif
