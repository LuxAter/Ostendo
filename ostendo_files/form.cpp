#include "form.hpp"
#include "types.hpp"
#include "window.hpp"
#include <ncurses.h>
#include <vector>

std::vector<ostendo::Var> ostendo::Form(ostendo::Window win, std::vector<Var> fields){
  int selected = 0, start_display = 0;
  bool running = true, update = true;
  win.SetAutoUpdate(false);
  while(running == true){
    if(update == true){
      update = false;
      win.Clear();
      for(int i = start_display; i < fields.size() && i - start_display < win.window_space.h - 1; i++){
        if(i == selected){
          wattron(win(), A_STANDOUT);
        }
        win.Print(fields[i].name + ":#oun          #fun\n");
        if(i == selected){
          wattroff(win(), A_STANDOUT);
        }
      }
      win.Update();
    }
    int in = getch();
    if(in == int('q')){
      running = false;
    }
  }
  win.Clear();
  win.SetAutoUpdate(true);
  return(fields); 
}
