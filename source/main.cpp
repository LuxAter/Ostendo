#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(COLOR | CBREAK);

  Window win("Ostendo", 20, 20, TITLE | BORDER | AUTO_UPDATE);
  win.SetLastLineAction(LLA_SCROLL);
  // win.Print("Hello ^?\nh\u1998\n");
  win.SetScroll(SB_LEFT, 5, 10);
  win.SetScrollBar(SB_LEFT, true);
  win.SetScrollBar(SB_RIGHT, true);
  win.Print("Hello World!\nWill this all work as it should? Let's hope so!");
  win.Update();
  int key = ERR;
  while (key == ERR) {
    key = getch();
  }
  win.DeleteWindow();

  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
