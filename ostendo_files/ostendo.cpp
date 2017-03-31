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
  std::map<std::string, Window> windows;
  int win_index = 0;
  bool color_init = false;
}

void ostendo::InitOstendo(bool color, int time_out) {
  initscr();
  cbreak();
  keypad(stdscr, true);
  getmaxyx(stdscr, std_scr.h, std_scr.w);
  noecho();
  curs_set(0);
  timeout(time_out);
  if(color == true){
    if(has_colors() == FALSE){
      OstendoLog(12, "Current terminal does not support color", "InitOstendo");
    }else{
      start_color();
      LoadColors();
    }
  }
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

void ostendo::InitWindow(std::string name) {
  windows[name] = Window();
}

void ostendo::InitWindow(std::string name, int width, int height) {
  windows[name] = Window(width, height);
}

void ostendo::InitWindow(std::string name, int width, int height, int x, int y) {
  windows[name] = Window(width, height, x, y);
}

void ostendo::TermWindow(std::string name) {
  windows.at(name).DelWin();
  windows.erase(name);
}

void ostendo::LoadColors(){
  for(int i = 0; i <= 7; i++){
    for(int j = 0; j <= 7; j++){
      init_pair((short)(i * 10 + j), (short)i, (short)j);
    }
  }
}
