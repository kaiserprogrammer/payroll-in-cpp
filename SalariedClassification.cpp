#pragma once

#include "PaymentClassification.h"

class SalariedClassification : public PaymentClassification
{
public:
  double salary;

  SalariedClassification(double salary) : salary(salary) {};

  double calculatePay(Paycheck* pc) {
    return salary;
  }
};
