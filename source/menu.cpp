#include "menu.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include <pessum/pessum.hpp>

#include "macros.hpp"
#include "position.hpp"
#include "window.hpp"

void ostendo::Menu::DeleteMenu() {
  win_.DeleteWindow();
  items_.clear();
}

void ostendo::Menu::SetWindow(Window win) { win_ = Window(win); }

std::string ostendo::Menu::Run() {
  bool running = true, update = true;
  int in = ERR;
  position_ = {{0, 0}};
  MoveSelection(KEY_RIGHT);
  MoveSelection(KEY_LEFT);
  MoveSelection(KEY_DOWN);
  MoveSelection(KEY_UP);
  // win_.Print("$fg:red$Hello World$0$Hello");
  while (running == true) {
    if (update == true) {
      update = false;
      Display();
    }
    in = getch();
    if (in == int('q')) {
      running = false;
    } else if (in == KEY_ENTER) {
      running = false;
    } else if (MoveSelection(in) == true) {
      update = true;
    }
  }
  return items_[position_[0]][position_[1]].second;
}

int ostendo::Menu::RunInt() {
  bool running = true, update = true;
  int in = ERR;
  position_ = {{0, 0}};
  MoveSelection(KEY_RIGHT);
  MoveSelection(KEY_LEFT);
  MoveSelection(KEY_DOWN);
  MoveSelection(KEY_UP);
  while (running == true) {
    if (update == true) {
      update = false;
      Display();
    }
    in = getch();
    if (in == int('q')) {
      running = false;
    } else if (in == KEY_ENTER) {
      running = false;
    } else if (MoveSelection(in) == true) {
      update = true;
    }
  }
  return ItemIndex();
}

std::vector<std::string> ostendo::Menu::RunMulti() {
  bool running = true, update = true;
  int in = ERR;
  position_ = {{0, 0}};
  MoveSelection(KEY_RIGHT);
  MoveSelection(KEY_LEFT);
  MoveSelection(KEY_DOWN);
  MoveSelection(KEY_UP);
  multi_ = true;
  std::vector<std::string> selected;
  while (running == true) {
    if (update == true) {
      update = false;
      Display();
    }
    in = getch();
    if (in == int('q')) {
      running = false;
    } else if (in == KEY_ENTER && position_[1] != -1) {
      items_[position_[0]][position_[1]].first =
          !items_[position_[0]][position_[1]].first;
      std::vector<std::string>::iterator it =
          std::find(selected.begin(), selected.end(),
                    items_[position_[0]][position_[1]].second);
      if (it != selected.end()) {
        selected.erase(it);
      } else {
        selected.push_back(items_[position_[0]][position_[1]].second);
      }
      update = true;
    } else if (in == KEY_ENTER && position_[1] == -1) {
      running = false;
    } else if (MoveSelection(in) == true) {
      update = true;
    }
  }
  return selected;
}

std::vector<int> ostendo::Menu::RunMultiInt() {
  bool running = true, update = true;
  int in = ERR;
  position_ = {{0, 0}};
  MoveSelection(KEY_RIGHT);
  MoveSelection(KEY_LEFT);
  MoveSelection(KEY_DOWN);
  MoveSelection(KEY_UP);
  multi_ = true;
  std::vector<int> selected;
  while (running == true) {
    if (update == true) {
      update = false;
      Display();
    }
    in = getch();
    if (in == int('q')) {
      running = false;
    } else if (in == KEY_ENTER && position_[1] != -1) {
      items_[position_[0]][position_[1]].first =
          !items_[position_[0]][position_[1]].first;
      std::vector<int>::iterator it =
          std::find(selected.begin(), selected.end(), ItemIndex());
      if (it != selected.end()) {
        selected.erase(it);
      } else {
        selected.push_back(ItemIndex());
      }
      update = true;
    } else if (in == KEY_ENTER && position_[1] == -1) {
      running = false;
    } else if (MoveSelection(in) == true) {
      update = true;
    }
  }
  return selected;
}

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

bool ostendo::Menu::MoveSelection(int key) {
  bool moved = false;
  if (key == KEY_UP &&
      (position_[1] > 0 || (multi_ == true && position_[1] == -1))) {
    moved = true;
    int revert = position_[1];
    if (position_[1] == -1) {
      revert = items_[position_[0]].size() - 1;
      position_[1] = items_[position_[0]].size();
    }
    position_[1] -= 1;
    while (position_[1] > 0 &&
           items_[position_[0]][position_[1]].second == std::string()) {
      position_[1] -= 1;
    }
    if (items_[position_[0]][position_[1]].second == std::string()) {
      position_[1] = revert;
    }
  } else if (key == KEY_DOWN &&
             position_[1] < items_[position_[0]].size() - 1) {
    moved = true;
    int revert = position_[1];
    bool out = false;
    position_[1] += 1;
    while (position_[1] < items_[position_[0]].size() - 1 &&
           items_[position_[0]][position_[1]].second == "") {
      position_[1] += 1;
    }
    if (multi_ == true && items_[position_[0]][position_[1]].second == "") {
      out = true;
      position_[1] = -1;
    }
    if (out == false && items_[position_[0]][position_[1]].second == "") {
      position_[1] = revert;
    }
  } else if (key == KEY_DOWN && multi_ == true) {
    position_[1] = -1;
    moved = true;
  } else if (key == KEY_LEFT && position_[0] > 0 && position_[1] != -1) {
    int revert = position_[0];
    moved = true;
    position_[0] -= 1;
    while (position_[0] > 0 &&
           (items_[position_[0]].size() == 0 ||
            items_[position_[0]][position_[1]].second == std::string())) {
      position_[0] -= 1;
    }
    if (items_[position_[0]].size() == 0 ||
        items_[position_[0]][position_[1]].second == std::string()) {
      position_[0] = revert;
    }
    position_[1] =
        (std::min)((int)(items_[position_[0]].size() - 1), position_[1]);
  } else if (key == KEY_RIGHT && position_[0] < items_.size() - 1 &&
             position_[1] != -1) {
    int revert = position_[0];
    moved = true;
    position_[0] += 1;
    while (position_[0] < items_.size() - 1 &&
           (items_[position_[0]].size() == 0 ||
            items_[position_[0]][position_[1]].second == std::string())) {
      position_[0] += 1;
    }
    if (items_[position_[0]].size() == 0 ||
        items_[position_[0]][position_[1]].second == std::string()) {
      position_[0] = revert;
    }
    position_[1] =
        (std::min)((int)(items_[position_[0]].size() - 1), position_[1]);
  }
  return moved;
}

void ostendo::Menu::Display() {
  int width = Longest(-1) + 2;
  int begin = 0, end = items_.size();
  win_.GetPosition();
  if (win_.GetPosition().w > items_.size() * width && items_.size() > 0) {
    width = win_.GetPosition().w / items_.size();
  } else if (win_.GetPosition().w < items_.size() * width) {
    // Begin scroll columns??
    win_.SetScrollBar(SB_BOTTOM, true);
    win_.SetScroll(SB_BOTTOM, position_[0], items_.size() - 1);
    std::array<int, 4> win_offset = win_.GetOffSet();
    int screen_count =
        (win_.GetPosition().w - win_offset[0] - win_offset[1]) / width;
    begin = position_[0] - (screen_count / 2);
    end = begin + screen_count;
    if (begin < 0) {
      begin = 0;
      end = screen_count - 1;
    }
    if (end >= items_.size()) {
      end = items_.size();
      begin = end - screen_count;
    }
  }
  int x = 0;
  for (int i = begin; i < items_.size() && i < end; i++, x += width) {
    DisplayCol(i, x, width);
  }
  if (multi_ == true) {
    win_.bErase(CENTER, "%sDone%s", selection_setting_[0].c_str(),
                selection_setting_[1].c_str());
    if (position_[1] == -1) {
      win_.bPrint(CENTER, "%sDone%s", selection_setting_[0].c_str(),
                  selection_setting_[1].c_str());
    } else {
      win_.bPrint(CENTER, "Done");
    }
  }
  win_.Update();
}

void ostendo::Menu::DisplayCol(int col, int x, int width) {
  int height = 2;
  int begin = 0, end = items_[col].size();
  if (win_.GetPosition().h > items_[col].size() * height &&
      items_[col].size() > 0) {
    height = win_.GetPosition().h / items_[col].size();
    if (win_.GetScrollBar(SB_RIGHT) == true) {
      win_.SetScroll(SB_RIGHT, position_[1], items_[col].size() - 1);
    }
  } else {
    // Begin scroll column
    if (position_[0] == col) {
      win_.SetScrollBar(SB_RIGHT, true);
      win_.SetScroll(SB_RIGHT, position_[1], items_[col].size() - 1);
    }
    std::array<int, 4> win_offset = win_.GetOffSet();
    int screen_count =
        (win_.GetPosition().h - win_offset[2] - win_offset[3]) / 2;
    begin = position_[1] - (screen_count / 2);
    end = begin + screen_count;
    if (begin < 0) {
      begin = 0;
      end = screen_count;
    }
    if (end >= items_[col].size()) {
      end = items_[col].size();
      begin = end - screen_count;
    }
  }
  int y = 0;
  for (int i = begin; i < items_[col].size() && i < end; i++, y += height) {
    std::string str = items_[col][i].second;
    if (items_[col][i].first == true) {
      str = selection_setting_[2] + str + selection_setting_[3];
    }
    if (position_[0] == col && position_[1] == i) {
      // str = "a: $un:on$ hello " + str + " $0$ hello";
      str = selection_setting_[0] + str + selection_setting_[1];
    }
    str = std::string((width - win_.PrintSize(str)) / 2, ' ') + str;
    // pessum::Log(pessum::DEBUG, "%i", "", win_.PrintSize(str));
    win_.mvPrint(x, y, str);
  }
}

int ostendo::Menu::Longest(int col) {
  int longest = 0;
  if (col == -1) {
    for (int j = 0; j < items_.size(); j++) {
      for (int i = 0; i < items_[j].size(); i++) {
        longest = (std::max)(longest, win_.PrintSize(items_[j][i].second));
      }
    }
  } else if (col >= 0 && col < items_.size()) {
    for (int i = 0; i < items_[col].size(); i++) {
      longest = (std::max)(longest, win_.PrintSize(items_[col][i].second));
    }
  }
  return longest;
}

int ostendo::Menu::ItemIndex() {
  int item = 0;
  bool found = false;
  for (int i = 0; i < items_.size() && found == false; i++) {
    for (int j = 0; j < items_[i].size() && found == false; j++) {
      if (std::array<int, 2>{{i, j}} == position_) {
        found = true;
        break;
      }
      if (items_[i][j].second != "") {
        item++;
      }
    }
  }
  return item;
}
