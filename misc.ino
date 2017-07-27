void switchRead() // between primary and auxiliary
{
  input = digitalRead(switchPin);
}


void buttonRead() // reading button to change dispMode
{
  static int buttonState, lastButtonState;
  static long lastDebounceTime; 

  // debounce
  int reading = digitalRead(buttonPin);
  if(reading != lastButtonState) lastDebounceTime = millis();

  if((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if(buttonState)
      {
        if(input == MAIN_IN) // on main input
        {
          mainDispMode ++;
          if(mainDispMode > MAIN_MODES-1) mainDispMode = 0;
        }
        else // on auxiliary input
        {
          auxDispMode ++;
          if(auxDispMode > AUX_MODES-1) auxDispMode = 0;
        }
      }
    }
  }
  lastButtonState = reading;
}
