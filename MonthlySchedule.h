#pragma once

class MonthlySchedule : public PaymentSchedule
{
public:
  std::string type() {
    return "monthly";
  }

  bool isPayday(boost::gregorian::date day) {
    return day == day.end_of_month();
  }

  date getPayPeriodStartDate(date day) {
    return day;
  }
};
