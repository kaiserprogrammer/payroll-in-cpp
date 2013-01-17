#include "ChangeEmployee.h"
#include "DB.h"

class ChangeAddress : public ChangeEmployee
{
public:
  std::string address;

  ChangeAddress(int empId, std::string address, DB* db)
    : ChangeEmployee(empId, db), address(address) {};

  void change() {
    employee->address = address;
  }
};
