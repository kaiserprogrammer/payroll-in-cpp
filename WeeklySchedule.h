class WeeklySchedule : public PaymentSchedule
{
public:
  std::string type() { return "weekly"; };

  bool isPayday(boost::gregorian::date day) {
    return day.day_of_week() == 5;
  }

  date getPayPeriodStartDate(date day) {
    return day - days(day.day_of_week() - 1);
  }
};
