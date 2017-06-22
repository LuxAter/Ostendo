#include "window.hpp"
#include <math.h>
#include <ncurses.h>
#include <pessum.h>
#include <stdarg.h>
#include <array>
#include <string>
#include "ostendo.hpp"
#include "size.hpp"

ostendo::Window::Window() {
  CreateWindow(std_scr.w, std_scr.h, std_scr.x, std_scr.y);
}

ostendo::Window::Window(unsigned int state, std::string title) {
  CreateWindow(std_scr.w, std_scr.h, std_scr.x, std_scr.y);
  ReadState(state, title);
}

ostendo::Window::Window(unsigned int state, double w, double h,
                        std::string title) {
  CreateWindow(w, h, std_scr.x, std_scr.y);
  ReadState(state, title);
}

ostendo::Window::Window(unsigned int state, double w, double h, double x,
                        double y, std::string title) {
  CreateWindow(w, h, x, y);
  ReadState(state, title);
}

ostendo::Window::Window(const Window& copy) {}

ostendo::Window::~Window() {}

void ostendo::Window::CreateWindow(double w, double h, double x, double y) {
  int iw, ih, ix, iy;
  if (floor(w) == w && w > 1.0) {
    iw = w;
  } else {
    iw = std_scr.w * w;
  }
  if (floor(h) == h && h > 1.0) {
    ih = h;
  } else {
    ih = std_scr.h * h;
  }
  if (floor(x) == x) {
    ix = x;
  } else {
    ix = std_scr.w * x;
  }
  if (floor(y) == y) {
    iy = y;
  } else {
    iy = std_scr.h * y;
  }
  size = Size(iw, ih, ix, iy);
  GenWin();
}

void ostendo::Window::SetTitle(std::string title) { win_title = title; }

void ostendo::Window::SetTitle(const char* title) {
  win_title = std::string(title);
}

bool ostendo::Window::SetBorder(int setting) {
  if (setting == true) {
    DrawBorder();
    border = setting;
  } else if (setting == false) {
    ClearBorder();
    border = setting;
  }
  return (border);
}

bool ostendo::Window::SetAutoUpdate(int setting) {
  if (setting == true || setting == false) {
    auto_update = setting;
  }
  return (auto_update);
}

void ostendo::Window::Show() {
  if (window_ptr != NULL) {
    wrefresh(window_ptr);
  } else {
    pessum::Log(pessum::WARNING, "Window has not been initialized",
                "ostendo::Window::Show");
  }
}

void ostendo::Window::DeleteWindow() {}

void ostendo::Window::GenWin() {
  if (window_ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window already initialized",
                "ostendo::Window::GenWin");
  } else {
    window_ptr = newwin(size.h, size.w, size.y, size.x);
    if (window_ptr == NULL) {
      pessum::Log(pessum::ERROR, "Failed to create window",
                  "ostendo::Window::GenWin");
    } else {
      pessum::Log(pessum::SUCCESS, "Created new window %ix%i at %i,%i",
                  "ostendo::Window::GenWin", size.w, size.h, size.x, size.y);
    }
  }
}

void ostendo::Window::ReadState(unsigned int state, std::string title) {
  if ((state & BORDER) != 0) {
    SetBorder(true);
  }
  if ((state & TITLE) != 0) {
    SetTitle(title);
  }
  if ((state & AUTO_UPDATE) != 0) {
    SetAutoUpdate(true);
  }
}

void ostendo::Window::DrawBorder() {
  if (window_ptr != NULL) {
    wborder(window_ptr, border_character_set[0], border_character_set[1],
            border_character_set[2], border_character_set[3],
            border_character_set[4], border_character_set[5],
            border_character_set[6], border_character_set[7]);
    wborder(window_ptr, '|', '|', '-', '-', '+', '+', '+', '+');
  }
}

void ostendo::Window::ClearBorder() {
  if (window_ptr != NULL) {
    // wborder(window_ptr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  }
}
