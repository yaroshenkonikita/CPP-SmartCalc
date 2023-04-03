#include "debitcalc.h"
#include "ui_debitcalcview.h"

using namespace s21;

DebitCalc::DebitCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebitCalc) {
    ui->setupUi(this);
}

DebitCalc::~DebitCalc() {
    delete ui;
}

void DebitCalc::on_resultButton_clicked() {
    std::vector<std::pair<int, double>> array_deposit{}, array_withdrawal{};
    array_deposit.push_back({ui->monthDepositSpinBox1->value(), ui->amountDepositMiddleDoubleSpinBox1->value()});
    array_deposit.push_back({ui->monthDepositSpinBox2->value(), ui->amountDepositMiddleDoubleSpinBox2->value()});
    array_deposit.push_back({ui->monthDepositSpinBox3->value(), ui->amountDepositMiddleDoubleSpinBox3->value()});
    array_deposit.push_back({ui->monthDepositSpinBox4->value(), ui->amountDepositMiddleDoubleSpinBox4->value()});
    array_deposit.push_back({ui->monthDepositSpinBox5->value(), ui->amountDepositMiddleDoubleSpinBox5->value()});
    array_deposit.push_back({ui->monthDepositSpinBox6->value(), ui->amountDepositMiddleDoubleSpinBox6->value()});
    array_deposit.push_back({ui->monthDepositSpinBox7->value(), ui->amountDepositMiddleDoubleSpinBox7->value()});
    array_deposit.push_back({ui->monthDepositSpinBox8->value(), ui->amountDepositMiddleDoubleSpinBox8->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox1->value(), ui->amountWithdrawalMiddleDoubleSpinBox1->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox2->value(), ui->amountWithdrawalMiddleDoubleSpinBox2->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox3->value(), ui->amountWithdrawalMiddleDoubleSpinBox3->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox4->value(), ui->amountWithdrawalMiddleDoubleSpinBox4->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox5->value(), ui->amountWithdrawalMiddleDoubleSpinBox5->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox6->value(), ui->amountWithdrawalMiddleDoubleSpinBox6->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox7->value(), ui->amountWithdrawalMiddleDoubleSpinBox7->value()});
    array_withdrawal.push_back({ui->monthWithdrawalSpinBox8->value(), ui->amountWithdrawalMiddleDoubleSpinBox8->value()});
    int accrual_period = 12, term_count = ui->termAmount->value();
    if (ui->periodicityPaymentRadioButtonMonth->isChecked()) {
        accrual_period = 1;
    } else if (ui->periodicityPaymentRadioButtonHalfYear->isChecked()) {
        accrual_period = 6;
    }
    if (ui->termRadioButtonYear->isChecked()) {
        term_count *= 12;
    }
    if (data.DepositCalculation(array_deposit, array_withdrawal, ui->amountDepositDoubleSpinBox->value(), term_count, ui->procentageDoubleSpinBox->value(), ui->taxDoubleSpinBox->value(), accrual_period, ui->procentageCapitalizationCheckBox->isChecked())) {
        ui->procentageAmountOutputLabel->setText(QString::number(data.interest_charges, 'f', 2));
        ui->taxAmountOutputLabel->setText(QString::number(data.tax_amount, 'f', 2));
        ui->totalAmountOutputLabel->setText(QString::number(data.total_amount, 'f', 2));
    } else {
        // ошибка
    }
}

