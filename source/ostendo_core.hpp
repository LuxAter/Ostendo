#ifndef OSTENDO_CORE_HPP
#define OSTENDO_CORE_HPP

#include <array>

#include <ncurses.h>

#include "position.hpp"

#define OSTENDO_VERSION_MAJOR 0
#define OSTENDO_VERSION_MINOR 5
#define OSTENDO_VERSION_PATCH 4

namespace ostendo {
  enum InitOptions {
    CBREAK = (1u << 0),
    RAW = (1u << 1),
    ECHO = (1u << 2),
    CURSOR = (1u << 3),
    MOUSE = (1u << 4),
    COLOR = (1u << 5)
  };

  extern Position std_scr;

  void InitOstendo(unsigned int state = 0);
  void TermOstendo();

  void SetCbreak(bool setting);
  void SetRaw(bool setting);
  void SetEcho(bool setting);
  void SetCursor(bool setting);
  void SetColor(bool setting);
  void SetTimeOut(int ms);

  bool GetCbreak();
  bool GetRaw();
  bool GetEcho();
  bool GetCursor();
  bool GetColor();
  int GetTimeOut();

  Position GetPosition(WINDOW* win);

  void GetVersion(int& major, int& minor, int& patch);
}  // namespace ostendo

#endif
