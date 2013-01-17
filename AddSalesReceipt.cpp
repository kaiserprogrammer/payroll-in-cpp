#include "boost/date_time/gregorian/gregorian.hpp"
#include "SalesReceipt.cpp"

using namespace boost::gregorian;

class AddSalesReceipt : public Transaction
{
public:
  int empId;
  DB* db;
  double value;
  date day;
  AddSalesReceipt(int empId, date day, double value, DB* db)
    : empId(empId), day(day), value(value), db(db) {};

  void execute() {
    SalesReceipt* sale = new SalesReceipt(day, value);
    Employee* e = db->getEmployee(empId);
    static_cast<CommissionedClassification*>(e->classification)->addSalesReceipt(sale);
  }
};
