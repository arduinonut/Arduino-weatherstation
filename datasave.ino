void datasave()
{
  clock.getTime();
  File dataFile = SD.open("datalog.txt", FILE_WRITE);     // if the file is available, write to it:
  if (dataFile)
  {
    dataFile.print(clock.hour, DEC);
    dataFile.print(":");
    dataFile.print(clock.minute, DEC);
    dataFile.print(":");
    dataFile.print(clock.second, DEC);
    dataFile.print(",");
    dataFile.print(clock.month, DEC);
    dataFile.print("/");
    dataFile.print(clock.dayOfMonth, DEC);
    dataFile.print("/");
    dataFile.print(clock.year + 2000, DEC);
    dataFile.print(",");
    dataFile.print(dailyrainin);
    dataFile.print(",");
    dataFile.print(hightemp);
    dataFile.print(",");
    dataFile.println(lowtemp);
    dataFile.close();
    delay(1);
  }
  else {
    lcd.clear();
    lcd.println("FILE ERROR");
  }
}
