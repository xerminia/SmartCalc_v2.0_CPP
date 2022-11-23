#include "CreditCalcView.h"

#include "ui_CreditCalcView.h"

namespace s21 {

CreditCalcView::CreditCalcView(SmartCalcController *controller, QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalcView), controller_(controller) {
  ui->setupUi(this);
  ui->lineEdit_total_sum->setEnabled(false);
  ui->lineEdit_month_1->setEnabled(false);
  ui->lineEdit_prepay->setEnabled(false);
  ui->lineEdit_month_2->setEnabled(false);
  ui->lineEdit_total_sum->setStyleSheet("color: rgb(102, 255, 0)");
  ui->lineEdit_month_1->setStyleSheet("color: rgb(102, 255, 0)");
  ui->lineEdit_prepay->setStyleSheet("color: rgb(102, 255, 0)");
  ui->lineEdit_month_2->setStyleSheet("color: rgb(102, 255, 0)");
}

CreditCalcView::~CreditCalcView() { delete ui; }

void CreditCalcView::fill_in_the_lines() {
  clear_result_lines();
  if (!result.empty()) {
    while (!result.empty()) {
      if (result.top().first == "total sum") {
        ui->lineEdit_total_sum->setText(
            QString::number(result.top().second, 'f', 2));
      }
      if (result.top().first == "prepay") {
        ui->lineEdit_prepay->setText(
            QString::number(result.top().second, 'f', 2));
      }
      if (result.top().first == "payment per month") {
        ui->lineEdit_month_1->setText(
            QString::number(result.top().second, 'f', 2));
      }
      if (result.top().first == "last month's payment") {
        ui->lineEdit_month_2->setText(
            QString::number(result.top().second, 'f', 2));
      }
      result.pop();
    }
  } else {
    ui->lineEdit_prepay->setText("Ошибка");
    ui->lineEdit_month->setText("Ошибка");
    ui->lineEdit_total_sum->setText("Ошибка");
    ui->lineEdit_month_2->setText("Ошибка");
  }
}

void CreditCalcView::clear_lines() {
  ui->lineEdit_month->clear();
  ui->lineEdit_perc->clear();
  ui->lineEdit_sum->clear();
  ui->lineEdit_year->clear();
  clear_result_lines();
}

void CreditCalcView::clear_result_lines() {
  ui->lineEdit_total_sum->clear();
  ui->lineEdit_month_1->clear();
  ui->lineEdit_prepay->clear();
  ui->lineEdit_month_2->clear();
}

bool CreditCalcView::check_error() {
  if (ui->lineEdit_year->text().isEmpty()) {
    year = 0;
    ok_year = true;
  }
  if (ui->lineEdit_month->text().isEmpty()) {
    month = 0;
    ok_month = true;
  }
  if (ok_sum && ok_year && ok_month && ok_perc && sum > 0 && perc > 0 &&
      perc < 1000 && (year * 12 + month) > 0)
    return true;
  return false;
}

void CreditCalcView::slot() { clear_lines(); }

void CreditCalcView::on_pushButton_res_clicked() {
  sum = ui->lineEdit_sum->text().toDouble(&ok_sum);
  year = ui->lineEdit_year->text().toDouble(&ok_year);
  month = ui->lineEdit_month->text().toDouble(&ok_month);
  perc = ui->lineEdit_perc->text().toDouble(&ok_perc);

  if (check_error()) {
    if (ui->radioButton_ann->isChecked()) {
      result = controller_->get_result(sum, month, year, perc, 1);
    } else if (ui->radioButton_diff->isChecked()) {
      result = controller_->get_result(sum, month, year, perc, 2);
    } else {
      QMessageBox *mb = new QMessageBox;
      mb->setWindowTitle("Error!");
      mb->setText("Не выбран тип расчета.");
      mb->show();
    }
    fill_in_the_lines();
  } else {
    QMessageBox *mb = new QMessageBox;
    mb->setWindowTitle("Fatal!");
    mb->setText("Error input!");
    mb->show();
  }
}

}  // namespace s21
