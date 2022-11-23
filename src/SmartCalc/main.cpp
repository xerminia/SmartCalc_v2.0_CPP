#include <QApplication>

#include "SmartCalc/Model/SmartCalcModel.h"
#include "SmartCalc/View/SmartCalcView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::SmartCalcModel model;
  s21::CreditCalcModel credit;
  s21::SmartCalcController controller(&model, &credit);
  s21::SmartCalcView main_window(&controller);
  main_window.setWindowTitle("Calculator");
  main_window.show();
  return a.exec();
}
