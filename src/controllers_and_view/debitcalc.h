#ifndef DEBITCALC_H_
#define DEBITCALC_H_

#include <QDialog>
#include <QMessageBox>

#include "../models/debitdata.h"

namespace Ui {
class DebitCalc;
}

namespace s21 {

class DebitCalc : public QDialog {
  Q_OBJECT

 public:
  explicit DebitCalc(QWidget *parent = nullptr);
  ~DebitCalc();

 private slots:
  void on_resultButton_clicked();

 private:
  Ui::DebitCalc *ui;
  DebitData data;
};

}  // namespace s21

#endif  // DEBITCALC_H_
