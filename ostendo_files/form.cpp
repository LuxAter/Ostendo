#include "form.hpp"
#include "types.hpp"
#include "window.hpp"
#include <ncurses.h>
#include <vector>

std::vector<ostendo::Var> ostendo::Form(ostendo::Window win, std::vector<Var> fields){
  int selected = 0, start_display = 0;
  bool running = true, update = true;
  win.SetAutoUpdate(false);
  for(int i = 0; i < fields.size(); i++){
    if(fields[i].var_type == INT){
      fields[i].str_value = std::to_string(fields[i].int_value);
    }else if(fields[i].var_type == DOUBLE){
      fields[i].str_value = std::to_string(fields[i].double_value);
    }
  }
  while(running == true){
    if(update == true){
      update = false;
      win.Clear();
      for(int i = start_display; i < fields.size() && i - start_display < win.window_space.h - 1; i++){
        if(i == selected){
          wattron(win(), A_STANDOUT);
        }
        std::string line = fields[i].name + ":#oun";
        int pre_insize = line.size();
        line += fields[i].str_value;
        while(line.size() - 4 < win.window_space.w){
          line += " ";
        }
        while(line.size() - 4 > win.window_space.w){
          line.erase(line.begin() + pre_insize);
        }
        line += "#fun";
        win.Print(line);
        if(i == selected){
          wattroff(win(), A_STANDOUT);
        }
      }
      win.Update();
    }
    int in = getch();
    if(in == int('q')){
      running = false;
    }else if(in == KEY_UP){
      if(selected > 0){
        if(fields[selected].str_value == ""){
          if(fields[selected].var_type == INT){
            fields[selected].str_value = std::to_string(int());
          }else if(fields[selected].var_type == DOUBLE){
            fields[selected].str_value = std::to_string(double());
          }
        }
        selected--;
        update = true;
        if(selected == start_display && start_display > 0){
          start_display--;
        }
      }
    }else if(in == KEY_DOWN){
      if(selected < fields.size() - 1){
        if(fields[selected].str_value == ""){
          if(fields[selected].var_type == INT){
            fields[selected].str_value = std::to_string(int());
          }else if(fields[selected].var_type == DOUBLE){
            fields[selected].str_value = std::to_string(double());
          }
        }
        selected++;
        update = true;
        if(selected - start_display == win.window_space.h - 2 && start_display < fields.size() - win.window_space.h + 1){
          start_display++;
        }
      }
    }else if(in == 10 || in == KEY_ENTER){
      if(selected < fields.size() - 1){
        if(fields[selected].str_value == ""){
          if(fields[selected].var_type == INT){
            fields[selected].str_value = std::to_string(int());
          }else if(fields[selected].var_type == DOUBLE){
            fields[selected].str_value = std::to_string(double());
          }
        }
        selected++;
        update = true;
        if(selected - start_display == win.window_space.h - 2 && start_display < fields.size() - win.window_space.h + 1){
          start_display++;
        }
      }else if(selected == fields.size() - 1){
        running = false;
      }
    }else if(in == KEY_BACKSPACE){
      if(fields[selected].str_value.size() > 0){
        fields[selected].str_value.pop_back();
      }
      update = true;

    }else if(in != ERR){
      if(fields[selected].var_type == INT && in >= 48 && in <= 57){
        fields[selected].str_value += char(in);
        update = true;
      }else if(fields[selected].var_type == DOUBLE && ((in >= 48 && in <= 57) || in == 46)){
        fields[selected].str_value += char(in);
        update = true;
      }else if(fields[selected].var_type == STRING){
        fields[selected].str_value += char(in);
        fields[selected].str_value += 'A';
        update = true;
      }else{
        fields[selected].str_value += std::to_string(fields[selected].var_type);
        update = true;
      }
    }
  }
  win.Clear();
  win.SetAutoUpdate(true);
  return(fields); 
}
