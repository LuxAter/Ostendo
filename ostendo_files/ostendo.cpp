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
  std::map<int, Window> windows;
  int win_index = 0;
}

void ostendo::InitOstendo(int time_out) {
  initscr();
  cbreak();
  keypad(stdscr, true);
  getmaxyx(stdscr, std_scr.h, std_scr.w);
  noecho();
  curs_set(0);
  timeout(time_out);
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

int ostendo::InitWindow() {
  win_index++;
  windows[win_index] = Window();
  return (win_index);
}

int ostendo::InitWindow(int width, int height) {
  win_index++;
  windows[win_index] = Window(width, height);
  return (win_index);
}

int ostendo::InitWindow(int width, int height, int x, int y) {
  win_index++;
  windows[win_index] = Window(width, height, x, y);
  return (win_index);
}

void ostendo::TermWindow(int index) {
  windows.at(index).DelWin();
  windows.erase(index);
}
