/**
 * @file FloodFilledImage.h
 * Definition for a class to do flood fill on an image
 */
#ifndef FLOODFILLEDIMAGE_H
#define FLOODFILLEDIMAGE_H

#include "cs225/PNG.h"
#include <iostream>
#include <list>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Animation.h"
#include "Point.h"

using namespace cs225;
/**
 *This class is used to do flood fill on an image
 */
class FloodFilledImage {
  public:
    FloodFilledImage(const PNG &png);
    void addFloodFill(ImageTraversal &traversal, ColorPicker &colorPicker);
    Animation animate(unsigned frameInterval) const;

  private:
    /** @todo [Part 2] */
    /** add private members here*/
};

#endif
