#include <pessum/pessum.h>
#include "ostendo.hpp"

using namespace ostendo;

int main(int argc, const char* argv[]) {
  InitOstendo(RAW | COLOR);
  TermOstendo();
  pessum::SaveLog("out.log");
  return (0);
}
