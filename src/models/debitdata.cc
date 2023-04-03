#include "debitdata.h"

using namespace s21;

double DebitData::GetMoneyFromArray(std::vector<std::pair<int, double>> &array_month_money, int count_month) {
  double buf = 0;
  for (int i = 0; i < array_month_money.size(); i++) {
    if (array_month_money[i].first == count_month) {
      buf += array_month_money[i].second;
    }
  }
  return buf;
}

bool DebitData::DepositCalculation(std::vector<std::pair<int, double>> &array_insert, std::vector<std::pair<int, double>> &array_erase, double original_amount, double term,
                       double interest, double tax, int accrual_period, bool capitalization) {
  interest_charges = 0;
  interest = interest / 100. / 12.;
  tax = tax / 100.;

  for (int i = 1, last_accrual_period = 0; i <= term; ++i) {
    original_amount += GetMoneyFromArray(array_insert, i);
    double tmp_amount = GetMoneyFromArray(array_erase, i);
    original_amount -= tmp_amount > original_amount ? original_amount : tmp_amount;
    if (capitalization) {
        if (i % accrual_period == 0) {
          interest_charges += interest * accrual_period * (original_amount + interest_charges);
          last_accrual_period = i;
        } else if (i == term) {
          int delta_accrual_period = i - last_accrual_period;
          interest_charges += interest * delta_accrual_period * (original_amount + interest_charges);
        }
    } else {
        interest_charges += interest * original_amount;
    }
  }
  total_amount = original_amount;
  if (capitalization) {
      total_amount += interest_charges;
  }

  tax_amount = ((interest_charges / term) - (95000 / 12.)) * term * tax;

  tax_amount = tax_amount < 0 ? 0 : tax_amount;
  if (std::isnan(interest_charges) || std::isinf(interest_charges) ||
      std::isnan(total_amount) || std::isinf(total_amount) ||
      std::isnan(tax_amount) || std::isinf(tax_amount)) {
    return false;
  }
  return true;
}
