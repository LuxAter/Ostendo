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
  if(sub_string != ""){
    lines.push_back(sub_string);
  }
  if (lines.size() == 0) {
    lines.push_back("");
  }
  bool running = true;
  int select_done = false;
  int current_line = 0;
  int start_line = 0;
  bool update = true;
  while (running == true) {
    if (update == true) {
      update = false;
      win.Clear();
      for (int i = 0;
           i < win.window_space.w - 2 && i < lines.size() + start_line; i++) {
        win.SetCurs(i + 1, 1);
        if (i + start_line == current_line) {
          win.Print("%s#ost #fst", lines[i + start_line].c_str());
        } else {
          win.Print("%s", lines[i + start_line].c_str());
        }
      }
      if (select_done == false) {
        win.SetCurs(win.window_space.h - 1, 0);
        win.Print("#cDone");
        select_done = 0;
      } else if (select_done == true) {
        win.SetCurs(win.window_space.h - 1, 0);
        win.Print("#c#ostDone#fst");
        select_done = 0;
      }
    }
    int in = getch();
    if (in == 10 && current_line < lines.size()) {
      update = true;
      current_line++;
      if (lines.size() == current_line) {
        if (lines.size() - start_line == win.window_space.h - 2) {
          start_line++;
        }
        lines.push_back("");
      }
    } else if (in == 10 && current_line == lines.size()) {
      running = false;
    } else if (in == KEY_DOWN && current_line < lines.size()) {
      update = true;
      current_line++;
      if (lines.size() == current_line) {
        select_done = 2;
      }
    } else if (in == KEY_UP && current_line < lines.size()) {
      update = true;
      if (current_line > 0) {
        current_line--;
      }
    } else if (in == KEY_UP && current_line == lines.size()) {
      update = true;
      current_line--;
      select_done = 1;
    } else if (in == KEY_BACKSPACE && current_line < lines.size()) {
      update = true;
      if (lines[current_line].size() > 0) {
        lines[current_line].pop_back();
      }else{
        current_line--;
        lines.pop_back();
      }
    } else if (in >= 32 && in <= 126 && current_line < lines.size()) {
      update = true;
      lines[current_line] += char(in);
      if (lines[current_line].size() == win.window_space.w - 1) {
        lines.push_back("");
        current_line++;
      }
    }
  }
  text = "";
  for (int i = 0; i < lines.size(); i++) {
    text += lines[i] + "\n";
  }
  return (text);
}
