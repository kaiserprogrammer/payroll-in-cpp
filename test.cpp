#include <iostream>
#include <cassert>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "Employee.cpp"
#include "SalariedClassification.cpp"
#include "CommissionedClassification.cpp"
#include "HourlyClassification.cpp"
#include "AddSalariedEmployee.cpp"
#include "AddCommissionedEmployee.cpp"
#include "AddHourlyEmployee.cpp"
#include "MemoryDB.cpp"
#include "ChangeAddress.cpp"
#include "ChangeName.cpp"
#include "ChangeCommissioned.cpp"
#include "ChangeHourly.cpp"
#include "ChangeSalaried.cpp"
#include "ChangeUnionMember.cpp"
#include "ChangeUnaffiliated.cpp"
#include "DeleteEmployee.cpp"
#include "AddSalesReceipt.cpp"
#include "AddTimeCard.cpp"
#include "AddServiceCharge.cpp"
#include "AddEmployeePresenter.cpp"
#include "Paycheck.h"
#include "Payday.cpp"

using namespace std;
using namespace boost::gregorian;

void add_salaried_employee_test() {
  MemoryDB db;
  AddSalariedEmployee t("Bob", "Home", 1000.0, &db);
  t.execute();
  int empId = t.empId;
  Employee* e = db.getEmployee(empId);
  assert(e->name == "Bob");
  assert(e->address == "Home");

  SalariedClassification* pc = static_cast<SalariedClassification*>(e->classification);
  assert(pc->salary == 1000.0);

  assert(e->schedule->type() == "monthly");
  assert(e->method->type() == "hold");
}

void add_commissioned_employee_test() {
  MemoryDB db;
  AddCommissionedEmployee t("Jim", "Garden", 500.0, 100.0, &db);
  t.execute();

  Employee* e = db.getEmployee(t.empId);
  assert(e->name == "Jim");
  assert(e->address == "Garden");

  CommissionedClassification* pc = static_cast<CommissionedClassification*>(e->classification);
  assert(pc->salary == 500);
  assert(pc->commission == 100.0);

  assert(e->schedule->type() == "biweekly");
  assert(e->method->type() == "hold");
}

void add_hourly_employee_test() {
  MemoryDB db;
  AddHourlyEmployee t("John", "Work", 20.0, &db);
  t.execute();

  Employee* e = db.getEmployee(t.empId);
  assert(e->name == "John");
  assert(e->address == "Work");

  HourlyClassification* pc = static_cast<HourlyClassification*>(e->classification);
  assert(pc->rate == 20.0);

  assert(e->schedule->type() == "weekly");
  assert(e->method->type() == "hold");
}

void change_address_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bill", "Work", 20.0, &db);
  t.execute();

  ChangeAddress cat(t.empId, "Home", &db);
  cat.execute();

  Employee* e = db.getEmployee(t.empId);
  assert(e->address == "Home");
}

void change_name_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bill", "Home", 15.25, &db);
  t.execute();

  ChangeName cnt(t.empId, "Bob", &db);
  cnt.execute();

  Employee* e = db.getEmployee(t.empId);
  assert(e->name == "Bob");
}

void change_commissioned_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bob", "Home", 15.25, &db);
  t.execute();

  ChangeCommissioned cct(t.empId, 1000, 3.0, &db);
  cct.execute();

  Employee* e = db.getEmployee(t.empId);

  CommissionedClassification* pc = static_cast<CommissionedClassification*>(e->classification);
  assert(pc->salary == 1000);
  assert(pc->commission == 3.0);

  assert(e->schedule->type() == "biweekly");
}

void change_hourly_test() {
  MemoryDB db;
  AddCommissionedEmployee t("Bill", "Home", 1000, 3.0, &db);
  t.execute();

  ChangeHourly cht(t.empId, 15.25, &db);
  cht.execute();

  Employee* e = db.getEmployee(t.empId);

  HourlyClassification* pc = static_cast<HourlyClassification*>(e->classification);
  assert(pc->rate == 15.25);

  assert(e->schedule->type() == "weekly");
}

void change_salaried_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bill", "Home", 15.25, &db);
  t.execute();

  ChangeSalaried cst(t.empId, 1500.0, &db);
  cst.execute();

  Employee* e = db.getEmployee(t.empId);

  SalariedClassification* pc = static_cast<SalariedClassification*>(e->classification);
  assert(pc->salary == 1500.0);

  assert(e->schedule->type() == "monthly");

}

void change_union_member_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bill", "Home", 1500, &db);
  t.execute();

  ChangeUnionMember cut(t.empId, 99.42, &db);
  cut.execute();

  Employee* e = db.getEmployee(t.empId);

  assert(e->affiliation->getDues() == 99.42);

  Employee* m = db.getUnionMember(cut.memberId);
  assert(e == m);
}

void change_unaffiliated_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bill", "Home", 1500, &db);
  t.execute();

  ChangeUnionMember cut(t.empId, 99.42, &db);
  cut.execute();

  Employee* e = db.getEmployee(t.empId);

  int memberId = e->memberId;

  ChangeUnaffiliated cuat(e->empId, &db);
  cuat.execute();

  assert(e->affiliation->getDues() == 0);
  assert(db.getUnionMember(memberId) == NULL);
}

void delete_employee_test() {
  MemoryDB db;
  AddCommissionedEmployee t("Bill", "Home", 250, 3, &db);
  t.execute();

  Employee* e = db.getEmployee(t.empId);
  assert(e != NULL);

  DeleteEmployee dt(t.empId, &db);
  dt.execute();

  assert(db.getEmployee(t.empId) == NULL);
}

void add_sales_receipt_test() {
  MemoryDB db;
  AddCommissionedEmployee t("John", "Home", 1500, 2.5, &db);
  t.execute();

  date day(2005, 3, 30);
  AddSalesReceipt srt(t.empId, day, 500, &db);
  srt.execute();

  Employee* e = db.getEmployee(t.empId);
  assert(e != NULL);

  CommissionedClassification* pc = static_cast<CommissionedClassification*>(e->classification);
  vector<SalesReceipt*>* srs = pc->getSalesReceipts();
  assert(srs->size() > 0);
  assert(srs->front()->amount == 500);
  assert(srs->front()->day == date(2005,3,30));
}

void add_time_card_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bill", "Home", 15.25, &db);
  t.execute();

  AddTimeCard tct(t.empId, date(2005, 7, 31), 8.0, &db);
  tct.execute();

  Employee* e = db.getEmployee(t.empId);
  TimeCard* tc = (static_cast<HourlyClassification*>
    (e->classification))->getTimeCard(date(2005, 7, 31));
  assert(tc != NULL);
  assert(tc->hours == 8.0);
  assert(tc->day == date(2005, 7, 31));
}

void add_service_charge_test() {
  MemoryDB db;
  AddHourlyEmployee t("Bill", "Home", 15.25, &db);
  t.execute();

  Employee* e = db.getEmployee(t.empId);

  ChangeUnionMember cut(t.empId, 10.0, &db);
  cut.execute();

  AddServiceCharge sct(cut.memberId, date(2005, 8, 8), 12.95, &db);
  sct.execute();

  ServiceCharge* sc = static_cast<UnionAffiliation*>(e->affiliation)
    ->getServiceCharge(date(2005, 8, 8));
  assert(sc != NULL);
  assert(sc->charge == 12.95);
  assert(sc->day == date(2005, 8, 8));
}

class MockAddEmployeeView : public AddEmployeeView
{
};

void add_employee_presenter_test() {
  MemoryDB db;
  AddEmployeePresenter presenter(new MockAddEmployeeView(),
                               new TransactionContainer(),
                               &db);

  assert(not presenter.hasAllInformationCollected());
  presenter.setEmpId(1);
  assert(not presenter.hasAllInformationCollected());
  presenter.setName("Bill");
  assert(not presenter.hasAllInformationCollected());
  presenter.setAddress("123_abc");
  assert(not presenter.hasAllInformationCollected());
  presenter.setHourly(true);
  assert(not presenter.hasAllInformationCollected());
  presenter.setHourlyRate(1.23);
  assert(presenter.hasAllInformationCollected());

  presenter.setHourly(false);
  assert(not presenter.hasAllInformationCollected());
  presenter.setHasSalary(true);
  assert(not presenter.hasAllInformationCollected());
  presenter.setSalary(1234);
  assert(presenter.hasAllInformationCollected());

  presenter.setHasSalary(false);
  assert(not presenter.hasAllInformationCollected());
  presenter.setHasCommission(true);
  assert(not presenter.hasAllInformationCollected());
  presenter.setCommissionSalary(1234);
  assert(not presenter.hasAllInformationCollected());
  presenter.setCommission(12);
  assert(presenter.hasAllInformationCollected());

  MockAddEmployeeView* view = new MockAddEmployeeView();
  TransactionContainer* container = new TransactionContainer();
  AddEmployeePresenter present(view, container, &db);

  assert(not view->submit_enabled);
  present.setEmpId(1);
  assert(not view->submit_enabled);
  present.setName("Bill");
  assert(not view->submit_enabled);
  present.setAddress("123 abc");
  assert(not view->submit_enabled);
  present.setHourly(true);
  assert(not view->submit_enabled);
  present.setHourlyRate(1.23);
  assert(view->submit_enabled);
  present.setHourly(false);
  assert(not view->submit_enabled);
}

void payday_test() {
  MemoryDB db;

  {
    // it should pay a single salaried employee
    AddSalariedEmployee t("Bill", "Home", 1000.0, &db);
    t.execute();

    date pay_date = date(2001, 11, 30);
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->grossPay == 1000.0);
    assert(pc->disposition == "Hold");
    assert(pc->deductions == 0);
    assert(pc->netPay == 1000.0);
  }

  {
    // it should not pay a single salaried employee on wrong date
    AddSalariedEmployee t("Bill", "Home", 1000.0, &db);
    t.execute();

    date pay_date = date(2001, 11, 29);
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc == NULL);
  }

  {
    // it should pay 0 to a single hourly employee with no time cards
    AddHourlyEmployee t("Bob", "Home", 15.25, &db);
    t.execute();

    date pay_date = date(2001, 11, 9);
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->grossPay == 0);
    assert(pc->disposition == "Hold");
    assert(pc->deductions == 0);
    assert(pc->netPay == 0);
  }

  {
    // it should pay a single hourly employee with one time card
    AddHourlyEmployee t("Bob", "Home", 15.25, &db);
    t.execute();

    date pay_date = date(2001, 11, 9);
    AddTimeCard tc(t.empId, pay_date, 2.0, &db);
    tc.execute();
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->grossPay == 30.5);
    assert(pc->disposition == "Hold");
    assert(pc->deductions == 0);
    assert(pc->netPay == 30.5);
  }

  {
    // it should pay for over time
    AddHourlyEmployee t("Bob", "Home", 15.25, &db);
    t.execute();

    date pay_date = date(2001, 11, 9);
    AddTimeCard tc(t.empId, pay_date, 9.0, &db);
    tc.execute();
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->grossPay == (8+1.5) * 15.25);
    assert(pc->disposition == "Hold");
    assert(pc->deductions == 0);
    assert(pc->netPay == (8+1.5) * 15.25);
  }

  {
    // it should not pay hourly employee on wrong date
    AddHourlyEmployee t("Bob", "Home", 15.25, &db);
    t.execute();

    date pay_date = date(2001, 11, 8);
    AddTimeCard tc(t.empId, pay_date, 9.0, &db);
    tc.execute();
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc == NULL);
  }

  {
    // it should pay hourly employee two time cards
    AddHourlyEmployee t("Bob", "Home", 15.25, &db);
    t.execute();

    date pay_date = date(2001, 11, 9);
    AddTimeCard tc(t.empId, pay_date, 5.0, &db);
    tc.execute();
    AddTimeCard tc2(t.empId, pay_date - days(1), 6.0, &db);
    tc2.execute();
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->netPay == 11 * 15.25);
  }

  {
    // it should pay only one pay period
    AddHourlyEmployee t("Bob", "Home", 15.25, &db);
    t.execute();

    date pay_date = date(2001, 11, 9);
    AddTimeCard tc(t.empId, pay_date, 5.0, &db);
    tc.execute();
    AddTimeCard tc2(t.empId, pay_date - days(7), 6.0, &db);
    tc2.execute();
    AddTimeCard tc3(t.empId, pay_date + days(1), 6.0, &db);
    tc3.execute();
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->netPay == 5 * 15.25);
  }

  {
    // it should pay a commissioned employee with no commission
    AddCommissionedEmployee t("Bob", "Home", 1000.0, 2.5, &db);
    t.execute();

    date pay_date = date(2001, 11, 16);
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->netPay == 1000);
  }

  {
    // it should pay a commissioned employee with one commission only
    // for current period
    AddCommissionedEmployee t("Bob", "Home", 1000.0, 10.0, &db);
    t.execute();

    date pay_date = date(2001, 11, 16);
    AddSalesReceipt ast(t.empId, pay_date, 500, &db);
    ast.execute();
    AddSalesReceipt ast2(t.empId, pay_date + days(1), 500, &db);
    ast2.execute();
    AddSalesReceipt ast3(t.empId, pay_date - days(14), 500, &db);
    ast3.execute();

    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->payDate == pay_date);
    assert(pc->netPay == 1050);
  }

  {
    // it should not pay a commissioned employee on wrong date
    AddCommissionedEmployee t("Bob", "Home", 1000.0, 2.5, &db);
    t.execute();

    date pay_date = date(2001, 11, 23);
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc == NULL);
  }

  {
    // it should deduct service charges from member
    AddHourlyEmployee t("Bob", "Home", 15.24, &db);
    t.execute();
    ChangeUnionMember cmt(t.empId, 9.42, &db);
    cmt.execute();

    date pay_date = date(2001, 11, 9);
    AddServiceCharge sct(cmt.memberId, pay_date, 19.42, &db);
    sct.execute();

    AddTimeCard tct(t.empId, pay_date, 8.0, &db);
    tct.execute();
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->grossPay == 8*15.24);
    assert(pc->deductions == 9.42 + 19.42);
    assert(pc->netPay == (8*15.24)-(9.42 + 19.42));
  }

{
    // it should deduct service charges correct when spanning multiple
    // pay periods
    AddHourlyEmployee t("Bob", "Home", 15.24, &db);
    t.execute();
    ChangeUnionMember cmt(t.empId, 9.42, &db);
    cmt.execute();

    date pay_date = date(2001, 11, 9);
    AddServiceCharge sct(cmt.memberId, pay_date, 19.42, &db);
    sct.execute();
    AddServiceCharge sct2(cmt.memberId, pay_date - days(7), 19.42, &db);
    sct2.execute();
    AddServiceCharge sct3(cmt.memberId, pay_date + days(7), 19.42, &db);
    sct3.execute();

    AddTimeCard tct(t.empId, pay_date, 8.0, &db);
    tct.execute();
    Payday pt(pay_date, &db);
    pt.execute();

    Paycheck* pc = pt.getPaycheck(t.empId);
    assert(pc->grossPay == 8*15.24);
    assert(pc->deductions == 9.42 + 19.42);
    assert(pc->netPay == (8*15.24)-(9.42 + 19.42));
  }

}

int main()
{
  add_salaried_employee_test();
  add_commissioned_employee_test();
  add_hourly_employee_test();
  change_address_test();
  change_name_test();
  change_commissioned_test();
  change_hourly_test();
  change_salaried_test();
  change_union_member_test();
  change_unaffiliated_test();
  delete_employee_test();
  add_sales_receipt_test();
  add_time_card_test();
  add_service_charge_test();
  add_employee_presenter_test();
  payday_test();
  cout << "All Tests passed.\n";
  return 0;
}
