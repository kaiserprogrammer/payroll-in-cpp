#pragma once

using namespace boost::gregorian;

class Paycheck
{
public:
  date payDate;
  date startDate;
  double grossPay;
  double deductions;
  double netPay;
  std::string disposition;

  Paycheck(date startDate, date payDate)
    : startDate(startDate), payDate(payDate) {};
};
