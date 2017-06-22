#ifndef OSTENDO_SIZE_HPP
#define OSTENDO_SIZE_HPP
namespace ostendo {
  struct Size {
    Size(int in_w = 0, int in_h = 0, int in_x = 0, int in_y = 0, int in_z = 0);
    int w, h, x, y, z;
  };
}
#endif
