#ifndef CREDITCALC_H_
#define CREDITCALC_H_

#include <QDialog>
#include <QMessageBox>

#include "../models/creditdata.h"

namespace Ui {
class CreditCalc;
}

namespace s21 {
/**
 * @brief Контроллер Кредитного калькулятора
 */
class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(
      QWidget *parent = nullptr);  ///< Дефолтный конструктор с вариационным
                                   ///< указателем на родителя
  ~CreditCalc();  ///< Дефолтный деструктор

 private slots:
  void on_diffButton_clicked();  ///< Слот вызывает функцию Дифференцированного
                                 ///< калькулятора

  void
  on_AnnButton_clicked();  ///< Слот вызывает функцию Аннуитетного калькулятора

 private:
  Ui::CreditCalc *ui;  ///< Указатель на View
  CreditData data;  ///< Объект класса модели Кредитного калькулятора

  void GetValuesFromData();  ///< Функция выводит значения класса модели в view
};

}  // namespace s21

#endif  // CREDITCALC_H_
