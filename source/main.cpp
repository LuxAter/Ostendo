#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(COLOR | CBREAK);

  Window win("Ostendo", 20, 20, TITLE | BORDER | AUTO_UPDATE | WORD_BREAK);
  win.SetLastLineAction(LLA_SCROLL);

  Menu menu;
  menu.SetWindow(win);
  menu.PushBackColumn({"Test 1", "Test 2", "Test 3", "Test 4"});
  menu.Run();
  menu.DeleteMenu();

  win.DeleteWindow();

  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
