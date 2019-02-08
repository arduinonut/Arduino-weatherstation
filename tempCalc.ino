void tempCalc()
{
   sensors.requestTemperatures();
  temp=sensors.getTempCByIndex(0);
  if (lowtemp > temp)
  {
    lowtemp = temp;
  }
  if  (hightemp < temp)
  {
    hightemp = temp;
  }
}

