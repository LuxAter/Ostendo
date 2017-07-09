#include "window.hpp"

#include <stdarg.h>
#include <string>

#include <ncurses.h>
#include <pessum/pessum.hpp>

#include "ostendo_core.hpp"

ostendo::Window::Window() {}

ostendo::Window::Window(unsigned int state) : pos_(std_scr) {
  GenerateWindow();
  ReadState(state);
}

ostendo::Window::Window(std::string name) : title_str_(name), pos_(std_scr) {
  GenerateWindow();
}

ostendo::Window::Window(std::string name, unsigned int state)
    : title_str_(name), pos_(std_scr) {
  GenerateWindow();
  ReadState(state);
}

ostendo::Window::Window(int width, int height) : pos_(width, height) {
  GenerateWindow();
}

ostendo::Window::~Window() {
  if (ptr_.use_count() == 1) {
    wclear(*ptr_);
    wrefresh(*ptr_);
    delwin(*ptr_);
  }
  ptr_ = NULL;
}

void ostendo::Window::DeleteWindow() {
  if (ptr_.use_count() == 1) {
    wclear(*ptr_);
    wrefresh(*ptr_);
    delwin(*ptr_);
  }
  ptr_ = NULL;
}

void ostendo::Window::SetBorder(bool setting) {
  if (border_ != setting && ptr_ != NULL) {
    border_ = setting;
    if (border_ == true) {
      DrawBorder();
    } else if (border_ == false) {
      EraseBorder();
    }
  }
}

void ostendo::Window::SetTitle(bool setting) {
  if (title_ != setting && ptr_ != NULL) {
    title_ = setting;
    if (title_ == true) {
      DrawTitle();
    } else if (title_ == false) {
      EraseTitle();
    }
  }
}

void ostendo::Window::SetTitleStr(std::string title) {
  if (title_ == true) {
    EraseTitle();
  }
  title_str_ = title;
  if (title_ == true) {
    DrawTitle();
  }
}

void ostendo::Window::SetTitleStr(const char* title) {
  if (title_ == true) {
    EraseTitle();
  }
  title_str_ = title;
  if (title_ == true) {
    DrawTitle();
  }
}

void ostendo::Window::SetTitlePosition(int position) {
  title_position_ = position;
  if (title_ == true) {
    EraseTitle();
    DrawTitle();
  }
}

void ostendo::Window::SetAutoUpdate(bool setting) { auto_update_ = setting; }

void ostendo::Window::SetWordBreak(bool setting) { word_break_ = setting; }

bool ostendo::Window::GetBorder() { return border_; }

bool ostendo::Window::GetTitle() { return title_; }

std::string ostendo::Window::GetTitleStr() { return title_str_; }

bool ostendo::Window::GetAutoUpdate() { return auto_update_; }

bool ostendo::Window::GetWordBreak() { return word_break_; }

void ostendo::Window::Scale(int dwidth, int dheight) {
  pos_.w += dwidth;
  pos_.h += dheight;
  if (ptr_ != NULL) {
    Resize();
  }
}

void ostendo::Window::Resize(int width, int height) {
  pos_.w = width;
  pos_.h = height;
  if (ptr_ != NULL) {
    Resize();
  }
}

void ostendo::Window::Translate(int dx, int dy) {
  pos_.x += dx;
  pos_.y += dy;
  if (ptr_ != NULL) {
    Move();
  }
}

void ostendo::Window::SetPosition(int x, int y) {
  pos_.x = x;
  pos_.y = y;
  if (ptr_ != NULL) {
    Move();
  }
}

void ostendo::Window::SetPosition(int width, int height, int x, int y) {
  pos_.w = width;
  pos_.h = height;
  pos_.x = x;
  pos_.y = y;
  if (ptr_ != NULL) {
    Resize();
    Move();
  }
}

void ostendo::Window::SetPosition(Position pos) {
  pos_ = pos;
  if (ptr_ != NULL) {
    Resize();
    Move();
  }
}

ostendo::Position ostendo::Window::GetPosition() {
  pessum::Log(pessum::DATA, "%ix%i @ (%i,%i,%i)",
              "ostendo::Window::GetPosition", pos_.w, pos_.h, pos_.x, pos_.y,
              pos_.z);
  return pos_;
}

void ostendo::Window::SetCursor(int x, int y) {
  if (ptr_ != NULL) {
    cursor_[0] = x;
    cursor_[1] = y;
  }
}

void ostendo::Window::GetCursor(int& x, int& y) {
  if (ptr_ != NULL) {
    x = cursor_[0];
    y = cursor_[1];
  }
}

void ostendo::Window::SetBufferSize(int size) {
  if (size > pos_.h) {
    buffer_.resize(size);
  }
}

int ostendo::Window::GetBufferSize() { return buffer_.size(); }

void ostendo::Window::Print(std::string fmt, ...) {
  if (ptr_ == NULL) {
    return;
  }
  va_list args;
  va_start(args, fmt);
  std::string str = FormatString(fmt, args);
  wprintw(*ptr_, str.c_str());
  if (auto_update_ == true) {
    Update();
  }
}

void ostendo::Window::mvPrint(int x, int y, std::string fmt, ...) {
  int curs_x, curs_y;
  GetCursor(curs_x, curs_y);
  if (x == -1) {
    x = curs_x;
  }
  if (y == -1) {
    y = curs_y;
  }
  va_list args;
  va_start(args, fmt);
  std::string str = FormatString(fmt, args);
  // mvwprintw(*ptr_, y, x, str.c_str());
  PrintBlock(x, y, str);
  if (auto_update_ == true) {
    Update();
  }
}

void ostendo::Window::Update() {
  if (ptr_ != NULL) {
    wrefresh(*ptr_);
  }
}

void ostendo::Window::Clear() {
  if (ptr_ != NULL) {
    wclear(*ptr_);
  }
}

void ostendo::Window::ClearAll() {
  if (ptr_ != NULL) {
    wclear(*ptr_);
    bool border_set = border_;
    bool title_set = title_;
    title_ = false;
    border_ = false;
    if (border_set == true) {
      EraseBorder();
    }
    if (title_set == true) {
      EraseTitle();
    }
    border_ = border_set;
    title_ = title_set;
  }
}

void ostendo::Window::GenerateWindow() {
  if (ptr_ != NULL) {
    pessum::Log(pessum::WARNING, "Window already initialized",
                "ostendo::Window::GenerateWindow");
  } else {
    ptr_ = std::make_shared<WINDOW*>(newwin(pos_.h, pos_.w, pos_.y, pos_.x));
    if (ptr_ == NULL) {
      pessum::Log(pessum::ERROR, "Failed to initialize window",
                  "ostendo::Window::GenerateWindow");
    }
  }
}

void ostendo::Window::ReadState(unsigned int state) {
  if ((state & CENTER) != 0) {
    SetTitlePosition(CENTER);
  }
  if ((state & LEFT) != 0) {
    SetTitlePosition(LEFT);
  }
  if ((state & RIGHT) != 0) {
    SetTitlePosition(RIGHT);
  }
  if ((state & BORDER) != 0) {
    SetBorder(true);
  }
  if ((state & TITLE) != 0) {
    SetTitle(true);
  }
  if ((state & AUTO_UPDATE) != 0) {
    SetAutoUpdate(true);
  }
}

void ostendo::Window::DrawTitle() {
  int title_width = title_str_.size();
  int title_start = 0;
  if (title_position_ == LEFT) {
    if (border_ == true) {
      title_start = 2;
    }
  } else if (title_position_ == CENTER) {
    title_start = (pos_.w - title_width) / 2;
  } else if (title_position_ == RIGHT) {
    title_start = pos_.w - title_width;
    if (border_ == true) {
      title_start -= 2;
    }
  }
  if (border_ == true) {
    mvwaddch(*ptr_, 0, title_start - 1, border_char_set_[8]);
  }
  mvwprintw(*ptr_, 0, title_start, title_str_.c_str());
  if (border_ == true) {
    mvwaddch(*ptr_, 0, title_start + title_width, border_char_set_[9]);
  }
  Update();
}

void ostendo::Window::DrawBorder() {
  wborder(*ptr_, border_char_set_[0], border_char_set_[1], border_char_set_[2],
          border_char_set_[3], border_char_set_[4], border_char_set_[5],
          border_char_set_[6], border_char_set_[7]);
  Update();
  if (title_ == true) {
    DrawTitle();
  }
}

void ostendo::Window::EraseTitle() {
  int title_width = title_str_.size();
  int title_start = 0;
  if (title_position_ == LEFT) {
    if (border_ == true) {
      title_start = 2;
    }
  } else if (title_position_ == CENTER) {
    title_start = (pos_.w - title_width) / 2;
  } else if (title_position_ == RIGHT) {
    title_start = pos_.w - title_width;
    if (border_ == true) {
      title_start -= 2;
    }
  }
  if (border_ == true) {
    mvwhline(*ptr_, 0, title_start - 1, border_char_set_[2], title_width + 2);
  } else if (border_ == false) {
    mvwhline(*ptr_, 0, title_start, ' ', title_width);
  }
  Update();
}

void ostendo::Window::EraseBorder() {
  wborder(*ptr_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  Update();
  if (title_ == true) {
    DrawTitle();
  }
}

void ostendo::Window::Resize() {
  if (ptr_ != NULL) {
    if (pos_.w != 0 && pos_.h != 0) {
      ClearAll();
      wresize(*ptr_, pos_.h, pos_.w);
      Update();
      if (border_ == true) {
        DrawBorder();
      }
      if (title_ == true) {
        DrawTitle();
      }
    } else {
      pessum::Log(pessum::WARNING, "New window size is invalid %ix%i",
                  "ostendo::Window::Resize", pos_.w, pos_.h);
    }
  }
}

void ostendo::Window::Move() {
  if (ptr_ != NULL) {
    if (pos_.w >= 0 && pos_.h >= 0) {
      ClearAll();
      mvwin(*ptr_, pos_.y, pos_.x);
      Update();
      if (border_ == true) {
        DrawBorder();
      }
      if (title_ == true) {
        DrawTitle();
      }
    } else {
      pessum::Log(pessum::WARNING, "New window position is invalid (%i,%i)",
                  "ostendo::Window::Resize", pos_.x, pos_.y);
    }
  }
}

std::string ostendo::Window::FormatString(std::string fmt, va_list args) {
  std::string formated_str = "";
  va_list buff_args;
  va_copy(buff_args, args);
  ssize_t buff_size = vsnprintf(NULL, 0, fmt.c_str(), buff_args);
  char* formated_string = new char[buff_size + 1];
  formated_string[buff_size] = '\0';
  vsprintf(formated_string, fmt.c_str(), args);
  formated_str = std::string(formated_string);
  va_end(buff_args);
  va_end(args);
  return formated_str;
}

void ostendo::Window::PrintBlock(int x, int y, std::string str) {
  mvwprintw(*ptr_, y, x, str.c_str());
}

void ostendo::Window::AddToBuffer(int x, int y, std::string str) {
  if (y < buffer_.size()) {
    int buffer_index = pos_.h - y;
    std::string buffer_str = buffer_[buffer_index];
    buffer_str.erase(x, GetFormatedLength(str));
    buffer_str.insert(x, str);
    buffer_[buffer_index] = buffer_str;
  }
}
