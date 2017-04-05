#ifndef OSTENDO_FORM_HPP
#define OSTENDO_FORM_HPP
#include <vector>
#include "types.hpp"
#include "window.hpp"
namespace ostendo {
  std::vector<Var> Form(ostendo::Window win, std::vector<Var> fields);
  std::string GetVarStr(Var in_var, int width);
  Var DownArrow(Var in_var, Window win);
  Var UpArrow(Var in_var, Window win);
  Var RightArrow(Var in_var, Window win);
  Var LeftArrow(Var in_var, Window win);
  Var Enter(Var in_var, Window win);
  Var Backspace(Var in_var, Window win);
  Var Add(Var in_var, int ch, Window win);
}
#endif
