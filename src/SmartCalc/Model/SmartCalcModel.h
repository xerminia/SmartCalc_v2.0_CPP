#ifndef SMARTCALCMODEL_H
#define SMARTCALCMODEL_H

#include <cmath>
#include <iostream>
#include <stack>
namespace s21 {

class SmartCalcModel {
 private:
  std::stack<double> number_;
  std::stack<char> sign_;
  std::string exp_;
  std::string x_;

  void clear();
  bool check_error_exp();
  bool check_error_x();
  void operate_on_numbers();
  bool check_unary(char znak);
  bool check_sign(char znak);
  bool check_numner(char znak);
  int check_func(int i);
  int push_func(int func, bool unary);
  int push_number(bool unary, int i);
  void push_number_x(bool unary);
  void counting_in_brackets();
  int priority(char a);
  void count_and_push_znak(int i);

 public:
  SmartCalcModel() {}
  ~SmartCalcModel() {}

  std::string parsing(std::string exp_, std::string x_);
};
}  // namespace s21

#endif  // SMARTCALCMODEL_H
