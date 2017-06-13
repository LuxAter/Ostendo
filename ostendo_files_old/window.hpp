#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP
#include <ncurses.h>
#include <map>
#include <string>
#include <vector>
#include "types.hpp"
namespace ostendo {
  //! Declaration for different components of the window.
  enum WINDOW_PARTS {
    WIN_BORDER = 1,    /*!<Selects the window border.*/
    WIN_TITLE = 2,     /*!<Selects the window title.*/
    WIN_TEXT = 3,      /*!<Selects the window test.*/
    WIN_BACKGROUND = 4 /*!<Selects the window background.*/
  };
  //! Declaration for different output attributes.
  enum ATTRS {
    ALTCHAR = 1, /*!<Uses alternate character set.*/
    BLINK = 2, /*!<Sets output to blinking (If posible in terminal emulator).*/
    BOLD = 3,  /*!<Sets output to bold.*/
    DIM = 4,   /*!<Sets output to dim colors.*/
    INVIS = 5, /*!<Sets output text to be invisable.*/
    PROTECT = 5,  /*!<Sets output mode to protected.*/
    REVERSE = 6,  /*!<Sets output to reverse mode.*/
    STANDOUT = 7, /*!<Sets output to be heighlighted.*/
    UNDERLINE = 8 /*!<Sets output to be underlined.*/
  };
  //! Core of everything output to the console.
  /*! The Window class is the base of everything that is output to the console.
   * Everything output must be part of a window, and the windows controll all
   * outputs, and output attributes.*/
  class Window {
   public:
    //! Creates a new window.
    /*! Creates a new window with the same base setting of std_scr.
     * \sa std_scr*/
    Window();
    //! Creates a new window.
    /*! Creates a new window with given width and height, at 0,0.
     * \param width Width of window.
     * \param height Height of window.*/
    Window(int width, int height);
    //! Creates a new window.
    /*! Creates a new window with width and height as a percentage of std_scr.
     * \param width Percentage of width.
     * \param height Percentage of height.
     * \sa std_scr
     */
    Window(double width, double height);
    //! Creates a new window.
    /*! Creates a new window with given width and height, at given position.
     * \param width Width of window.
     * \param height Height of window.
     * \param pos_x X position of window.
     * \param pos_y Y position of window.*/
    Window(int width, int height, int pos_x, int pos_y);
    //! Creates a new window.
    /*! Creates a new window with given width and height, and at x and y of
     * percentage of std_scr.
     * \param width Width of window.
     * \param height Height of window.
     * \param pos_x Percentage of width.
     * \param pos_y Percentage of height.
     * \sa std_scr
     */
    Window(int width, int height, double pos_x, double pos_y);
    //! Creates a new window.
    /*! Creates a new window with width and height as a percentage of std_scr,
     * and at x and y of percentage of std_scr.
     * \param width Percentace of width.
     * \param height Percentage of height.
     * \param pos_x Percentage of width.
     * \param pos_y Percentage of height.
     * \sa std_scr
     */
    Window(double width, double height, double pos_x, double pos_y);
    //! Creates a new window.
    /*! Creates a new window with given width and height, and at x and y.
     * \param width Percentage of width.
     * \param height Percentage of height.
     * \param pos_x X position of window.
     * \param pos_y Y position of window.
     * \sa std_scr
     */
    Window(double width, double height, int pos_x, int pos_y);
    //! Creates a new window.
    /*! Creates a window with the width, height, and position given by Position
     * object.
     * \param pos Position definition of window.
     * \sa Pos
     */
    Window(Pos pos);
    //! Copies a window.
    /*! Creates a copy of a given window.
     * \param win Window to create a copy of.
     */
    Window(const Window& win);

    //! Deletes window.
    /*Deletes all window data, and erases ncurses window. Should be called
     * before dereferencing window objects.*/
    void DelWin();

    //! Deletes window and creates a new window.
    /*! Creates a new window with the same base setting of std_scr.
     * \sa std_scr*/
    void NewWindow();
    //! Deletes window and creates a new window.
    /*! Creates a new window with given width and height, at 0,0.
     * \param width Width of window.
     * \param height Height of window.*/
    void NewWindow(int width, int height);
    //! Deletes window and creates a new window.
    /*! Creates a new window with width and height as a percentage of std_scr.
     * \param width Percentage of width.
     * \param height Percentage of height.
     * \sa std_scr
     */
    void NewWindow(double width, double height);
    //! Deletes window and creates a new window.
    /*! Creates a new window with given width and height, at given position.
     * \param width Width of window.
     * \param height Height of window.
     * \param pos_x X position of window.
     * \param pos_y Y position of window.*/
    void NewWindow(int width, int height, int pos_x, int pos_y);
    //! Deletes window and creates a new window.
    /*! Creates a new window with given width and height, and at x and y of
     * percentage of std_scr.
     * \param width Width of window.
     * \param height Height of window.
     * \param pos_x Percentage of width.
     * \param pos_y Percentage of height.
     * \sa std_scr
     */
    void NewWindow(int width, int height, double pos_x, double pos_y);
    //! Deletes window and creates a new window..
    /*! Creates a new window with width and height as a percentage of std_scr,
     * and at x and y of percentage of std_scr.
     * \param width Percentace of width.
     * \param height Percentage of height.
     * \param pos_x Percentage of width.
     * \param pos_y Percentage of height.
     * \sa std_scr
     */
    void NewWindow(double width, double height, double pos_x, double pos_y);
    //! Deletes window and creates a new window.
    /*! Creates a new window with given width and height, and at x and y.
     * \param width Percentage of width.
     * \param height Percentage of height.
     * \param pos_x X position of window.
     * \param pos_y Y position of window.
     * \sa std_scr
     */
    void NewWindow(double width, double height, int pos_x, int pos_y);

    //! Updates window display.
    /*! Updates the window display, to show recently printed outputs. Must be
     * called for display to be visible.
     */
    void Update();
    //! Toggles drawing window border.
    /*! Toggles wether the window border should be drawn.
     */
    void ToggleBorder();
    //! Toggles window scrolling
    /*! Toggles if the window should handle last line output by scrolling.
     */
    void ToggleScroll();
    //! Toggles window title
    /*! Toggles wether the window title should be drawn.
     * \param setting String to set as the new window title.
     */
    void ToggleTitle(std::string setting = "");

    //! Sets window auto updating.
    /*! Sets window auto updating to specified value.
     * \param setting Value to set auto updating to.
     */
    void SetAutoUpdate(bool setting = true);

    //! Enables a color for output.
    /*! Enables output color.
     * \param attrs Color index represented by a two digit number.
     */
    void ColorOn(int attrs);
    //! Disables a color for output.
    /*! Disables previously enabled output color.
     * \param attrs Color index represented by a two digit number.
     */
    void ColorOff(int attrs);
    //! Enables an attribute for output.
    /*! Enables output attribute.
     * \param attrs Attribute value from Attrs.
     * \sa Attrs
     */
    void AttrOn(int attrs);
    //! Disables an attribute for output.
    /*! Disables previously enabled output attribute.
     * \param attrs Attribute value from Attrs.
     * \sa Attrs
     */
    void AttrOff(int attrs);
    //! Sets display color of window part.
    /*! Sets the color of compnents of the window.
     * \param color Color represented by two digit number.
     * \param value Window component to color.
     */
    void SetColor(int color, int value);
    //! Clears window of outputs.
    /*! Clears window of all ouputs.
     * \param all If true, then clears window of border and title aswell.
     */
    void Clear(bool all = false);
    //! Clears the current line of window.
    /*! Clears the current line of cursor y, and sets cursor x to begining of
     * the line.
     * \param line Specify line to clear.
     */
    void ClearLine(int line = -1);
    //! Print output to window.
    /*!Main output function for ostendo. str is a formated string such as for
     * printf, with additional arguments as required. Accepts additional excape
     * sequenced initialized with a '#'. '#o__' will turn on specified
     * attribute, while '#f__' will turn off the specified attribute. Attributes
     * can be two digit numbers (0-7)(0-7), where the first number is the
     * forground color, and the second number is the backround color. These
     * attributes can also be any of the following: ac(alternate character set),
     * bl(blink), bo(bold), di(dim), in(invisible), pr(protected), re(reverse),
     * st(standout), un(underlined).
     * \param str Format string.
     * \param ... Additional arguments as required.
     * \return -1 if window has not been initialized, otherwise 0.
     */
    int Print(std::string str, ...);
    //! Sets cursor position in window.
    /*! Sets the position of the output cursor for the window.
     * \param x X position of the cursor.
     * \param y Y position of the cursor.
     */
    void SetCurs(int y = -1, int x = -1);

    //! Gets ncurses window pointer.
    /*! Gets the ncurses window pointer for the current window.
     * \return pointer to ncurses window.
     */
    inline WINDOW* operator()() { return (window_pointer); }

    Pos window_space; /*!<Window space avalible for output (Excluding
                         borders/title).*/

   private:
    //! Creates ncurses window.
    /*! Genorates the ncurses window based off of set values for window size and
     * position.
     * \sa NewWindow(), Window(), window_pos
     */
    void GenWindow();
    //! Draws window border.
    /*! Draws the window border if window_border is true.
     * \sa window_border, ToggleBorder()
     */
    void DrawBorder();
    //! Draws window title.
    /*! Draws the set title for window if window_title is true.
     * \sa window_title, ToggleTitle()
     */
    void DrawTitle();
    //! Handles output when window is full.
    /*! If window_scroll is true, then all previous outputs are shifted up one
     * line, to alow for another line of output, otherwise the window is
     * cleared, and the cursor is placed in the top left.
     * \sa window_scroll, Printf(), ToggleScroll()
     */
    void LastLine();
    //! Checks if charicter is an integer value.
    /*! Checks if given character is an integer.
     * \param ch Character to check.
     * \return true if the charcter is an integer.
     */
    bool IsInt(char ch);

    WINDOW* window_pointer = nullptr; /*!<Pointer to Ncurses window object.*/
    bool window_border = false,
         /*!<Determines if the window border should be drawn.*/ window_title =
             false,
         /*!<Determines if the window title should be drawn.*/ window_scroll =
             false, /*!<Determines if the window scrolls when output reaches the
                       end.*/
        auto_update = true; /*!<Determines if the window should update after
                               every output.*/
    std::string window_title_str; /*!< Title of the window.*/
    std::vector<unsigned long> border_character_set = {
        ACS_VLINE,    ACS_VLINE,    ACS_HLINE,   ACS_HLINE, ACS_ULCORNER,
        ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER}; /*!< Character set for the
                                                      characters to draw the
                                                      border with*/
    Pos window_pos;                                /*!<Window position and size.
                                                    * \sa Pos
                                                    */
    std::pair<int, int>
        curs;              /*!<Current cursor position relative to the window.*/
    int border_color = 70, /*!<Color to draw the window border.*/
        title_color = 70,  /*<Color to draw the window title*/
        background_color = 70, /*<Color to draw the background of the window*/
        text_color = 70;       /*!<Base color for text output.*/
  };
}
#endif
