#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(COLOR | CBREAK);
  Window win("Ostendo", 50, 25, TITLE | BORDER | AUTO_UPDATE);

  Menu menu;
  menu.SetWindow(win);
  std::vector<std::string> vec;
  for (int i = 0; i < 5; i++) {
    vec.push_back("Test" + std::to_string(i));
  }
  menu.PushBackColumn(vec);

  menu.Run();

  win.DeleteWindow();

  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
