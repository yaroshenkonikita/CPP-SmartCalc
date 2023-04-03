#ifndef DEBITDATA_H_
#define DEBITDATA_H_

#include <cmath>
#include <vector>

namespace s21 {

struct DebitData {
    DebitData() = default;
    ~DebitData() = default;

    bool DepositCalculation(std::vector<std::pair<int, double>> &array_insert, std::vector<std::pair<int, double>> &array_erase, double original_amount, double term,
                           double interest, double tax, int accrual_period, bool capitalization);

    double interest_charges{},
    tax_amount{},
    total_amount{};
private:
    double GetMoneyFromArray(std::vector<std::pair<int, double>> &array_month_money, int count_month);
};

} // namespace s21

#endif // DEBITDATA_H_
