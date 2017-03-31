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
  extern std::map<std::string, Window> windows;
  extern int win_index;
  extern bool color_init;
  void InitOstendo(bool color = false, int time_out = -1);
  void TermOstendo();
  void OstendoLog(int error_code, std::string log_string,
                  std::string function_string);
  void SetLogHandle(void (*handle)(std::string, std::string, std::string));
  void InitWindow(std::string name);
  void InitWindow(std::string name, int width, int height);
  void InitWindow(std::string name, int width, int height, int x, int y);
  void TermWindow(std::string name);
  void LoadColors();
}
#endif
