#pragma once

class Transaction
{
public:
  virtual void execute(void) =0;
};
