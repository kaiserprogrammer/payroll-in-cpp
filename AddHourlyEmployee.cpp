#include "WeeklySchedule.h"

class AddHourlyEmployee : public AddEmployee
{
public:
  double rate;
  AddHourlyEmployee(string name, string address, double rate, DB* db) : AddEmployee(name, address, db), rate(rate) {};

  void makeClassification() {
    employee->classification = new HourlyClassification(rate);
  }

  void makeSchedule() {
    employee->schedule = new WeeklySchedule();
  }
};
