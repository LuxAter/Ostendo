#ifndef OSTENDO_FORM_HPP
#define OSTENDO_FORM_HPP

#include <string>
#include <vector>

#include <ncurses.h>

#include "window.hpp"

// TODO(Arden): Add basic form display framework
// TODO(Arden): Add form movement
// TODO(Arden): Add form entering (controled by regex)
// TODO(Arden): Add form option (select choice from menu)
// TODO(Arden): Add closing form
// TODO(Arden): Find a way to return form values

namespace ostendo {
  enum FormRegExr {
    NUMBER = 0,
    DECIMAL = 1,
    WORD = 2,
    LINE = 3,
    DATE = 4,
    TIME = 5,
    PERCENT = 6
  };
  class Form {
   public:
    void DeleteForm();

    void SetWindow(Window win);

    void Run();

    void PushBackItem(std::string name, std::string fmt);
    void PushBackItem(std::string name, int fmt);

   private:
    void Display();

    int selected = 0;
    std::vector<std::array<std::string, 3>> items_;
    std::array<std::string, 6> selection_setting_ = {
        {"", "", "$un:on$", "$un:off$", "$st:on$", "$st:off$"}};

    Window win_;
  };
}  // namespace ostendo
#endif
