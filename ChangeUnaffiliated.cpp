class ChangeUnaffiliated : public ChangeAffiliation
{
public:
  ChangeUnaffiliated(int empId, DB* db)
    : ChangeAffiliation(empId, db) {};

  void makeAffiliation() {
    employee->affiliation = new NoAffiliation();
  };

  void recordMembership(Employee* m) {
    db->deleteMember(m->memberId);
  }
};
