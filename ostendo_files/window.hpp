#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP
#include <ncurses.h>
#include <stdarg.h>
#include <array>
#include <string>
#include "ostendo.hpp"
#include "size.hpp"

namespace ostendo {
  enum WindowOptions {
    BORDER = (1u << 0),
    TITLE = (1u << 1),
    AUTO_UPDATE = (1u << 2)
  };
  class Window {
   public:
    Window();
    Window(unsigned int state, std::string title = "");
    Window(unsigned int state, double w, double h, std::string title = "");
    Window(unsigned int state, double w, double h, double x, double y,
           std::string title = "");
    Window(const Window& copy);
    ~Window();

    void CreateWindow(double w, double h, double x, double y);

    void SetTitle(std::string title = "null");
    void SetTitle(const char* title = "null");

    bool SetBorder(int setting = -1);

    bool SetAutoUpdate(int setting = -1);

    void Show();

    void DeleteWindow();

    WINDOW* operator()() { return window_ptr; }

    Size size = Size(0, 0, 0, 0, 0);

   private:
    void GenWin();
    void ReadState(unsigned int state, std::string title);

    void DrawBorder();
    void ClearBorder();

    WINDOW* window_ptr = NULL;
    std::string win_title = "";
    bool border = false, auto_update = false;
    std::array<unsigned long, 9> border_character_set = {
        ACS_VLINE,    ACS_VLINE,    ACS_HLINE,    ACS_HLINE,
        ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER};
  };
}
#endif
