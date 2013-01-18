#include "Transaction.h"
#include "DB.h"
#include "HoldMethod.h"

using namespace std;
class AddEmployee : public Transaction
{
 public:
 AddEmployee(string name, string address, DB* db)
   : name(name), address(address), db(db) {};
  int empId;
  string name;
  string address;
  Employee* employee;
  DB* db;
  virtual void makeClassification() =0;
  virtual void makeSchedule() =0;

  void execute() {
    employee = new Employee(name, address);
    makeClassification();
    makeSchedule();
    employee->method = new HoldMethod();
    db->addEmployee(employee);
    empId = employee->empId;
    db->deletePointer(employee);
  }
};
