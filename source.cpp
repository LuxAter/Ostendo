#include <pessum.h>
#include "ostendo_files/ostendo_headers.hpp"

using namespace ostendo;

int main(int argc, char const* argv[]) {
  InitOstendo(RAW | CURSOR);
  TermOstendo();
  pessum::SaveLog("out.log");
  return 0;
}
