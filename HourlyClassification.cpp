#include "TimeCard.cpp"
#include <map>

using namespace boost::gregorian;
using namespace std;

class HourlyClassification : public PaymentClassification
{
public:
  double rate;
  map<date,TimeCard*> timecards;

  HourlyClassification(double rate) : rate(rate) {};

  TimeCard* getTimeCard(date day) {
    TimeCard* tc = timecards.find(day)->second;
    return tc;
  };

  void addTimeCard(TimeCard* tc) {
    timecards.insert(pair<date, TimeCard*>(tc->day, tc));
  }

  double calculatePay(Paycheck* pc) {
    double pay = 0;
    for(map<date, TimeCard*>::iterator it = timecards.begin();
        it != timecards.end();
        ++it) {
      if (it->first >= pc->startDate && it->first <= pc->payDate) {
        pay += it->second->hours * rate;
        if (it->second->hours > 8)
          pay += (it->second->hours - 8) / 2 * rate;
      }
    }
    return pay;
  }
};
