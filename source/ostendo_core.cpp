#include "ostendo_core.hpp"

#include <array>

#include <ncurses.h>
#include <pessum/pessum.hpp>

namespace ostendo {
  std::array<int, 5> std_scr;
  bool ostendo_cbreak = false, ostendo_raw = false, ostendo_echo = false,
       ostendo_cursor = false, ostendo_color = false;
  int ostendo_timeout;
}

void ostendo::InitOstendo(unsigned int state) {
  pessum::Log(pessum::INFO, "Ostendo Version: %i.%i.%i", "ostendo::InitOstendo",
              OSTENDO_VERSION_MAJOR, OSTENDO_VERSION_MINOR,
              OSTENDO_VERSION_PATCH);
  initscr();
  bool g_cbreak = false, g_raw = false, g_echo = false, g_cursor = false;
  if (state != 0) {
    if ((state & CBREAK) != 0) {
      SetCbreak(true);
    }
    if ((state & RAW) != 0 && g_cbreak != true) {
      SetRaw(true);
    }
    if ((state & ECHO) != 0) {
      SetEcho(true);
    }
    if ((state & CURSOR) != 0) {
      SetCursor(true);
    }
    if ((state & COLOR) != 0) {
      SetColor(true);
    }
  }
}

void ostendo::TermOstendo() {
  if (ostendo_cbreak == true) {
    SetCbreak(false);
  }
  if (ostendo_raw == true) {
    SetRaw(false);
  }
  if (ostendo_echo == true) {
    SetEcho(false);
  }
  if (ostendo_cursor == true) {
    SetCursor(false);
  }
  if (ostendo_color == true) {
    SetColor(false);
  }
  refresh();
  endwin();
}

void ostendo::SetCbreak(bool setting) {
  if (setting != ostendo_cbreak) {
    ostendo_cbreak = setting;
    if (ostendo_cbreak == true) {
      cbreak();
    } else if (ostendo_cbreak == false) {
      nocbreak();
    }
  }
}

void ostendo::SetRaw(bool setting) {
  if (setting != ostendo_raw) {
    ostendo_raw = setting;
    if (ostendo_raw == true) {
      raw();
    } else if (ostendo_raw == false) {
      noraw();
    }
  }
}

void ostendo::SetEcho(bool setting) {
  if (setting != ostendo_echo) {
    ostendo_echo = setting;
    if (ostendo_echo == true) {
      echo();
    } else if (ostendo_echo == false) {
      noecho();
    }
  }
}

void ostendo::SetCursor(bool setting) {
  if (setting != ostendo_cursor) {
    ostendo_cursor = setting;
    if (ostendo_cursor == true) {
      curs_set(1);
    } else if (ostendo_cursor == false) {
      curs_set(0);
    }
  }
}

void ostendo::SetColor(bool setting) {
  if (setting != ostendo_color) {
    ostendo_color = setting;
    if (ostendo_color == true) {
      if (has_colors()) {
        start_color();
      } else {
        pessum::Log(pessum::ERROR, "Terminal emulator does not support colors",
                    "ostendo::SetColor");
      }
    } else if (ostendo_color == false) {
    }
  }
}

void ostendo::SetTimeOut(int ms) {
  if (ms != ostendo_timeout) {
    ostendo_timeout = ms;
    timeout(ostendo_timeout);
  }
}

std::array<int, 5> ostendo::GetPosition(WINDOW* win) {
  std::array<int, 5> ret;
  if (win != NULL) {
    ret = {0, 0, 0, 0, -1};
    getmaxyx(win, ret[1], ret[0]);
  } else {
    ret = {0, 0, 0, 0, -1};
  }
}

void ostendo::GetVersion(int& major, int& minor, int& patch) {
  major = OSTENDO_VERSION_MAJOR;
  minor = OSTENDO_VERSION_MINOR;
  patch = OSTENDO_VERSION_PATCH;
}
