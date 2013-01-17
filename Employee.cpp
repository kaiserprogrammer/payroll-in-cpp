#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"
#include "Affiliation.h"
#include "Paycheck.h"

using namespace boost::gregorian;

class Employee
{
public:
  std::string name;
  std::string address;
  int empId;
  int memberId;
  PaymentClassification* classification;
  PaymentSchedule* schedule;
  PaymentMethod* method;
  Affiliation* affiliation = new NoAffiliation();

  Employee(std::string name, std::string address)
    : name(name),
      address(address) {};

  bool isPayday(date day) {
    schedule->isPayday(day);
  }

  date getPayPeriodStartDate(date day) {
    return schedule->getPayPeriodStartDate(day);
  }

  void payday(Paycheck* pc) {
    double pay = classification->calculatePay(pc);
    double deductions = affiliation->calculateDeductions(pc);
    pc->grossPay = pay;
    pc->deductions = deductions;
    pc->netPay = pay - deductions;
    pc->disposition = method->disposition();
    method->pay(pc);
  }
};
