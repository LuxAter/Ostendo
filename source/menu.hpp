#ifndef OSTENDO_MENU_HPP
#define OSTENDO_MENU_HPP

#include <array>
#include <string>
#include <vector>

namespace ostendo {
  class Menu {
   public:
    std::string Run();
    int RunInt();
    std::vector<std::string> RunMulti();
    std::vector<int> RunMultiInt();

   protected:
   private:
    std::array<std::string, 4> selection_setting_;
  };
}  // namespace ostendo
#endif
