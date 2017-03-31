#include <ncurses.h>
#include <pessum.h>
#include <iostream>
#include "ostendo_files/ostendo_headers.hpp"

void log(std::string str) { pessum::logging::Log(str); }

int main(int argc, char const* argv[]) {
  pessum::InitializePessum(true, true);
  ostendo::InitOstendo(true, 1);
  ostendo::SetLogHandle(pessum::logging::Log);
  ostendo::Window win(40, 20);
  win.SetColor(ostendo::WIN_BORDER, 12);
  win.SetColor(ostendo::WIN_TITLE, 34);
  win.SetColor(ostendo::WIN_TEXT, 56);
  win.Clear();
  win.ToggleTitle("Hello Window!");
  win.ToggleBorder();
  win.Print("Hello arden how are you this is a long line to test to see if it works, and the new line functions don't seem to work correctly. This does not seem to be working right every time there is a new line it seems to jump to a new line a little sooner.");
  while(getch() != int('q')){
  }
  win.DelWin();
  ostendo::TermOstendo();
  pessum::TerminatePessum();
  return 0;
}
