#ifndef OSTENDO_TEXT_BOX_HPP
#define OSTENDO_TEXT_BOX_HPP
#include "window.hpp"
namespace ostendo {
  /*!Function for basic extended text entry from user.
   * This function alows the user to write text to a text box, and when
   * compleated, the writen text is formated into a string.
   * \param win window to display to.
   * \param base Starting string to display in text box.
   * \return String of what user entered.
   * \sa Window
   */
  std::string TextBox(ostendo::Window win, std::string base = "");
  /*!Function for basic extended text entry from user.
   * This function alows the user to write text to a text box, and when
   * compleated, the writen text is formated into a string.
   * \param win window to display to.
   * \param base Starting vector of strings representing different lines of
   * text.
   * \return String of what user entered.
   * \sa Window
   */
  std::string TextBox(ostendo::Window win, std::vector<std::string> base);
  /*!Function for basic extended text entry from user.
   * This function alows the user to write text to a text box, and when
   * compleated, the writen text is formated into a a vector of strings, each
   * representing a lines of text.
   * \param win window to display to.
   * \param base Starting string to display in text box.
   * \return Vector of strings representing the different lines of input from
   * the user.
   * \sa Window
   */
  std::vector<std::string> VTextBox(ostendo::Window win, std::string base = "");
  /*!Function for basic extended text entry from user.
   * This function alows the user to write text to a text box, and when
   * compleated, the writen text is formated into a a vector of strings, each
   * representing a lines of text.
   * \param win window to display to.
   * \param base Starting vector of stirngs representing different lines of
   * text.
   * \return Vector of strings representing the different lines of input from
   * the user.
   * \sa Window
   */
  std::vector<std::string> VTextBox(ostendo::Window win,
                                    std::vector<std::string> base);
  /*!Displays lines from a vector of strings.
   * Displays the lines from a vector of string to a given window, and auto
   * centers the current line, so that it is always on screen.
   * \param win Window to display to.
   * \param lines Vector of string to display.
   * \param current_line Current line to center in window.
   * \param start_line line of vector to begin display from.
   * \sa Window
   */
  void DisplayLines(ostendo::Window win, std::vector<std::string> lines,
                    int current_line, int& start_line);
}
#endif
