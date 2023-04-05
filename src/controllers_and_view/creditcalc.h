#ifndef CREDITCALC_H_
#define CREDITCALC_H_

#include <QDialog>
#include <QMessageBox>

#include "../models/creditdata.h"

namespace Ui {
class CreditCalc;
}

namespace s21 {

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:
  void on_diffButton_clicked();

  void on_AnnButton_clicked();

 private:
  Ui::CreditCalc *ui;
  CreditData data;

  void GetValuesFromData();
};

}  // namespace s21

#endif  // CREDITCALC_H_
