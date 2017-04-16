#include <ncurses.h>
#include <pessum.h>
#include <iostream>
#include "ostendo_files/ostendo_headers.hpp"

void log(std::string str) { pessum::Log(pessum::ERROR, str, "Ostendo"); }

int main(int argc, char const* argv[]) {
  ostendo::InitOstendo(true, 1);
  ostendo::Window win(40, 20);
  win.Clear();
  win.ToggleTitle("Hello Window!");
  win.ToggleBorder();
  win.Print("Hello World\n");
  win.Print("#l#ounleft#fun just\n#c#o15center just#f15\n#rright just\n");
  win.Print("Test int %i\nTest string %s\nTest double %f\n", 1998, "hello world", 3.1415);
  while (getch() != int('q')) {
  }
  win.DelWin();
  ostendo::TermOstendo();
  pessum::SaveLog("out.log");
  return 0;
}
