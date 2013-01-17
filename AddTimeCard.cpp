#include "TimeCard.cpp"

using namespace boost::gregorian;

class AddTimeCard : public Transaction
{
public:
  int empId;
  date day;
  double hours;
  DB* db;

  AddTimeCard(int empId, date day, double hours, DB* db)
    : empId(empId), day(day), hours(hours), db(db) {};

  void execute() {
    Employee* e = db->getEmployee(empId);
    TimeCard* tc = new TimeCard(day, hours);
    static_cast<HourlyClassification*>(e->classification)->addTimeCard(tc);
  };
};
