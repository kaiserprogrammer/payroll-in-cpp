#pragma once

#include "ChangeEmployee.h"

class ChangeClassification : public ChangeEmployee
{
 public:
  virtual void makeClassification() =0;
  virtual void makeSchedule() =0;

  ChangeClassification(int empId, DB* db)
    : ChangeEmployee(empId, db) {};

  void change() {
    delete(employee->classification);
    delete(employee->schedule);
    makeClassification();
    makeSchedule();
  }
};
