#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP
#include <ncurses.h>
#include <map>
#include <string>
#include <vector>
#include "types.hpp"
namespace ostendo {
  enum WINDOW_PARTS{
    WIN_BORDER = 1,
    WIN_TITLE = 2,
    WIN_TEXT = 3,
    WIN_BACKGROUND = 4
  };
  enum ATTRS{
    ALTCHAR = 1,
    BLINK = 2,
    BOLD = 3,
    DIM = 4,
    INVIS = 5,
    PROTECT = 5,
    REVERSE = 6,
    STANDOUT = 7,
    UNDERLINE = 8
  };
  class Window {
   public:
    Window();
    Window(int width, int height);
    Window(double width, double height);
    Window(int width, int height, int pos_x, int pos_y);
    Window(double width, double height, double pos_x, double pos_y);
    Window(Pos pos);
    Window(const Window& win);

    void DelWin();

    void NewWindow();
    void NewWindow(int width, int height);
    void NewWindow(double width, double height);
    void NewWindow(int width, int height, int pos_x, int pos_y);
    void NewWindow(double width, double height, double pos_x, double pos_y);

    void Update();
    void ToggleBorder();
    void ToggleScroll();
    void ToggleTitle(std::string setting = "");

    void SetAutoUpdate(bool setting = true);

    void ColorOn(int attrs);
    void ColorOff(int attrs);
    void AttrOn(int attrs);
    void AttrOff(int attrs);
    void SetColor(int color, int value);

    void Clear(bool all = false);
    void ClearLine(int line = -1);
    int Print(std::string str, ...);
    void SetCurs(int y = -1, int x = -1);

    inline WINDOW* operator()() { return (window_pointer); }
    
    Pos window_space;

   private:
    void GenWindow();
    void DrawBorder();
    void DrawTitle();
    void LastLine();
    bool IsInt(char ch);

    WINDOW* window_pointer = nullptr;
    bool window_border = false, window_title = false, window_scroll = false, auto_update = true;
    std::string window_title_str;
    std::vector<unsigned long> border_character_set = {
        ACS_VLINE,    ACS_VLINE,    ACS_HLINE,    ACS_HLINE,
        ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER};
    Pos window_pos;
    std::pair<int, int> curs;
    int border_color = 70, title_color = 70, background_color = 70, text_color = 70;
  };
}
#endif
