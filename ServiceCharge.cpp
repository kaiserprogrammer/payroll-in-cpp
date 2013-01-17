#pragma once

using namespace boost::gregorian;

class ServiceCharge
{
public:
  date day;
  double charge;

  ServiceCharge(date day, double charge)
    : day(day), charge(charge) {};
};
