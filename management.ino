void sensorManagement()
{
  static long lastSensorTime;
  
  if(millis()-lastSensorTime > sensorPeriod)
  {
    lastSensorTime = millis();
    
    batRead();
    mpuRead();
    hmcRead();
  }
}

void displayManagement()
{
  static long lastDispTime;
  static boolean messageDisplayed;
  
  if(millis()-lastDispTime > dispPeriod)
  {
    lastDispTime = millis();
    
    if(millis()-messageStartTime < messageTime) // display message
    {
      displayMessage();
      messageDisplayed = true;
    }
    else
    {
      if(messageDisplayed) // remove message only once
      {
        osdClear();
        messageDisplayed = false;
      }
      if(input == MAIN_IN) // main input
      {
        if(mainDispMode == STANDARD) // standard mode
        {
          displayCrosshair();
          displayPitch();
          displayHeading();
          displayBattery_down_long();
        }
        else if(mainDispMode == TRACKER) // target tracking
        {
          displayTarget();
          displayHeading();
          displayPitch();
          displayBattery_down_long();
        }
        else if(mainDispMode == MOTION) // Motion detectors
        {
          displayMotion();
          displayCrosshair();
          displayPitch();
          displayHeading();
          displayBattery_down_long();
        }
        else if(mainDispMode == INFO) // Informations
        {
          displayInfo();
        }
      }
      else // auxiliary input
      {
        if(auxDispMode == OSDOFF)
        {
          // nothing displayed
        }
        else if(auxDispMode == SENTRY) // sentry control
        {
          displaySentry();
          displayBattery_down_long();
        }
        else if(auxDispMode == RIFLE) // Firing computer
        {
          displayRifle();
          displayBattery_down_long();
        }
      }
    }
  }
}



void wirelessManagement()
{
  static long lastTXTime, lastRXReqTime;
  
  // TX
  if(millis()-lastTXTime > TX_PERIOD)
  {
    lastTXTime = millis();
    
    if(input == MAIN_IN) // main input
    {
      // nothing for now
    }
    else // auxiliary input
    {
      if(auxDispMode == SENTRY) sentryTX();
    }
  }
  
  // RX
  if(millis()-lastRXReqTime > RX_PERIOD)
  {
    lastRXReqTime = millis();
    
    if(input == MAIN_IN) // main input
    {
      if(mainDispMode == TRACKER) trackerRX();
      else if(mainDispMode == MOTION) motionRX();
    }
    else // auxiliary input
    {
      if(auxDispMode == RIFLE) rifleRX();
    }
  }
  
}

void changeManagement()
{
  static int lastInput, lastMainDispMode, lastAuxDispMode;
  
  if(input != lastInput || lastMainDispMode != mainDispMode || lastAuxDispMode!= auxDispMode)
  {
    lastInput = input;
    lastMainDispMode = mainDispMode;
    lastAuxDispMode = auxDispMode;
    
    osdClear();
    messageStartTime = millis();
    
    lastTrackerRX = -RX_TIMEOUT_TRACKER;
    lastMotion1RX = -RX_TIMEOUT_MOTION;
    lastMotion2RX = -RX_TIMEOUT_MOTION;
    lastRifleRX = -RX_TIMEOUT_RIFLE;
    
    // Wirless parameters
    if(input == MAIN_IN) // on main input
    {
      digitalWrite(MAX7456CS,LOW); // enable device
      writeToMAX7456(VM0, PAL | SYNC_EXTERNAL | ENABLE | SYNC_VSYNC); // Original
      digitalWrite(MAX7456CS,HIGH); // disable device
  
      if(mainDispMode == TRACKER)
      {
        Mirf.setRADDR((byte *)"argtr");
        Mirf.payload = 3;
        Mirf.config();
      }
      else if(mainDispMode == MOTION)
      {
        Mirf.setRADDR((byte *)"msr01");
        Mirf.payload = 1;
        Mirf.config();
      }
      else
      {
        Mirf.setRADDR((byte *)"arg01");
        Mirf.payload = 2;
        Mirf.config();
      }
    }
    else // on auxiliary input
    {
      digitalWrite(MAX7456CS,LOW); // enable device
      writeToMAX7456(VM0, NTSC | SYNC_EXTERNAL | ENABLE | SYNC_VSYNC); // Altered
      digitalWrite(MAX7456CS,HIGH); // disable device
      
      if(auxDispMode == SENTRY)
      {
        headingZeroTX = headingDegMean; // zero sentry
        Mirf.payload = 2;
        Mirf.config();
      }
      else if(auxDispMode == RIFLE)
      {
        Mirf.setRADDR((byte *)"argfc");
        Mirf.payload = 2;
        Mirf.config();
      }
      else
      {
        Mirf.setRADDR((byte *)"arg01");
        Mirf.payload = 2;
        Mirf.config();
      }
    }
  }
  
  
}
