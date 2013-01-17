#pragma once

using namespace boost::gregorian;

class SalesReceipt
{
public:
  date day;
  double amount;
  SalesReceipt(date day, double amount) : day(day), amount(amount) {};
};
