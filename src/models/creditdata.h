#ifndef CREDITDATA_H_
#define CREDITDATA_H_

#include <cmath>

namespace s21 {
/**
 * @brief Модель для кредитного калькулятора
 */
struct CreditData {
  CreditData() = default;   ///< Дефолтный конструктор
  ~CreditData() = default;  ///< Дефолтный деструктор

  /**
   * @brief  Вычисляет ежемесячный платеж и общую переплату по кредиту с
   * аннуитетным графиком платежей.
   * @param amount_payment сумма кредита
   * @param credit_term срок кредита в месяцах
   * @param pay_percentage процентная ставка по кредиту
   * @return true, если расчет прошел успешно и false, если невозможно посчитать
   * с данными аргументами
   */
  bool CreditAnnuity(double amount_payment, double time_credit,
                     double pay_percentage);

  /** @brief Вычисляет ежемесячный платеж и общую переплату по кредиту с
   * дифференцированным графиком платежей.
   * @param amount_payment сумма кредита
   * @param credit_term срок кредита в месяцах
   * @param pay_percentage процентная ставка по кредиту
   * @return true, если расчет прошел успешно и false, если невозможно посчитать
   * с данными аргументами
   */
  bool CreditDifferentiated(double amount_payment, double time_credit,
                            double pay_percentage);

  double month_pay_first{},  ///< Результат функций, платеж в первый месяц
      month_pay_last{},  ///< Результат функций, платеж в последний месяц
      overpayment{},  ///< Результат функций, переплата от основного долга
      all_payment{};  ///< Результат функций, полная сумма к возврату
};

}  // namespace s21

#endif  // CREDITDATA_H_
