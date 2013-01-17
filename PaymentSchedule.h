using namespace boost::gregorian;

class PaymentSchedule
{
public:
  virtual std::string type() =0;
  virtual bool isPayday(date day) =0;
  virtual date getPayPeriodStartDate(date day) =0;
};
