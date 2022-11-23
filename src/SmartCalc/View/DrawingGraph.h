#ifndef DRAWINGGRAPH_H
#define DRAWINGGRAPH_H

#include <QWidget>
#include <iostream>

#include "SmartCalc/Controller/SmartCalcController.h"

constexpr double step = 100000;

namespace Ui {
class DrawingGraph;
}

namespace s21 {

class DrawingGraph : public QWidget {
  Q_OBJECT

 public:
  explicit DrawingGraph(s21::SmartCalcController *controller,
                        QWidget *parent = nullptr);
  ~DrawingGraph();

 private:
  Ui::DrawingGraph *ui;
  s21::SmartCalcController *controller_;
  double X, xBegin, xEnd, h;
  QVector<double> x, y;

 public slots:
  void slot(QString input_str);
 private slots:
  void on_pushButton_graf_clicked();
};

}  // namespace s21

#endif  // DRAWINGGRAPH_H
