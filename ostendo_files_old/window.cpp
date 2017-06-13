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

ostendo::Window::Window(double width, double height) {
  window_pos = Pos(0, 0, std_scr.w * width, std_scr.h * height);
  GenWindow();
}

ostendo::Window::Window(int width, int height, int pos_x, int pos_y) {
  window_pos = Pos(pos_x, pos_y, width, height);
  GenWindow();
}

ostendo::Window::Window(int width, int height, double pos_x, double pos_y) {
  window_pos = Pos(std_scr.w * pos_x, std_scr.h * pos_y, width, height);
  GenWindow();
}

ostendo::Window::Window(double width, double height, double pos_x,
                        double pos_y) {
  window_pos = Pos(std_scr.w * pos_x, std_scr.h * pos_y, std_scr.w * width,
                   std_scr.h * height);
  GenWindow();
}

ostendo::Window::Window(double width, double height, int pos_x, int pos_y) {
  window_pos = Pos(pos_x, pos_y, std_scr.w * width, std_scr.h * height);
  GenWindow();
}

ostendo::Window::Window(Pos pos) {
  window_pos = pos;
  GenWindow();
}

ostendo::Window::Window(const Window& win) {
  window_pos = win.window_pos;
  window_pointer = win.window_pointer;
  window_space = win.window_space;
  window_border = win.window_border;
  window_title = win.window_title;
  window_scroll = win.window_scroll;
  window_title_str = win.window_title_str;
  border_character_set = win.border_character_set;
  curs = win.curs;
  border_color = win.border_color;
  title_color = win.title_color;
  background_color = win.background_color;
  text_color = win.text_color;
  auto_update = win.auto_update;
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

void ostendo::Window::NewWindow(double width, double height) {
  DelWin();
  window_pos = Pos(0, 0, std_scr.w * width, std_scr.h * height);
  GenWindow();
}

void ostendo::Window::NewWindow(int width, int height, int pos_x, int pos_y) {
  DelWin();
  window_pos = Pos(pos_x, pos_y, width, height);
  GenWindow();
}

void ostendo::Window::NewWindow(int width, int height, double pos_x,
                                double pos_y) {
  DelWin();
  window_pos = Pos(std_scr.w * pos_x, std_scr.h * pos_y, width, height);
  GenWindow();
}

void ostendo::Window::NewWindow(double width, double height, double pos_x,
                                double pos_y) {
  DelWin();
  window_pos = Pos(std_scr.w * pos_x, std_scr.h * pos_y, std_scr.w * width,
                   std_scr.h * height);
  GenWindow();
}

void ostendo::Window::NewWindow(double width, double height, int pos_x,
                                int pos_y) {
  DelWin();
  window_pos = Pos(pos_x, pos_y, std_scr.w * width, std_scr.h * height);
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

void ostendo::Window::SetAutoUpdate(bool setting) { auto_update = setting; }

void ostendo::Window::ColorOn(int attrs) {
  if (window_pointer != NULL) {
    wattron(window_pointer, COLOR_PAIR(attrs));
  }
}
void ostendo::Window::ColorOff(int attrs) {
  if (window_pointer != NULL) {
    wattroff(window_pointer, COLOR_PAIR(attrs));
  }
}

void ostendo::Window::AttrOn(int attrs) {
  bool good = true;
  if (attrs == ALTCHAR) {
    attrs = A_ALTCHARSET;
  } else if (attrs == BLINK) {
    attrs = A_BLINK;
  } else if (attrs == BOLD) {
    attrs = A_BOLD;
  } else if (attrs == DIM) {
    attrs = A_DIM;
  } else if (attrs == INVIS) {
    attrs = A_INVIS;
  } else if (attrs == PROTECT) {
    attrs = A_PROTECT;
  } else if (attrs == REVERSE) {
    attrs = A_REVERSE;
  } else if (attrs == STANDOUT) {
    attrs = A_STANDOUT;
  } else if (attrs == UNDERLINE) {
    attrs = A_UNDERLINE;
  } else {
    good = false;
  }
  if (window_pointer != NULL && good == true) {
    wattron(window_pointer, attrs);
  }
}

void ostendo::Window::AttrOff(int attrs) {
  bool good = true;
  if (attrs == ALTCHAR) {
    attrs = A_ALTCHARSET;
  } else if (attrs == BLINK) {
    attrs = A_BLINK;
  } else if (attrs == BOLD) {
    attrs = A_BOLD;
  } else if (attrs == DIM) {
    attrs = A_DIM;
  } else if (attrs == INVIS) {
    attrs = A_INVIS;
  } else if (attrs == PROTECT) {
    attrs = A_PROTECT;
  } else if (attrs == REVERSE) {
    attrs = A_REVERSE;
  } else if (attrs == STANDOUT) {
    attrs = A_STANDOUT;
  } else if (attrs == UNDERLINE) {
    attrs = A_UNDERLINE;
  } else {
    good = false;
  }
  if (window_pointer != NULL && good == true) {
    wattroff(window_pointer, attrs);
  }
}
void ostendo::Window::SetColor(int color, int value) {
  if (color == 1) {
    border_color = value;
  } else if (color == 2) {
    title_color = value;
  } else if (color == 3) {
    text_color = value;
  } else if (color == 4) {
    background_color = value;
  }
}

void ostendo::Window::Clear(bool all) {
  if (window_pointer != NULL) {
    ColorOn(background_color);
    wclear(window_pointer);
    curs = std::make_pair(0, 0);
    window_space = window_pos;
    if (all == false) {
      if (window_border == true) {
        DrawBorder();
      }
      if (window_title == true) {
        DrawTitle();
      }
    }
    if (window_border == true || window_title == true) {
      curs.second++;
    }
    if (window_border == true) {
      curs.first++;
    }
    ColorOff(background_color);
  }
}

void ostendo::Window::ClearLine(int line) {
  if (line == -1) {
    line = curs.second;
  }
  if (window_pointer != NULL) {
    ColorOn(background_color);
    if (window_border == true) {
      curs.first = 1;
      mvwhline(window_pointer, line, 1, ' ', window_pos.w - 2);
    } else if (window_border == false) {
      curs.first = 0;
      mvwhline(window_pointer, line, 0, ' ', window_pos.w);
    }
    ColorOff(background_color);
  }
  Update();
}

int ostendo::Window::Print(std::string str, ...) {
  if (window_pointer == NULL) {
    return (-1);
  }
  int align = 0;
  AttrOn(text_color);
  va_list args, buff_args;
  va_start(args, str);
  va_start(buff_args, str);
  ssize_t buff_size = vsnprintf(NULL, 0, str.c_str(), buff_args);
  char* formated_string = new char[buff_size + 1];
  formated_string[buff_size] = '\0';
  vsprintf(formated_string, str.c_str(), args);
  va_end(args);
  va_end(buff_args);
  str = std::string(formated_string);
  std::string substring;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '#') {
      bool off = false;
      int action = -1, index = 0;
      if (str.size() > i + 1) {
        if (str[i + 1] == 'o') {
          action = -2;
        } else if (str[i + 1] == 'f') {
          off = true;
          action = -2;
        } else if (str[i + 1] == 'l') {
          action = 0;
        } else if (str[i + 1] == 'c') {
          action = 1;
        } else if (str[i + 1] == 'r') {
          action = 2;
        }
        if (str.size() > i + 3 && action == -2) {
          if (str[i + 1] == 'a' && str[i + 2] == 'l') {
            action = 3;
            index = ALTCHAR;
          } else if (str[i + 2] == 'b' && str[i + 3] == 'l') {
            action = 3;
            index = BLINK;
          } else if (str[i + 2] == 'b' && str[i + 3] == 'o') {
            action = 3;
            index = BOLD;
          } else if (str[i + 2] == 'd' && str[i + 3] == 'i') {
            action = 3;
            index = DIM;
          } else if (str[i + 2] == 'i' && str[i + 3] == 'n') {
            action = 3;
            index = INVIS;
          } else if (str[i + 2] == 'p' && str[i + 3] == 'r') {
            action = 3;
            index = PROTECT;
          } else if (str[i + 2] == 'r' && str[i + 3] == 'e') {
            action = 3;
            index = REVERSE;
          } else if (str[i + 2] == 's' && str[i + 3] == 't') {
            action = 3;
            index = STANDOUT;
          } else if (str[i + 2] == 'u' && str[i + 3] == 'n') {
            action = 3;
            index = UNDERLINE;
          } else if (IsInt(str[i + 2]) && IsInt(str[i + 3])) {
            action = 4;
            index = (10 * (int(str[i + 2]) - 48)) + (int(str[i + 3]) - 48);
          }
        }
      }
      if (action != -1) {
        if (align == 1) {
          curs.first = (window_pos.w - substring.size()) / 2;
        } else if (align == 2) {
          curs.first = (window_pos.w - substring.size()) - window_border;
        }
        mvwprintw(window_pointer, curs.second, curs.first, substring.c_str());
        curs.first += substring.length();
        substring = "";
      }
      if (action == -1) {
        substring += str[i];
      } else if (action == 0) {
        i += 1;
        align = 0;
      } else if (action == 1) {
        i += 1;
        align = 1;
      } else if (action == 2) {
        i += 1;
        align = 2;
      } else if (action == 3) {
        i += 3;
        if (off == false) {
          AttrOn(index);
        } else if (off == true) {
          AttrOff(index);
        }
      } else if (action == 4) {
        i += 3;
        if (off == false) {
          ColorOn(index);
        } else if (off == true) {
          ColorOff(index);
        }
      }
    } else if (str[i] == '\n') {
      if (curs.second >= window_pos.h - window_border) {
        LastLine();
      }
      if (align == 1) {
        curs.first = (window_pos.w - substring.size()) / 2;
      } else if (align == 2) {
        curs.first = (window_pos.w - substring.size()) - window_border;
      }
      mvwprintw(window_pointer, curs.second, curs.first, substring.c_str());
      substring = "";
      curs.first = window_border;
      curs.second++;
    } else if (substring.length() + curs.first >=
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
  if (align == 1) {
    curs.first = (window_pos.w - substring.size()) / 2;
  } else if (align == 2) {
    curs.first = (window_pos.w - substring.size()) - window_border;
  }
  mvwprintw(window_pointer, curs.second, curs.first, substring.c_str());
  curs.first += substring.length();
  substring = "";
  AttrOff(text_color);
  if (auto_update == true) {
    Update();
  }
  return(0);
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
  window_space = Pos(0, 0, window_pos.h, window_pos.w);
  window_pointer =
      newwin(window_pos.h, window_pos.w, window_pos.y, window_pos.x);
  if (window_pointer == NULL) {
    pessum::Log(pessum::WARNING, "Failed to genorate window",
                "ostendo/Window/GenWindow");
  }
  Update();
  Clear();
}

void ostendo::Window::DrawBorder() {
  if (window_border == true && window_pointer != NULL) {
    if (window_title == true) {
      window_space.h -= 1;
      window_space.w -= 2;
    } else {
      window_space.h -= 2;
      window_space.w -= 2;
    }
    ColorOn(border_color);
    wborder(window_pointer, border_character_set[0], border_character_set[1],
            border_character_set[2], border_character_set[3],
            border_character_set[4], border_character_set[5],
            border_character_set[6], border_character_set[7]);
    ColorOff(border_color);
  } else if (window_border == false && window_pointer != NULL) {
    if (window_title == true) {
      window_space.h += 1;
      window_space.w += 2;
    } else {
      window_space.h += 2;
      window_space.w += 2;
    }
    ColorOn(background_color);
    wborder(window_pointer, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ColorOff(background_color);
  }
  Update();
}

void ostendo::Window::DrawTitle() {
  if (window_title == true && window_pointer != NULL) {
    if (window_border == false) {
      window_space.h -= 1;
    }
    ColorOn(title_color);
    int pos = (window_pos.w - window_title_str.length()) / 2;
    mvwprintw(window_pointer, 0, pos, window_title_str.c_str());
    ColorOff(title_color);
  } else if (window_title == false && window_pointer != NULL) {
    unsigned long ch = int(' ');
    if (window_border == true) {
      ColorOn(border_color);
      ch = border_character_set[2];
    } else {
      ColorOn(background_color);
    }
    mvwhline(window_pointer, 0, 1, ch, window_pos.w - 2);
    if (window_border == true) {
      window_space.h += 1;
      ColorOff(border_color);
    } else {
      ColorOff(background_color);
    }
  }
  Update();
}

void ostendo::Window::LastLine() {
  if (window_scroll == false && window_pointer != NULL) {
    Clear();
  } else if (window_scroll == true && window_pointer != NULL) {
    curs.second = window_pos.h - window_border - 1;
    curs.first = window_border;
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
    ClearLine(window_pos.h - window_border - 1);
  }
}

bool ostendo::Window::IsInt(char ch) {
  if (int(ch) >= 48 && int(ch) <= 57) {
    return (true);
  } else {
    return (false);
  }
}
