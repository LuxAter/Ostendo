#include "ostendo_core.hpp"

#include <array>

#include <locale.h>

#include <ncurses.h>

#include "log.hpp"
#include "position.hpp"

namespace ostendo {
  Position std_scr;
  bool ostendo_cbreak = false, ostendo_raw = false, ostendo_echo = false,
       ostendo_cursor = false, ostendo_color = false;
  int ostendo_timeout;
}

void ostendo::InitOstendo(unsigned int state) {
  ostendo::log::Log(ostendo::log::INFO, "Ostendo Version: %i.%i.%i",
                    "ostendo::InitOstendo", OSTENDO_VERSION_MAJOR,
                    OSTENDO_VERSION_MINOR, OSTENDO_VERSION_PATCH);
  initscr();
  if ((state & CBREAK) != 0) {
    SetCbreak(true);
  }
  if ((state & RAW) != 0 && (state & CBREAK) == 0) {
    SetRaw(true);
  }
  if ((state & ECHO) != 0) {
    SetEcho(true);
  } else {
    SetEcho(false);
  }
  if ((state & CURSOR) != 0) {
    SetCursor(true);
  } else {
    SetCursor(false);
  }
  if ((state & COLOR) != 0) {
    SetColor(true);
  } else {
    SetColor(false);
  }
  keypad(stdscr, true);
  setlocale(LC_ALL, "");
  refresh();
  std_scr = GetPosition(stdscr);
}

void ostendo::TermOstendo() {
  if (ostendo_cbreak == true) {
    SetCbreak(false);
  }
  if (ostendo_raw == true) {
    SetRaw(false);
  }
  if (ostendo_echo == false) {
    SetEcho(true);
  }
  if (ostendo_cursor == false) {
    SetCursor(true);
  }
  if (ostendo_color == true) {
    SetColor(false);
  }
  refresh();
  endwin();
}

void ostendo::SetCbreak(bool setting) {
  ostendo_cbreak = setting;
  if (ostendo_cbreak == true) {
    cbreak();
  } else if (ostendo_cbreak == false) {
    nocbreak();
  }
}

void ostendo::SetRaw(bool setting) {
  ostendo_raw = setting;
  if (ostendo_raw == true) {
    raw();
  } else if (ostendo_raw == false) {
    noraw();
  }
}

void ostendo::SetEcho(bool setting) {
  ostendo_echo = setting;
  if (ostendo_echo == true) {
    echo();
  } else if (ostendo_echo == false) {
    noecho();
  }
}

void ostendo::SetCursor(bool setting) {
  ostendo_cursor = setting;
  if (ostendo_cursor == true) {
    curs_set(1);
  } else if (ostendo_cursor == false) {
    curs_set(0);
  }
}

void ostendo::SetColor(bool setting) {
  ostendo_color = setting;
  if (ostendo_color == true) {
    if (has_colors()) {
      start_color();
      for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
          init_pair((short)(i * 10 + j), (short)i, (short)j);
        }
      }
    } else {
      ostendo::log::Log(ostendo::log::ERROR,
                        "Terminal emulator does not support colors",
                        "ostendo::SetColor");
    }
  } else if (ostendo_color == false) {
  }
}

void ostendo::SetTimeOut(int ms) {
  ostendo_timeout = ms;
  timeout(ostendo_timeout);
}

ostendo::Position ostendo::GetPosition(WINDOW* win) {
  std::array<int, 4> ret = {{0, 0, 0, 0}};
  if (win != NULL) {
    getmaxyx(win, ret[1], ret[0]);
  }
  ostendo::log::Log(ostendo::log::DATA, "%ix%i @ (%i,%i)",
                    "ostendo::GetPosition", ret[0], ret[1], ret[2], ret[3]);
  return Position(ret);
}

void ostendo::GetVersion(int& major, int& minor, int& patch) {
  major = OSTENDO_VERSION_MAJOR;
  minor = OSTENDO_VERSION_MINOR;
  patch = OSTENDO_VERSION_PATCH;
}
