#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <QMainWindow>

#include "../models/model.h"
#include "creditcalc.h"
#include "debitcalc.h"
#include "graphplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controller;
}
QT_END_NAMESPACE

namespace s21 {

class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(QWidget *parent = nullptr);
  ~Controller();

 private slots:
  void on_buttonGraph_clicked();
  void on_buttonC_clicked();
  void on_buttonCE_clicked();
  void on_buttonRES_clicked();

  void AnyButtonClick();

  void on_openCreditCalc_clicked();
  void on_openDebitCalc_clicked();

 private:
  Ui::Controller *ui;
  Model data;
};

}  // namespace s21

#endif  // CONTROLLER_H_
