#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(COLOR | CBREAK);

  Window win("Ostendo", -1, 20, TITLE | BORDER | AUTO_UPDATE | WORD_BREAK);
  win.SetLastLineAction(LLA_SCROLL);

  win.DeleteWindow();

  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
