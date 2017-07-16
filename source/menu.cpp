#include "menu.hpp"

void ostendo::Menu::DeleteMenu() {
  win_.DeleteWindow();
  items_.clear();
}

void ostendo::Menu::SetWindow(Window win) { win_ = win; }

std::string ostendo::Menu::Run() {
  bool running = true, update = true;
  int in = ERR;
  while (running == true) {
    if (update == true) {
      update = false;
      Display();
    }
    in = getch();
    if (in == int('q')) {
      running = false;
    }
  }
  return std::string();
}

int ostendo::Menu::RunInt() { return int(); }

std::vector<std::string> ostendo::Menu::RunMulti() {
  return std::vector<std::string>();
}

std::vector<int> ostendo::Menu::RunMultiInt() { return std::vector<int>(); }

void ostendo::Menu::PushBackItem(std::string item, int col) {
  if (col >= items_.size()) {
    items_.resize(col);
  }
  items_[col].push_back(std::make_pair(false, item));
}

void ostendo::Menu::InsertItem(std::string item, int position, int col) {
  if (col >= items_.size()) {
    items_.resize(col);
  }
  if (position >= items_[col].size()) {
    items_[col].resize(position);
  }
  items_[col].insert(items_[col].begin() + position,
                     std::make_pair(false, item));
}

void ostendo::Menu::PushBackColumn(std::vector<std::string> col) {
  std::vector<std::pair<bool, std::string>> new_col;
  for (int i = 0; i < col.size(); i++) {
    new_col.push_back(std::make_pair(false, col[i]));
  }
  items_.push_back(new_col);
}

void ostendo::Menu::InsertColumn(std::vector<std::string> col, int position) {
  if (position >= items_.size()) {
    items_.resize(position);
  }
  std::vector<std::pair<bool, std::string>> new_col;
  for (int i = 0; i < col.size(); i++) {
    new_col.push_back(std::make_pair(false, col[i]));
  }
  items_.insert(items_.begin() + position, new_col);
}

void ostendo::Menu::SetItems(std::vector<std::vector<std::string>> items) {
  items_.resize(items.size());
  for (int i = 0; i < items.size(); i++) {
    items_[i].resize(items[i].size());
    for (int j = 0; j < items[i].size(); j++) {
      items_[i][j] = std::make_pair(false, items[i][j]);
    }
  }
}

void ostendo::Menu::ClearItems() { items_.clear(); }

void ostendo::Menu::Display() {
  int width = Longest(-1) + 1;
  if (win_.GetPosition().w > items_.size() * width && items_.size() > 0) {
    width = win_.GetPosition().w / items_.size();
  }
  for (int i = 0; i < items_.size(); i++) {
    DisplayCol(i, width * i, width);
  }
  if (multi_ == true) {
    if (position == std::array<int, 2>{{-1, -1}}) {
      win_.mvPrint(win_.GetPosition().w / 2, win_.GetPosition().h - 1, "Ok");
    } else {
      win_.mvPrint(win_.GetPosition().w / 2, win_.GetPosition().h - 1, "Ok");
    }
  }
  win_.Update();
}

void ostendo::Menu::DisplayCol(int col, int x, int width) {
  int height = 1;
  if (win_.GetPosition().h > items_[col].size() * height &&
      items_[col].size() > 0) {
    height = win_.GetPosition().h / items_[col].size();
  }
  int y = 0;
  for (int i = 0; i < items_[col].size(); i++, y += height) {
    std::string str = items_[col][i].second;
    str = std::string((width - str.size() - 1) / 2, ' ') + str;
    // win_.mvPrint(x, y, str);
    // win_.mvPrint(x, y, items_[col][i].second);
  }
}

int ostendo::Menu::Longest(int col) {
  int longest = 0;
  if (col == -1) {
    for (int j = 0; j < items_.size(); j++) {
      for (int i = 0; i < items_[j].size(); i++) {
        longest = std::max(longest, win_.PrintSize(items_[j][i].second));
      }
    }
  } else if (col >= 0 && col < items_.size()) {
    for (int i = 0; i < items_[col].size(); i++) {
      longest = std::max(longest, win_.PrintSize(items_[col][i].second));
    }
  }
  return longest;
}
