#ifndef OSTENDO_WINDOW_HPP
#define OSTENDO_WINDOW_HPP

#include <ncurses.h>

namespace ostendo {
  enum WindowSettings {
    BORDER = (1u << 0),
    TITLE = (1u << 1),
    AUTO_UPDATE = (1u << 2)
  };
  class Window {
   public:
    Window();
    ~Window();

    void SetBorder();
    void SetTitle();
    void SetAutoUpdate();

   protected:
   private:
  };
};

#endif
