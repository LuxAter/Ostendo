#include <ncurses.h>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include "ostendo.hpp"
#include "pos.hpp"

namespace ostendo {
  void (*log_handle)(std::string);
  std::queue<std::pair<int, std::string>> ostendo_log;
  Pos std_scr;
}

void ostendo::InitOstendo() {
  initscr();
  cbreak();
  keypad(stdscr, true);
  int std_scr_w, std_scr_h;
  getmaxyx(stdscr, std_scr_w, std_scr_h);
  noecho();
  curs_set(0);
  refresh();
}

void ostendo::TermOstendo() {
  refresh();
  endwin();
  while (ostendo_log.empty() == false) {
    ostendo_log.pop();
  }
}

void ostendo::OstendoLog(int error_code, std::string log_string,
                         std::string function_string) {
  log_string += ">>[" + function_string + "]";
  ostendo_log.push(std::make_pair(error_code, log_string));
  log_handle(log_string);
}

void ostendo::SetLogHandle(void (*handle)(std::string)) { log_handle = handle; }
