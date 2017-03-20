#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP
#include <ncurses.h>
#include <string>
#include <vector>
#include "types.hpp"
namespace ostendo {
  extern int color_index, pair_index;
  enum Window_Option { WIN_BORDER = 0, WIN_TITLE = 1, WIN_MENU_BAR = 2 };
  class Window {
   public:
    Window();
    Window(int width, int height);
    Window(int width, int height, int pos_x, int pos_y);
    Window(Pos pos);
    Window(const Window& win);
    ~Window();

    void Update();
    void SetWindowOption(int option, bool setting);
    void SetWindowOption(int option, std::string setting);
    void SetWindowOption(int option, std::vector<std::string> setting);
    void AttrOn(int attrs);
    void AttrOn(std::vector<int> attrs);
    void AttrOff(int attrs);
    void AttrOff(std::vector<int> attrs);
    void SetAttr(int attrs);
    void SetAttr(std::vector<int> attrs);

    int SetColor(Color col);

    inline WINDOW* operator()() { return (window_pointer); }

   private:
    void GenWindow();
    void DrawBorder();
    void DrawTitle();
    void DrawMenuBar();

    WINDOW* window_pointer = nullptr;
    bool window_border = false, window_title = false, window_menu_bar = false;
    std::vector<std::string> menu_bar_options = {}, title_set = {};
    std::vector<unsigned long> border_character_set = {
        ACS_VLINE,    ACS_VLINE,    ACS_HLINE,    ACS_HLINE,
        ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER};
    Color border_color, text_color, background_color;
    Pos window_pos;
  };
}
#endif
