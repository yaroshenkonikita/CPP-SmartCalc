#ifndef DEBITDATA_H_
#define DEBITDATA_H_

#include <cmath>
#include <vector>

namespace s21 {
/**
 * @brief Модель для дебетового калькулятора
 */
struct DebitData {
  DebitData() = default;   ///< Дефолтный конструктор
  ~DebitData() = default;  ///< Дефолтный деструктор

  /**
   * @brief Рассчитывает сумму депозита после заданного срока
   * @param array_insert Вектор пар, представляющих суммы денег, которые
   * необходимо добавить в конкретные сроки
   * @param array_erase Вектор пар, представляющих суммы денег, которые
   * необходимо вычесть в конкретные сроки
   * @param original_amount Изначальная сумма депозита
   * @param term Срок депозита в месяцах
   * @param interest Процентная ставка депозита в годовом выражении
   * @param tax Процент налога на доходы в депозите
   * @param accrual_period Период начисления процентов в месяцах
   * @param capitalization Флаг, указывающий на ежемесячную капитализацию
   * процентов
   * @return Возвращает true, если расчёт прошёл успешно, и false, если
   * невозможно подсчитать для данных аргументов
   */
  bool DepositCalculation(std::vector<std::pair<int, double>> &array_insert,
                          std::vector<std::pair<int, double>> &array_erase,
                          double original_amount, double term, double interest,
                          double tax, int accrual_period, bool capitalization);

  double interest_charges{},  ///< Результат функции, начисленный процент
      tax_amount{},  ///< Результат функции, налог к выплате
      total_amount{};  ///< Результат функции, всего на счёте под конец вклада

 private:
  static constexpr double key_rate = 7.5 / 100.;  ///< Ключевая ставка в РФ

  /**
   * @brief Получает сумму денег по указанному месяцу из массива пар
   * месяц-сумма.
   * @param array_month_money Массив пар месяц-сумма, из которого нужно получить
   * деньги.
   * @param count_month Месяц, для которого нужно получить деньги.
   * @return Сумма денег по указанному месяцу.
   */
  double GetMoneyFromArray(
      std::vector<std::pair<int, double>> &array_month_money, int count_month);
};

}  // namespace s21

#endif  // DEBITDATA_H_
