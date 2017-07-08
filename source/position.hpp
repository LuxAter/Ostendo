#ifndef OSTENDO_POSITION_HPP
#define OSTENDO_POSITION_HPP

#include <array>

namespace ostendo {
  struct Position {
   public:
    Position() {}
    Position(int v0, int v1) : w(v0), h(v1) {}
    Position(int v0, int v1, int v2) : x(v0), y(v1), z(v2) {}
    Position(int v0, int v1, int v2, int v3) : w(v0), h(v1), x(v2), y(v3) {}
    Position(int v0, int v1, int v2, int v3, int v4)
        : w(v0), h(v1), x(v2), y(v3), z(v4) {}
    Position(std::array<int, 5> v)
        : w(v[0]), h(v[1]), x(v[2]), y(v[3]), z(v[4]) {}

    operator std::array<int, 5>() { return {{w, h, x, y, z}}; }

    int w = 0, h = 0;
    int x = 0, y = 0, z = 0;

   private:
  };
}
#endif
