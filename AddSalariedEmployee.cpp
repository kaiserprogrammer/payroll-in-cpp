#include "AddEmployee.h"
#include "DB.h"
#include "MonthlySchedule.h"
#include "SalariedClassification.cpp"

using namespace std;

class AddSalariedEmployee : public AddEmployee
{
  double salary;
public:
  AddSalariedEmployee(string name, string address, double salary, DB* db)
    : salary(salary), AddEmployee(name, address, db) {
  };

  void makeClassification() {
    employee->classification = new SalariedClassification(salary);
  }

  void makeSchedule() {
    employee->schedule = new MonthlySchedule();
  }

};
