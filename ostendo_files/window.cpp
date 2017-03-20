#include <ncurses.h>
#include <string>
#include "ostendo.hpp"
#include "types.hpp"
#include "window.hpp"

namespace ostendo {
  int color_index = 8, pair_index = 0;
}

ostendo::Window::Window() { window_pos = std_scr; }

ostendo::Window::Window(int width, int height) {
  window_pos = Pos(std_scr.x, std_scr.y, width, height);
}

ostendo::Window::Window(int width, int height, int pos_x, int pos_y) {
  window_pos = Pos(pos_x, pos_y, width, height);
}

ostendo::Window::Window(Pos pos) { window_pos = pos; }

ostendo::Window::Window(const Window& win) { window_pos = win.window_pos; }

ostendo::Window::~Window() {
  wclear(window_pointer);
  wrefresh(window_pointer);
  delwin(window_pointer);
  window_border = false;
  window_title = false;
  window_menu_bar = false;
  window_pos = Pos();
}

void ostendo::Window::Update() {
  if (window_pointer != nullptr) {
    wrefresh(window_pointer);
  }
}

void ostendo::Window::SetWindowOption(int option, bool setting) {
  if (option == WIN_BORDER) {
    if (window_border != setting) {
      window_border = setting;
      DrawBorder();
    }
  } else if (option == WIN_TITLE) {
    if (window_title != setting) {
      window_title = setting;
      DrawTitle();
    }
  } else if (option == WIN_MENU_BAR) {
    if (window_menu_bar != setting) {
      window_menu_bar = setting;
      DrawMenuBar();
    }
  }
  Update();
}
void ostendo::Window::SetWindowOption(int option, std::string setting) {
  if (option == WIN_BORDER) {
    // border_character_set = {setting};
  } else if (option == WIN_TITLE) {
    title_set = {setting};
  } else if (option == WIN_MENU_BAR) {
    menu_bar_options = {setting};
  }
}

void ostendo::Window::SetWindowOption(int option,
                                      std::vector<std::string> setting) {
  if (option == WIN_BORDER) {
    // border_character_set = setting;
  } else if (option == WIN_TITLE) {
    title_set = setting;
  } else if (option == WIN_MENU_BAR) {
    menu_bar_options = setting;
  }
}

void ostendo::Window::AttrOn(int attrs) { wattron(window_pointer, attrs); }

void ostendo::Window::AttrOn(std::vector<int> attrs) {
  int att = 0;
  for (int i = 0; i < attrs.size(); i++) {
    att = att | attrs[i];
  }
  wattron(window_pointer, att);
}

void ostendo::Window::AttrOff(int attrs) { wattroff(window_pointer, attrs); }

void ostendo::Window::AttrOff(std::vector<int> attrs) {
  int att = 0;
  for (int i = 0; i < attrs.size(); i++) {
    att = att | attrs[i];
  }
  wattroff(window_pointer, att);
}

void ostendo::Window::SetAttr(int attrs) { wattrset(window_pointer, attrs); }

void ostendo::Window::SetAttr(std::vector<int> attrs) {
  int att = 0;
  for (int i = 0; i < attrs.size(); i++) {
    att = att | attrs[i];
  }
  wattrset(window_pointer, att);
}

int ostendo::Window::SetColor(Color col) {
  int fg = color_index++;
  int bg = color_index++;
  fg = init_color(fg, (int)col[0] * 1000, (int)col[1] * 1000,
                  (int)col[2] * 1000);
  bg = init_color(bg, (int)col[3] * 1000, (int)col[4] * 1000,
                  (int)col[5] * 1000);
  int pair = pair_index++;
  pair = init_pair(pair, fg, bg);
  AttrOn(COLOR_PAIR(pair));
  return (pair);
}

void ostendo::Window::GenWindow() {
  window_pointer =
      newwin(window_pos.h, window_pos.w, window_pos.y, window_pos.x);
  if (window_pointer == nullptr) {
    OstendoLog(10, "Failed to genorate window", "GenWindow");
  }
  Update();
}

void ostendo::Window::DrawBorder() {
  if (window_border == true) {
    SetColor(border_color);
    box(window_pointer, 0, 0);
    // wborder(window_pointer, border_character_set[0], border_character_set[1],
    //         border_character_set[2], border_character_set[3],
    //         border_character_set[4], border_character_set[5],
    //         border_character_set[6], border_character_set[7]);
  } else if (window_border == false) {
    wborder(window_pointer, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  }
}

void ostendo::Window::DrawTitle() {}

void ostendo::Window::DrawMenuBar() {}
