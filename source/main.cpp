#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(COLOR | CBREAK);
  Window win("Ostendo", TITLE | BORDER | AUTO_UPDATE | WORD_BREAK);
  win.SetLastLineAction(LLA_SCROLL);
  win.Print(
      "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do "
      "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad "
      "minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip "
      "ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
      "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur "
      "sint occaecat cupidatat non proident, sunt in culpa qui officia "
      "deserunt mollit anim id est laborum.");
  int key = ERR;
  while (key != int('q')) {
    key = getch();
  }
  win.DeleteWindow();
  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
