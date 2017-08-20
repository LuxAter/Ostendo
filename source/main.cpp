#include "ostendo.hpp"

#include <regex>
#include <string>
#include <vector>

// BUG(Arden): std::to_string causes attibutes to fail.
// BUG(Arden): std::regex causes attibutes to fail.

using namespace ostendo;

Window make() {
  Window win("Ostendo_test", 50, 25, TITLE | BORDER | AUTO_UPDATE);
  return win;
}

int main() {
  InitOstendo(COLOR | CBREAK);

  Window win_b = make();

  Form form;
  form.SetWindow(win_b);

  form.PushBackItem("Name", LINE);
  form.PushBackItem("Date", DATE);
  form.PushBackItem("KeyWord", WORD);

  form.Run();

  form.DeleteForm();

  win_b.DeleteWindow();

  TermOstendo();
  ostendo::log::SaveLog("out.log");
  return (0);
}
