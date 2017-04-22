#ifndef OSTENDO_TEXT_BOX_HPP
#define OSTENDO_TEXT_BOX_HPP
#include "window.hpp"
namespace ostendo {
  std::string TextBox(ostendo::Window win, std::string base = "");
  std::string TextBox(ostendo::Window win, std::vector<std::string> base);
  std::vector<std::string> VTextBox(ostendo::Window win, std::string base = "");
  std::vector<std::string> VTextBox(ostendo::Window win,
                                    std::vector<std::string> base);
  void DisplayLines(ostendo::Window win, std::vector<std::string> lines,
                    int current_line, int& start_line);
}
#endif
