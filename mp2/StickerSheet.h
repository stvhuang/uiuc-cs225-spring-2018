/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

#include "Image.h"
#include <iostream>

namespace cs225 {
  class StickerSheet {
   public:
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    //~StickerSheet();
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index) const;
    Image render() const;

   private:
    unsigned max_;  // maximun of stickers(images)
    unsigned num_;  // num of stickers(images)
    Image base;
    Image **stickers;
    unsigned *x_index;
    unsigned *y_index;
  };
}

#endif
