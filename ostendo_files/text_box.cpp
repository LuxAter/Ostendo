#include <ncurses.h>
#include <string>
#include "text_box.hpp"
#include "window.hpp"

std::string ostendo::TextBox(ostendo::Window win, std::string base) {
  std::string text = base;
  std::vector<std::string> lines;
  std::string sub_string = "";
  for (int i = 0; i < text.size(); i++) {
    if (text[i] == '\n' || sub_string.size() == win.window_space.w) {
      lines.push_back(sub_string);
      sub_string = "";
    } else {
      sub_string += text[i];
    }
  }
  if (lines.size() == 0) {
    lines.push_back("");
  }
  bool running = true;
  int select_done = 1;
  int current_line = 0;
  int start_line = 0;
  while (running == true) {
    if (select_done == 1) {
      win.SetCurs(win.window_space.h, 0);
      win.Print("#cDone");
      select_done = 0;
    } else if (select_done == 2) {
      win.SetCurs(win.window_space.h, 0);
      win.Print("#c#ostDone#fst");
      select_done = 0;
    }
    int in = getch();
    if (in == 10 && current_line < lines.size()) {
      win.ClearLine((current_line - start_line) + 1);
      win.SetCurs((current_line - start_line) + 1, 1);
      win.Print("%s", lines[current_line].c_str());
      current_line++;
      if (lines.size() == current_line) {
        if (lines.size() - start_line == win.window_space.h - 2) {
          start_line++;
        }
        lines.push_back("");
      }
      win.ClearLine((current_line - start_line) + 1);
      win.SetCurs((current_line - start_line) + 1, 1);
      win.Print("%s#ost #fst", lines[current_line].c_str());
    } else if (in == 10 && current_line == lines.size()) {
      running = false;
    } else if (in == KEY_DOWN && current_line < lines.size()) {
      win.ClearLine((current_line - start_line) + 1);
      win.SetCurs((current_line - start_line) + 1, 1);
      win.Print("%s", lines[current_line].c_str());
      current_line++;
      if (lines.size() == current_line) {
        select_done = 2;
      } else {
        win.ClearLine((current_line - start_line) + 1);
        win.SetCurs((current_line - start_line) + 1, 1);
        win.Print("%s#ost #fst", lines[current_line].c_str());
      }
    } else if (in == KEY_UP && current_line < lines.size()) {
      if (current_line > 0) {
        win.ClearLine((current_line - start_line) + 1);
        win.SetCurs((current_line - start_line) + 1, 1);
        win.Print("%s", lines[current_line].c_str());
        current_line--;
        win.ClearLine((current_line - start_line) + 1);
        win.SetCurs((current_line - start_line) + 1, 1);
        win.Print("%s#ost #fst", lines[current_line].c_str());
      }
    } else if (in == KEY_UP && current_line == lines.size()) {
      current_line--;
      select_done = 1;
      win.ClearLine((current_line - start_line) + 1);
      win.SetCurs((current_line - start_line) + 1, 1);
      win.Print("%s#ost #fst", lines[current_line].c_str());
    } else if (in == KEY_BACKSPACE && current_line < lines.size()) {
      if (lines[current_line].size() > 0) {
        lines[current_line].pop_back();
        win.ClearLine((current_line - start_line) + 1);
        win.SetCurs((current_line - start_line) + 1, 1);
        win.Print("%s#ost #fst", lines[current_line].c_str());
      }
    } else if (in >= 32 && in <= 126 && current_line < lines.size()) {
      lines[current_line] += char(in);
      if (lines[current_line].size() == win.window_space.w - 1) {
        win.ClearLine((current_line - start_line) + 1);
        win.SetCurs((current_line - start_line) + 1, 1);
        win.Print("%s", lines[current_line].c_str());
        lines.push_back("");
        current_line++;
      }
      win.ClearLine((current_line - start_line) + 1);
      win.SetCurs((current_line - start_line) + 1, 1);
      win.Print("%s#ost #fst", lines[current_line].c_str());
    }
  }
  text = "";
  for (int i = 0; i < lines.size(); i++) {
    text += lines[i] + "\n";
  }
  return (text);
}
