#include "BiWeeklySchedule.h"

using namespace std;

class AddCommissionedEmployee : public AddEmployee
{
public:
  double salary;
  double rate;
  AddCommissionedEmployee(string name, string address, double salary, double rate, DB* db)
    : AddEmployee(name, address, db), salary(salary), rate(rate){};

  void makeClassification() {
employee->classification = new CommissionedClassification(salary, rate);
  }

  void makeSchedule() {
    employee->schedule = new BiWeeklySchedule();
  }
};
