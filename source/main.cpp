#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(RAW);
  Window win("Ostendo", TITLE | BORDER);
  int key = ERR;
  while (key != int('q')) {
    key = getch();
    if (key == int('t')) {
      win.SetTitle(!win.GetTitle());
    }
    if (key == int('b')) {
      win.SetBorder(!win.GetBorder());
    }
  }
  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
