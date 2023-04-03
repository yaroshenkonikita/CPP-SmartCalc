#ifndef CREDITDATA_H_
#define CREDITDATA_H_

#include <cmath>

namespace s21 {

struct CreditData {
    CreditData() = default;
    ~CreditData() = default;

    bool CreditAnnuity(double amount_payment, double time_credit, double pay_percentage);
    bool CreditDifferentiated(double amount_payment, double time_credit, double pay_percentage);

    double month_pay_first{},
    month_pay_last{},
    overpayment{},
    all_payment{};
};

} // namespace s21

#endif // CREDITDATA_H_
