#include <ncurses.h>
#include <pessum.h>
#include <iostream>
#include "ostendo_files/ostendo_headers.hpp"

void log(std::string str) { pessum::logging::Log(str); }

int main(int argc, char const* argv[]) {
  pessum::InitializePessum(true, true);
  ostendo::InitOstendo(1);
  ostendo::SetLogHandle(pessum::logging::Log);
  ostendo::Window win(40, 20);
  win.ToggleTitle("Hello Window!");
  win.ToggleBorder();
  win.ToggleScroll();
  int counter = 0;
  int pause = 0;
  std::string input = "";
  bool update = true, running = true;
  while (running == true) {
    if (update == true) {
      update = false;
      win.ClearLine();
      win.Print(">>%s", input.c_str());
    }
    int in = getch();
    if (in == 10) {
      win.Print("\n");
      // RunInput(input);
      input = "";
    } else if (in == KEY_BACKSPACE) {
      if (input.length() > 0) {
        input.pop_back();
        update = true;
      }
    } else if (in != ERR) {
      input += char(in);
      update = true;
    }
  }
  win.DelWin();
  ostendo::TermOstendo();
  pessum::TerminatePessum();
  return 0;
}
