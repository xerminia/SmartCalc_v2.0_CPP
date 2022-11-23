#ifndef CREDITCALCMODEL_H
#define CREDITCALCMODEL_H

#include <cmath>
#include <stack>
#include <string>

namespace s21 {

class CreditCalcModel {
 public:
  CreditCalcModel() {}
  ~CreditCalcModel() {}
  std::stack<std::pair<std::string, double>> annuity(double sum, double month,
                                                     double year, double perc);
  std::stack<std::pair<std::string, double>> differentiated(double sum,
                                                            double month,
                                                            double year,
                                                            double perc);
};

}  // namespace s21

#endif  // CREDITCALCMODEL_H
