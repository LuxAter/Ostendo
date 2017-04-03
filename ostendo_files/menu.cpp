#include "menu.hpp"
#include <vector>
#include <string>
#include "window.hpp"
#include "types.hpp"
#include <ncurses.h>

std::string ostendo::Menu(ostendo::Window win, std::vector<std::string> options){
  int selected = 0, start_display = 0;
  std::string selected_str = "\0";
  bool running = true, update = true;
  win.SetAutoUpdate(false);
  while(running == true){
    if(update == true){
      update = false;
      win.Clear();
      for(int i = start_display; i < options.size() && i - start_display < win.window_space.h - 1; i++){
        if(i == selected){
          wattron(win(), A_STANDOUT);
        }
        win.Print("#c" + options[i] + "\n#c");
        if(i == selected){
          wattroff(win(), A_STANDOUT);
        }
      }
      win.Update();
    }
    int in = getch();
    if(in == KEY_UP || in == int('w')){
      if(selected > 0){
        selected--;
        update = true;
        if(selected == start_display && start_display > 0){
          start_display--;
        }
      }
    }else if(in == KEY_DOWN || in == int('s')){
      if(selected < options.size() - 1){
        selected++;
        update = true;
        if(selected - start_display == win.window_space.h - 2 && start_display < options.size() - win.window_space.h + 1){
          start_display++;
        }
      }
    }else if(in == 10 || in == KEY_ENTER){
      selected_str = options[selected];
      running = false;
    }else if(in == int('q')){
      running = false;
    }
  }
  win.Clear();
  win.SetAutoUpdate(true);
  return(selected_str);
}
