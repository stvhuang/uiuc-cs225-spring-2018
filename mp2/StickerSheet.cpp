#include "StickerSheet.h"

using namespace std;

namespace cs225 {
  StickerSheet::StickerSheet(const Image &picture, unsigned max)
    : max_(max), num_(0), base(picture),
      stickers(new Image*[max_]),
      x_index(new unsigned[max_]),
      y_index(new unsigned[max_]) {
    for (unsigned i = 0; i < max_; ++i) {
      stickers[i] = NULL;
      x_index[i] = 0;
      y_index[i] = 0;
    }
  }

  StickerSheet::StickerSheet(const StickerSheet &other)
    : max_(other.max_), num_(other.num_), base(other.base),
      stickers(new Image*[max_]),
      x_index(new unsigned[max_]),
      y_index(new unsigned[max_]) {
    for (unsigned i = 0; i < max_; ++i) {
      if (i < num_) {
        stickers[i] = new Image(*other.stickers[i]);
        x_index[i] = other.x_index[i];
        y_index[i] = other.y_index[i];
      } else {
        stickers[i] = NULL;
        x_index[i] = 0;
        y_index[i] = 0;
      }
    }
  }

  StickerSheet::~StickerSheet() {
    _clear();
  }

  const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    _clear();

    max_ = other.max_;
    num_ = other.num_;
    base = other.base;

    stickers = new Image*[max_];
    x_index = new unsigned[max_];
    y_index = new unsigned[max_];

    for (unsigned i = 0; i < max_; ++i) {
      if (i < num_) {
        stickers[i] = new Image(*other.stickers[i]);
        x_index[i] = other.x_index[i];
        y_index[i] = other.y_index[i];
      } else {
        stickers[i] = NULL;
        x_index[i] = 0;
        y_index[i] = 0;
      }
    }

    return *this;
  };

  void StickerSheet::changeMaxStickers(unsigned max) {
    Image **new_stickers = new Image*[max];
    unsigned *new_x_index = new unsigned[max];
    unsigned *new_y_index = new unsigned[max];
    for (unsigned i = 0; i < max; ++i) {
      new_stickers[i] = NULL;
      new_x_index[i] = 0;
      new_y_index[i] = 0;
    }

    for (unsigned i = 0; i < num_ && i < max; ++i) {
      new_stickers[i] = stickers[i];
      new_x_index[i] = x_index[i];
      new_y_index[i] = y_index[i];
    }

    max_ = max;
    if (num_ > max_) {
      num_ = max_;
    }

    if (stickers != NULL) {
      delete[] stickers;
      stickers = new_stickers;
    }

    if (x_index != NULL) {
      delete[] x_index;
      x_index = new_x_index;
    }

    if (y_index != NULL) {
      delete[] y_index;
      y_index = new_y_index;
    }
  };

  int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (num_ == max_) {
      return -1;
    } else {
      stickers[num_] = new Image(sticker);
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
      if (stickers[index] != NULL) {
        delete stickers[index];
        stickers[index] = NULL;
      }
    }
  }

  Image * StickerSheet::getSticker(unsigned index) const {
    if (index >= num_) {
      return NULL;
    } else {
      return stickers[index];
    }
  }

  Image StickerSheet::render() const {
    Image result(base);
    unsigned width, height, x_idx, y_idx;
    for (unsigned i = 0; i < num_; ++i) {
      if (stickers[i] != NULL) {
        width = stickers[i]->width();
        height = stickers[i]->height();
        x_idx = x_index[i];
        y_idx = y_index[i];
        for (unsigned x = 0; x < width; ++x) {
          for (unsigned y = 0; y < height; ++y) {
            HSLAPixel &pixel = result.getPixel(x_idx + x, y_idx + y);
            if (stickers[i]->getPixel(x, y).a != 0.0) {
              pixel = stickers[i]->getPixel(x, y);
            }
          }
        }
      }
    }

    return result;
  }

  void StickerSheet::_clear() {
    if (stickers != NULL) {
      for (unsigned i = 0; i < max_; ++i) {
        if (stickers[i] != NULL) {
            delete stickers[i];
            stickers[i] = NULL;
        }
      }
      delete[] stickers;
      stickers = NULL;
    }

    if (x_index != NULL) {
      delete[] x_index;
      x_index = NULL;
    }

    if (y_index != NULL) {
      delete[] y_index;
      y_index = NULL;
    }
  }
}
