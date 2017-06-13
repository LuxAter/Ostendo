#ifndef OSTENDO_FORM_HPP
#define OSTENDO_FORM_HPP
#include <vector>
#include "types.hpp"
#include "window.hpp"
namespace ostendo {
  /*! Simple form function to get several inputs from the user.
   * This function takes a window, and a set of inputs to request of the user.
   * After the user enters the values for the requested inputs, the values are
   * returned.
   * \param win Window to use for displaying inputs.
   * \param fields Vector of Var's for taking in input from the user.
   * \return Vector of Var's filled with user input.
   * \sa Window, Var
   */
  std::vector<Var> Form(ostendo::Window win, std::vector<Var> fields);
  /*! Gets the string representation of the variable to display.
   * This function reads the Var object, and creates a string to represent the
   * data stored by the object.
   * \param in_var Var to interpret.
   * \param width Maximum width for return string.
   * \return String representation of in_var.
   * \sa Var.
   */
  std::string GetVarStr(Var in_var, int width);
  /*! Handles form user input arrow key down.
   * Provides functionality for different Var types for the user input of down
   * arrow key.
   * \param in_var Var to apply action to.
   * \param win Window to display to.
   * \return Var after action is applied.
   * \sa Var, Window
   */
  Var DownArrow(Var in_var, Window win);
  /*! Handles form user input arrow key up.
   * Provides functionality for different Var types for the user input of up
   * arrow key.
   * \param in_var Var to apply action to.
   * \param win Window to display to.
   * \return Var after action is applied.
   * \sa Var, Window
   */
  Var UpArrow(Var in_var, Window win);
  /*! Handles form user input arrow key right.
   * Provides functionality for different Var types for the user input of right
   * arrow key.
   * \param in_var Var to apply action to.
   * \param win Window to display to.
   * \return Var after action is applied.
   * \sa Var, Window
   */
  Var RightArrow(Var in_var, Window win);
  /*! Handles form user input arrow key left.
   * Provides functionality for different Var types for the user input of left
   * arrow key.
   * \param in_var Var to apply action to.
   * \param win Window to display to.
   * \return Var after action is applied.
   * \sa Var, Window
   */
  Var LeftArrow(Var in_var, Window win);
  /*! Handles form user input enter key.
   * Provides functionality for different Var types for the user input of enter
   * key.
   * \param in_var Var to apply action to.
   * \param win Window to display to.
   * \return Var after action is applied.
   * \sa Var, Window
   */
  Var Enter(Var in_var, Window win);
  /*! Handles form user input backspace key.
   * Provides functionality for different Var types for the user input of
   * backspace key.
   * \param in_var Var to apply action to.
   * \param win Window to display to.
   * \return Var after action is applied.
   * \sa Var, Window
   */
  Var Backspace(Var in_var, Window win);
  /*! Handles form user input of any other key.
   * Provides functionality for different Var types for the user input of any
   * other key.
   * \param in_var Var to apply action to.
   * \param ch Character representation of key input.
   * \param win Window to display to.
   * \return Var after action is applied.
   * \sa Var, Window
   */
  Var Add(Var in_var, int ch, Window win);
}
#endif
