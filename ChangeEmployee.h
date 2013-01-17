#pragma once

#include "Transaction.h"

class ChangeEmployee : public Transaction
{
 public:
  int empId;
  DB* db;
  Employee* employee;

  ChangeEmployee(int empId, DB* db)
    : empId(empId), db(db) {};

  void execute() {
    employee = db->getEmployee(empId);
    change();
  }

  virtual void change() =0;
};
