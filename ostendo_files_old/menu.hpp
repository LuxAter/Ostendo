#ifndef OSTENDO_MENU_HPP
#define OSTENDO_MENU_HPP
#include <string>
#include <vector>
#include "window.hpp"
namespace ostendo {
  /*! Menu function for selecting an option from a set.
   * This function takes a set of options, and a window, then provides a simple
   * user interface for selecting one of the provided options. This selected
   * option is then returned.
   * \param win Window to use to display all options.
   * \param options Options that the user must select from.
   * \return String from selected option of Options.
   * \sa Window
   */
  std::string Menu(ostendo::Window win, std::vector<std::string> options);
}
#endif
