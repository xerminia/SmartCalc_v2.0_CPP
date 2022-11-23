#include "DrawingGraph.h"

#include "SmartCalc/View/SmartCalcView.h"
#include "ui_DrawingGraph.h"

namespace s21 {

DrawingGraph::DrawingGraph(SmartCalcController *controller, QWidget *parent)
    : QWidget(parent), ui(new Ui::DrawingGraph), controller_(controller) {
  ui->setupUi(this);
}

DrawingGraph::~DrawingGraph() { delete ui; }

void DrawingGraph::slot(QString input_str) { ui->label->setText(input_str); }

void DrawingGraph::on_pushButton_graf_clicked() {
  x.clear();
  y.clear();
  QString tmp_x_b = ui->lineEdit_xb->text();
  QString tmp_x_e = ui->lineEdit_xe->text();
  bool ok1, ok2;
  setlocale(LC_NUMERIC, "C");
  double x_b = tmp_x_b.toDouble(&ok1);
  double x_e = tmp_x_e.toDouble(&ok2);
  if (ok1 && ok2 && x_b < x_e) {
    h = fabs(x_b - x_e) / step;
    xBegin = x_b;
    xEnd = x_e + h;
    std::string input_str = ui->label->text().toStdString();
    for (X = x_b; X <= x_e; X += h) {
      std::string input_str_x = std::to_string(X);
      double Y = std::stod(controller_->get_result(input_str, input_str_x));
      x.push_back(X);
      y.push_back(Y);
    }
  } else {
    QMessageBox *error = new QMessageBox;
    error->setWindowTitle("Fatal!");
    error->setText("Error input!");
    error->show();
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRange(x_b, x_e);
  ui->widget->yAxis->setRange(x_b, x_e);
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
  ui->widget->replot();
  ui->lineEdit_xb->clear();
  ui->lineEdit_xe->clear();
}

}  // namespace s21
