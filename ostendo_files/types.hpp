#ifndef OSTENDO_TYPES_HPP
#define OSTENDO_TYPES_HPP
namespace ostendo {
  struct Pos {
    Pos() {
      x = int();
      y = int();
      w = int();
      h = int();
      z = int();
    }
    Pos(int value_x, int value_y) {
      x = value_x;
      y = value_y;
      w = int();
      h = int();
      z = int();
    }
    Pos(int value_x, int value_y, int value_w, int value_h) {
      x = value_x;
      y = value_y;
      w = value_w;
      h = value_h;
      z = int();
    }
    int x, y, z, w, h;
  };
  inline Pos make_pos(int x, int y, int w, int h) { return (Pos(x, y, w, h)); }

  struct Color {
    Color() {
      color_data[0] = float();
      color_data[1] = float();
      color_data[2] = float();
      color_data[3] = float();
      color_data[4] = float();
      color_data[5] = float();
    }
    Color(float c) {
      color_data[0] = c;
      color_data[1] = c;
      color_data[2] = c;
      color_data[3] = c;
      color_data[4] = c;
      color_data[5] = c;
    }
    Color(float fg, float bg) {
      color_data[0] = fg;
      color_data[1] = fg;
      color_data[2] = fg;
      color_data[3] = bg;
      color_data[4] = bg;
      color_data[5] = bg;
    }
    Color(float red, float green, float blue) {
      color_data[0] = red;
      color_data[1] = green;
      color_data[2] = blue;
      color_data[3] = float();
      color_data[4] = float();
      color_data[5] = float();
    }
    Color(float red, float green, float blue, float bg_red, float bg_green,
          float bg_blue) {
      color_data[0] = red;
      color_data[1] = green;
      color_data[2] = blue;
      color_data[3] = bg_red;
      color_data[4] = bg_green;
      color_data[5] = bg_blue;
    }
    inline float operator[](int i) { return (color_data[i]); }
    float color_data[6];
  };
  inline Color make_color(float r, float b, float g) {
    return (Color(r, b, g));
  }
}
#endif
