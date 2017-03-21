#ifndef OSTENDO_TYPES_HPP
#define OSTENDO_TYPES_HPP
#include <ncurses.h>
#include <map>
#include <string>
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
      color_data[0] = int();
      color_data[1] = int();
    }
    Color(int c) {
      color_data[0] = c;
      color_data[1] = int();
    }
    Color(int fg, int bg) {
      color_data[0] = fg;
      color_data[1] = bg;
    }
    inline int operator[](int i) { return (color_data[i]); }
    int color_data[2];
  };
  inline Color make_color(int fg, int bg) { return (Color(fg, bg)); }
  inline Color make_color_str(std::string fg, std::string bg) {
    std::map<std::string, int> color_map;
    color_map["black"] = COLOR_BLACK;
    color_map["red"] = COLOR_RED;
    color_map["green"] = COLOR_GREEN;
    color_map["yellow"] = COLOR_YELLOW;
    color_map["blue"] = COLOR_BLUE;
    color_map["magenta"] = COLOR_MAGENTA;
    color_map["cyan"] = COLOR_CYAN;
    color_map["white"] = COLOR_WHITE;
    int fg_i = 0, bg_i = 0;
    if (color_map.find(fg) == color_map.end()) {
      fg_i = COLOR_WHITE;
    } else {
      fg_i = color_map.find(fg)->second;
    }
    if (color_map.find(bg) == color_map.end()) {
      bg_i = COLOR_BLACK;
    } else {
      bg_i = color_map.find(bg)->second;
    }
    return (Color(fg_i, bg_i));
  }
}
#endif
