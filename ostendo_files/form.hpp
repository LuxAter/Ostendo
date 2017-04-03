#ifndef OSTENDO_FORM_HPP
#define OSTENDO_FORM_HPP
#include "types.hpp"
#include <vector>
#include "window.hpp"
namespace ostendo{
  std::vector<Var> Form(ostendo::Window win, std::vector<Var> fields);
}
#endif
