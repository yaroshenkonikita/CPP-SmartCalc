#ifndef MODEL_H_
#define MODEL_H_

#include <cmath>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace s21 {
/**
 * @brief Модель для приложения калькулятора
 */
class Model {
 public:
  Model() = default;  ///< Дефолтный конструктор

  typedef enum TypeOfError {
    NO_ERROR,          ///< Ошибки нет
    DOT_FOR_CONST,     ///< Точка после константы
    DOUBLE_DOT,        ///< Две точки в одном числе
    DOUBLE_OPER,       ///< Два бинарных оператора
    OPER_FOR_NEW_EXP,  ///< Бинарный оператор в начале строки или после
                       ///< открывающейся скобки
    BRACKET_MINUS,  ///< Закрывающихся скобок больше чем открывающихся
    OVER_FLOW_EXP,  ///< Значений в контейнере 255(потолок по заданию)
    INCOMPLETE_EXP  ///< Закрывающаяся скобка после операторов
  } CalcTypeError;  ///< Список ошибок на стадии ввода значений в контейнер

  typedef enum TypeOfCalculationError {
    SUCCESS,    ///< Ошибки нет, все посчитано
    WRONG_EXP,  ///< Неверное уравнение или параметр
    LOG_MINUS,  ///< Логарифм отрицательного числа
    LN_MINUS,   ///< Логарифм отрицательного числа
    SQRT_MINUS,        ///< Корень отрицательного числа
    ASIN_RANGE,        ///< Невозможное определение arcsin
    ACOS_RANGE,        ///< Невозможное определение arccos
    DIV_ZERO           ///< Деление на ноль
  } CalculationError;  ///< Список ошибок на стадии решения уравнения

  /**
   * @brief Добавление символа уравнения в конец контейнера
   * @param symbol символ для добавления в уравнение
   * @return true, если символ уложился в уравнение и false, если не уложился
   */
  CalcTypeError PushBack(char symbol);
  /**
   * @brief Удаляет последний добавленный символ в контейнере
   */
  void PopBack();
  /**
   * @brief Заполняет контейнер посимвольно из строки
   * @param exp строка с уравнением
   * @return true, если все символы удачно записались и false, в обратном
   */
  bool AddNewExp(std::string exp);
  /**
   * @brief Проверяет уравнение в контейнере на валидацию
   * @return true, если уравнение закончено и может посчитаться и false, если
   * обратное
   */
  bool IsValid();
  /**
   * @brief Проверяет контейнер на пустоту
   * @return true, если пустой и false, если обратное
   */
  bool Empty();
  /**
   * @brief Очищает контейнер
   */
  void Clear();
  /**
   * @brief Возвращает все символы контейнера в человеческом представлении
   * @return строку с уравнением для view
   */
  std::string ToString();
  /**
   * @brief Считает ответ для уравнения
   * @param result запись результирующего чиста
   * @param x значение числа для X
   * @return возвращает значение из списка с ошибками CalculationError
   */
  CalculationError SolveEquation(double *result, double x);

 private:
  typedef enum TypeOfChar {
    NUMBER,            ///< Число
    NEW_EXP,           ///< Начало уравнения, то есть '('
    END_EXP,           ///< Конец уравнения, то есть ')'
    DOT,               ///< Точка
    NUMBER_AFTER_DOT,  ///< Число после точки
    CONST,             ///< Константа
    LOW_OPER,  ///< Бинарный оператор с низкой приоритетностью
    MIDDLE_OPER,  ///< Бинарный оператор с средней приоритетностью
    HIGH_OPER,  ///< Бинарный оператор с высокой приоритетностью
    FUNCTION_OPER,   ///< Функция
    UNAR_OPER        ///< Унарный оператор
  } CalcTypeSymbol;  ///< Обозначение состояния для каждого символа в контейнере

  /**
   * @brief Внутренняя функция определения состояния у символа в контейнере
   * @param symbol исходный символ для определения
   * @return элемент из списка CalcTypeSymbol с корректным значением состояния
   * символа
   */
  CalcTypeSymbol WhatIsSymbol(char symbol);
  /**
   * @brief Возвращает строку из контейнера в том виде как хранится для
   * проведения вычисления
   * @return строку из контейнера
   */
  std::string ToStringOfOneChar();
  /**
   * @brief Функция для получения типа последнего добавленного символа
   * @return тип CalcTypeSymbol последнего символа из контейнера
   */
  CalcTypeSymbol BackType();
  /**
   * Функция для вычисления, берет элемент из стэка операторов и применяет его
   * на числа в стеке чисел
   * @param numbers стек чисел
   * @param operators стек операторов
   * @return результат работы оператора из списка CalculationError
   */
  CalculationError UseOneOperFromStack(std::stack<double> &numbers,
                                       std::stack<char> &operators);

  std::vector<std::pair<char, CalcTypeSymbol>>
      _expression{};  ///< Вектор пар, хранит в себе символ и состояние этого
                      ///< символа

  int _brackets{};  ///< Переменная для хранения количества открытых скобок в
                    ///< контейнере
};

}  // namespace s21

#endif  // MODEL_H_
