#ifndef DEBITCALC_H_
#define DEBITCALC_H_

#include <QDialog>
#include <QMessageBox>

#include "../models/debitdata.h"

namespace Ui {
class DebitCalc;
}

namespace s21 {
/**
 * @brief Контроллер Дебетового калькулятора
 */
class DebitCalc : public QDialog {
  Q_OBJECT

 public:
  explicit DebitCalc(
      QWidget *parent = nullptr);  ///< Дефолтный конструктор с вариационным
                                   ///< указателем на родителя
  ~DebitCalc();  ///< Дефолтный деструктор

 private slots:
  void on_resultButton_clicked();  ///< Слот вызывает функцию Депозитного
                                   ///< калькулятора

 private:
  Ui::DebitCalc *ui;  ///< Указатель на View
  DebitData data;  ///< Объект класса модели Дебетового калькулятора
};

}  // namespace s21

#endif  // DEBITCALC_H_
