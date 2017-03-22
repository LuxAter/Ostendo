#include <ncurses.h>
#include <pessum.h>
#include <string>
#include "ostendo.hpp"
#include "types.hpp"
#include "window.hpp"

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

void ostendo::Window::DelWin() {
  wclear(window_pointer);
  wrefresh(window_pointer);
  delwin(window_pointer);
}

void ostendo::Window::NewWindow() {
  DelWin();
  window_pos = std_scr;
  GenWindow();
}

void ostendo::Window::NewWindow(int width, int height) {
  DelWin();
  window_pos = Pos(0, 0, width, height);
  GenWindow();
}

void ostendo::Window::NewWindow(int width, int height, int pos_x, int pos_y) {
  DelWin();
  window_pos = Pos(pos_x, pos_y, width, height);
  GenWindow();
}

void ostendo::Window::Update() {
  if (window_pointer != NULL) {
    wrefresh(window_pointer);
  }
}

void ostendo::Window::ToggleBorder() {
  window_border = !window_border;
  if (window_border == true && curs.first == 0) {
    curs.first++;
  }
  if (window_border == true && curs.second == 0) {
    curs.second++;
  }
  DrawBorder();
  if (window_title == true) {
    DrawTitle();
  }
}

void ostendo::Window::ToggleScroll() { window_scroll = !window_scroll; }

void ostendo::Window::ToggleTitle(std::string setting) {
  window_title = !window_title;
  if (setting != "") {
    window_title_str = setting;
  }
  if (window_title == true && curs.second == 0) {
    curs.second++;
  }
  DrawTitle();
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

void ostendo::Window::Clear(bool all) {
  if (window_pointer != NULL) {
    wclear(window_pointer);
    if (all == false) {
      if (window_border == true) {
        DrawBorder();
      }
      if (window_title == true) {
        DrawTitle();
      }
    }
  }
}

int ostendo::Window::Print(std::string str, ...) {
  if (window_pointer == NULL) {
    return (-1);
  }
  va_list args;
  va_start(args, str);
  char* formated_string = new char[256];
  vsprintf(formated_string, str.c_str(), args);
  va_end(args);
  str = std::string(formated_string);
  std::string substring;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '\n') {
      if (curs.second >= window_pos.h - window_border) {
        LastLine();
      }
      mvwprintw(window_pointer, curs.second, curs.first, substring.c_str());
      substring = "";
      curs.first = window_border;
      curs.second++;
    } else if (substring.length() + curs.second >
               window_pos.w - window_border) {
      if (curs.second >= window_pos.h - window_border) {
        LastLine();
      }
      mvwprintw(window_pointer, curs.second, curs.first, substring.c_str());
      substring = "";
      curs.first = window_border;
      curs.second++;
      i--;
    } else {
      substring += str[i];
    }
  }
  if (substring != "" && curs.second >= window_pos.h - window_border) {
    LastLine();
  }
  mvwprintw(window_pointer, curs.second, curs.first, substring.c_str());
  curs.first += substring.length();
  substring = "";
  Update();
  return (0);
}

void ostendo::Window::SetCurs(int y, int x) {
  if (x >= 0) {
    curs.first = x;
  }
  if (y >= 0) {
    curs.second = y;
  }
}

void ostendo::Window::GenWindow() {
  curs = std::make_pair(0, 0);
  window_pointer =
      newwin(window_pos.h, window_pos.w, window_pos.y, window_pos.x);
  if (window_pointer == NULL) {
    OstendoLog(10, "Failed to genorate window", "GenWindow");
  }
  Update();
}

void ostendo::Window::DrawBorder() {
  if (window_border == true && window_pointer != NULL) {
    wborder(window_pointer, border_character_set[0], border_character_set[1],
            border_character_set[2], border_character_set[3],
            border_character_set[4], border_character_set[5],
            border_character_set[6], border_character_set[7]);
  } else if (window_border == false && window_pointer != NULL) {
    wborder(window_pointer, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  }
  Update();
}

void ostendo::Window::DrawTitle() {
  if (window_title == true && window_pointer != NULL) {
    int pos = (window_pos.w - window_title_str.length()) / 2;
    mvwprintw(window_pointer, 0, pos, window_title_str.c_str());
  } else if (window_title == false && window_pointer != NULL) {
    unsigned long ch = int(' ');
    if (window_border == true) {
      ch = border_character_set[2];
    }
    mvwhline(window_pointer, 0, 1, ch, window_pos.w - 2);
  }
  Update();
}

void ostendo::Window::LastLine() {
  if (window_scroll == false && window_pointer != NULL) {
    Clear();
    curs = std::make_pair(0, 0);
    if (window_border == true || window_title == true) {
      curs.second++;
    }
    if (window_border == true) {
      curs.first++;
    }
  } else if (window_scroll == true && window_pointer != NULL) {
    curs.second = window_pos.h - window_border - 1;
    int start = 1;
    if (window_border == true || window_title == true) {
      start++;
    }
    for (int i = start; i < window_pos.h - window_border; i++) {
      for (int j = window_border; j < window_pos.w - window_border; j++) {
        unsigned long ch = mvwinch(window_pointer, i, j);
        mvwaddch(window_pointer, i - 1, j, ch);
      }
    }
  }
}
