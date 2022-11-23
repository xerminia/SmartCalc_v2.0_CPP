#include "SmartCalcView.h"

#include "ui_SmartCalcView.h"

namespace s21 {

SmartCalcView::SmartCalcView(s21::SmartCalcController *controller,
                             QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalcView), controller_(controller) {
  ui->setupUi(this);
  graph = new DrawingGraph(controller_);
  connect(this, &s21::SmartCalcView::signal_graph, graph,
          &s21::DrawingGraph::slot);
  credit = new CreditCalcView(controller_);
  connect(this, &s21::SmartCalcView::signal_credit, credit,
          &s21::CreditCalcView::slot);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_closeb, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_openb, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));

  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

SmartCalcView::~SmartCalcView() { delete ui; }

void SmartCalcView::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonText = button->text();

  if (ui->radioButton_x->isChecked()) {
    QString tmpLabel = ui->lineEdit_x->text();
    ui->lineEdit_x->setText(tmpLabel + buttonText);
  } else {
    QString tmpLabel = ui->lineEdit_exp->text();
    ui->lineEdit_exp->setText(tmpLabel + buttonText);
  }
}

void SmartCalcView::on_pushButton_clear_clicked() {
  if (ui->radioButton_exp->isChecked()) {
    ui->lineEdit_exp->clear();
  } else if (ui->radioButton_x->isChecked()) {
    ui->lineEdit_x->clear();
  } else {
    ui->lineEdit_exp->clear();
    ui->lineEdit_x->clear();
  }
}

void SmartCalcView::on_pushButton_clear_one_sym_clicked() {
  if (ui->radioButton_exp->isChecked()) {
    QString tmp_exp;
    tmp_exp = ui->lineEdit_exp->text();
    if (tmp_exp.endsWith("acos") || tmp_exp.endsWith("asin") ||
        tmp_exp.endsWith("atan") || tmp_exp.endsWith("sqrt")) {
      tmp_exp.chop(4);
    } else if (tmp_exp.endsWith("cos") || tmp_exp.endsWith("sin") ||
               tmp_exp.endsWith("tan") || tmp_exp.endsWith("log")) {
      tmp_exp.chop(3);
    } else if (tmp_exp.endsWith("ln")) {
      tmp_exp.chop(2);
    } else {
      tmp_exp.chop(1);
    }
    ui->lineEdit_exp->setText(tmp_exp);
  } else if (ui->radioButton_x->isChecked()) {
    QString tmp_x = ui->lineEdit_x->text();
    tmp_x.chop(1);
    ui->lineEdit_x->setText(tmp_x);
  }
}

void SmartCalcView::on_pushButton_equals_clicked() {
  QString res_str = ui->lineEdit_exp->text();
  QString res_x = ui->lineEdit_x->text();
  if (!res_str.isEmpty()) {
    setlocale(LC_NUMERIC, "C");
    std::string str_exp = res_str.toStdString();
    std::string str_x = res_x.toStdString();
    std::string result = controller_->get_result(str_exp, str_x);
    if (result == "Error") {
      QMessageBox *error = new QMessageBox;
      error->setMaximumSize(2500, 2500);
      error->setWindowTitle("Fatal!");
      error->setText("Error input!");
      error->show();
      on_pushButton_clear_clicked();
      ui->lineEdit_exp->clear();
      ui->lineEdit_x->clear();
    } else if (result == "graph") {
      graph->setWindowTitle("График");
      graph->show();
      emit signal_graph(ui->lineEdit_exp->text());
    } else {
      ui->lineEdit_exp->setText(QString::fromStdString(result));
    }
  }
}

void SmartCalcView::on_action_triggered() {
  credit->setWindowTitle("Кредитный Калькулятор");
  credit->show();
  emit signal_credit();
}

}  // namespace s21
