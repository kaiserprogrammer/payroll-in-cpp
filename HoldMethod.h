class HoldMethod : public PaymentMethod
{
public:
  std::string type() { return "hold"; }
  std::string disposition() { return "Hold"; }
  void pay(Paycheck* pc) {

  };
};
