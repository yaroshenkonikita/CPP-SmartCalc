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
/**
 * @brief Контроллер для приложения калькулятора
 */
class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(
      QWidget *parent = nullptr);  ///< Дефолтный конструктор с вариационным
                                   ///< указателем на родителя
  ~Controller();  ///< Дефолтный деструктор

 private slots:
  void on_buttonGraph_clicked();  ///< Слот вызывает создание графика
  void on_buttonC_clicked();  ///< Слот вызывает очистку всего уравнения
  void on_buttonCE_clicked();  ///< Слот вызывает очистку последнего
                               ///< добавленного элемента
  void on_buttonRES_clicked();  ///< Слот вызывает вызов решения уравнения

  void
  AnyButtonClick();  ///< Слот добавляет символ кнопки которая вызвала этот слот

  void on_openCreditCalc_clicked();  ///< Слот вызывает открытие Кредитного
                                     ///< калькулятора
  void on_openDebitCalc_clicked();  ///< Слот вызывает открытие Депозитного
                                    ///< калькулятора

 private:
  Ui::Controller *ui;  ///< Указатель на View
  Model data;          ///< Объект класса Model
};

}  // namespace s21

#endif  // CONTROLLER_H_
