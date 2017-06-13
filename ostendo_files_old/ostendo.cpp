#include <ncurses.h>
#include <pessum.h>
#include <string>
#include "ostendo.hpp"
#include "types.hpp"

namespace ostendo {
  Pos std_scr;
  std::map<std::string, Window> windows;
  int win_index = 0;
  bool color_init = false;
}

void ostendo::InitOstendo(bool color, int time_out) {
  initscr();
  cbreak();
  keypad(stdscr, true);
  getmaxyx(stdscr, std_scr.h, std_scr.w);
  noecho();
  curs_set(0);
  timeout(time_out);
  if (color == true) {
    if (has_colors() == FALSE) {
      pessum::Log(pessum::WARNING, "Current terminal does not support color", "ostendo/InitOstendo");
    } else {
      start_color();
      LoadColors();
    }
  }
  refresh();
}

void ostendo::TermOstendo() {
  nocbreak();
  echo();
  curs_set(1);
  refresh();
  endwin();
}

void ostendo::InitWindow(std::string name) { windows[name] = Window(); }

void ostendo::InitWindow(std::string name, int width, int height) {
  windows[name] = Window(width, height);
}

void ostendo::InitWindow(std::string name, int width, int height, int x,
                         int y) {
  windows[name] = Window(width, height, x, y);
}

void ostendo::TermWindow(std::string name) {
  windows.at(name).DelWin();
  windows.erase(name);
}

void ostendo::LoadColors() {
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      init_pair((short)(i * 10 + j), (short)i, (short)j);
    }
  }
}
