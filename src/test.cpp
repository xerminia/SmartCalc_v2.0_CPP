#include <gtest/gtest.h>

#include "SmartCalc/Model/CreditCalcModel.h"
#include "SmartCalc/Model/SmartCalcModel.h"

using s21::CreditCalcModel;
using s21::SmartCalcModel;

TEST(calculateBase, test_1) {
  double result = 10 + 5;
  SmartCalcModel test_calc;
  double myResult = std::stod(test_calc.parsing("10+5", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateBase, test_2) {
  double result = 10.2 - 5.2;
  SmartCalcModel test_calc;
  double myResult = std::stod(test_calc.parsing("10.2-5.2", ""));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateBase, test_3) {
  double result = 10 * 5;
  SmartCalcModel test_calc;
  double myResult = std::stod(test_calc.parsing("10*5", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateBase, test_4) {
  double result = 10e-5 / 5e-5;
  SmartCalcModel test_calc;
  double myResult = std::stod(test_calc.parsing("10e-5/5e-5", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateBase, test_5) {
  double result = fmod(10, 5);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("10%5", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateBase, test_6) {
  double result = pow(10, 5);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("10^5", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateBase, test_7) {
  double result = (10 - 5);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("(10-5)", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateBase, test_8) {
  double result = -15;
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("-15", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateBase, test_9) {
  double result = +15;
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("+15", ""));
  ASSERT_EQ(myResult, result);
}

TEST(calculateFunction, test_1) {
  double x = 5;
  double result = cos(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("cos(x)", "5"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_2) {
  double x = 5;
  double result = sin(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("sin(x)", "5"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_3) {
  double x = 5;
  double result = tan(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("tan(x)", "5"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_4) {
  double x = 0.123;
  double result = acos(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("acos(x)", "0.123"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_5) {
  double x = 0.123;
  double result = asin(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("asin(x)", "0.123"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_6) {
  double x = 0.123;
  double result = atan(-x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("atan(-x)", "0.123"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_7) {
  double x = 25.5e-5;
  double result = sqrt(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("sqrt(x)", "25.5e-5"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_8) {
  double x = 25.5;
  double result = log(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("ln(x)", "25.5"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateFunction, test_9) {
  double x = 25.5;
  double result = log10(x);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("log(x)", "25.5"));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculatePrimer, test_1) {
  double result = 1804275000027.3699;
  SmartCalcModel testCalc;
  double myResult = std::stod(
      testCalc.parsing("10+20-(((((30*30))^2)^2)-(-sin(+27)))*-2.75", ""));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculatePrimer, test_2) {
  double result = 16 / 4 * (3 - 1);
  SmartCalcModel testCalc;
  double myResult = std::stod(testCalc.parsing("16/4*(3-1)", ""));
  ASSERT_NEAR(myResult, result, 0.7);
}

TEST(calculateError, test_1) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("--1", "");
  ASSERT_EQ("Error", result);
}

TEST(calculateError, test_2) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("qwe", "");
  ASSERT_EQ("Error", result);
}

TEST(calculateError, test_3) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("sin(x", "");
  ASSERT_EQ("Error", result);
}

TEST(calculateError, test_4) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("1+*5", "");
  ASSERT_EQ("Error", result);
}

TEST(calculateError, test_5) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("1+x", "1.1.1");
  ASSERT_EQ("Error", result);
}

TEST(calculateGraph, test_1) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("x", "");
  ASSERT_EQ("graph", result);
}

TEST(calculateGraph, test_2) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("sin(x)", "");
  ASSERT_EQ("graph", result);
}

TEST(calculateGraph, test_3) {
  SmartCalcModel testCalc;
  std::string result = testCalc.parsing("1+x-56.3*-cos(x)", "");
  ASSERT_EQ("graph", result);
}

TEST(CreditCalc_annuity, test_1) {
  double sum = 200000;
  double month = 0;
  double year = 2;
  double perc = 10;
  CreditCalcModel creditTest;
  std::stack<std::pair<std::string, double>> result =
      creditTest.annuity(sum, month, year, perc);
  double payment_per_month = 9228.99;
  double prepay = 21495.6;
  double total_sum = 221495.64;
  ASSERT_NEAR(result.top().second, payment_per_month, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, prepay, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, total_sum, 0.2);
  result.pop();
}

TEST(CreditCalc_annuity, test_2) {
  double sum = 1000000;
  double month = 6;
  double year = 2;
  double perc = 8.7;
  CreditCalcModel creditTest;
  std::stack<std::pair<std::string, double>> result =
      creditTest.annuity(sum, month, year, perc);
  double payment_per_month = 37209.85;
  double prepay = 116295.53;
  double total_sum = 1116295.53;
  ASSERT_NEAR(result.top().second, payment_per_month, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, prepay, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, total_sum, 0.2);
  result.pop();
}

TEST(CreditCalc_differentiated, test_1) {
  double sum = 200000;
  double month = 0;
  double year = 2;
  double perc = 10;
  CreditCalcModel creditTest;
  std::stack<std::pair<std::string, double>> result =
      creditTest.differentiated(sum, month, year, perc);
  double last_months_payment = 8402.77;
  double prepay = 20833.33;
  double total_sum = 220833.33;
  double payment_per_month = 10000;
  ASSERT_NEAR(result.top().second, last_months_payment, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, prepay, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, total_sum, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, payment_per_month, 0.2);
  result.pop();
}

TEST(CreditCalc_differentiated, test_2) {
  double sum = 1000000;
  double month = 6;
  double year = 2;
  double perc = 8.7;
  CreditCalcModel creditTest;
  std::stack<std::pair<std::string, double>> result =
      creditTest.differentiated(sum, month, year, perc);
  double last_months_payment = 33574.99;
  double prepay = 112374.99;
  double total_sum = 1112374.99;
  double payment_per_month = 40583.33;
  ASSERT_NEAR(result.top().second, last_months_payment, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, prepay, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, total_sum, 0.2);
  result.pop();
  ASSERT_NEAR(result.top().second, payment_per_month, 0.2);
  result.pop();
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
