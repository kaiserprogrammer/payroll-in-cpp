#include "ServiceCharge.cpp"

using namespace std;
using namespace boost::gregorian;

class UnionAffiliation : public Affiliation
{
public:
  double dues;
  map<date, ServiceCharge*> charges;

  UnionAffiliation(double dues)
    : dues(dues) {};

  double getDues() {
    return dues;
  }

  ServiceCharge* getServiceCharge(date day) {
    return charges.find(day)->second;
  }

  void addServiceCharge(ServiceCharge* sc) {
    charges.insert(pair<date, ServiceCharge*>(sc->day, sc));
  }

  double calculateDeductions(Paycheck* pc) {
    double charged = dues;
    for(map<date, ServiceCharge*>::iterator it = charges.begin();
        it != charges.end();
        ++it) {
      if (it->first >= pc->startDate && it->first <= pc->payDate) {
        charged += it->second->charge;
      }
    }
    return charged;
  };
};
