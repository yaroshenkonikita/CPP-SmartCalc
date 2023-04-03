#ifndef MODEL_H_
#define MODEL_H_

#include <cmath>
#include <stack>
#include <stdexcept>
#include <utility>
#include <vector>

namespace s21 {

class Model {
 public:
  Model() = default;

  typedef enum TypeOfError {
    NO_ERROR,
    DOT_FOR_CONST,
    DOUBLE_DOT,
    DOUBLE_OPER,
    OPER_FOR_NEW_EXP,
    BRACKET_MINUS,
    OVER_FLOW_EXP,
    INCOMPLETE_EXP
  } CalcTypeError;

  typedef enum TypeOfCalculationError {
    SUCCESS,
    WRONG_EXP,
    LOG_MINUS,
    LN_MINUS,
    SQRT_MINUS,
    ASIN_RANGE,
    ACOS_RANGE,
    DIV_ZERO
  } CalculationError;

  CalcTypeError PushBack(char symbol);
  void PopBack();
  bool AddNewExp(std::string exp);
  bool IsValid();
  bool Empty();
  void Clear();
  std::string ToString();
  CalculationError SolveEquation(double *result, double x);

//  QLineSeries *GetSeriesOfSolveEquation(int xAxisSize);

 private:
  typedef enum TypeOfChar {
    NUMBER,
    NEW_EXP,
    END_EXP,
    DOT,
    NUMBER_AFTER_DOT,
    CONST,
    LOW_OPER,
    MIDDLE_OPER,
    HIGH_OPER,
    FUNCTION_OPER,
    UNAR_OPER
  } CalcTypeSymbol;

  CalcTypeSymbol WhatIsSymbol(char symbol);
  std::string ToStringOfOneChar();
  CalcTypeSymbol BackType();
  CalculationError UseOneOperFromStack(std::stack<double> &numbers,
                                       std::stack<char> &operators);

  std::vector<std::pair<char, CalcTypeSymbol>> _expression{};

  int _brackets{};
};

}  // namespace s21

#endif  // MODEL_H_
