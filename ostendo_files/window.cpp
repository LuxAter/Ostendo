#include "window.hpp"
#include "pos.hpp"
#include <ncurses.h>
#include "ostendo.hpp"
#include <string>

ostendo::Window::Window(){
  window_pos = std_scr;
}

ostendo::Window::Window(int width, int height){
  window_pos = Pos(std_scr.x, std_scr.y, width, height);
}

ostendo::Window::Window(int width, int height, int pos_x, int pos_y){
  window_pos = Pos(pos_x, pos_y, width, height);
}

ostendo::Window::Window(Pos pos){
  window_pos = pos;
}

ostendo::Window::Window(const Window& win){
  window_name = win.window_name;
  window_pos = win.window_pos;
}

ostendo::Window::~Window(){

}
