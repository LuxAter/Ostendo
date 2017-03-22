#ifndef OSTENDO_OSTENDO_HPP
#define OSTENDO_OSTENDO_HPP
#include <map>
#include <queue>
#include <string>
#include <utility>
#include "types.hpp"
#include "window.hpp"
namespace ostendo {
  extern void (*log_handle)(std::string, std::string, std::string);
  extern Pos std_scr;
  extern std::map<int, Window> windows;
  extern int win_index;
  void InitOstendo(int time_out = -1);
  void TermOstendo();
  void OstendoLog(int error_code, std::string log_string,
                  std::string function_string);
  void SetLogHandle(void (*handle)(std::string, std::string, std::string));
  int InitWindow();
  int InitWindow(int width, int height);
  int InitWindow(int width, int height, int x, int y);
  void TermWindow(int index);
}
#endif
