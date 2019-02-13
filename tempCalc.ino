void tempCalc()
{
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  if (temp == -127.00)
  {
    lowtemp = lowtemp;
  }
  if (lowtemp > temp)
  {
    lowtemp = temp;
  }
  if  (hightemp < temp)
  {
    hightemp = temp;
  }
}

