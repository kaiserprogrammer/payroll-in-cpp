class Affiliation
{
 public:
  virtual double getDues() =0;
  virtual double calculateDeductions(Paycheck* pc) =0;
};

class NoAffiliation : public Affiliation
{
  double getDues() { return 0; };
  double calculateDeductions(Paycheck* pc) { return 0; };
};
