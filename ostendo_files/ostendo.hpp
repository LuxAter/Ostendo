#ifndef OSTENDO_OSTENDO_HPP
#define OSTENDO_OSTENDO_HPP
#include <queue>
#include <string>
#include <utility>
#include "types.hpp"
namespace ostendo {
  extern void (*log_handle)(std::string, std::string, std::string);
  extern Pos std_scr;
  void InitOstendo();
  void TermOstendo();
  void OstendoLog(int error_code, std::string log_string,
                  std::string function_string);
  void SetLogHandle(void (*handle)(std::string, std::string, std::string));
}
#endif
