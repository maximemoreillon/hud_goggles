boolean nrfInit()
{
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"arg01"); // adress of the antenna
  Mirf.setTADDR((byte *)"sen01"); // address of the target
  Mirf.payload = 2;
  Mirf.channel = 125; // to change the channel if necessary
  Mirf.config();
  
  return true;
}


void sentryTX()
{  
  byte NRFTX[2] = {0,0};
  
  // Horizontal
  headingTX = headingDegMean - headingZeroTX;
  if(headingDegMean < headingZeroTX -180) headingTX += 360;
  if(headingDegMean > headingZeroTX + 180) headingTX -=360;
  headingTX = constrain(headingTX,-90,90);
  NRFTX[0] = map(headingTX,-90,90,0x00,0x7f);
  
  // Vertical
  pitchTX = constrain(pitchDegMean,-90,90);
  NRFTX[1] = map(pitchTX,-90,90,0x00,0x7f);
  
  // parameters
  NRFTX[0] |= (1<<7); // Activate absolute mode
  NRFTX[1] &=~ (1<<7); // No fire

  Mirf.send(NRFTX);
  while(Mirf.isSending());
}


void motionRX()
{
  if(Mirf.dataReady() && !Mirf.isSending())
  {
    byte NRFRX[1];
    
    Mirf.getData(NRFRX);
    
    if( ((NRFRX[0] & 0x70)>>4) == 1) // motion sensor unit 1
    {
      lastMotion1RX = millis();
      motion1Bat = map((NRFRX[0] & 0x0f),0x00,0x0f,LOWBAT,HIGHBAT);
      if(NRFRX[0] & (1<<7)) lastMotion1Det = millis();
      
    }
    else if( ((NRFRX[0] & 0x70)>>4) == 2) // motion sensor unit 2
    {
      lastMotion2RX = millis();
      motion2Bat = map((NRFRX[0] & 0x0f),0x00,0x0f,LOWBAT,HIGHBAT);
      if(NRFRX[0] & (1<<7)) lastMotion2Det = millis();
    }
  }
}

void rifleRX()
{
  if(!Mirf.isSending() && Mirf.dataReady())
  {
    byte NRFRX[2];
    lastRifleRX = millis();
    Mirf.getData(NRFRX);
    
    rifleBat = NRFRX[0] >> 5;
    rifleAmmo = NRFRX[0] & 0x1f; // 5 LSB bits
    riflePitch = map(NRFRX[1],0x00,0xff,-90,90);
  }
  
  
}

void trackerRX() // has to be updated
{
  if(!Mirf.isSending() && Mirf.dataReady())
  {
    byte NRFRX[3];
    lastTrackerRX = millis();
    Mirf.getData(NRFRX);
    
    if(NRFRX[0] & (1<<7)) trackerLock = true;
    else trackerLock = false;
    
    if(NRFRX[0] & (1<<6)) beaconLock = true;
    else beaconLock = false;
    
    Serial.println(NRFRX[0],BIN);
    
    if( (NRFRX[0] & 0x3f) != 0x00)
    {
      trackerData = true;
      if((NRFRX[0] & 0x3f) != 0x3f) targetDistance = map( (NRFRX[0] & 0x3f), 0x01,0x3e,0,999);
      else targetDistance = 1000;
    }
    else trackerData = false;
    
    if(NRFRX[1] & (1<<7)) beaconRX = true;
    else beaconRX = false;
    
    targetBearing = map( (NRFRX[1] & 0x7f), 0x00,0x7f,0,359);
    
    trackerBat = map((NRFRX[2]>>4),0x00,0x0f,LOWBAT_3V7,HIGHBAT_3V7);
    beaconBat = map((NRFRX[2]&0x0f),0x00,0x0f,LOWBAT_3V7,HIGHBAT_3V7);
  }
}


