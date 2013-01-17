#include "SalesReceipt.cpp"

using namespace std;

class CommissionedClassification : public PaymentClassification
{
public:
  double salary;
  double commission;
  vector<SalesReceipt*> sales;

  CommissionedClassification(double salary, double commission) : salary(salary), commission(commission) {};

  vector<SalesReceipt*>* getSalesReceipts() {
    return &sales;
  }

  void addSalesReceipt(SalesReceipt* sale) {
    sales.push_back(sale);
  };

  double calculatePay(Paycheck* pc) {
    double pay = salary;
    for(vector<SalesReceipt*>::iterator it = sales.begin();
        it != sales.end();
        ++it) {
      if ((*it)->day >= pc->startDate &&
          (*it)->day <= pc->payDate) {
        pay += (*it)->amount * commission / 100;
      }
    }
    return pay;
  }
};
