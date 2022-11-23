#include "SmartCalcModel.h"

namespace s21 {

std::string SmartCalcModel::parsing(std::string str_exp, std::string str_x) {
  clear();
  exp_ = str_exp;
  x_ = str_x;
  bool no_error_x = true, no_error_exp = true;
  if (!x_.empty()) no_error_x = check_error_x();
  if (!exp_.empty()) no_error_exp = check_error_exp();
  if (!no_error_x || !no_error_exp) return "Error";
  if (exp_.find('x') < 256 && x_.empty()) return "graph";
  bool unary = false;
  int func;
  for (int i = 0; exp_[i] != '\0'; i++) {
    if ((i == 0 || check_sign(exp_[i - 1]) || exp_[i - 1] == '(') &&
        check_unary(exp_[i]) &&
        (check_numner(exp_[i + 1]) || exp_[i + 1] == '.' || check_func(i + 1) ||
         exp_[i + 1] == 'x')) {
      if (exp_[i] == '-') unary = true;
      continue;
    } else if (exp_[i] == ')') {
      counting_in_brackets();
    } else if (exp_[i] == '(') {
      sign_.push(exp_[i]);
    } else if (check_numner(exp_[i]) || exp_[i] == '.' || exp_[i] == 'x') {
      if (exp_[i] == 'x') {
        push_number_x(unary);
      } else {
        i = push_number(unary, i);
      }
    } else if (check_sign(exp_[i])) {
      count_and_push_znak(i);
    } else if ((func = check_func(i))) {
      i += push_func(func, unary);
    }
    unary = false;
  }
  while (!sign_.empty()) operate_on_numbers();
  std::string result = std::to_string(number_.top());
  return result;
}

void SmartCalcModel::clear() {
  while (!number_.empty()) number_.pop();
  while (!sign_.empty()) sign_.pop();
}

bool SmartCalcModel::check_error_exp() {
  int check_znak = 0, check_chislo = 0;
  bool sign = false, unary = false, check_x = false;
  int bracket = 0;
  for (int i = 0; exp_[i] != '\0'; i++) {
    if ((i == 0 || check_sign(exp_[i - 1]) || exp_[i - 1] == '(') &&
        check_unary(exp_[i]) && unary == false &&
        (check_numner(exp_[i + 1]) || exp_[i + 1] == '.' || check_func(i + 1) ||
         exp_[i + 1] == 'x')) {
      unary = true, sign = false, check_x = false;
      continue;
    } else if (check_sign(exp_[i]) && sign == false) {
      sign = true, unary = false, check_x = false;
      check_znak++;
      continue;
    } else if (check_numner(exp_[i]) || exp_[i] == '.') {
      bool dot = false, exp = false;
      for (; exp_[i] != '\0' && (check_numner(exp_[i]) || exp_[i] == '.' ||
                                 exp_[i] == 'E' || exp_[i] == 'e');
           i++) {
        if (check_numner(exp_[i])) {
          continue;
        } else if (exp_[i] == '.' && dot == false) {
          dot = true;
          continue;
        } else if (check_unary(exp_[i + 1]) && check_numner(exp_[i + 2]) &&
                   exp == false && (exp_[i] == 'E' || exp_[i] == 'e')) {
          exp = true;
          i += 2;
          continue;
        } else {
          return false;
        }
      }
      sign = false, unary = false;
      i--;
      check_chislo++;
    } else if (exp_[i] == '(') {
      bracket++;
    } else if (exp_[i] == ')') {
      bracket--;
      if (bracket < 0) return false;
      check_x = false;
    } else if (int x = check_func(i)) {
      if (x == 8)
        i++;
      else if ((x >= 1 && x <= 3) || x == 9)
        i += 2;
      else if (x >= 4 && x <= 7)
        i += 3;
      sign = false, check_x = false, unary = false;
      if (exp_[i + 1] != '(') return false;
      continue;
    } else if (exp_[i] == 'x' && check_x == false) {
      check_x = true, sign = false, unary = false;
      check_chislo++;
    } else {
      return false;
    }
  }
  if (bracket != 0 || check_znak != (check_chislo - 1)) return false;
  return true;
}

bool SmartCalcModel::check_error_x() {
  auto end = x_.end();
  auto i = x_.begin();
  if (i == end) return false;
  if (*i == '.' || *i == '-' || *i == '+' || (*i >= '0' && *i <= '9')) {
    bool dot = false;
    if (*i == '.') dot = true;
    i++;
    bool exp = false;
    for (; i != end; i++) {
      if (*i >= '0' && *i <= '9') {
        continue;
      } else if ((*i == 'e' || *i == 'E') && exp == false) {
        i++;
        if (i == end) return false;
        if (*i == '-' || *i == '+') {
          i++;
          exp = true;
          continue;
        } else {
          return false;
        }
      } else if (*i == '.' && dot == false) {
        dot = true;
        continue;
      } else {
        return false;
      }
    }
  } else {
    return false;
  }
  return true;
}

bool SmartCalcModel::check_unary(char znak) {
  return (znak == '+' || znak == '-');
}

bool SmartCalcModel::check_sign(char znak) {
  return (znak == '+' || znak == '-' || znak == '*' || znak == '/' ||
          znak == '%' || znak == '^');
}

bool SmartCalcModel::check_numner(char znak) {
  return (znak >= '0' && znak <= '9');
}

int SmartCalcModel::check_func(int i) {
  if (exp_[i] == 'c' && exp_[i + 1] == 'o' && exp_[i + 2] == 's')
    return 1;
  else if (exp_[i] == 's' && exp_[i + 1] == 'i' && exp_[i + 2] == 'n')
    return 2;
  else if (exp_[i] == 't' && exp_[i + 1] == 'a' && exp_[i + 2] == 'n')
    return 3;
  else if (exp_[i] == 'a' && exp_[i + 1] == 'c' && exp_[i + 2] == 'o' &&
           exp_[i + 3] == 's')
    return 4;
  else if (exp_[i] == 'a' && exp_[i + 1] == 's' && exp_[i + 2] == 'i' &&
           exp_[i + 3] == 'n')
    return 5;
  else if (exp_[i] == 'a' && exp_[i + 1] == 't' && exp_[i + 2] == 'a' &&
           exp_[i + 3] == 'n')
    return 6;
  else if (exp_[i] == 's' && exp_[i + 1] == 'q' && exp_[i + 2] == 'r' &&
           exp_[i + 3] == 't')
    return 7;
  else if (exp_[i] == 'l' && exp_[i + 1] == 'n')
    return 8;
  else if (exp_[i] == 'l' && exp_[i + 1] == 'o' && exp_[i + 2] == 'g')
    return 9;
  return 0;
}

void SmartCalcModel::operate_on_numbers() {
  char sim = sign_.top();
  sign_.pop();
  double y = number_.top();
  number_.pop();
  double x = 0;
  if ((sim >= '1' && sim <= '9') || (sim >= 'a' && sim <= 'i')) {
  } else {
    x = number_.top();
    number_.pop();
  }
  double res = 0;
  switch (sim) {
    case '^':
      res = pow(x, y);
      break;
    case '*':
      res = x * y;
      break;
    case '/':
      res = x / y;
      break;
    case '%':
      res = fmod(x, y);
      break;
    case '-':
      res = x - y;
      break;
    case '+':
      res = x + y;
      break;
    case 'a':
    case '1':  // cos
      res = cos(y);
      break;
    case 'b':
    case '2':  // sin
      res = sin(y);
      break;
    case 'c':
    case '3':  // tan
      res = tan(y);
      break;
    case 'd':
    case '4':  // acos
      res = acos(y);
      break;
    case 'e':
    case '5':  // asin
      res = asin(y);
      break;
    case 'f':
    case '6':  // atan
      res = atan(y);
      break;
    case 'g':
    case '7':  // sqrt
      res = sqrt(y);
      break;
    case 'h':
    case '8':  // ln
      res = log(y);
      break;
    case 'i':
    case '9':  // log
      res = log10(y);
      break;
  }
  number_.push(res);
}

int SmartCalcModel::push_func(int func, bool unary) {
  int i = 0;
  if (func == 8)
    i++;
  else if ((func >= 1 && func <= 3) || func == 9)
    i += 2;
  else if (func >= 4 && func <= 7)
    i += 3;
  func += 48;
  if (unary) func += 48;
  sign_.push(func);
  return i;
}

int SmartCalcModel::push_number(bool unary, int i) {
  size_t count = 0;
  double num = std::stod(&exp_[i], &count);
  if (unary) num *= -1;
  number_.push(num);
  return i + count - 1;
}

void SmartCalcModel::push_number_x(bool unary) {
  double num = std::stod(x_);
  if (unary) num *= -1;
  number_.push(num);
}

void SmartCalcModel::counting_in_brackets() {
  while (sign_.top() != '(') {
    operate_on_numbers();
  }
  sign_.pop();
  if (!sign_.empty() && ((sign_.top() >= '1' && sign_.top() <= '9') ||
                         (sign_.top() >= 'a' && sign_.top() <= 'i'))) {
    operate_on_numbers();
  }
}

int SmartCalcModel::priority(char a) {
  int flag = 0;
  switch (a) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '^':
      flag = 4;
      break;
    case '*':
    case '/':
    case '%':
      flag = 3;
      break;
    case '-':
    case '+':
      flag = 2;
      break;
    case '(':
      flag = 1;
      break;
  }
  return flag;
}

void SmartCalcModel::count_and_push_znak(int i) {
  if (priority(exp_[i]) == 2) {
    while (!sign_.empty() && priority(sign_.top()) >= 2) {
      operate_on_numbers();
    }
  } else if (priority(exp_[i]) == 3) {
    while (!sign_.empty() && priority(sign_.top()) >= 3) {
      operate_on_numbers();
    }
  }
  sign_.push(exp_[i]);
}

}  // namespace s21
