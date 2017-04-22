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
  std::string out = ostendo::TextBox(win, "Hello World My name is arden!!\n Did this work?");
  // while (getch() != int('q')) {
  // }
  win.DelWin();
  ostendo::TermOstendo();
  pessum::SaveLog("out.log");
  return 0;
}
