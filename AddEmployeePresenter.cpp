#include "AddEmployeeView.hpp"
#include "TransactionContainer.hpp"

class AddEmployeePresenter
{
  int empId = -1;
  string name = "";
  string address = "";

  bool hourly = false;
  double hourlyRate = -1;

  bool hasSalary = false;
  double salary = -1;

  bool hasCommission = false;
  double commissionSalary = -1;
  double commission = -1;

public:
  AddEmployeeView* view;
  TransactionContainer* container;
  DB* db;

  void setEmpId(int empId)
  {
    this->empId = empId;
    updateView();
  }

  void setName(string name)
  {
    this->name = name;
    updateView();
  }

  void setAddress(string address)
  {
    this->address = address;
    updateView();
  }

  void setHourly(bool hourly)
  {
    this->hourly = hourly;
    updateView();
  }

  void setHourlyRate(double hourlyRate)
  {
    this->hourlyRate = hourlyRate;
    updateView();
  }

  void setHasSalary(bool hasSalary)
  {
    this->hasSalary = hasSalary;
    updateView();
  }

  void setSalary(double salary)
  {
    this->salary = salary;
    updateView();
  }

  void setHasCommission(bool hasCommission)
  {
    this->hasCommission = hasCommission;
    updateView();
  }

  void setCommissionSalary(double commissionSalary)
  {
    this->commissionSalary = commissionSalary;
    updateView();
  }

  void setCommission(double commission)
  {
    this->commission = commission;
    updateView();
  }

  void updateView() {
    view->submit_enabled = hasAllInformationCollected();
  }

  AddEmployeePresenter(AddEmployeeView* view, TransactionContainer* container, DB* db)
    : view(view), container(container), db(db) {};

  bool hasAllInformationCollected() {
    return empId != -1 && name != "" && address != ""
      && ((hourly && hourlyRate != -1)
          || (hasSalary && salary != -1)
          || (hasCommission
              && commission != -1
              && commissionSalary != 1));
  }

};
