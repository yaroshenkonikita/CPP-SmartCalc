#include "model.h"

using namespace s21;

Model::CalcTypeSymbol Model::BackType() { return _expression.back().second; }

Model::CalcTypeSymbol Model::WhatIsSymbol(char symbol) {
  switch (symbol) {
    case '.':
      return Model::DOT;
    case 'x':
    case 'p':
    case 'e':
      return Model::CONST;
    case '+':
    case '-':
      if (Empty() || BackType() == Model::LOW_OPER ||
          BackType() == Model::MIDDLE_OPER || BackType() == Model::HIGH_OPER ||
          BackType() == Model::NEW_EXP) {
        return Model::UNAR_OPER;
      }
      return Model::LOW_OPER;
    case '*':
    case '/':
    case 'm':
      return Model::MIDDLE_OPER;
    case '^':
      return Model::HIGH_OPER;
    case 'l':
    case 'n':
    case 'q':
    case 's':
    case 'i':
    case 'c':
    case 'o':
    case 't':
    case 'a':
      return Model::FUNCTION_OPER;
    case '(':
      return Model::NEW_EXP;
    case ')':
      return Model::END_EXP;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      if (!Empty()) {
        if (BackType() == Model::DOT || BackType() == Model::NUMBER_AFTER_DOT) {
          return Model::NUMBER_AFTER_DOT;
        }
      }
      return Model::NUMBER;
    case 'u':
      return Model::UNAR_OPER;
    default:
      throw std::invalid_argument("Wrong symbol in model expression");
  }
}

void Model::Clear() {
  _expression.clear();
  _brackets = 0;
}

bool Model::Empty() { return _expression.empty(); }

bool Model::IsValid() {
  return Empty() || (_brackets == 0 &&
                     (BackType() == Model::NUMBER ||
                      BackType() == Model::NUMBER_AFTER_DOT ||
                      BackType() == Model::CONST || BackType() == END_EXP));
}

Model::CalcTypeError Model::PushBack(char symbol) {
  if (_expression.size() == 255) return OVER_FLOW_EXP;
  if (symbol == ',') {
    symbol = '.';
  }
  CalcTypeSymbol type_symbol = WhatIsSymbol(symbol);
  switch (type_symbol) {
    case CONST:
      if (!Empty()) {
        if (BackType() == DOT || BackType() == NUMBER ||
            BackType() == NUMBER_AFTER_DOT || BackType() == CONST) {
          PushBack('*') if (_expression.size() == 255) return OVER_FLOW_EXP;
        }
      }
      break;
    case NUMBER:
      if (!Empty()) {
        if (BackType() == CONST || BackType() == END_EXP) {
          PushBack('*') if (_expression.size() == 255) return OVER_FLOW_EXP;
        }
      }
      break;
    case DOT:
      if (Empty() || BackType() == UNAR_OPER || BackType() == LOW_OPER ||
          BackType() == MIDDLE_OPER || BackType() == HIGH_OPER ||
          BackType() == FUNCTION_OPER || BackType() == NEW_EXP) {
        PushBack('0') if (_expression.size() == 255) return OVER_FLOW_EXP;
      }
      if (BackType() == CONST || BackType() == END_EXP) {
        return DOT_FOR_CONST;
      }
      if (BackType() == DOT || BackType() == NUMBER_AFTER_DOT) {
        return DOUBLE_DOT;
      }
      break;
    case LOW_OPER:
    case MIDDLE_OPER:
    case HIGH_OPER:
      if (Empty()) {
        PushBack('0');
      } else if (BackType() == NEW_EXP) {
        return OPER_FOR_NEW_EXP;
      }
      if (BackType() == LOW_OPER || BackType() == MIDDLE_OPER ||
          BackType() == HIGH_OPER || BackType() == FUNCTION_OPER ||
          BackType() == UNAR_OPER) {
        return DOUBLE_OPER;
      }
      if (BackType() == DOT) {
        PushBack('0') if (_expression.size() == 255) return OVER_FLOW_EXP;
      }
      break;
    case FUNCTION_OPER:
      if (!Empty()) {
        if (BackType() == DOT || BackType() == NUMBER ||
            BackType() == NUMBER_AFTER_DOT || BackType() == CONST ||
            BackType() == END_EXP) {
          PushBack('*') if (_expression.size() == 255) return OVER_FLOW_EXP;
        }
      }
      break;
    case NEW_EXP:
      if (!Empty()) {
        if (BackType() == DOT || BackType() == NUMBER ||
            BackType() == NUMBER_AFTER_DOT || BackType() == CONST ||
            BackType() == END_EXP) {
          PushBack('*') if (_expression.size() == 255) return OVER_FLOW_EXP;
        }
      }
      ++_brackets;
      break;
    case END_EXP:
      if (_brackets == 0) {
        return BRACKET_MINUS;
      }
      if (BackType() == DOT) {
        PushBack('0') if (_expression.size() == 255) return OVER_FLOW_EXP;
      }
      if (BackType() == UNAR_OPER || BackType() == LOW_OPER ||
          BackType() == MIDDLE_OPER || BackType() == HIGH_OPER ||
          BackType() == FUNCTION_OPER || BackType() == NEW_EXP) {
        return INCOMPLETE_EXP;
      }
      --_brackets;
  }
  _expression.push_back(std::make_pair(symbol, type_symbol));
  return NO_ERROR;
}

void Model::PopBack() {
  if (_expression.back().second == END_EXP) {
    ++_brackets;
  } else if (_expression.back().second == NEW_EXP) {
    --_brackets;
  }
  _expression.pop_back();
}

bool Model::AddNewExp(std::string exp) {
  Clear();
  for (char symbol : exp) {
    if (PushBack(symbol)) {
      Clear();
      return false;
    }
  }
  return true;
}

std::string Model::ToStringOfOneChar() {
  std::string exp{};
  for (auto item : _expression) {
    if (item.second == UNAR_OPER) {
      if (item.first == '-') {
        exp.push_back('u');
      }
    } else {
      exp.push_back(item.first);
    }
  }
  if (exp.empty()) {
    exp.push_back('0');
  }
  return exp;
}

std::string Model::ToString() {
  std::string exp{};
  for (auto item : _expression) {
    switch (item.first) {
      case 'l':
        exp.append("log");
        break;
      case 'n':
        exp.append("ln");
        break;
      case 'q':
        exp.append("sqrt");
        break;
      case 's':
        exp.append("sin");
        break;
      case 'i':
        exp.append("asin");
        break;
      case 'c':
        exp.append("cos");
        break;
      case 'o':
        exp.append("acos");
        break;
      case 't':
        exp.append("tan");
        break;
      case 'a':
        exp.append("atan");
        break;
      case 'm':
        exp.append("mod");
        break;
      case 'p':
        exp.append("π");
        break;
      default:
        exp.push_back(item.first);
    }
  }
  if (exp.empty()) {
    exp.push_back('0');
  }
  return exp;
}

Model::CalculationError Model::UseOneOperFromStack(
    std::stack<double> &numbers, std::stack<char> &operators) {
  double tmp;
  if (!operators.empty()) {
    switch (operators.top()) {
      case 'u':
        numbers.top() *= -1;
        break;
      case 'l':
        if (numbers.top() < 0) {
          return LOG_MINUS;
        }
        numbers.top() = log10(numbers.top());
        break;
      case 'n':
        if (numbers.top() < 0) {
          return LN_MINUS;
        }
        numbers.top() = log(numbers.top());
        break;
      case 'q':
        if (numbers.top() < 0) {
          return SQRT_MINUS;
        }
        numbers.top() = sqrt(numbers.top());
        break;
      case 's':
        numbers.top() = sin(numbers.top());
        break;
      case 'i':
        if (numbers.top() > 1 || numbers.top() < -1) {
          return ASIN_RANGE;
        }
        numbers.top() = asin(numbers.top());
        break;
      case 'c':
        numbers.top() = cos(numbers.top());
        break;
      case 'o':
        if (numbers.top() > 1 || numbers.top() < -1) {
          return ACOS_RANGE;
        }
        numbers.top() = acos(numbers.top());
        break;
      case 't':
        numbers.top() = tan(numbers.top());
        break;
      case 'a':
        numbers.top() = atan(numbers.top());
        break;
      case 'm':
        if (numbers.top() < 1e-6) {
          return DIV_ZERO;
        }
        tmp = numbers.top();
        numbers.pop();
        numbers.top() = fmod(numbers.top(), tmp);
        break;
      case '/':
        if (numbers.top() < 1e-6) {
          return DIV_ZERO;
        }
        tmp = numbers.top();
        numbers.pop();
        numbers.top() = numbers.top() / tmp;
        break;
      case '*':
        tmp = numbers.top();
        numbers.pop();
        numbers.top() = numbers.top() * tmp;
        break;
      case '+':
        tmp = numbers.top();
        numbers.pop();
        numbers.top() = numbers.top() + tmp;
        break;
      case '-':
        tmp = numbers.top();
        numbers.pop();
        numbers.top() = numbers.top() - tmp;
        break;
      case '^':
        tmp = numbers.top();
        numbers.pop();
        numbers.top() = pow(numbers.top(), tmp);
    }
    operators.pop();
  }
  return SUCCESS;
}

Model::CalculationError Model::SolveEquation(double *result, double x) {
  if (!IsValid() || !result) {
    return WRONG_EXP;
  } else if (Empty()) {
    *result = 0;
    return SUCCESS;
  }
  std::stack<double> numbers;
  std::stack<char> operators;
  std::string exp = ToStringOfOneChar();
  std::size_t countOfShift;
  for (char *current_pos = (char *)exp.c_str(); *current_pos;
       current_pos += countOfShift) {
    countOfShift = 1;
    switch (*current_pos) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        countOfShift = 0;
        numbers.push(std::strtod(current_pos, &current_pos));
        break;
      case 'x':
        numbers.push(x);
        break;
      case 'e':
        numbers.push(2.71828182845904523536);
        break;
      case 'p':
        numbers.push(3.14159265358979323846);
        break;
      case '(':
        operators.push('(');
        break;
      case 'u':
        operators.push('u');
        break;
      default:
        if (operators.empty()) {
          operators.push(*current_pos);
        } else {
          switch (WhatIsSymbol(*current_pos)) {
            case FUNCTION_OPER:
              operators.push(*current_pos);
              break;
            case HIGH_OPER:
              while (WhatIsSymbol(operators.top()) == FUNCTION_OPER ||
                     WhatIsSymbol(operators.top()) == UNAR_OPER) {
                CalculationError error_output =
                    UseOneOperFromStack(numbers, operators);
                if (error_output) {
                  return error_output;
                }
                if (operators.empty()) break;
              }
              operators.push(*current_pos);
              break;
            case MIDDLE_OPER:
              while (WhatIsSymbol(operators.top()) > LOW_OPER) {
                CalculationError error_output =
                    UseOneOperFromStack(numbers, operators);
                if (error_output) {
                  return error_output;
                }
                if (operators.empty()) break;
              }
              operators.push(*current_pos);
              break;
            case LOW_OPER:
              while (!operators.empty()) {
                if (operators.top() == '(') break;
                CalculationError error_output =
                    UseOneOperFromStack(numbers, operators);
                if (error_output) {
                  return error_output;
                }
              }
              operators.push(*current_pos);
              break;
            default:
              while (operators.top() != '(') {
                CalculationError error_output =
                    UseOneOperFromStack(numbers, operators);
                if (error_output) {
                  return error_output;
                }
              }
              operators.pop();
          }
        }
    }
  }
  while (!operators.empty()) {
    CalculationError error_output = UseOneOperFromStack(numbers, operators);
    if (error_output) {
      return error_output;
    }
  }
  *result = numbers.top();
  return SUCCESS;
}
