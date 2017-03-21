#include <ncurses.h>
#include <pessum.h>
#include <string>
#include "ostendo.hpp"
#include "types.hpp"
#include "window.hpp"

namespace ostendo {
  int pair_index = 0;
}

ostendo::Window::Window() {
  window_pos = std_scr;
  GenWindow();
}

ostendo::Window::Window(int width, int height) {
  window_pos = Pos(0, 0, width, height);
  GenWindow();
}

ostendo::Window::Window(int width, int height, int pos_x, int pos_y) {
  window_pos = Pos(pos_x, pos_y, width, height);
  GenWindow();
}

ostendo::Window::Window(Pos pos) {
  window_pos = pos;
  GenWindow();
}

ostendo::Window::Window(const Window& win) {
  window_pos = win.window_pos;
  window_pointer = win.window_pointer;
  GenWindow();
}

ostendo::Window::~Window() {
  wclear(window_pointer);
  wrefresh(window_pointer);
  delwin(window_pointer);
  window_border = false;
  window_title = false;
  window_menu_bar = false;
  window_pos = Pos();
  window_pointer = NULL;
}

void ostendo::Window::Update() {
  if (window_pointer != NULL) {
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
    // title_set = {setting};
  } else if (option == WIN_MENU_BAR) {
    // menu_bar_options = {setting};
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

void ostendo::Window::AttrOn(int attrs) {
  if (window_pointer != NULL) {
    wattron(window_pointer, attrs);
  }
}

void ostendo::Window::AttrOn(std::vector<int> attrs) {
  int att = 0;
  for (int i = 0; i < attrs.size(); i++) {
    att = att | attrs[i];
  }
  if (window_pointer != NULL) {
    wattron(window_pointer, att);
  }
}

void ostendo::Window::AttrOff(int attrs) {
  if (window_pointer != NULL) {
    wattroff(window_pointer, attrs);
  }
}

void ostendo::Window::AttrOff(std::vector<int> attrs) {
  int att = 0;
  for (int i = 0; i < attrs.size(); i++) {
    att = att | attrs[i];
  }
  if (window_pointer != NULL) {
    wattroff(window_pointer, att);
  }
}

void ostendo::Window::SetAttr(int attrs) {
  if (window_pointer != NULL) {
    wattrset(window_pointer, attrs);
  }
}

void ostendo::Window::SetAttr(std::vector<int> attrs) {
  int att = 0;
  for (int i = 0; i < attrs.size(); i++) {
    att = att | attrs[i];
  }
  if (window_pointer != NULL) {
    wattrset(window_pointer, att);
  }
}

int ostendo::Window::DispColor(Color col) {
  int pair = pair_index++;
  init_pair(pair, (short)col[0], (short)col[1]);
  AttrOn(COLOR_PAIR(pair));
  return (pair);
}

void ostendo::Window::SetColor(int option, Color col) {
  if (option == WIN_BORDER) {
    border_color = col;
  } else if (option == WIN_TITLE) {
    title_color = col;
  } else if (option == WIN_MENU_BAR) {
    menu_bar_color = col;
  } else if (option == WIN_TEXT) {
    text_color = col;
  } else if (option == WIN_BACKGROUND) {
    background_color = col;
  }
}

void ostendo::Window::GenWindow() {
  border_color = Color(COLOR_GREEN, COLOR_BLACK);
  window_pointer =
      newwin(window_pos.h, window_pos.w, window_pos.y, window_pos.x);
  if (window_pointer == NULL) {
    OstendoLog(10, "Failed to genorate window", "GenWindow");
  }
  Update();
}

void ostendo::Window::DrawBorder() {
  if (window_border == true && window_pointer != NULL) {
    int pair = DispColor(border_color);
    wborder(window_pointer, border_character_set[0], border_character_set[1],
            border_character_set[2], border_character_set[3],
            border_character_set[4], border_character_set[5],
            border_character_set[6], border_character_set[7]);
    AttrOff(COLOR_PAIR(pair));
    pair_index--;
  } else if (window_border == false && window_pointer != NULL) {
    wborder(window_pointer, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  }
}

void ostendo::Window::DrawTitle() {}

void ostendo::Window::DrawMenuBar() {}
