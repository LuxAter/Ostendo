#include <ncurses.h>
#include <pessum.h>
#include <iostream>
#include "ostendo_files/ostendo_headers.hpp"

void log(std::string str) { pessum::logging::Log(str); }

int main(int argc, char const* argv[]) {
  pessum::InitializePessum(true, true);
  ostendo::InitOstendo(true, 1);
  ostendo::SetLogHandle(pessum::logging::Log);
  ostendo::Window win(40, 20);
  win.Clear();
  win.ToggleTitle("Hello Window!");
  win.ToggleBorder();
  win.Print("Hello World\n");
  win.Print("#l#ounleft#fun just\n#c#o15center just#f15\n#rright just\n");
  std::vector<ostendo::Var> fields;
  fields.push_back(ostendo::Var("Int Val", 0));
  fields.push_back(ostendo::Var("Double Val", 0.0));
  fields.push_back(ostendo::Var("String Val", std::string("")));
  fields.push_back(ostendo::Var("Bool Val", false));
  fields.push_back(ostendo::Var("Int Set", std::vector<int>{1, 2, 3, 4, 5}));
  fields.push_back(
      ostendo::Var("Double Set", std::vector<double>{1.0, 1.1, 1.2, 1.3, 1.4}));
  fields.push_back(ostendo::Var(
      "String Set",
      {"Test 1", "Test 2", "Hello", "Arden", "Will", "This", "Work?"}));
  for (int i = 0; i < fields.size(); i++) {
    // printf("field %i type:%i\n", i, fields[i].var_type);
    // win.Print("field type: %i \n", 15);
  }
  ostendo::Form(win, fields);
  while (getch() != int('q')) {
  }
  win.DelWin();
  ostendo::TermOstendo();
  pessum::TerminatePessum();
  return 0;
}
