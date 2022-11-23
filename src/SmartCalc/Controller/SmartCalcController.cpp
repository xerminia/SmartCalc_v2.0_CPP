#include "SmartCalcController.h"

namespace s21 {

std::string SmartCalcController::get_result(std::string exp, std::string x) {
  return model_->parsing(exp, x);
}
// type == 1 аннуитетный
// type == 2 дифференцированный
std::stack<std::pair<std::string, double>> SmartCalcController::get_result(
    double sum, double month, double year, double perc, int type) {
  if (type == 1)
    return credit_->annuity(sum, month, year, perc);
  else if (type == 2)
    return credit_->differentiated(sum, month, year, perc);
  return std::stack<std::pair<std::string, double>>();
}

}  // namespace s21
