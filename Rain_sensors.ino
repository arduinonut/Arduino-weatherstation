/*
  Include information about how the rain gauge operates
  // Count rain gauge bucket tips as they occur
  // Activated by the magnet and reed switch in the rain gauge, attached to input D2
*/

void rainIRQ()
{
  noInterrupts();
  delayMicroseconds(16000);
  delayMicroseconds(16000);
  delayMicroseconds(16000);
  delayMicroseconds(16000);       //Debounce the reed switch
  rain ++;                   //Each bucket tip is 0.2 mm of water
  interrupts();
  attachInterrupt(0, rainIRQ, FALLING);
}


