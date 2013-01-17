class Payday : public Transaction
{
  map<int,Paycheck*> paychecks;

public:
  date payDate;
  DB* db;

  Payday(date payDate, DB* db)
    : payDate(payDate), db(db) {};

  void execute() {
    vector<Employee*> employees = db->getEmployees();

    for(vector<Employee*>::iterator it = employees.begin();
        it != employees.end();
        ++it) {
      if ((*it)->isPayday(payDate)) {
        date startDate = (*it)->getPayPeriodStartDate(payDate);
        Paycheck* pc = new Paycheck(startDate, payDate);
        (*it)->payday(pc);
        paychecks.insert(pair<int,Paycheck*>((*it)->empId, pc));
      }
    }
  }

  Paycheck* getPaycheck(int empId) {
    if (paychecks.find(empId) != paychecks.end()) {
      return paychecks.find(empId)->second;
    } else {
      return NULL;
    }
  }
};
