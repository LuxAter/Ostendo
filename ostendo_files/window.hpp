#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP
#include <ncurses.h>
#include <map>
#include <string>
#include <vector>
#include "types.hpp"
namespace ostendo {
  class Window {
   public:
    Window();
    Window(int width, int height);
    Window(int width, int height, int pos_x, int pos_y);
    Window(Pos pos);
    Window(const Window& win);

    void DelWin();

    void NewWindow();
    void NewWindow(int width, int height);
    void NewWindow(int width, int height, int pos_x, int pos_y);

    void Update();
    void ToggleBorder();
    void ToggleScroll();
    void ToggleTitle(std::string setting = "");
    void AttrOn(int attrs);
    void AttrOn(std::vector<int> attrs);
    void AttrOff(int attrs);
    void AttrOff(std::vector<int> attrs);
    void SetAttr(int attrs);
    void SetAttr(std::vector<int> attrs);

    void Clear(bool all = false);
    void ClearLine(int line = -1);
    int Print(std::string str, ...);
    void SetCurs(int y = -1, int x = -1);

    inline WINDOW* operator()() { return (window_pointer); }

   private:
    void GenWindow();
    void DrawBorder();
    void DrawTitle();
    void LastLine();

    WINDOW* window_pointer = nullptr;
    bool window_border = false, window_title = false, window_scroll = false;
    std::string window_title_str;
    std::vector<unsigned long> border_character_set = {
        ACS_VLINE,    ACS_VLINE,    ACS_HLINE,    ACS_HLINE,
        ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER};
    Pos window_pos;
    std::pair<int, int> curs;
  };
}
#endif
