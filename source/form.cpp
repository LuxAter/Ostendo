#include "form.hpp"

#include <regex>

#include <ncurses.h>

#include "log.hpp"
#include "macros.hpp"
#include "window.hpp"

std::vector<std::string> RegExrs{
    "[+-]?[0-9]+",
    "[+-]?([0-9]*[.,])?[0-9]+",
    "[A-Za-z0-9_]+",
    ".+"
    "[0-1]?[0-9][-/.][0-3]?[0-9][-/.][0-9]?[0-9]?[0-9]{2}",
    "[0-2]?[0-9]:[0-5][0-9]",
    "[0-1]?[0-9]?[0-9]%"};

void ostendo::Form::DeleteForm() {
  win_.DeleteWindow();
  items_.clear();
}

void ostendo::Form::SetWindow(Window win) { win_ = win; }

void ostendo::Form::Run() {
  bool running = true, update = true;
  int in = ERR;
  selected = 0;
  // win_.Print("$fg:red$Hello World$0$Hello");
  while (running == true) {
    if (update == true) {
      update = false;
      Display();
    }
    in = getch();
    if (in == KEY_ENTER) {
      running = false;
    } else if (in == KEY_DOWN && selected < (int)items_.size() - 1) {
      selected++;
      update = true;
    } else if (in == KEY_UP && selected > 0) {
      selected--;
      update = true;
    } else {
      AddChar(in);
      update = true;
    }
  }
}

void ostendo::Form::PushBackItem(std::string name, std::string fmt) {
  items_.push_back(std::array<std::string, 3>{{name, fmt, ""}});
}

void ostendo::Form::PushBackItem(std::string name, int fmt) {
  items_.push_back(std::array<std::string, 3>{{name, RegExrs[fmt], ""}});
}

void ostendo::Form::Display() {
  size_t start = 0, end = items_.size();
  for (size_t i = start, y = 0; i < items_.size() && i < end; i++, y += 2) {
    int border = win_.GetOffSet()[0] + win_.GetOffSet()[1];
    std::string str = selection_setting_[0] + items_[i][0] +
                      selection_setting_[1] + ": " + selection_setting_[2] +
                      items_[i][2];
    str +=
        std::string(win_.GetPosition().w - win_.PrintSize(str) - border, ' ') +
        selection_setting_[3];
    if (i == (unsigned long)selected) {
      str = selection_setting_[4] + str + selection_setting_[5];
    }
    win_.mvPrint(0, y, str);
  }
  win_.Update();
}

void ostendo::Form::AddChar(int ch) {
  bool add = false;
  std::string current_str = items_[selected][2] + char(ch);
  // TODO(Arden): Add regex interpreter
  if (add == true) {
    items_[selected][2] += char(ch);
  }
}
