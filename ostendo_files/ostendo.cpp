#include "ostendo.hpp"
#include <pessum.h>
#include <ncurses.h>

namespace ostendo{
  bool ostendo_cbreak = false, ostendo_raw = false, ostendo_echo = false, ostendo_cursor = false;
  int ostendo_time_delay;
}

void ostendo::InitOstendo(unsigned int state){
  pessum::Log(pessum::INFO, "Ostendo Version: %i.%i.%i", "ostendo::InitOstendo", OSTENDO_VERSION_MAJOR, OSTENDO_VERSION_MINOR, OSTENDO_VERSION_PATCH); 
  initscr();
  if(state != 0){
    pessum::Log(pessum::DEBUG, "State = %ui", "", state);
    bool g_cbreak = false, g_raw = false, g_echo = false, g_cursor = false;
    if((state & CBREAK) != 0){
      g_cbreak = true;
    }
    if((state & RAW) != 0 && g_cbreak != true){
      g_raw = true;
    }
    if((state & ECHO) != 0){
      g_echo = true;
    }
    if((state & CURSOR) != 0){
      g_cursor = true;
    }
    pessum::Log(pessum::DEBUG, "%i,%i,%i,%i", "", g_cbreak, g_raw, g_echo, g_cursor);
  }
}

void ostendo::TermOstendo(){
  endwin();
}

bool ostendo::Cbreak(int setting){
  if(setting == true){
    cbreak();
    ostendo_cbreak = setting;
  }else if(setting == false){
    nocbreak();
    ostendo_cbreak = setting;
  }
  return(ostendo_cbreak);
}

bool ostendo::Raw(int setting){
  if(setting == true){
    raw();
    ostendo_raw = setting;
  }else if(setting == false){
    noraw();
    ostendo_raw = setting;
  }
  return(ostendo_raw);
}

bool ostendo::Echo(int setting){
  if(setting == true){
    echo();
    ostendo_echo = setting;
  }else if(setting == false){
    noecho();
    ostendo_echo = setting;
  }
  return(ostendo_echo);
}

bool ostendo::Cursor(int setting){
  if(setting == true){
    curs_set(1);
    ostendo_cursor = setting;
  }else if(setting == false){
    curs_set(0);
    ostendo_cursor = setting;
  }
  return(ostendo_cursor);
}

int ostendo::TimeOut(int setting){
 if(setting != -2){
    timeout(setting);
    ostendo_time_delay = setting;
  } 
  return(ostendo_time_delay);
}

void ostendo::GetVersion(int& major, int& minor, int& patch){
  major = OSTENDO_VERSION_MAJOR;
  minor = OSTENDO_VERSION_MINOR;
  patch = OSTENDO_VERSION_PATCH;
}
