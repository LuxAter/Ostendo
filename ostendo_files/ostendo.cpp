#include <ncurses.h>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include "ostendo.hpp"
#include "types.hpp"

namespace ostendo {
  void (*log_handle)(std::string, std::string, std::string) = NULL;
  Pos std_scr;
}

void ostendo::InitOstendo(int time_out) {
  initscr();
  cbreak();
  keypad(stdscr, true);
  int std_scr_w, std_scr_h;
  getmaxyx(stdscr, std_scr_w, std_scr_h);
  noecho();
  curs_set(0);
  timeout(time_out);
  start_color();
  refresh();
}

void ostendo::TermOstendo() {
  nocbreak();
  echo();
  curs_set(1);
  refresh();
  endwin();
}

void ostendo::OstendoLog(int error_code, std::string log_string,
                         std::string function_string) {
  std::string log_type = "";
  std::string error_str = std::to_string(error_code);
  if (error_str[0] == '1') {
    log_type = "ERROR";
  }
  if (log_handle != NULL) {
    log_handle(log_type, log_string, function_string);
  }
}

void ostendo::SetLogHandle(void (*handle)(std::string, std::string,
                                          std::string)) {
  log_handle = handle;
}
