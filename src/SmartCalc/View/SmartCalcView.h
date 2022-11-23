#ifndef SMARTCALCVIEW_H
#define SMARTCALCVIEW_H

#include <SmartCalc/View/DrawingGraph.h>

#include <QMainWindow>
#include <QMessageBox>

#include "SmartCalc/View/CreditCalcView.h"
#include "SmartCalc/Controller/SmartCalcController.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalcView;
}
QT_END_NAMESPACE
namespace s21 {
class SmartCalcView : public QMainWindow {
  Q_OBJECT

 public:
  explicit SmartCalcView(s21::SmartCalcController *controller,
                         QWidget *parent = nullptr);
  ~SmartCalcView();

 private slots:
  void digits_numbers();
  void on_pushButton_clear_clicked();
  void on_pushButton_clear_one_sym_clicked();
  void on_pushButton_equals_clicked();

  void on_action_triggered();

 private:
  Ui::SmartCalcView *ui;
  s21::SmartCalcController *controller_;
  s21::DrawingGraph *graph;
  s21::CreditCalcView *credit;

 signals:
  void signal_graph(QString);
  void signal_credit();
};

}  // namespace s21

#endif  // SMARTCALCVIEW_H
