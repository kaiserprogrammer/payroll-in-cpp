#include "ChangeAffiliation.h"
#include "UnionAffiliation.cpp"

class ChangeUnionMember : public ChangeAffiliation
{
public:
  int memberId;
  double dues;

  ChangeUnionMember(int empId, double dues, DB* db)
    : ChangeAffiliation(empId, db), dues(dues) {};

  void makeAffiliation() {
    employee->affiliation = new UnionAffiliation(dues);
  }

  void recordMembership(Employee* e) {
    db->addUnionMember(e);
    memberId = e->memberId;
  }
};
