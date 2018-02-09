#include "StickerSheet.h"

using namespace std;

namespace cs225 {
  StickerSheet::StickerSheet(const Image &picture, unsigned max)
    : max_(max), num_(0) {
      imageArr = new Image*[max];
      for (unsigned i = 0; i < max_; ++i) {
        imageArr[i] = NULL;
      }
      imageArr[0] = new Image(picture);
      x_index = new unsigned[max];
      x_index[0] = 0;
      y_index = new unsigned[max];
      y_index[0] = 0;
      ++num_;
    }

  StickerSheet::StickerSheet(const StickerSheet &other) {}

  StickerSheet::~StickerSheet() {
    for (unsigned i = 0; i < max_; ++i) {
      delete imageArr[i];
      imageArr[i] = NULL;
    }
    delete imageArr;
    imageArr = NULL;
    delete x_index;
    x_index = NULL;
    delete y_index;
    y_index = NULL;
  }

  //const StickerSheet & operator=(const StickerSheet &other) {};

  void StickerSheet::changeMaxStickers(unsigned max) {
  };

  int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (num_ == max_) {
      return -1;
    } else {
      imageArr[num_] = new Image(sticker);
      x_index[num_] = x;
      y_index[num_] = y;
      return num_++;
    }
  }
  
  bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= num_) {
      return false;
    } else {
      x_index[index] = x;
      y_index[index] = y;
      return true;
    }
  }

  void StickerSheet::removeSticker(unsigned index) {
    if (index < num_) {
      delete imageArr[index];
      for (unsigned i = index; i < num_ - 1; ++i) {
        imageArr[i] = imageArr[i + 1];
        x_index[i] = x_index[i + 1];
        y_index[i] = y_index[i + 1];
      }
      --num_;
    }
  }

  Image * StickerSheet::getSticker(unsigned index) const {
    if (index >= num_) {
      return NULL;
    } else {
      return imageArr[index];
    }
  }

  Image StickerSheet::render() const {
    Image result(imageArr[0]->width(), imageArr[0]->height());
    for (unsigned i = 0; i < num_; ++i) {
      for (unsigned x = 0; x < imageArr[i]->width(); ++x) {
        for (unsigned y = 0; y < imageArr[i]->height(); ++y) {
          HSLAPixel &pixel = result.getPixel(x + x_index[i], y + y_index[i]);
          if (imageArr[i]->getPixel(x, y).a == 0) {
            continue;
          } else {
            pixel = imageArr[i]->getPixel(x, y);
          }
        }
      }
    }
    return result;
  };
}
