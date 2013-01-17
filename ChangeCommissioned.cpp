#include "ChangeClassification.h"

class ChangeCommissioned : public ChangeClassification
{
public:
  double salary, commission;

  ChangeCommissioned(int empId, double salary, double commission, DB* db)
    : ChangeClassification(empId, db), salary(salary), commission(commission) {};

  void makeClassification() {
    employee->classification = new CommissionedClassification(salary, commission);
  }

  void makeSchedule() {
    employee->schedule = new BiWeeklySchedule();
  }
};
