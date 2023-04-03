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
calc.AddNewExp("sp/5)*c20)-te^2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
EXPECT_DOUBLE_EQ(-1.753762037981895, res);
}

TEST(SmartCalc, solve_exp3) {
s21::Model calc;
calc.AddNewExp("ip/5)*oe/4)-ae^2)");
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
calc.AddNewExp("q-1)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err2) {
s21::Model calc;
calc.AddNewExp("i2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err3) {
s21::Model calc;
calc.AddNewExp("o2)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err4) {
s21::Model calc;
calc.AddNewExp("l-1)");
EXPECT_TRUE(calc.IsValid());
EXPECT_FALSE(calc.Empty());
double res{};
EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err5) {
s21::Model calc;
calc.AddNewExp("n-1)");
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