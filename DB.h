#pragma once

class DB
{
public:
  virtual Employee* getEmployee(int empId) =0;
  virtual void addEmployee(Employee* employee) =0;
  virtual void deleteEmployee(int empId) =0;
  virtual std::vector<Employee*> getEmployees() =0;
  virtual Employee* getUnionMember(int memberId) =0;
  virtual void addUnionMember(Employee* member) =0;
  virtual void deleteMember(int memberId) =0;
  virtual void deletePointer(Employee* e) =0;
};
