#include "Image.h"
#include <algorithm>

namespace cs225 {
  Image::Image() : PNG() {}

  Image::Image(unsigned width, unsigned height) : PNG(width, height) {}

  void Image::lighten() {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.l += 0.1;
        if (pixel.l > 1.0) {
          pixel.l = 1.0;
        }
      }
    }
    return;
  };

  void Image::lighten(double amount) {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.l += amount;
        if (pixel.l > 1.0) {
          pixel.l = 1.0;
        }
      }
    }
    return;
  };

  void Image::darken() {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.l -= 0.1;
        if (pixel.l < 0.0) {
          pixel.l = 0.0;
        }
      }
    }
    return;
  };

  void Image::darken(double amount) {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.l -= amount;
        if (pixel.l < 0.0) {
          pixel.l = 0.0;
        }
      }
    }
    return;
  };

  void Image::saturate() {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.s += 0.1;
        if (pixel.s > 1.0) {
          pixel.s = 1.0;
        }
      }
    }
    return;
  };

  void Image::saturate(double amount) {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.s += amount;
        if (pixel.s > 1.0) {
          pixel.s = 1.0;
        }
      }
    }
    return;
  };

  void Image::desaturate() {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.s -= 0.1;
        if (pixel.s < 0.0) {
          pixel.s = 0.0;
        }
      }
    }
    return;
  };

  void Image::desaturate(double amount) {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.s -= amount;
        if (pixel.s < 0.0) {
          pixel.s = 0.0;
        }
      }
    }
    return;
  };

  void Image::grayscale() {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.s = 0.0;
      }
    }
    return;
  };

  void Image::rotateColor(double degrees) {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        pixel.h += degrees;
        if (pixel.h > 360.0) {
          pixel.h -= 360.0;
        } else if (pixel.h < 0.0) {
          pixel.h += 360.0;
        }
      }
    }
    return;
  };

  void Image::illinify() {
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel &pixel = this->getPixel(x, y);
        if (pixel.h >= 114 && pixel.h <= 318) {
          pixel.h = 216;
        } else {
          pixel.h = 11;
        }
      }
    }
    return;
  }

  void Image::scale(double factor) {
    unsigned width = this->width();
    unsigned height = this->height();
    unsigned new_width = static_cast<int>(width * factor);
    unsigned new_height = static_cast<int>(height * factor);

    if (factor > 1.0) {
      unsigned ori_x = 0;
      unsigned ori_y = 0;
      this->resize(new_width, new_height);
      for (unsigned x = new_width - 1; x != 0; --x) {
        for (unsigned y = new_height - 1; y != 0; --y) {
          ori_x = static_cast<unsigned>(x / factor);
          ori_y = static_cast<unsigned>(y / factor);
          HSLAPixel &pixel = this->getPixel(x, y);
          HSLAPixel &ori_pixel = this->getPixel(ori_x, ori_y);
          pixel = ori_pixel;
        }
      }
    } else if (factor < 1.0) {
      unsigned ori_x = 0;
      unsigned ori_y = 0;
      for (unsigned x = 0; x < new_width; ++x) {
        for (unsigned y = 0; y < new_height; ++y) {
          ori_x = static_cast<unsigned>(x / factor);
          ori_y = static_cast<unsigned>(y / factor);
          HSLAPixel &pixel = this->getPixel(x, y);
          HSLAPixel &ori_pixel = this->getPixel(ori_x, ori_y);
          pixel = ori_pixel;
        }
      }
      this->resize(new_width, new_height);
    }

    return;
  };

  void Image::scale(unsigned w, unsigned h) {
    unsigned width = this->width();
    unsigned height = this->height();

    double w_factor = 0.0;
    double h_factor = 0.0;

    this->resize(std::max(width, w), std::max(height, h));

    if (w >= width && h >= height) {
      unsigned ori_x = 0;
      unsigned ori_y = 0;
      for (unsigned x = w - 1; x != 0; ++x) {
        for (unsigned y = h - 1; y != 0; ++y) {
          ori_x = static_cast<unsigned>(x / w_factor);
          ori_y = static_cast<unsigned>(y / h_factor);
          HSLAPixel &pixel = this->getPixel(x, y);
          HSLAPixel &ori_pixel = this->getPixel(ori_x, ori_y);
          pixel = ori_pixel;
        }
      }
    } else if (w >= width && h < height) {
      unsigned ori_x = 0;
      unsigned ori_y = 0;
      for (unsigned x = w - 1; x != 0; ++x) {
        for (unsigned y = 0; y < h; ++y) {
          ori_x = static_cast<unsigned>(x / w_factor);
          ori_y = static_cast<unsigned>(y / h_factor);
          HSLAPixel &pixel = this->getPixel(x, y);
          HSLAPixel &ori_pixel = this->getPixel(ori_x, ori_y);
          pixel = ori_pixel;
        }
      }
    } else if (w < width && h >= height) {
      unsigned ori_x = 0;
      unsigned ori_y = 0;
      for (unsigned x = 0; x < w; ++x) {
        for (unsigned y = h - 1; y != 0; ++y) {
          ori_x = static_cast<unsigned>(x / w_factor);
          ori_y = static_cast<unsigned>(y / h_factor);
          HSLAPixel &pixel = this->getPixel(x, y);
          HSLAPixel &ori_pixel = this->getPixel(ori_x, ori_y);
          pixel = ori_pixel;
        }
      }
    } else { // w < width && h < height
      unsigned ori_x = 0;
      unsigned ori_y = 0;
      for (unsigned x = 0; x < w; ++x) {
        for (unsigned y = 0; y < h; ++y) {
          ori_x = static_cast<unsigned>(x / w_factor);
          ori_y = static_cast<unsigned>(y / h_factor);
          HSLAPixel &pixel = this->getPixel(x, y);
          HSLAPixel &ori_pixel = this->getPixel(ori_x, ori_y);
          pixel = ori_pixel;
        }
      }
    }

    this->resize(w, h);
    return;
  };
} // namespace cs225
