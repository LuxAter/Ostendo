#ifndef OSTENDO_POS_HPP
#define OSTENDO_POS_HPP
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
}
#endif
