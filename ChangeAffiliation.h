class ChangeAffiliation : public ChangeEmployee
{
 public:
  ChangeAffiliation(int empId, DB* db)
    : ChangeEmployee(empId, db) {};

  void change() {
    delete(employee->affiliation);
    makeAffiliation();
    recordMembership(employee);
  }

  virtual void makeAffiliation() =0;
  virtual void recordMembership(Employee* e) =0;
};
