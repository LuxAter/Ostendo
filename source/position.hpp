#ifndef OSTENDO_POSITION_HPP
#define OSTENDO_POSITION_HPP

#include <array>

namespace ostendo {
  struct Position {
   public:
    Position() {}
    Position(int v0, int v1) : w(v0), h(v1) {}
    Position(int v0, int v1, int v2, int v3) : w(v0), h(v1), x(v2), y(v3) {}
    explicit Position(std::array<int, 4> v)
        : w(v[0]), h(v[1]), x(v[2]), y(v[3]) {}

    operator std::array<int, 4>() { return {{w, h, x, y}}; }

    int w = 0, h = 0;
    int x = 0, y = 0;

   private:
  };
}  // namespace ostendo
#endif
