#include <ncurses.h>
#include <pessum.h>
#include <iostream>
#include "ostendo_files/ostendo_headers.hpp"

void log(std::string str) { pessum::logging::Log(str); }

int main(int argc, char const* argv[]) {
  pessum::InitializePessum(true, true);
  ostendo::InitOstendo(100);
  ostendo::SetLogHandle(pessum::logging::Log);
  ostendo::Window win(10, 10, 20, 20);
  win.SetWindowOption(ostendo::WIN_BORDER, true);
  while(getch() == ERR){
  }
  win.~Window();
  ostendo::TermOstendo();
  pessum::TerminatePessum();
  return 0;
}
