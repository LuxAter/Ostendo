#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP
#include "pos.hpp"
namespace ostendo {
  class Window {
   public:
    Window();
    Window(int width, int height);
    Window(int width, int height, int pos_x, int pos_y);
    Window(Pos pos);
    Window(const Window& win);
    ~Window();

   private:
    std::string window_name = "";
    Pos window_pos;
  };
}
#endif
