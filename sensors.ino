boolean mpuInit()
{
  boolean out;
  accelgyro.initialize();
  if(accelgyro.testConnection()) out = true;
  else out = false;
  return out;
}

boolean hmcInit()
{
  boolean out;
  compass = HMC5883L();
  
  //return out;
  int scaleError = 0, measurementError = 0;
  scaleError = compass.SetScale(8.1); // Set the scale of the compass.
  measurementError = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  
  if(scaleError == 512 && measurementError == 512) out = true;
  else out = false;
  return out;
}

void mpuRead()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  pitchRad = -atan2(az,ay);
  rollRad = atan2(ax,ay); // check this!
  
  // Computing average
  static int pitchDeg1, pitchDeg2, pitchDeg3, pitchDeg4, pitchDeg5;
  
  pitchDeg5 = pitchDeg4;
  pitchDeg4 = pitchDeg3;
  pitchDeg3 = pitchDeg2;
  pitchDeg2 = pitchDeg1;
  pitchDeg1 = pitchRad*180.00/M_PI; // conversion to degrees
  
  pitchDegMean = (pitchDeg1 + pitchDeg2 + pitchDeg3 + pitchDeg4 + pitchDeg5)/5;
}

void hmcRead()
{
  MagnetometerScaled mag = compass.ReadScaledAxis();
  
  // compensation
  float xc = mag.XAxis * cos(rollRad) - 0.8 * mag.YAxis * sin(rollRad);
  float zc = mag.ZAxis * cos(pitchRad) + 0.6 * mag.YAxis * sin(pitchRad); // perfect pitch compensation
  
  // averaging disabled
  
  headingDegMean = atan2(xc,zc)*180.00/PI; // conversion to degrees
  headingDegMean += 180+28; // offset
  
  // range adjustement
  if(headingDegMean < 0) headingDegMean += 360;
  if(headingDegMean >= 360) headingDegMean -= 360;
}

void batRead()
{
  bat = map(analogRead(batPin),0,486,0,7950);
}
