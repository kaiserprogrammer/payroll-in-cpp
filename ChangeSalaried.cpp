#include "MonthlySchedule.h"
#include "SalariedClassification.cpp"

class ChangeSalaried : public ChangeClassification
{
public:
  double salary;

  ChangeSalaried(int empId, double salary, DB* db)
    : ChangeClassification(empId, db), salary(salary) {};

  void makeClassification() {
    employee->classification = new SalariedClassification(salary);
  }

  void makeSchedule() {
    employee->schedule = new MonthlySchedule();
  }
};
