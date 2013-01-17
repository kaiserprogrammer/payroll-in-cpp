class BiWeeklySchedule : public PaymentSchedule
{
public:
  std::string type() { return "biweekly"; };

  bool isPayday(boost::gregorian::date day) {
    return day.day_of_week() == 5 && (day.day_number() / 7) % 2 == 0;
  }

  date getPayPeriodStartDate(date day) {
    date mondayWeekBefore = day - days(7 + day.day_of_week()-1);
    return mondayWeekBefore;
  }
};
