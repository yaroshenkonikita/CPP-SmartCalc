#include "creditcalc.h"
#include "ui_creditcalcview.h"

using namespace s21;

CreditCalc::CreditCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditCalc) {
    ui->setupUi(this);
}

CreditCalc::~CreditCalc() {
    delete ui;
}

void CreditCalc::GetValuesFromData() {
    if (data.month_pay_first == data.month_pay_last) {
        ui->monthPaymentLabelOutput->setText(QLocale().toString(data.month_pay_first, 7));
    } else {
        ui->monthPaymentLabelOutput->setText(QLocale().toString(data.month_pay_first, 7) + " ... " + QLocale().toString(data.month_pay_last, 7));
    }
    ui->AllPaymentsLabelOutput->setText(QLocale().toString(data.all_payment, 7));
    ui->overpaymentLabelOutput->setText(QLocale().toString(data.overpayment, 7));
}

void CreditCalc::Error() {
    ui->AllPaymentsLabelOutput->setText("Не правильные аргументы");
    ui->monthPaymentLabelOutput->setText("Не правильные аргументы");
    ui->overpaymentLabelOutput->setText("Не правильные аргументы");
}


void CreditCalc::on_diffButton_clicked() {
    int count_month = ui->termCreditSpinBox->value();
    if (ui->termCreditRadioButtonYear->isChecked()) {
        count_month *= 12;
    }
    if (data.CreditDifferentiated(ui->amountCreditDoubleSpinBox->value(), count_month, ui->procentageCreditDoubleSpinBox->value())) {
        GetValuesFromData();
    } else {
        Error();
    }
}


void CreditCalc::on_AnnButton_clicked() {
    int count_month = ui->termCreditSpinBox->value();
    if (ui->termCreditRadioButtonYear->isChecked()) {
        count_month *= 12;
    }
    if (data.CreditAnnuity(ui->amountCreditDoubleSpinBox->value(), count_month, ui->procentageCreditDoubleSpinBox->value())) {
        GetValuesFromData();
    } else {
        Error();
    }
}

