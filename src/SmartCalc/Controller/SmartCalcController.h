#ifndef SMARTCALCCONTROLLER_H
#define SMARTCALCCONTROLLER_H

#include "SmartCalc/Model/CreditCalcModel.h"
#include "SmartCalc/Model/SmartCalcModel.h"

namespace s21 {

class SmartCalcController {
 private:
  s21::SmartCalcModel *model_;
  s21::CreditCalcModel *credit_;

 public:
  SmartCalcController(s21::SmartCalcModel *model, s21::CreditCalcModel *credit)
      : model_(model), credit_(credit) {}
  ~SmartCalcController() {}
  std::string get_result(std::string exp, std::string x);
  std::stack<std::pair<std::string, double>> get_result(double sum,
                                                        double month,
                                                        double year,
                                                        double perc, int type);
};

}  // namespace s21

#endif  // SMARTCALCCONTROLLER_H
