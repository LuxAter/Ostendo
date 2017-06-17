#include "ostendo.hpp"
#include <ncurses.h>
#include <pessum.h>

namespace ostendo {
  bool ostendo_cbreak = false, ostendo_raw = false, ostendo_echo = false,
       ostendo_cursor = false, ostendo_color = false;
  int ostendo_time_delay;
}

void ostendo::InitOstendo(unsigned int state) {
  pessum::Log(pessum::INFO, "Ostendo Version: %i.%i.%i", "ostendo::InitOstendo",
              OSTENDO_VERSION_MAJOR, OSTENDO_VERSION_MINOR,
              OSTENDO_VERSION_PATCH);
  initscr();
  bool g_cbreak = false, g_raw = false, g_echo = false, g_cursor = false;
  if (state != 0) {
    if ((state & CBREAK) != 0) {
      g_cbreak = true;
    }
    if ((state & RAW) != 0 && g_cbreak != true) {
      g_raw = true;
    }
    if ((state & ECHO) != 0) {
      g_echo = true;
    }
    if ((state & CURSOR) != 0) {
      g_cursor = true;
    }
  }
  Cbreak(g_cbreak);
  Raw(g_raw);
  Echo(g_echo);
  Cursor(g_cursor);
}

void ostendo::TermOstendo() {
  nocbreak();
  echo();
  curs_set(1);
  refresh();
  endwin();
}

bool ostendo::Cbreak(int setting) {
  if (setting == true) {
    cbreak();
    ostendo_cbreak = setting;
  } else if (setting == false) {
    nocbreak();
    ostendo_cbreak = setting;
  }
  return (ostendo_cbreak);
}

bool ostendo::Raw(int setting) {
  if (setting == true) {
    raw();
    ostendo_raw = setting;
  } else if (setting == false) {
    noraw();
    ostendo_raw = setting;
  }
  return (ostendo_raw);
}

bool ostendo::Echo(int setting) {
  if (setting == true) {
    echo();
    ostendo_echo = setting;
  } else if (setting == false) {
    noecho();
    ostendo_echo = setting;
  }
  return (ostendo_echo);
}

bool ostendo::Cursor(int setting) {
  if (setting == true) {
    curs_set(1);
    ostendo_cursor = setting;
  } else if (setting == false) {
    curs_set(0);
    ostendo_cursor = setting;
  }
  return (ostendo_cursor);
}

int ostendo::TimeOut(int setting) {
  if (setting != -2) {
    timeout(setting);
    ostendo_time_delay = setting;
  }
  return (ostendo_time_delay);
}

bool ostendo::Color(int setting) {
  if (setting == true) {
    if (has_colors() == false) {
      pessum::Log(pessum::WARNING, "Terminal emulator does not support colors",
                  "ostendo::Color");
    } else {
      start_color();
    }
  } else if (setting == false) {
  }
  return (ostendo_color);
}

void ostendo::GetVersion(int &major, int &minor, int &patch) {
  major = OSTENDO_VERSION_MAJOR;
  minor = OSTENDO_VERSION_MINOR;
  patch = OSTENDO_VERSION_PATCH;
}
