#include "creditdata.h"

using namespace s21;

bool CreditData::CreditAnnuity(double amount_payment, double credit_term, double pay_percentage) {
  all_payment = 0;
  pay_percentage = pay_percentage / 12. / 100.;
  month_pay_last = month_pay_first = pay_percentage * std::pow(1 + pay_percentage, credit_term) / (std::pow(1 + pay_percentage, credit_term) - 1) * amount_payment;
  overpayment = month_pay_first * credit_term - amount_payment;
  all_payment = overpayment + amount_payment;
  if (std::isnan(month_pay_first) || std::isinf(month_pay_first)) {
    return false;
  }
  return true;
}

bool CreditData::CreditDifferentiated(double amount_payment, double credit_term, double pay_percentage) {
  pay_percentage /= 100.;
  all_payment = 0;
  double delta_m = amount_payment / credit_term,
  buf_sum = amount_payment;
  for (int i = 0; i < credit_term; i++) {
    month_pay_last = buf_sum * pay_percentage * 30.4166666666667 / 365 + delta_m;
    buf_sum -= delta_m;
    all_payment += month_pay_last;
    if (!i) {
      month_pay_first = month_pay_last;
    }
  }
  overpayment = all_payment - amount_payment;
  if (std::isnan(month_pay_first) || std::isinf(month_pay_first) || std::isnan(delta_m) ||
      std::isinf(delta_m)) {
    return false;
  }

  return true;
}
