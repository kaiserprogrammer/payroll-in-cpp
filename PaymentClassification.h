#pragma once

#include "Paycheck.h"

class PaymentClassification
{
public:
  virtual double calculatePay(Paycheck* pc) =0;
};
