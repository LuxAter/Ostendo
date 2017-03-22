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
  // ostendo::Window win(40, 20);
  win.ToggleTitle("Hello Window!");
  win.ToggleBorder();
  win.ToggleScroll();
  // win.Print(
  // "Hello Arden!\nThis is a test? will it work correctly lets find out!!");
  // win.Print("A");
  int counter = 0;
  int pause = 0;
  while (true) {
    int in = getch();
    if (pause > 1) {
      win.Print("%i\n", counter);
      counter++;
      pause = 0;
    }
    if (in == int('q')) {
      break;
    }
    pause++;
  }
  win.DelWin();
  // ostendo::TermWindow(win);
  ostendo::TermOstendo();
  pessum::TerminatePessum();
  return 0;
}
