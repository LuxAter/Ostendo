#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP

#include <array>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <ncurses.h>

#include "position.hpp"

namespace ostendo {
  // Used for setting window options on creation.
  enum WindowSettings {
    BORDER = (1u << 0),
    TITLE = (1u << 1),
    AUTO_UPDATE = (1u << 2),
    WORD_BREAK = (1u << 3),
    CENTER = (1u << 4),
    LEFT = (1u << 5),
    RIGHT = (1u << 6)
  };
  // Used for defining color of output to the window.
  enum ColorAttribute {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7,
    DEFAULT = 8,
  };
  // Used for defining additional attributes of output to the window.
  enum OutputAttribute {
    ALTCHARSET = A_ALTCHARSET,
    BLINK = A_BLINK,
    BOLD = A_BOLD,
    DIM = A_DIM,
    INVIS = A_INVIS,
    PROTECT = A_PROTECT,
    REVERSE = A_REVERSE,
    STANDOUT = A_STANDOUT,
    UNDERLINE = A_UNDERLINE,
    NONE
  };
  // Used to define the handeling for printing at the final line.
  enum LastLineAction { LLA_NONE, LLA_SCROLL, LLA_CLEAR };
  // Used to define the different elements of a window.
  enum WindowElements { WE_BASE = 0, WE_TEXT = 1, WE_BORDER = 2, WE_TITLE = 3 };
  // Base class that controls all ncurses windows, and output to said windows.
  class Window {
   public:
    // Base constructor.
    Window();
    // Constructor accepting set of window settings.
    explicit Window(unsigned int state);
    // Constructor accpeting name and set of window settings.
    Window(std::string name, unsigned int state = 0);
    // Constructor accepting width/height and set of window settings.
    Window(int width, int height, unsigned int state = 0);
    // Constructor accepting name, width/height, and set of window settings.
    Window(std::string name, int width, int height, unsigned int state = 0);
    // Constructor accpeting width/height, x/y, and set of window settings.
    Window(int width, int height, int x, int y, unsigned int state = 0);
    // Constructor accepting position data as an array, and set of window
    // settings.
    Window(std::array<int, 4> pos, unsigned int state = 0);
    // Constructor accepting name, width/height, x/y, and set of window
    // settings.
    Window(std::string name, int width, int height, int x, int y,
           unsigned int state = 0);
    // Constructor accepting name, position data as an array, and set of window
    // settings.
    Window(std::string name, std::array<int, 4> pos, unsigned int state = 0);

    // Copy constructor.
    Window(const Window& win);

    // Base Destructor.
    ~Window();

    // Manual Destructor.
    void DeleteWindow();

    // Sets if the border should be drawn or not.
    void SetBorder(bool setting);
    // Sets if the title should be drawn or not.
    void SetTitle(bool setting);
    // Sets the title string.
    void SetTitleStr(std::string title);
    // Sets the title string.
    void SetTitleStr(const char* title);
    // Sets the title position(LEFT, CENTER, RIGHT) in the window.
    void SetTitlePosition(int position);
    // Sets if the window should auto update at all outputs.
    void SetAutoUpdate(bool setting);
    // Sets if the window should automatticaly move the line breaks to not split
    // words.
    void SetWordBreak(bool setting);

    // Checks if the border is drawn.
    bool GetBorder();
    // Checks if the title is drawn.
    bool GetTitle();
    // Gets the title string.
    std::string GetTitleStr();
    // Checks if the window will auto update.
    bool GetAutoUpdate();
    // Checks if the window will break lines at spaces.
    bool GetWordBreak();

    // Scales the window relativly to the current size.
    void Scale(int dwidth, int dheight);
    // Sets the size of the window.
    void Resize(int width, int height);
    // Moves the window relative to the current position.
    void Translate(int dx, int dy);
    // Sets the position of the window.
    void SetPosition(int x, int y);

    // Sets the width/height, and x/y of the window.
    void SetPosition(int width, int height, int x, int y);
    // Sets the position data of the window.
    void SetPosition(Position pos);

    // Returns the position data of the window.
    Position GetPosition();

    // Sets the cursor position for the window.
    void SetCursor(int x, int y);
    // Returns the current position of the cursor.
    void GetCursor(int& x, int& y);

    // Prints the formated string to the window at the cursor position.
    void Print(std::string fmt, ...);
    // Moves the cursor position, then prints the formated string to the window.
    void mvPrint(int x, int y, std::string fmt, ...);

    // Sets output attribute settings
    void ToggleAttribute(int attr, bool setting);
    // Disables all current attribues and sets new ones.
    void SetAttribute(unsigned int attr);
    // Sets the color of the output.
    void SetColor(int foreground, int background);

    // Sets color of window elements.
    void SetBaseColor(int window_element, int foreground, int background);

    // Sets the border character set.
    void SetBorderChars(std::array<unsigned long, 10> char_set);
    // Sets a border character.
    void SetBorderChar(int character, unsigned long ch);

    // Sets how printing on the final line should be handled.
    void SetLastLineAction(int action);

    // Updates the window.
    void Update();
    // Clears the window.
    void Clear();
    // Clears the window of everything, including border, and title.
    void ClearAll();
    // Clears a single line of the window.
    void ClearLine(int line = -1);

   protected:
   private:
    // Generates ncurses window.
    void GenerateWindow();
    // Reads and applys a set of window settings.
    void ReadState(unsigned int state);

    // Draws the title.
    void DrawTitle();
    // Draws the border.
    void DrawBorder();

    // Erases the title.
    void EraseTitle();
    // Erases the border.
    void EraseBorder();

    // Resizes the window.
    void Resize();
    // Moves the window.
    void Move();

    // Creates a formated string.
    std::string FormatString(std::string fmt, va_list args);

    // Prints string at coordinates.
    void PrintStr(int x, int y, std::string str);
    // Reads and applies any escape block entries.
    std::string ReadEscapeBlock(std::string str);
    // Parses escape block attributes.
    std::array<int, 2> ParseAttr(std::vector<std::string> args);

    // Parses color string to integer value.
    int ParseColor(std::string str);
    // Updates the output color.
    void UpdateColor();

    // Handles printing on last line of window.
    void HandleLastLine();

    bool auto_update_ = false, title_ = false, border_ = false,
         word_break_ = false;
    int title_position_ = CENTER, last_line_action_ = LLA_NONE;
    std::string title_str_ = "";

    std::array<unsigned long, 10> border_char_set_ = {
        {ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
         ACS_LLCORNER, ACS_LRCORNER, ACS_RTEE, ACS_LTEE}};

    std::array<std::array<int, 2>, 4> base_color_ = {{{{WHITE, BLACK}},
                                                      {{WHITE, BLACK}},
                                                      {{WHITE, BLACK}},
                                                      {{WHITE, BLACK}}}};
    std::array<int, 2> cursor_ = {{0, 0}};
    std::array<int, 2> color_ = {{WHITE, BLACK}};

    Position pos_;
    std::shared_ptr<WINDOW*> ptr_ = NULL;
  };
}  // namespace ostendo

#endif
