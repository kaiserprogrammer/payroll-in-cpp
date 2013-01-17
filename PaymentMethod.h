class PaymentMethod
{
public:
  virtual std::string type() =0;
  virtual std::string disposition() =0;
  virtual void pay(Paycheck* pc) =0;
};
