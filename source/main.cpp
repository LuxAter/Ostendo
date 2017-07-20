#include <pessum/pessum.h>
#include "ostendo.hpp"

#include <string>
#include <vector>

// BUG(Arden): std::to_string causes attibutes to fail.

using namespace ostendo;

Window make() {
  Window win("Ostendo_test", 50, 25, TITLE | BORDER | AUTO_UPDATE);
  return win;
}

int main(int argc, const char* argv[]) {
  InitOstendo(COLOR | CBREAK);

  Window win_b = make();

  // win_b.Print("$fg:red$Hello Arden!$0$\n");
  /* win_b.Print("Unicode: \u2713\n"); */
  /* win_b.Print("Color: $bg:red;fg:blue$Color$c$\n"); */
  /* win_b.Print("Attribute: $un:on$Underline$a$\n"); */
  /* win_b.Print("Attribute: $un:on$Standout\u2713$a$\n"); */

  // int key = ERR;
  // while (key == ERR) {
  //   key = getch();
  // }

  Menu menu;
  menu.SetWindow(win_b);
  std::vector<std::string> veca, vecb, vecc, vecd, vece, vecf, vecg, vech, veci;
  for (int i = 0; i < 26; i++) {
    std::string row = " xx ";
    row += (i + 65);
    veca.push_back("a" + row);
    vecb.push_back("b" + row);
    vecc.push_back("c" + row);
    vecd.push_back("d" + row);
    vece.push_back("e" + row);
    vecf.push_back("f" + row);
    vecg.push_back("g" + row);
    vech.push_back("h" + row);
    veci.push_back("i" + row);
  }
  menu.SetItems({veca, vecb, vecc, vecd, vece, vecf, vecg, vech, veci});

  menu.RunMulti();

  menu.DeleteMenu();

  win_b.DeleteWindow();

  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
