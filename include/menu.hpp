#ifndef OSTENDO_MENU_HPP
#define OSTENDO_MENU_HPP

#include <array>
#include <string>
#include <vector>

#include "window.hpp"

namespace ostendo {
  class Menu {
   public:
    void DeleteMenu();

    void SetWindow(Window win);

    std::string Run();
    int RunInt();
    std::vector<std::string> RunMulti();
    std::vector<int> RunMultiInt();

    void PushBackItem(std::string item, size_t col = 0);
    void InsertItem(std::string item, size_t position, size_t col = 0);
    void PushBackColumn(std::vector<std::string> col);
    void InsertColumn(std::vector<std::string> col, size_t position);
    void SetItems(std::vector<std::vector<std::string>> items);
    void ClearItems();

   protected:
   private:
    bool MoveSelection(int key);
    void Display();
    void DisplayCol(int col, int x, int width);

    int Longest(int col = -1);

    int ItemIndex();

    bool multi_ = false;

    std::array<int, 2> position_ = {{0, 0}};

    std::array<std::string, 4> selection_setting_ = {
        {"$st:on$", "$st:off$", "$un:on$", "$un:off$"}};
    std::vector<std::vector<std::pair<bool, std::string>>> items_;

    Window win_;
  };
}  // namespace ostendo
#endif
