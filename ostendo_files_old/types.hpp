#ifndef OSTENDO_TYPES_HPP
#define OSTENDO_TYPES_HPP
#include <string>
#include <vector>
namespace ostendo {
  //! Declares the posible types of the variable structure.
  enum VarType {
    INT = 0,    /*!<Sets the variable type to be integer*/
    DOUBLE = 1, /*!<Sets the variable type to be doubles*/
    STRING = 2, /*!<Sets the variable type to be strings*/
    BOOL = 3    /*!<Sets the variable type to be boolians*/
  };
  //! Structure to contains position/size data
  /*! Contains the x, y positional data, and the width, height size data.*/
  struct Pos {
    //! Creates new position
    /*! Creates position with zero for all terms*/
    Pos() {
      x = int();
      y = int();
      w = int();
      h = int();
    }
    //! Creates new position
    /*! Creates position with set x and y position, and width and height are set
     * to zero
     * \param value_x Value for the X position.
     * \param value_y Value for the y position.
     */
    Pos(int value_x, int value_y) {
      x = value_x;
      y = value_y;
      w = int();
      h = int();
    }
    //! Creates new position
    /*! Creates position data with set x, y, width, and height data
     * \param value_x Value for the x position.
     * \param value_y Value for the y position.
     * \param value_w Value for the width.
     * \param value_h Value for the height.
     */
    Pos(int value_x, int value_y, int value_w, int value_h) {
      x = value_x;
      y = value_y;
      w = value_w;
      h = value_h;
    }
    int x, /*!<X term of the position data.*/
        y, /*!<Y term of the position data.*/
        w, /*!<Width term for the position data.*/
        h; /*!<Height term for the position data.*/
  };
  //! Creates a new position object
  /*! Creates position object given the four terms.
   * \param x X term for position.
   * \param y Y term for position.
   * \param w Width term for position.
   * \param h Height term for position.
   * \returns Pos New position structure from given values.
   */
  inline Pos make_pos(int x, int y, int w, int h) { return (Pos(x, y, w, h)); }
  //! Creates a new position object
  /*! Creates a position object given two terms.
   * \param x X term for position.
   * \param y Y term for position.
   * \returns Pos New position structure from given values.
   */
  inline Pos make_pos(int x, int y) { return (Pos(x, y)); }
  //! Structure to use as general variable.
  /*! Structure that can act as a variable for int, double, string, or bool*/
  struct Var {
    //! Creates new Var
    /*! Creates the default variable, with standard values for all terms.*/
    Var() {
      name = std::string();
      var_type = int();
      int_value = int();
      double_value = double();
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    //! Creates new Var
    /*! Creates new integer variable.
     * \param value Integer value for variable.
     */
    Var(int value) {
      name = std::string();
      var_type = INT;
      int_value = value;
      double_value = double();
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    //! Creates new Var
    /*! Creates new double variable.
     * \param value Double value for variable.
     */
    Var(double value) {
      name = std::string();
      var_type = DOUBLE;
      int_value = int();
      double_value = value;
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    //! Creates new Var
    /*! Creates new string variable.
     * \param value String value for variable.
     */
    Var(std::string value) {
      name = std::string();
      var_type = STRING;
      int_value = int();
      double_value = double();
      str_value = value;
      bool_value = bool();
      has_set = false;
    }
    //! Creates new Var
    /*! Creates new boolian variable.
     * \param value Boolian value for variable.
     */
    Var(bool value) {
      name = std::string();
      var_type = BOOL;
      int_value = int();
      double_value = double();
      str_value = std::string();
      bool_value = value;
      has_set = false;
    }
    //! Creates new Var
    /*! Creates a new integer variable.
     * \param str_name Name of variable.
     * \param value Integer value for variable.
     */
    Var(std::string str_name, int value) {
      name = str_name;
      var_type = INT;
      int_value = value;
      double_value = double();
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    //! Creates new Var
    /*! Creates a new double variable.
     * \param str_name Name of variable.
     * \param value Double value for variable.
     */
    Var(std::string str_name, double value) {
      name = str_name;
      var_type = DOUBLE;
      int_value = int();
      double_value = value;
      str_value = std::string();
      bool_value = bool();
      has_set = false;
    }
    //! Creates new Var
    /*! Creates a new string variable.
     * \param str_name Name of variable.
     * \param value String value for variable.
     */
    Var(std::string str_name, std::string value) {
      name = str_name;
      var_type = STRING;
      int_value = int();
      double_value = double();
      str_value = value;
      bool_value = bool();
      has_set = false;
    }
    //! Creates new Var
    /*! Creates a new boolian variable.
     * \param str_name Name of variable.
     * \param value Boolian value for variable.
     */
    Var(std::string str_name, bool value) {
      name = str_name;
      var_type = BOOL;
      int_value = int();
      double_value = double();
      str_value = std::string();
      bool_value = value;
      has_set = false;
    }
    //! Creates new Var set
    /*! Creates new variable set of integers with given default.
     * \param str_name Name of variable.
     * \param set Set of integer options.
     * \param value Default option from the set.
     */
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
    //! Creates new Var set
    /*! Creates new variable set of doubles with given default.
     * \param str_name Name of variable.
     * \param set Set of double options.
     * \param value Default option from the set.
     */
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
    //! Creates new Var set
    /*! Creates new variable set of strings with given default.
     * \param str_name Name of variable.
     * \param set Set of strings options.
     * \param value Default option from the set.
     */
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
    //! Sets the value of the variable
    /*! Sets the variable to the given integer value.
     * \param value Value to set variable to.
     */
    void operator=(int value) {
      var_type = INT;
      int_value = value;
    }
    //! Sets the value of the variable
    /*! Sets the variable to the given double value.
     * \param value Value to set variable to.
     */
    void operator=(double value) {
      var_type = DOUBLE;
      double_value = value;
    }
    //! Sets the value of the variable
    /*! Sets the variable to the given string value.
     * \param value Value to set variable to.
     */
    void operator=(std::string value) {
      var_type = STRING;
      str_value = value;
    }
    //! Sets the value of the variable
    /*! Sets the variable to the given boolian value.
     * \param value Value to set variable to.
     */
    void operator=(bool value) {
      var_type = BOOL;
      bool_value = value;
    }
    //! Sets the set of the variable
    /*! Set the variable set to a set of integers.
     * \param set Set of integers to use in the variable.
     */
    void SetSet(std::vector<int> set) {
      has_set = true;
      int_set = set;
    }
    //! Sets the set of the variable
    /*! Set the variable set to a set of doubles.
     * \param set Set of doubles to use in the variable.
     */
    void SetSet(std::vector<double> set) {
      has_set = true;
      double_set = set;
    }
    //! Sets the set of the variable
    /*! Set the variable set to a set of strings.
     * \param set Set of strings to use in the variable.
     */
    void SetSet(std::vector<std::string> set) {
      has_set = true;
      str_set = set;
    }

    //! Returns integer value of the variable.
    int Int() { return (int_value); }
    //! Returns the double value of the varaible.
    double Double() { return (double_value); }
    //! Returns the string value of the variable.
    std::string String() { return (str_value); }
    //! Returns the boolian value of the variable.
    bool Bool() { return (bool_value); }
    //! Returns the name of the variable.
    std::string Name() { return (name); }

    bool has_set;          /*!<Boolian determining if variable is a set.*/
    std::string name;      /*!<Name of variable.*/
    int var_type;          /*!<Variable type setting from VarTypes.\sa VarType*/
    int int_value;         /*!<Integer value.*/
    double double_value;   /*!<Double value.*/
    std::string str_value; /*!<String value.*/
    bool bool_value;       /*!<Boolian value.*/
    std::vector<int> int_set;         /*!<Set of integer options.*/
    std::vector<double> double_set;   /*!<Set of double options.*/
    std::vector<std::string> str_set; /*!<Set of string options.*/
  };
}
#endif
