#include "CreditCalcModel.h"

namespace s21 {

std::stack<std::pair<std::string, double>> CreditCalcModel::annuity(
    double sum, double month, double year, double perc) {
  double date = month + year * 12;
  perc = (perc / 100) / 12;
  double payment_per_month = sum * (perc + (perc / (pow(1 + perc, date) - 1)));
  double total_sum = payment_per_month * date;
  double prepay = total_sum - sum;
  std::stack<std::pair<std::string, double>> result;
  result.push(std::pair<std::string, double>("total sum", total_sum));
  result.push(std::pair<std::string, double>("prepay", prepay));
  result.push(
      std::pair<std::string, double>("payment per month", payment_per_month));
  return result;
}

std::stack<std::pair<std::string, double>> CreditCalcModel::differentiated(
    double sum, double month, double year, double perc) {
  double date = month + year * 12;
  perc = (perc / 100) / 12;
  double sum_on_month = sum / date;
  double payment_per_month = sum / date + sum * perc;
  std::stack<std::pair<std::string, double>> result;
  result.push(
      std::pair<std::string, double>("payment per month", payment_per_month));
  double total_sum = payment_per_month;
  double tmp_sum = sum;
  date -= 1;
  for (int i = 0; i < date;) {
    sum = sum - sum_on_month;
    payment_per_month = sum / date + sum * perc;
    total_sum += payment_per_month;
    date -= 1;
  }
  double prepay = total_sum - tmp_sum;
  result.push(std::pair<std::string, double>("total sum", total_sum));
  result.push(std::pair<std::string, double>("prepay", prepay));
  result.push(std::pair<std::string, double>("last month's payment",
                                             payment_per_month));
  return result;
}

}  // namespace s21
