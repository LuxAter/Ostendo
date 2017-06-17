#ifndef OSTENDO_OSTENDO_HPP
#define OSTENDO_OSTENDO_HPP

#define OSTENDO_VERSION_MAJOR 0
#define OSTENDO_VERSION_MINOR 4
#define OSTENDO_VERSION_PATCH 1

namespace ostendo {
  enum InitOptions {
    CBREAK = (1u << 0),
    RAW = (1u << 1),
    ECHO = (1u << 2),
    CURSOR = (1u << 3),
  };
  extern bool ostendo_cbreak, ostendo_raw, ostendo_echo, ostendo_cursor,
      ostendo_color;
  extern int ostendo_time_delay;
  void InitOstendo(unsigned int state = 0);
  void TermOstendo();
  bool Cbreak(int setting = -1);
  bool Raw(int setting = -1);
  bool Echo(int setting = -1);
  bool Cursor(int setting = -1);
  int TimeOut(int setting = -2);
  bool Color(int setting = -1);
  void GetVersion(int &major, int &minor, int &patch);
}
#endif
