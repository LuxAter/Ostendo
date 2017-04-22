#include <ncurses.h>
#include <pessum.h>
#include <iostream>
#include "ostendo_files/ostendo_headers.hpp"

int main(int argc, char const* argv[]) {
  ostendo::InitOstendo(true, 1);
  ostendo::TermOstendo();
  pessum::SaveLog("out.log");
  return 0;
}
