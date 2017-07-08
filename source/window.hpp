#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP

#include <array>
#include <memory>
#include <string>

#include <ncurses.h>

#include "position.hpp"

namespace ostendo {
  enum WindowSettings {
    BORDER = (1u << 0),
    TITLE = (1u << 1),
    AUTO_UPDATE = (1u << 2),
    CENTER = (1u << 3),
    LEFT = (1u << 4),
    RIGHT = (1u << 5)
  };
  class Window {
   public:
    Window();
    explicit Window(unsigned int state);
    explicit Window(std::string name);
    Window(std::string name, unsigned int state);
    Window(int width, int height);
    ~Window();

    void SetBorder(bool setting);
    void SetTitle(bool setting);
    void SetTitleStr(std::string title);
    void SetTitleStr(const char* title);
    void SetTitlePosition(int position);
    void SetAutoUpdate(bool setting);

    bool GetBorder();
    bool GetTitle();
    std::string GetTitleStr();
    bool GetAutoUpdate();

    void Scale(int dwidth, int dheight);
    void Resize(int width, int height);
    void Translate(int dx, int dy);
    void SetPosition(int x, int y);

    void SetPosition(int width, int height, int x, int y);
    void SetPosition(Position pos);

    Position GetPosition();

    void SetCursor(int x, int y);
    void GetCursor(int& x, int& y);

    void Print(std::string fmt, ...);
    void mvPrint(int x, int y, std::string fmt, ...);

    void Update();
    void Clear();
    void ClearAll();

   protected:
   private:
    void GenerateWindow();
    void ReadState(unsigned int state);

    void DrawTitle();
    void DrawBorder();

    void EraseTitle();
    void EraseBorder();

    void Resize();
    void Move();

    std::string FormatString(std::string fmt, va_list args);

    bool auto_update_ = false, title_ = false, border_ = false;
    int title_position_ = CENTER;
    std::string title_str_ = "";
    Position pos_;
    std::array<unsigned long, 10> border_char_set_ = {
        {ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
         ACS_LLCORNER, ACS_LRCORNER, ACS_RTEE, ACS_LTEE}};

    std::shared_ptr<WINDOW*> ptr_ = NULL;
  };
};

#endif
