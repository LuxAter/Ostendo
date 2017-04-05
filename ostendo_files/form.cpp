#include <ncurses.h>
#include <vector>
#include "form.hpp"
#include "menu.hpp"
#include "types.hpp"
#include "window.hpp"

std::vector<ostendo::Var> ostendo::Form(ostendo::Window win,
                                        std::vector<Var> fields) {
  int selected = 0, start_display = 0;
  bool running = true, update = true;
  win.SetAutoUpdate(false);
  for (int i = 0; i < fields.size(); i++) {
    if (fields[i].var_type == INT) {
      fields[i].str_value = std::to_string(fields[i].int_value);
      if (fields[i].has_set == true) {
        for (int j = 0; j < fields[i].int_set.size(); j++) {
          fields[i].str_set.push_back(std::to_string(fields[i].int_set[j]));
        }
      }
    } else if (fields[i].var_type == DOUBLE) {
      fields[i].str_value = std::to_string(fields[i].double_value);
      if (fields[i].has_set == true) {
        for (int j = 0; j < fields[i].double_set.size(); j++) {
          fields[i].str_set.push_back(std::to_string(fields[i].double_set[j]));
        }
      }
    }
  }
  while (running == true) {
    if (update == true) {
      update = false;
      win.Clear();
      for (int i = start_display;
           i < fields.size() && i - start_display < win.window_space.h - 1;
           i++) {
        if (i == selected) {
          wattron(win(), A_STANDOUT);
        }
        win.Print(GetVarStr(fields[i], win.window_space.w));
        if (i == selected) {
          wattroff(win(), A_STANDOUT);
        }
      }
      win.Update();
    }
    int in = getch();
    if (in == int('q')) {
      running = false;
    } else if (in == KEY_UP) {
      if (selected > 0) {
        fields[selected] = UpArrow(fields[selected], win);
        selected--;
        update = true;
        if (selected == start_display && start_display > 0) {
          start_display--;
        }
      }
    } else if (in == KEY_DOWN) {
      if (selected < fields.size() - 1) {
        fields[selected] = DownArrow(fields[selected], win);
        selected++;
        update = true;
        if (selected - start_display == win.window_space.h - 2 &&
            start_display < fields.size() - win.window_space.h + 1) {
          start_display++;
        }
      }
    } else if (in == KEY_RIGHT) {
      fields[selected] = RightArrow(fields[selected], win);
      update = true;
    } else if (in == KEY_LEFT) {
      fields[selected] = LeftArrow(fields[selected], win);
      update = true;
    } else if (in == 10 || in == KEY_ENTER) {
      if (selected < fields.size() - 1) {
        fields[selected] = Enter(fields[selected], win);
        update = true;
      } else if (selected == fields.size() - 1) {
        running = false;
      }
    } else if (in == KEY_BACKSPACE) {
      fields[selected] = Backspace(fields[selected], win);
      update = true;

    } else if (in != ERR) {
      fields[selected] = Add(fields[selected], in, win);
      update = true;
    }
  }
  win.Clear();
  win.SetAutoUpdate(true);
  return (fields);
}

std::string ostendo::GetVarStr(Var in_var, int width) {
  std::string str = "";
  bool colin = false;
  if (in_var.name != "") {
    str += in_var.name + ":";
    colin = true;
  }
  if ((in_var.var_type == INT || in_var.var_type == DOUBLE ||
       in_var.var_type == STRING) &&
      in_var.has_set == false) {
    str += "#oun";
    int pre_insize = str.size();
    str += in_var.str_value;
    while (str.size() - 4 < width) {
      str += " ";
    }
    while (str.size() - 4 > width) {
      str.erase(str.begin() + pre_insize);
    }
    str += "#fun";
  } else if (in_var.var_type == INT || in_var.var_type == DOUBLE ||
             in_var.var_type == STRING) {
    int pre_insize = str.size();
    str += "#oun";
    str += in_var.str_value;
    while (str.size() - 3 < width) {
      str += " ";
    }
    while (str.size() - 3 > width) {
      str.erase(str.begin() + pre_insize);
    }
    str += "#fun";
    str += ">";
  } else if (in_var.var_type == BOOL) {
    int spaces = (width - str.size() - 9) / 3;
    str += std::string(spaces, ' ');
    if (in_var.bool_value == true) {
      str += "#oun";
    }
    str += "True";
    if (in_var.bool_value == true) {
      str += "#fun";
    }
    str += std::string(spaces, ' ');
    if (in_var.bool_value == false) {
      str += "#oun";
    }
    str += "False";
    if (in_var.bool_value == false) {
      str += "#fun";
    }
    while (str.size() - 8 < width) {
      str += " ";
    }
  }
  return (str);
}

ostendo::Var ostendo::DownArrow(Var in_var, Window win) {
  if (in_var.has_set == true) {
  } else if (in_var.var_type == INT) {
    if (in_var.str_value.size() == 0) {
      in_var.str_value = std::to_string(int());
    }
    in_var.int_value = stoi(in_var.str_value);
    in_var.str_value = std::to_string(in_var.int_value);
  } else if (in_var.var_type == DOUBLE) {
    if (in_var.str_value.size() == 0) {
      in_var.str_value = std::to_string(double());
    }
    in_var.double_value = stod(in_var.str_value);
    in_var.str_value = std::to_string(in_var.double_value);
  } else if (in_var.var_type == STRING) {
  } else if (in_var.var_type == BOOL) {
  }
  return (in_var);
}

ostendo::Var ostendo::UpArrow(Var in_var, Window win) {
  if (in_var.has_set == true) {
  } else if (in_var.var_type == INT) {
    if (in_var.str_value.size() == 0) {
      in_var.str_value = std::to_string(int());
    }
    in_var.int_value = stoi(in_var.str_value);
    in_var.str_value = std::to_string(in_var.int_value);
  } else if (in_var.var_type == DOUBLE) {
    if (in_var.str_value.size() == 0) {
      in_var.str_value = std::to_string(double());
    }
    in_var.double_value = stod(in_var.str_value);
    in_var.str_value = std::to_string(in_var.double_value);
  } else if (in_var.var_type == DOUBLE) {
  } else if (in_var.var_type == STRING) {
  } else if (in_var.var_type == BOOL) {
  }
  return (in_var);
}

ostendo::Var ostendo::RightArrow(Var in_var, Window win) {
  if (in_var.has_set == true) {
    if (in_var.var_type == INT) {
      in_var.str_value = Menu(win, in_var.str_set);
    } else if (in_var.var_type == DOUBLE) {
      in_var.str_value = Menu(win, in_var.str_set);
    } else if (in_var.var_type == STRING) {
      in_var.str_value = Menu(win, in_var.str_set);
    }
  } else if (in_var.var_type == INT) {
  } else if (in_var.var_type == DOUBLE) {
  } else if (in_var.var_type == STRING) {
  } else if (in_var.var_type == BOOL) {
    in_var.bool_value = false;
  }
  return (in_var);
}

ostendo::Var ostendo::LeftArrow(Var in_var, Window win) {
  if (in_var.has_set == true) {
  } else if (in_var.var_type == INT) {
  } else if (in_var.var_type == DOUBLE) {
  } else if (in_var.var_type == STRING) {
  } else if (in_var.var_type == BOOL) {
    in_var.bool_value = true;
  }
  return (in_var);
}

ostendo::Var ostendo::Enter(Var in_var, Window win) {
  if (in_var.has_set == true) {
  } else if (in_var.var_type == INT) {
  } else if (in_var.var_type == DOUBLE) {
  } else if (in_var.var_type == STRING) {
  } else if (in_var.var_type == BOOL) {
  }
  return (in_var);
}

ostendo::Var ostendo::Backspace(Var in_var, Window win) {
  if (in_var.has_set == true) {
  } else if (in_var.var_type == INT) {
    if (in_var.str_value.size() > 0) {
      in_var.str_value.pop_back();
    }
  } else if (in_var.var_type == DOUBLE) {
    if (in_var.str_value.size() > 0) {
      in_var.str_value.pop_back();
    }
  } else if (in_var.var_type == STRING) {
    if (in_var.str_value.size() > 0) {
      in_var.str_value.pop_back();
    }
  } else if (in_var.var_type == BOOL) {
    in_var.bool_value = false;
  }
  return (in_var);
}

ostendo::Var ostendo::Add(Var in_var, int ch, Window win) {
  if (in_var.has_set == true) {
  } else if (in_var.var_type == INT) {
    if (ch >= 48 && ch <= 57) {
      in_var.str_value += char(ch);
    }
  } else if (in_var.var_type == DOUBLE) {
    if (ch >= 48 && ch <= 57) {
      in_var.str_value += char(ch);
    } else if (ch == int('.')) {
      bool good = true;
      for (int i = 0; i < in_var.str_value.size(); i++) {
        if (in_var.str_value[i] == char(ch)) {
          good = false;
        }
      }
      if (good == true) {
        in_var.str_value += char(ch);
      }
    }
  } else if (in_var.var_type == STRING) {
    if (ch >= 32 && ch <= 126) {
      in_var.str_value += char(ch);
    }
  } else if (in_var.var_type == BOOL) {
  }
  return (in_var);
}
