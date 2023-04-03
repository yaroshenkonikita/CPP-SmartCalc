#include <gtest/gtest.h>

#include "models/creditdata.h"
#include "models/debitdata.h"
#include "models/model.h"

TEST(SmartCalc, empty_valid) {
    s21::Model calc;
    EXPECT_TRUE(calc.Empty());
    EXPECT_TRUE(calc.IsValid());
}

TEST(SmartCalc, push_back_digit_and_valid) {
s21::Model calc;
calc.PushBack('5');
EXPECT_FALSE(calc.Empty());
EXPECT_TRUE(calc.IsValid());
}

TEST(SmartCalc, clear) {
s21::Model calc;
calc.PushBack('5');
EXPECT_FALSE(calc.Empty());
EXPECT_TRUE(calc.IsValid());
}

TEST(SmartCalc, solve_one_digit) {
s21::Model calc;
calc.PushBack('5');
EXPECT_TRUE(calc.IsValid());
double res{};
calc.SolveEquation(&res, 0);
EXPECT_EQ(res, 5);
}

TEST(SmartCalc, pop_back) {
s21::Model calc;
calc.PushBack('5');
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
calc.PopBack();
EXPECT_TRUE(calc.IsValid());
EXPECT_TRUE(calc.Empty());
}

TEST(SmartCalc, empty_to_string) {
s21::Model calc;
calc.PushBack('5');
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
EXPECT_STREQ(calc.ToString().c_str(), "5");
}

TEST(SmartCalc, addNewExp_valid) {
        s21::Model calc;
        calc.AddNewExp("5+5+5");
        EXPECT_TRUE(calc.IsValid());
        EXPECT_FALSE(calc.Empty());
EXPECT_STREQ(calc.ToString().c_str(), "5+5+5");
}

TEST(SmartCalc, add_new_exp_no_valid) {
s21::Model calc;
calc.AddNewExp("5+5+5-");
EXPECT_FALSE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
}

TEST(SmartCalc, solve_and_add_exp) {
s21::Model calc;
calc.AddNewExp("5+5+5*5");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
calc.SolveEquation(&res, 0);
EXPECT_DOUBLE_EQ(35, res);
}

TEST(SmartCalc, solve_and_add_exp_with_x) {
s21::Model calc;
calc.AddNewExp("x/5+5+5*5");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
calc.SolveEquation(&res, 5);
EXPECT_DOUBLE_EQ(31, res);
}

TEST(SmartCalc, solve_and_add_exp_with_x2) {
s21::Model calc;
calc.AddNewExp("x/(5+5+5+5)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
calc.SolveEquation(&res, 40);
EXPECT_DOUBLE_EQ(2, res);
}

TEST(SmartCalc, solve_exp) {
s21::Model calc;
calc.AddNewExp("2^1^45");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
EXPECT_DOUBLE_EQ(2, res);
}

TEST(SmartCalc, solve_exp2) {
s21::Model calc;
calc.AddNewExp("s(p/5)*c(20)-t(e^2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
EXPECT_DOUBLE_EQ(-1.753762037981895, res);
}

TEST(SmartCalc, solve_exp3) {
s21::Model calc;
calc.AddNewExp("i(p/5)*o(e/4)-a(e^2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
EXPECT_DOUBLE_EQ(-0.8767196277991767, res);
}

TEST(SmartCalc, solve_exp4) {
s21::Model calc;
calc.AddNewExp("1+2--3^0");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
EXPECT_DOUBLE_EQ(2, res);
}

TEST(SmartCalc, solve_exp_err) {
s21::Model calc;
calc.AddNewExp("q(-1)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err2) {
s21::Model calc;
calc.AddNewExp("i(2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err3) {
s21::Model calc;
calc.AddNewExp("o(2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err4) {
s21::Model calc;
calc.AddNewExp("l(-1)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err5) {
s21::Model calc;
calc.AddNewExp("n(-1)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err6) {
s21::Model calc;
calc.AddNewExp("1/0");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err7) {
s21::Model calc;
calc.AddNewExp("1m0");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp5) {
s21::Model calc;
calc.AddNewExp("aq128^c25");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
calc.SolveEquation(&res, 0);
EXPECT_DOUBLE_EQ(res, 1.4775093327295221);
}

TEST(SmartCalc, solve_exp6) {
s21::Model calc;
calc.AddNewExp("nq6m4");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
calc.SolveEquation(&res, 0);
EXPECT_DOUBLE_EQ(res, 0.8958797346140275);
}

TEST(SmartCalc, solve_exp7) {
s21::Model calc;
calc.AddNewExp("+2,5*(-2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
calc.SolveEquation(&res, 0);
EXPECT_DOUBLE_EQ(res, -5);
}

TEST(SmartCalc, solve_exp8) {
s21::Model calc;
calc.AddNewExp("l256");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
calc.SolveEquation(&res, 0);
EXPECT_DOUBLE_EQ(res, 2.4082399653118496);
}

TEST(SmartCalc, exp_err) {
s21::Model calc;
EXPECT_FALSE(calc.AddNewExp("1..2"));
}

TEST(SmartCalc, exp_err1) {
s21::Model calc;
EXPECT_FALSE(calc.AddNewExp("p.*1"));
}

TEST(SmartCalc, exp_err2) {
s21::Model calc;
EXPECT_FALSE(calc.AddNewExp("(*5)"));
}

TEST(SmartCalc, exp_err3) {
s21::Model calc;
EXPECT_FALSE(calc.AddNewExp("(5**3)"));
}

TEST(SmartCalc, exp_err4) {
s21::Model calc;
EXPECT_FALSE(calc.AddNewExp("5*3)"));
}

TEST(SmartCalc, exp_err5) {
s21::Model calc;
EXPECT_FALSE(calc.AddNewExp("(5*)"));
}

TEST(SmartCalc, exp_true) {
s21::Model calc;
EXPECT_TRUE(calc.AddNewExp("./5"));
}

TEST(SmartCalc, pop_back2) {
s21::Model calc;
EXPECT_TRUE(calc.AddNewExp("(4)"));
calc.PopBack();
calc.PopBack();
calc.PopBack();
EXPECT_TRUE(calc.Empty());
}

TEST(SmartCalc, to_string) {
s21::Model calc;
double res = 4;
calc.SolveEquation(&res, 0);
EXPECT_EQ(res, 0);
EXPECT_TRUE(calc.AddNewExp("lnqsicota0.5mp"));
EXPECT_STREQ("loglnsqrtsinasincosacostanatan0.5modπ", calc.ToString().c_str());
}

TEST(DebitCalc, test1_with_capitalization) {
 s21::DebitData debit;
 std::vector<std::pair<int, double>> insertion, erase;
 insertion.push_back({2, 50000});
 erase.push_back({5, 10000});
 debit.DepositCalculation(insertion, erase, 300000, 13, 25, 13, 2, true);
EXPECT_NEAR(debit.total_amount, 444433.3499405, 1e-7);
EXPECT_NEAR(debit.interest_charges, 104433.3499405, 1e-7);
EXPECT_NEAR(debit.tax_amount, 197.1688256, 1e-7);
}

TEST(DebitCalc, test1_without_capitalization) {
s21::DebitData debit;
std::vector<std::pair<int, double>> insertion, erase;
insertion.push_back({2, 5000});
erase.push_back({5, 5000});
debit.DepositCalculation(insertion, erase, 10000, 6, 20, 13, 1, false);
EXPECT_NEAR(debit.total_amount, 10000, 1e-7);
EXPECT_NEAR(debit.interest_charges, 1250, 1e-7);
EXPECT_NEAR(debit.tax_amount, 0, 1e-7);
}

TEST(CreditCalc, testDiff1) {
 s21::CreditData credit;
 EXPECT_TRUE(credit.CreditDifferentiated(1000, 12, 9));
EXPECT_NEAR(credit.all_payment, 1048.75, 1e-7);
 EXPECT_NEAR(credit.month_pay_first, 90.83333333, 1e-7);
EXPECT_NEAR(credit.month_pay_last, 83.9583333, 1e-7);
EXPECT_NEAR(credit.overpayment, 48.75, 1e-7);
}

TEST(CreditCalc, testDiff2) {
 s21::CreditData credit;
EXPECT_TRUE(credit.CreditDifferentiated(100456, 24, 12));
EXPECT_NEAR(credit.all_payment, 113013, 1e-7);
EXPECT_NEAR(credit.month_pay_first, 5190.2266666, 1e-7);
EXPECT_NEAR(credit.month_pay_last, 4227.5233333, 1e-7);
EXPECT_NEAR(credit.overpayment, 12557, 1e-7);
}

TEST(CreditCalc, testAnn1) {
 s21::CreditData credit;
EXPECT_TRUE(credit.CreditAnnuity(56743, 18, 15));
EXPECT_NEAR(credit.all_payment, 63718.1997081, 1e-7);
EXPECT_NEAR(credit.month_pay_first, 3539.8999837, 1e-7);
EXPECT_NEAR(credit.month_pay_last, 3539.8999837, 1e-7);
EXPECT_NEAR(credit.overpayment, 6975.1997081, 1e-7);
}

TEST(CreditCalc, testAnn2) {
 s21::CreditData credit;
EXPECT_TRUE(credit.CreditAnnuity(76142761, 6, 11));
EXPECT_NEAR(credit.all_payment, 78604249.762625, 1e-7);
EXPECT_NEAR(credit.month_pay_first, 13100708.2937708, 1e-7);
EXPECT_NEAR(credit.month_pay_last, 13100708.2937708, 1e-7);
EXPECT_NEAR(credit.overpayment, 2461488.762625, 1e-7);
}
