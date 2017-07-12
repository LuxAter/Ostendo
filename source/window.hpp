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
  enum WindowSettings {
    BORDER = (1u << 0),
    TITLE = (1u << 1),
    AUTO_UPDATE = (1u << 2),
    WORD_BREAK = (1u << 3),
    CENTER = (1u << 4),
    LEFT = (1u << 5),
    RIGHT = (1u << 6)
  };
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
  enum LastLineAction { LLA_NONE, LLA_SCROLL, LLA_CLEAR };
  enum WindowElements { WE_BASE = 0, WE_TEXT = 1, WE_BORDER = 2, WE_TITLE = 3 };
  class Window {
   public:
    Window();
    explicit Window(unsigned int state);
    explicit Window(std::string name);
    Window(std::string name, unsigned int state);
    Window(int width, int height);
    ~Window();

    void DeleteWindow();

    void SetBorder(bool setting);
    void SetTitle(bool setting);
    void SetTitleStr(std::string title);
    void SetTitleStr(const char* title);
    void SetTitlePosition(int position);
    void SetAutoUpdate(bool setting);
    void SetWordBreak(bool setting);

    bool GetBorder();
    bool GetTitle();
    std::string GetTitleStr();
    bool GetAutoUpdate();
    bool GetWordBreak();

    void Scale(int dwidth, int dheight);
    void Resize(int width, int height);
    void Translate(int dx, int dy);
    void SetPosition(int x, int y);

    void SetPosition(int width, int height, int x, int y);
    void SetPosition(Position pos);

    Position GetPosition();

    void SetCursor(int x, int y);
    void GetCursor(int& x, int& y);

    void SetBufferSize(int size);
    int GetBufferSize();

    void Print(std::string fmt, ...);
    void mvPrint(int x, int y, std::string fmt, ...);

    void ToggleAttribute(int attr, bool setting);
    void SetAttribute(unsigned int attr);
    void SetColor(int foreground, int background);

    void SetBaseColor(int window_element, int foreground, int background);

    void SetLastLineAction(int action);

    void Update();
    void Clear();
    void ClearAll();
    void ClearLine(int line = -1);

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

    void PrintStr(int x, int y, std::string str);
    std::string ReadEscapeBlock(std::string str);
    std::array<int, 2> ParseAttr(std::vector<std::string> args);

    int ParseColor(std::string str);
    void UpdateColor();

    void HandleLastLine();

    bool auto_update_ = false, title_ = false, border_ = false,
         word_break_ = false;
    int title_position_ = CENTER;
    int last_line_action_ = LLA_NONE;
    std::string title_str_ = "";
    Position pos_;
    std::array<unsigned long, 10> border_char_set_ = {
        {ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
         ACS_LLCORNER, ACS_LRCORNER, ACS_RTEE, ACS_LTEE}};
    std::array<std::array<int, 2>, 4> base_color_ = {{{{WHITE, BLACK}},
                                                      {{WHITE, BLACK}},
                                                      {{WHITE, BLACK}},
                                                      {{WHITE, BLACK}}}};
    std::array<int, 2> cursor_ = {{0, 0}};
    std::array<int, 2> color_ = {{WHITE, BLACK}};
    std::vector<std::string> buffer_;

    std::shared_ptr<WINDOW*> ptr_ = NULL;
  };
}  // namespace ostendo

#endif
