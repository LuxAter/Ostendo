#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(RAW);
  Window win("Ostendo", TITLE | BORDER | AUTO_UPDATE);
  win.mvPrint(5, 5, "Hello %i", 15);
  int key = ERR;
  while (key != int('q')) {
    key = getch();
    if (key == int('t')) {
      win.SetTitle(!win.GetTitle());
    }
    if (key == int('b')) {
      win.SetBorder(!win.GetBorder());
    }
    if (key == int('a')) {
      win.Scale(-1, 0);
    }
    if (key == int('d')) {
      win.Scale(1, 0);
    }
    if (key == int('w')) {
      win.Scale(0, 1);
    }
    if (key == int('s')) {
      win.Scale(0, -1);
    }
    if (key == int('j')) {
      win.Translate(-1, 0);
    }
    if (key == int('k')) {
      win.Translate(0, 1);
    }
    if (key == int('l')) {
      win.Translate(1, 0);
    }
    if (key == int('i')) {
      win.Translate(0, -1);
    }
  }
  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
