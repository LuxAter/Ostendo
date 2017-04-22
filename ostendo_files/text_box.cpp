#include <ncurses.h>
#include <pessum.h>
#include <string>
#include "text_box.hpp"
#include "window.hpp"

std::string ostendo::TextBox(ostendo::Window win, std::string base) {
  std::vector<std::string> lines;
  std::string sub_string = "";
  for (int i = 0; i < base.size(); i++) {
    if (base[i] == '\n' || sub_string.size() == win.window_space.w) {
      lines.push_back(sub_string);
      sub_string = "";
    } else {
      sub_string += base[i];
    }
  }
  lines.push_back(sub_string);
  return (TextBox(win, lines));
}
std::string ostendo::TextBox(ostendo::Window win,
                             std::vector<std::string> base) {
  std::vector<std::string> lines = base;
  bool running = true, update = true;
  int current_line = 0, start_line = 0;
  while (running == true) {
    if (update == true) {
      update = false;
      DisplayLines(win, lines, current_line, start_line);
    }
    int in = getch();
    if (in == KEY_UP && current_line > 0) {
      current_line--;
      update = true;
    } else if (in == KEY_DOWN && current_line < lines.size()) {
      current_line++;
      update = true;
    } else if (in == KEY_BACKSPACE && current_line != lines.size()) {
      if (lines[current_line].size() > 0) {
        lines[current_line].pop_back();
      } else if (current_line > 0) {
        lines.erase(lines.begin() + current_line);
        current_line--;
      }
      update = true;
    } else if (in == KEY_DC && current_line != lines.size()) {
      if (lines.size() > current_line + 1) {
        lines[current_line] += lines[current_line + 1];
        lines.erase(lines.begin() + current_line + 1);
        update = true;
      }
    } else if ((in == 10 || in == KEY_ENTER) && current_line != lines.size()) {
      lines.insert(lines.begin() + current_line + 1, "");
      current_line++;
      update = true;
    } else if ((in == 10 || in == KEY_ENTER) && current_line == lines.size()) {
      running = false;
    } else if (in >= 32 && in <= 126 && current_line != lines.size()) {
      lines[current_line] += char(in);
      update = true;
    }
  }
  std::string text = "";
  for (int i = 0; i < lines.size(); i++) {
    text += lines[i] + "\n";
  }
  return (text);
}

std::vector<std::string> ostendo::VTextBox(ostendo::Window win,
                                           std::string base) {
  std::vector<std::string> lines;
  std::string sub_string = "";
  for (int i = 0; i < base.size(); i++) {
    if (base[i] == '\n' || sub_string.size() == win.window_space.w) {
      lines.push_back(sub_string);
      sub_string = "";
    } else {
      sub_string += base[i];
    }
  }
  lines.push_back(sub_string);
  return (VTextBox(win, lines));
}

std::vector<std::string> ostendo::VTextBox(ostendo::Window win,
                                           std::vector<std::string> base) {
  std::vector<std::string> lines = base;
  bool running = true, update = true;
  int current_line = 0, start_line = 0;
  while (running == true) {
    if (update == true) {
      update = false;
      DisplayLines(win, lines, current_line, start_line);
    }
    int in = getch();
    if (in == KEY_UP && current_line > 0) {
      current_line--;
      update = true;
    } else if (in == KEY_DOWN && current_line < lines.size()) {
      current_line++;
      update = true;
    } else if (in == KEY_BACKSPACE && current_line != lines.size()) {
      if (lines[current_line].size() > 0) {
        lines[current_line].pop_back();
      } else if (current_line > 0) {
        lines.erase(lines.begin() + current_line);
        current_line--;
      }
      update = true;
    } else if (in == KEY_DC && current_line != lines.size()) {
      if (lines.size() > current_line + 1) {
        lines[current_line] += lines[current_line + 1];
        lines.erase(lines.begin() + current_line + 1);
        update = true;
      }
    } else if ((in == 10 || in == KEY_ENTER) && current_line != lines.size()) {
      lines.insert(lines.begin() + current_line + 1, "");
      current_line++;
      update = true;
    } else if ((in == 10 || in == KEY_ENTER) && current_line == lines.size()) {
      running = false;
    } else if (in >= 32 && in <= 126 && current_line != lines.size()) {
      lines[current_line] += char(in);
      update = true;
    }
  }
  return (lines);
}

void ostendo::DisplayLines(ostendo::Window win, std::vector<std::string> lines,
                           int current_line, int& start_line) {
  while (current_line - start_line >= win.window_space.h - 2 &&
         start_line + (win.window_space.h - 1) < lines.size()) {
    start_line++;
  }
  while (current_line - start_line < 1 && start_line > 0) {
    start_line--;
  }
  win.Clear();
  for (int i = 0; i < win.window_space.h - 2 && i + start_line < lines.size();
       i++) {
    win.SetCurs(i + 1, 1);
    if (i + start_line == current_line) {
      win.Print("%s#ost #fst", lines[i + start_line].c_str());
    } else if (i + start_line != current_line) {
      win.Print("%s", lines[i + start_line].c_str());
    }
  }
  if (current_line == lines.size()) {
    win.SetCurs(win.window_space.h - 1, 0);
    win.Print("#c#ostDone#fst");
  } else {
    win.SetCurs(win.window_space.h - 1, 0);
    win.Print("#cDone");
  }
}
