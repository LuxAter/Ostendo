#ifndef OSTENDO_TYPES_HPP
#define OSTENDO_TYPES_HPP
#include <string>
#include <vector>
namespace ostendo {
  enum VarType { INT = 0, DOUBLE = 1, STRING = 2, BOOL = 3 };
  struct Pos {
    Pos() {
      x = int();
      y = int();
      w = int();
      h = int();
    }
    Pos(int value_x, int value_y) {
      x = value_x;
      y = value_y;
      w = int();
      h = int();
    }
    Pos(int value_x, int value_y, int value_w, int value_h) {
      x = value_x;
      y = value_y;
      w = value_w;
      h = value_h;
    }
    int x, y, w, h;
  };
  inline Pos make_pos(int x, int y, int w, int h) { return (Pos(x, y, w, h)); }
  inline Pos make_pos(int x, int y) { return (Pos(x, y)); }

  struct Var {
    Var() {
      name = std::string();
      var_type = int();
      int_value = int();
      double_value = double();
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    Var(int value) {
      name = std::string();
      var_type = INT;
      int_value = value;
      double_value = double();
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    Var(double value) {
      name = std::string();
      var_type = DOUBLE;
      int_value = int();
      double_value = value;
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    Var(std::string value) {
      name = std::string();
      var_type = STRING;
      int_value = int();
      double_value = double();
      str_value = value;
      bool_value = bool();
      has_set = false;
    }
    Var(bool value) {
      name = std::string();
      var_type = BOOL;
      int_value = int();
      double_value = double();
      str_value = std::string();
      bool_value = value;
      has_set = false;
    }
    Var(std::string str_name, int value) {
      name = str_name;
      var_type = INT;
      int_value = value;
      double_value = double();
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    Var(std::string str_name, double value) {
      name = str_name;
      var_type = DOUBLE;
      int_value = int();
      double_value = value;
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    Var(std::string str_name, std::string value) {
      name = str_name;
      var_type = STRING;
      int_value = int();
      double_value = double();
      str_value = value;
      bool_value = bool();
      has_set = false;
    }
    Var(std::string str_name, bool value) {
      name = str_name;
      var_type = BOOL;
      int_value = int();
      double_value = double();
      str_value = std::string();
      bool_value = value;
      has_set = false;
    }
    Var(std::string str_name, std::vector<int> set, int value = 0) {
      name = str_name;
      var_type = INT;
      int_value = set[value];
      double_value = double();
      str_value = std::string();
      bool_value = bool();
      int_set = set;
      has_set = true;
    }
    Var(std::string str_name, std::vector<double> set, int value = 0) {
      name = str_name;
      var_type = DOUBLE;
      int_value = int();
      double_value = set[value];
      str_value = std::string();
      bool_value = bool();
      double_set = set;
      has_set = true;
    }
    Var(std::string str_name, std::vector<std::string> set, int value = 0) {
      name = str_name;
      var_type = STRING;
      int_value = int();
      double_value = double();
      str_value = set[value];
      bool_value = bool();
      str_set = set;
      has_set = true;
    }
    void operator=(int value) {
      var_type = INT;
      int_value = value;
    }
    void operator=(double value) {
      var_type = DOUBLE;
      double_value = value;
    }
    void operator=(std::string value) {
      var_type = STRING;
      str_value = value;
    }
    void operator=(bool value) {
      var_type = BOOL;
      bool_value = value;
    }
    void SetSet(std::vector<int> set) {
      has_set = true;
      int_set = set;
    }
    void SetSet(std::vector<double> set) {
      has_set = true;
      double_set = set;
    }
    void SetSet(std::vector<std::string> set) {
      has_set = true;
      str_set = set;
    }
    int Int() { return (int_value); }
    double Double() { return (double_value); }
    std::string String() { return (str_value); }
    bool Bool() { return (bool_value); }
    std::string Name() { return (name); }
    bool has_set;
    std::string name;
    int var_type;
    int int_value;
    double double_value;
    std::string str_value;
    bool bool_value;
    std::vector<int> int_set;
    std::vector<double> double_set;
    std::vector<std::string> str_set;
  };
}
#endif
