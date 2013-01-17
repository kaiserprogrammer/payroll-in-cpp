#include "ServiceCharge.cpp"

using namespace boost::gregorian;

class AddServiceCharge : public Transaction
{
public:
  int memberId;
  date day;
  double charge;
  DB* db;

  AddServiceCharge(int memberId, date day, double charge, DB* db)
    : memberId(memberId), day(day), charge(charge), db(db) {};

  void execute() {
    Employee* e = db->getUnionMember(memberId);
    ServiceCharge* sc = new ServiceCharge(day, charge);
    static_cast<UnionAffiliation*>(e->affiliation)
      ->addServiceCharge(sc);
  }
};
