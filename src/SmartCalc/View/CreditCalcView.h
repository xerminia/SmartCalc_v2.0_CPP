#ifndef CREDITCALCVIEW_H
#define CREDITCALCVIEW_H

#include <QMessageBox>
#include <QWidget>

#include "SmartCalc/Controller/SmartCalcController.h"

namespace Ui {
class CreditCalcView;
}

namespace s21 {

class CreditCalcView : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalcView(s21::SmartCalcController *controller,
                          QWidget *parent = nullptr);
  ~CreditCalcView();

 private:
  Ui::CreditCalcView *ui;
  s21::SmartCalcController *controller_;
  double sum, month, year, perc;
  bool ok_sum, ok_year, ok_month, ok_perc;
  std::stack<std::pair<std::string, double>> result;
  void fill_in_the_lines();
  void clear_lines();
  void clear_result_lines();
  bool check_error();
 public slots:
  void slot();
 private slots:
  void on_pushButton_res_clicked();
};

}  // namespace s21

#endif  // CREDITCALCVIEW_H
