#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(CBREAK);
  Window win("Ostendo", TITLE | BORDER | AUTO_UPDATE);
  win.mvPrint(0, 0, "$fg:blue$Hello $fg:red;bg:green$ARDEN$0$ $$%i", 15);
  int key = ERR;
  while (key != int('q')) {
    key = getch();
  }
  win.DeleteWindow();
  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
