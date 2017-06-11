#ifndef OSTENDO_OSTENDO_HPP
#define OSTENDO_OSTENDO_HPP
#include <map>
#include <queue>
#include <string>
#include <utility>
#include "types.hpp"
#include "window.hpp"
//! Core namespace for all Ostendo methods
namespace ostendo {
  extern Pos
      std_scr; /*!<Width and height data for full window, measured at startup.*/
  extern std::map<std::string, Window>
      windows; /*!<Optional map for windows, to link windows with given name.*/
  extern int win_index; /*!<Current window index, from windows map.*/
  extern bool
      color_init; /*!<Boolian to check if colors have been initialized.*/
                  //! Initializes Ostendo/Ncurses
  /*!Initializes ncurses with default settings, and enables keypad input, and
   * reads std_scr data. Optionaly enables color, disables cursor, and sets
   * input timeout time.
   * \param color Determines if colors should be enabled.
   * \param cursor Determines if cursor should be disabled.
   * \param time_out Sets the time out time for intput. -1 for no time out.
   * \sa std_scr, windows, color_init, TermOstendo()
   */
  void InitOstendo(bool color = false, int time_out = -1);
  //! Terminates Ostendo/Ncurses
  /*!Terminates ncurses, and returns the console to standard settings.
   * \sa InitOstendo()
   */
  void TermOstendo();
  //! Creates a new window
  /*!Creates a new window, and adds it to windows. The window has the same
   * dimensions of std_scr.
   * \param name The name of the window for the key in windows map.
   * \sa windows, std_scr
   */
  void InitWindow(std::string name);
  //! Creates a new window
  /*!Creates a new window, and adds it to windows. The window is positioned at
   * 0,0 with given width and height.
   * \param name The name of the window for the key in windows map.
   * \param width The width of the window in characters.
   * \param height The height of the window in characters.
   * \sa windows, std_scr
   */
  void InitWindow(std::string name, int width, int height);
  //! Creates a new window
  /*!Creates a new window, and adds it to windows. The window is at a given
   * position with a given width and height.
   * \param name The name of the window for the key in windows map.
   * \param width The width of the window in characters.
   * \param height The height of the window in characters.
   * \param x The x position of the window in characters from the left.
   * \param y the y position of the window in characters from the top.
   * \sa windows, std_scr
   */
  void InitWindow(std::string name, int width, int height, int x, int y);
  //! Terminates a window
  /*! Termainates a specified window from the windows map.
   * \param name The name of the window to be deleted.
   * \sa windows
   */
  void TermWindow(std::string name);
  //! Loads console color pairs
  /*! Loads every combination of the console color pairs, if colors are
   * initialized.
   * \sa color_init
   */
  void LoadColors();
}
#endif
