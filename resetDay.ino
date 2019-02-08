//Reset all dailiy variables at midnight
void resetDay()
{
  weatherReport();
  rain = 0.00;
  dailyrainin = 0.00;
  lowtemp = 50;
  hightemp = 0;
  // winspeed = 0;
  // wind=0;
  //lowwind=50;
  //highwind=0;
}
