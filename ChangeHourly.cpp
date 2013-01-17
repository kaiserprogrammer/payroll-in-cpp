#include "ChangeClassification.h"

class ChangeHourly : public ChangeClassification
{
public:
  double rate;

  ChangeHourly(int empId, double rate, DB* db)
    : ChangeClassification(empId, db), rate(rate) {};

  void makeClassification() {
    employee->classification = new HourlyClassification(rate);
  }

  void makeSchedule() {
    employee->schedule = new WeeklySchedule();
  }
};
