#pragma once

class TimeCard
{
public:
  double hours;
  boost::gregorian::date day;

  TimeCard(boost::gregorian::date day, double hours)
    : day(day), hours(hours) {};
};
