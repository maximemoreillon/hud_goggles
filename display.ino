#define middleX 14
#define middleY 8

void displayIntro(byte error)
{
  osdWriteString("HUD Goggles v12",2,2,0,0);
  osdWriteString("M. Moreillon",2,3,0,0);
  
  delay(500);
  
  osdWriteString("DISPLAY: ",2,5,0,0);
  if(error &= (1<<0)) osdWriteString("ERROR",18,5,0,0);
  else osdWriteString("OK",18,5,0,0);
  
  delay(200);
  
  osdWriteString("ACCELEROMETER: ",2,6,0,0);
  if(error &= (1<<1)) osdWriteString("ERROR",18,6,0,0);
  else osdWriteString("OK",18,6,0,0);
  
  delay(200);
  
  osdWriteString("MAGNETOMETER: ",2,7,0,0);
  if(error &= (1<<2)) osdWriteString("ERROR",18,7,0,0);
  else osdWriteString("OK",18,7,0,0);
  
  delay(200);
  
  osdWriteString("WIRELESS: ",2,8,0,0);
  if(error &= (1<<3)) osdWriteString("ERROR",18,8,0,0);
  else osdWriteString("OK",18,8,0,0);
  
  delay(200);
  
  if(error) osdWriteString("SYSTEM ERROR",2,10,1,0);
  else osdWriteString("ALL SYSTEMS READY",2,10,1,0);
  
  delay(1000);
}


void displayHeading()
{
  int fovH = 50;
  int angStep = 15;
  int startX = middleX - 8;
  int endX = middleX + 8;
  
  for(int i=startX; i<=endX; i++)
  {
    boolean match = false;
    int matchAngle;
    char* dispChar;
    for(int j=headingDegMean-360; j<= headingDegMean+360; j+=angStep)
    {
      if(i == map(j,fovH/2,-fovH/2,startX,endX))
      {
        match = true;
        matchAngle = j;
      }
    }
    if(match)
    {
      if(matchAngle == headingDegMean+0) dispChar="N";
      
      else if(matchAngle == headingDegMean+45) dispChar="I";
      else if(matchAngle == headingDegMean+90) dispChar="W";
      else if(matchAngle == headingDegMean+135) dispChar="I";
      else if(matchAngle == headingDegMean+180) dispChar="S";
      else if(matchAngle == headingDegMean+225) dispChar="I";
      else if(matchAngle == headingDegMean+270) dispChar="E";
      else if(matchAngle == headingDegMean+315) dispChar="I";
      else if(matchAngle == headingDegMean+360) dispChar="N";
      
      else if(matchAngle == headingDegMean-45) dispChar="I";
      else if(matchAngle == headingDegMean-90) dispChar="E";
      else if(matchAngle == headingDegMean-135) dispChar="I";
      else if(matchAngle == headingDegMean-180) dispChar="S";
      else if(matchAngle == headingDegMean-225) dispChar="I";
      else if(matchAngle == headingDegMean-270) dispChar="W";
      else if(matchAngle == headingDegMean-315) dispChar="I";
      else if(matchAngle == headingDegMean-360) dispChar="N";

      else dispChar="l";osdWriteString("l",i,1,0,0);
    }
    else dispChar=" ";
    osdWriteString(dispChar,i,1,0,0);
    osdWriteChar(0xED,startX-1,1,0,0);
    osdWriteChar(0xF3,endX+1,1,0,0);
    osdWriteChar(0x3A,middleX,0,0,0);
  }
}

void displayPitch()
{
  int fovV = 30;
  int angStep = 5;
  int startY = 3;
  int endY = 13;
  
  for(int i=startY; i<=endY; i++)
  {
    boolean match = false;
    int matchAngle;
    char* dispChar;
    for(int j=pitchDegMean-90; j<= pitchDegMean+90; j+=angStep)
    {
      if(i == map(j,-fovV/2,fovV/2,startY,endY))
      {
        match = true;
        matchAngle = j;
      }
    }
    if(match)
    {
      if(matchAngle ==pitchDegMean) dispChar=" 0 ";
      else if(matchAngle == pitchDegMean+15) dispChar="-15";
      else if(matchAngle == pitchDegMean+30) dispChar="-30";
      else if(matchAngle == pitchDegMean+45) dispChar="-45";
      else if(matchAngle == pitchDegMean+60) dispChar="-60";
      else if(matchAngle == pitchDegMean-15) dispChar=" 15";
      else if(matchAngle == pitchDegMean-30) dispChar=" 30";
      else if(matchAngle == pitchDegMean-45) dispChar=" 45";
      else if(matchAngle == pitchDegMean-60) dispChar=" 60";
      else dispChar=" - ";
    }
    else dispChar="   ";
    
    osdWriteString(dispChar,1,i,0,0);
    osdWriteString(dispChar,26,i,0,0);
    osdWriteChar(0x4a,4,middleY,0,0); // draw cursor (<)
    osdWriteChar(0x4b,25,middleY,0,0); // draw cursor (>)
  }
}


void displayBattery_down()
{
  osdWriteChar(constrain(map(bat,LOWBAT,HIGHBAT,0xf2,0xee),0xee,0xf2),middleX,15,0,0);
  osdWriteChar(0xed,middleX-1,15,0,0);
  osdWriteChar(0xf3,middleX+1,15,0,0);
}

void displayBattery_down_long()
{
  osdWriteChar(0xed,middleX-2,15,0,0); // [
  osdWriteChar(constrain(map(bat,LOWBAT,LOWBAT+(HIGHBAT-LOWBAT)/3,0xf2,0xee),0xee,0xf2),middleX-1,15,0,0);
  osdWriteChar(constrain(map(bat,LOWBAT+(HIGHBAT-LOWBAT)/3,LOWBAT+2*(HIGHBAT-LOWBAT)/3,0xf2,0xee),0xee,0xf2),middleX,15,0,0);
  osdWriteChar(constrain(map(bat,LOWBAT+2*(HIGHBAT-LOWBAT)/3,HIGHBAT,0xf2,0xee),0xee,0xf2),middleX+1,15,0,0);
  osdWriteChar(0xf3,middleX+2,15,0,0); // ]
}

void displayBattery_corner()
{
  osdWriteChar(0xed,25,1,0,0); // [
  osdWriteChar(constrain(map(bat,LOWBAT,LOWBAT+(HIGHBAT-LOWBAT)/2,0xf2,0xee),0xee,0xf2),26,1,0,0);
  osdWriteChar(constrain(map(bat,LOWBAT+(HIGHBAT-LOWBAT)/2,HIGHBAT,0xf2,0xee),0xee,0xf2),27,1,0,0);
  osdWriteChar(0xf3,28,1,0,0); // ]
}

void displayCrosshair()
{
  static int lastcrosshairX, lastcrosshairY;
  int crosshairX = map(-gy,-20000,20000,2,28);
  int crosshairY = map(-gx,-15000,15000,1,14);
  
  // refresh upon change
  if(crosshairX!=lastcrosshairX || crosshairY != lastcrosshairY)
  {
    // clear previous crosshair
    osdWriteChar(0x00,lastcrosshairX,lastcrosshairY-1,0,0);
    osdWriteChar(0x00,lastcrosshairX,lastcrosshairY+1,0,0);
    osdWriteChar(0x00,lastcrosshairX-1,lastcrosshairY,0,0);
    osdWriteChar(0x00,lastcrosshairX+1,lastcrosshairY,0,0);
    
    // draw new crosshair
    osdWriteChar(0x30,crosshairX,crosshairY-1,0,0);
    osdWriteChar(0x30,crosshairX,crosshairY+1,0,0);
    osdWriteChar(0x49,crosshairX-1,crosshairY,0,0);
    osdWriteChar(0x49,crosshairX+1,crosshairY,0,0);
    
    // new value attribution
    lastcrosshairX = crosshairX;
    lastcrosshairY = crosshairY;
  }
}

void displayTarget()
{
  int fovH = 40;
  int fovV = 30;
  int startX = 6;
  int endX = 23;
  int startY = 3;
  int endY = 12;
  
  int infoY = 15;
  int trackerInfoX = 2;
  int beaconInfoX = 18;
  
  static int lastTargetX, lastTargetY, lastTargetDistance;
  static boolean tracking;
  
  // General infos
  
  // Tracker
  
  osdWriteString("T",trackerInfoX,infoY,0,0);
  
  // bat 
  osdWriteChar(0xed,trackerInfoX+1,infoY,0,0); // [
  osdWriteChar(constrain(map(trackerBat,LOWBAT_3V7,HIGHBAT_3V7,0xf2,0xee),0xee,0xf2),trackerInfoX+2,infoY,0,0); // battery
  osdWriteChar(0xf3,trackerInfoX+3,infoY,0,0); // ]
  
  // RX
  if(millis()-lastTrackerRX < RX_TIMEOUT_TRACKER) osdWriteChar(0xfa,trackerInfoX+4,infoY,0,0);
  else osdWriteString(" ",trackerInfoX+4,infoY,0,0);
  
  if(trackerLock) osdWriteString("GPS",trackerInfoX+6,infoY,0,0);
  else osdWriteString("   ",trackerInfoX+6,infoY,0,0);
  

  // Beacon
  osdWriteString("B",beaconInfoX,infoY,0,0);
  
  // bat
  osdWriteChar(0xed,beaconInfoX+1,infoY,0,0); // [
  osdWriteChar(constrain(map(beaconBat,LOWBAT_3V7,HIGHBAT_3V7,0xf2,0xee),0xee,0xf2),beaconInfoX+2,infoY,0,0); // battery
  osdWriteChar(0xf3,beaconInfoX+3,infoY,0,0); // ]
  
  // RX 
  if(beaconRX) osdWriteChar(0xfa,beaconInfoX+4,infoY,0,0);
  else osdWriteString(" ",beaconInfoX+4,infoY,0,0);
  
  // GPS
  if(beaconLock) osdWriteString("GPS",beaconInfoX+6,infoY,0,0);
  else osdWriteString("   ",beaconInfoX+6,infoY,0,0);
  
  
  
  // displayMarker
  if((millis() - lastTrackerRX < RX_TIMEOUT_TRACKER) && trackerData) // display target when not timed out and data available
  {
    if(!tracking) // erease "NO SIGNAL"
    {
      osdWriteString("         ",10,middleY,0,0);
      tracking = true;
    }
    
    // adjustement because of 0 - 360 jumps
    int headingTargetMode = headingDegMean;
    
    if(targetBearing - fovH/2 < 0 && headingTargetMode > 360-fovH/2) headingTargetMode -= 360;
    if(targetBearing + fovH/2 > 360-fovH/2 && headingTargetMode < -fovH/2) headingTargetMode += 360;
    
    // computing position on screen
    int targetX = map(targetBearing, headingTargetMode-fovH/2,headingTargetMode+fovH/2,startX,endX);
    int targetY = map(0, pitchDegMean-fovV/2,pitchDegMean+fovV/2,endY, startY);
  
    if(lastTargetX != targetX || lastTargetY != targetY || lastTargetDistance != targetDistance) // remove previous display
    {
      if(lastTargetX >= startX && lastTargetX <= endX && lastTargetY >= startY && lastTargetY <= endY) // clear only if in field
      {
        osdWriteString("   ",lastTargetX-1,lastTargetY-1,0,0); // clear
        osdWriteString("   ",lastTargetX-1,lastTargetY,0,0); // clear
        osdWriteString("   ",lastTargetX-1,lastTargetY+1,0,0); // clear
      }
      
      if(targetX >= startX && targetX <= endX && targetY >= startY && targetY <= endY) // display if in field of view
      {
        char distBuf[5];
        itoa(targetDistance,distBuf,10);
        osdWriteString("TGT",targetX-1,targetY-1,0,0);
        osdWriteString("> <",targetX-1,targetY,0,0);
        if(targetDistance == 1000) osdWriteString(">1k",targetX-1,targetY+1,0,0);
        else osdWriteString(distBuf,targetX-1,targetY+1,0,0);
      }
      else
      {
        // could add arrows here maybe
      }
      // updating last variables
      lastTargetX = targetX;
      lastTargetY = targetY;
      lastTargetDistance = targetDistance;
    }
  }
  else // display tiemout
  {
    if(tracking) // erase data
    {
      tracking = false;
      osdWriteString("   ",lastTargetX-1,lastTargetY-1,0,0); // clear
      osdWriteString("   ",lastTargetX-1,lastTargetY,0,0); // clear
      osdWriteString("   ",lastTargetX-1,lastTargetY+1,0,0); // clear
    }
    
    if(millis() - lastTrackerRX >= RX_TIMEOUT_TRACKER) osdWriteString("NO SIGNAL",10,middleY,0,0);
    else if(!trackerData) osdWriteString(" NO DATA ",10,middleY,0,0);
  }
}

void displaySentry()
{
  int startX =  6;
  int endX = 24;
  int startY = 3;
  int endY = 13;

  // Sentry limits
  for(int i = startX; i<=endX; i++) // horizontal
  {
    if(i == map(headingTX,-90,90,startX,endX)) osdWriteChar(0xff,i,1,0,0);
    else osdWriteChar(0x30,i,1,0,0); 
  }
  
  for(int i = startY; i<=endY; i++) // vertical
  {
    if(i == map(pitchTX,90,-90,startY,endY)) osdWriteChar(0xff,1,i,0,0);
    else osdWriteChar(0x49,1,i,0,0); 
  }
  
  // Crosshair
  osdWriteChar(0x30,middleX,middleY-1,0,0);
  osdWriteChar(0x30,middleX,middleY+1,0,0);
  osdWriteChar(0x49,middleX-1,middleY,0,0);
  osdWriteChar(0x49,middleX+1,middleY,0,0);
}

void displayRifle()
{
  int startX =  6;
  int endX = 24;
  int startY = 2;
  int endY = 13;
  
  int lastAmmo;
  static boolean timedOut;
  char buf[3];
  
  // display bat
  osdWriteString("BATT",24,3,0,0);
  osdWriteChar(0xed,24,5,0,0);
  osdWriteChar(map(rifleBat,0x00,0x07, 0xf2, 0xee),25,5,0,0);
  osdWriteChar(0xf3,26,5,0,0);
  
  // display ammo
  osdWriteString("AMMO ",24,10,0,0);
  if(lastAmmo != rifleAmmo)
  {
    lastAmmo = rifleAmmo;
    osdWriteString("  ",25,12,0,0);
    itoa(rifleAmmo,buf,10);
    osdWriteString(buf,25,12,0,0);
  }
  
  // display pitch
  for(int i = startY; i<=endY; i++)
  {
    if(i == constrain(map(riflePitch,-45,45,endY,startY),startY,endY)) osdWriteChar(0xff,1,i,0,0);
    else osdWriteChar(0x49,1,i,0,0); 
  }
  
  // crosshair
  osdWriteChar(0x30,middleX,middleY+1,0,0);
  osdWriteChar(0x49,middleX-1,middleY,0,0);
  osdWriteChar(0x49,middleX+1,middleY,0,0);
  
  // display timeout
  if(millis() - lastRifleRX < RX_TIMEOUT_RIFLE)
  {
    if(timedOut)
    {
      osdWriteString("         ",10,4,0,0);
      timedOut = false;
    }
  }
  else
  {
    timedOut = true;
    osdWriteString("NO SIGNAL",10,4,0,0);
  }
}

void displayMotion()
{
  int startX1 = 4;
  int startX2 = 18;
  int startY = 15;
  
  // SENSOR 1
  osdWriteString("1",startX1,startY,0,0);

  // battery
  osdWriteChar(0xed,startX1+1,startY,0,0); // [
  osdWriteChar(constrain(map(motion1Bat,LOWBAT,HIGHBAT,0xf2,0xee),0xee,0xf2),startX1+2,startY,0,0); // battery
  osdWriteChar(0xf3,startX1+3,startY,0,0); // [
  
  // RX
  if(millis()-lastMotion1RX < RX_TIMEOUT_MOTION) osdWriteChar(0xfa,startX1+4,startY,0,0);
  else osdWriteChar(0x00,startX1+4,startY,0,0);
  // DET
  if(millis()-lastMotion1Det < MOTION_TIMEOUT)
  {
    osdWriteChar(0xf5,startX1+5,startY,1,0);
    osdWriteChar(0xf6,startX1+6,startY,1,0);
  }
  else osdWriteString("  ",startX1+5,startY,0,0);
  
  // SENSOR 2
  osdWriteString("2",startX2,startY,0,0);

  // battery
  osdWriteChar(0xed,startX2+1,startY,0,0); // [
  osdWriteChar(constrain(map(motion2Bat,LOWBAT,HIGHBAT,0xf2,0xee),0xee,0xf2),startX2+2,startY,0,0); // battery
  osdWriteChar(0xf3,startX2+3,startY,0,0); // [
  
  // RX
  if(millis()-lastMotion2RX < RX_TIMEOUT_MOTION) osdWriteChar(0xfa,startX2+4,startY,0,0);
  else osdWriteChar(0x00,startX2+4,startY,0,0);
  // DET
  if(millis()-lastMotion2Det < MOTION_TIMEOUT)
  {
    osdWriteChar(0xf5,startX2+5,startY,1,0);
    osdWriteChar(0xf6,startX2+6,startY,1,0);
  }
  else osdWriteString("  ",startX2+5,startY,0,0);
}



void displayInfo()
{
  char buf[5];
  static int lastHeading,lastPitch;
  osdWriteString("INFO",2,4,0,0);
  
  // battery
  osdWriteString("BATTERY",2,4,0,0);
  itoa(bat,buf,10);
  osdWriteString(buf,middleX,4,0,0);
  
  // heading
  osdWriteString("HEADING",2,5,0,0);
  if(lastHeading != headingDegMean)
  {
    lastHeading = headingDegMean;
    osdWriteString("    ",middleX,5,0,0);
    itoa(headingDegMean,buf,10);
    osdWriteString(buf,middleX,5,0,0);
  }
  
  // pitch
  osdWriteString("PITCH",2,6,0,0);
  if(lastPitch != pitchDegMean)
  {
    lastPitch = pitchDegMean;
    osdWriteString("    ",middleX,6,0,0);
    itoa(pitchDegMean,buf,10);
    osdWriteString(buf,middleX,6,0,0);
  }
  
}

void displayMessage()
{
  if(input == MAIN_IN) // Main input
  {
    if(mainDispMode == STANDARD)      osdWriteString(" STANDARD MODE",7,middleY,0,0);
    else if(mainDispMode == TRACKER)  osdWriteString("TARGET TRACKING",7,middleY,0,0);
    else if(mainDispMode == MOTION)   osdWriteString("MOTION SENSORS",7,middleY,0,0);
    else if(mainDispMode == INFO)     osdWriteString("   ARG INFO",7,middleY,0,0);
    else                              osdWriteString("    ERROR",7,middleY,0,0);
  }
  else // Auxiliary input
  {
    if(auxDispMode == OSDOFF)         osdWriteString("   OSD OFF",7,middleY,0,0);
    else if(auxDispMode == SENTRY)    osdWriteString(" SENTRY CONTROL",7,middleY,0,0);
    else if(auxDispMode == RIFLE)     osdWriteString("FIRING COMPUTER",7,middleY,0,0);
    else                              osdWriteString("    ERROR",7,middleY,0,0);
  }
}

