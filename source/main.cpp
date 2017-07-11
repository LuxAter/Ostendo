#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(COLOR | CBREAK);
  Window win("Ostendo", TITLE | BORDER | AUTO_UPDATE);
  win.mvPrint(0, 0, "Hello Arden");
  int key = ERR;
  while (key != int('q')) {
    key = getch();
  }
  win.DeleteWindow();
  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
