#include <pessum.h>
#include <iostream>
#include "ostendo_files/ostendo_headers.hpp"

void log(std::string str) { pessum::logging::Log(str); }

int main(int argc, char const* argv[]) {
  pessum::InitializePessum(true, true);
  ostendo::InitOstendo();
  ostendo::SetLogHandle(log);
  ostendo::OstendoLog(0, "Test", "main");
  ostendo::TermOstendo();
  pessum::TerminatePessum();
  return 0;
}
