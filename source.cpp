#include <ncurses.h>
#include <pessum.h>
#include "ostendo_files/ostendo_headers.hpp"

using namespace ostendo;

int main(int argc, char const* argv[]) {
  InitOstendo(RAW | COLOR);
  Window win(BORDER | TITLE, 10, 10, 10, 10, "Ostendo");
  // wprintw(win(), "Hello World!");
  // win.Show();
  while (getch() == ERR) {
    refresh();
  }
  TermOstendo();
  pessum::SaveLog("out.log");
  return 0;
}
