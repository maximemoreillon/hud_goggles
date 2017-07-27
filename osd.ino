boolean osdInit()
{
  pinMode(MAX7456CS,OUTPUT);
  digitalWrite(MAX7456CS,HIGH); // disable device
  
  digitalWrite(MAX7456CS,LOW); // enable device
  writeToMAX7456(VM0, RESET); // Reset the chip
  digitalWrite(MAX7456CS,HIGH); // disable device
  
  digitalWrite(MAX7456CS,LOW); // enable device
  writeToMAX7456(VM0, PAL | SYNC_EXTERNAL | ENABLE | SYNC_VSYNC); // Original
  // writeToMAX7456(VM0, NTSC | SYNC_EXTERNAL | ENABLE | SYNC_VSYNC); // Altered
  writeToMAX7456(VM1, BLINK_DUTY_50 | BLINK_TIME_3);
  digitalWrite(MAX7456CS,HIGH); // disable device
  
  return true;
}

void osdWriteChar(char c, byte x, byte y, boolean blinking, boolean inverting)
{
  unsigned int linePos;
  byte char_add_hi, char_add_lo, settings;
  
  linePos = y*30+x;
  char_add_hi = linePos >> 8;
  char_add_lo = linePos;
  
  // blinking and inverting parameters
  settings = 0x00;
  if(blinking) settings |= BLINK;
  if(inverting) settings |= INVERT;
  
  digitalWrite(MAX7456CS,LOW);
  
  
  writeToMAX7456(DMM,settings);
  writeToMAX7456(DMAH,char_add_hi);
  writeToMAX7456(DMAL,char_add_lo);
  writeToMAX7456(DMDI, c);
  digitalWrite(MAX7456CS,HIGH);
}

void osdWriteString(const char s[], byte x, byte y, boolean blinking, boolean inverting)
{
  unsigned int linePos;
  byte char_add_hi, char_add_lo, settings, count;
  
  linePos = y*30+x;
  char_add_hi = linePos >> 8;
  char_add_lo = linePos;
  
  // blinking and inverting parameters
  settings = AUTO_INCREMENT;
  if(blinking) settings |= BLINK;
  if(inverting) settings |= INVERT;
  
  count = 0;
  digitalWrite(MAX7456CS,LOW);
  writeToMAX7456(DMM,settings);
  writeToMAX7456(DMAH,char_add_hi);
  writeToMAX7456(DMAL,char_add_lo);
  while(s[count]!='\0') // write out full string
  {
    writeToMAX7456(DMDI,ASCIIToMAX7456(s[count]));
    count++;
  }
  writeToMAX7456(DMDI,ESCAPE_CHAR);
  digitalWrite(MAX7456CS,HIGH);
}

void writeToMAX7456(byte reg, byte val)
{
  SPI.transfer(reg);
  SPI.transfer(val);
}

byte readFromMAX7456(byte reg)
{
  byte out;
  SPI.transfer(reg);
  out = SPI.transfer(0x00);
  return out;
}

char ASCIIToMAX7456(char in)
{
  char out;
  
  if(in == ' ') out = 0x00;
  else if(in == '1') out = 0x01;
  else if(in == '2') out = 0x02;
  else if(in == '3') out = 0x03;
  else if(in == '4') out = 0x04;
  else if(in == '5') out = 0x05;
  else if(in == '6') out = 0x06;
  else if(in == '7') out = 0x07;
  else if(in == '8') out = 0x08;
  else if(in == '9') out = 0x09;
  else if(in == '0') out = 0x0A;
  else if(in == 'A') out = 0x0B;
  else if(in == 'B') out = 0x0C;
  else if(in == 'C') out = 0x0D;
  else if(in == 'D') out = 0x0E;
  else if(in == 'E') out = 0x0F;
  else if(in == 'F') out = 0x10;
  else if(in == 'G') out = 0x11;
  else if(in == 'H') out = 0x12;
  else if(in == 'I') out = 0x13;
  else if(in == 'J') out = 0x14;
  else if(in == 'K') out = 0x15;
  else if(in == 'L') out = 0x16;
  else if(in == 'M') out = 0x17;
  else if(in == 'N') out = 0x18;
  else if(in == 'O') out = 0x19;
  else if(in == 'P') out = 0x1A;
  else if(in == 'Q') out = 0x1B;
  else if(in == 'R') out = 0x1C;
  else if(in == 'S') out = 0x1D;
  else if(in == 'T') out = 0x1E;
  else if(in == 'U') out = 0x1F;
  else if(in == 'V') out = 0x20;
  else if(in == 'W') out = 0x21;
  else if(in == 'X') out = 0x22;
  else if(in == 'Y') out = 0x23;
  else if(in == 'Z') out = 0x24;
  else if(in == 'a') out = 0x25;
  else if(in == 'b') out = 0x26;
  else if(in == 'c') out = 0x27;
  else if(in == 'd') out = 0x28;
  else if(in == 'e') out = 0x29;
  else if(in == 'f') out = 0x2A;
  else if(in == 'g') out = 0x2B;
  else if(in == 'h') out = 0x2C;
  else if(in == 'i') out = 0x2D;
  else if(in == 'j') out = 0x2E;
  else if(in == 'k') out = 0x2F;
  else if(in == 'l') out = 0x30;
  else if(in == 'm') out = 0x31;
  else if(in == 'n') out = 0x32;
  else if(in == 'o') out = 0x33;
  else if(in == 'p') out = 0x34;
  else if(in == 'q') out = 0x35;
  else if(in == 'r') out = 0x36;
  else if(in == 's') out = 0x37;
  else if(in == 't') out = 0x38;
  else if(in == 'u') out = 0x39;
  else if(in == 'v') out = 0x3A;
  else if(in == 'w') out = 0x3B;
  else if(in == 'x') out = 0x3C;
  else if(in == 'y') out = 0x3D;
  else if(in == 'z') out = 0x3E;
  else if(in == '(') out = 0x3F;
  else if(in == ')') out = 0x40;
  else if(in == '.') out = 0x41;
  else if(in == '?') out = 0x42;
  else if(in == ';') out = 0x43;
  else if(in == ':') out = 0x44;
  else if(in == ',') out = 0x45;
  else if(in == '/') out = 0x47;
  else if(in == '-') out = 0x49;
  else if(in == '<') out = 0x4A;
  else if(in == '>') out = 0x4B;
  else out = 0x42; // default is a "?"
  
  return out;
}

/*
char* intToChar(int in)
{
  char out[10]; //char array of string
  itoa(in, out, 10);
  return out;
}
*/

void osdClear()
{
  for(int i=0; i<30; i++)
  {
    for(int j=0; j<16; j++)
    {
      osdWriteChar(0x00,i,j,0,0);
    }
  }
}


void videoMode()
{
  byte stat;
  digitalWrite(MAX7456CS,LOW);
  stat = readFromMAX7456(STATUS); // Access status register
  if(stat & (1<<0)) writeToMAX7456(VM0, PAL | SYNC_EXTERNAL | ENABLE | SYNC_VSYNC);
  else if(stat & (1<<1)) writeToMAX7456(VM0, NTSC | SYNC_EXTERNAL | ENABLE | SYNC_VSYNC);
  digitalWrite(MAX7456CS,HIGH);
}


void displayVideoMode() // remove this when done
{
  byte stat;
  digitalWrite(MAX7456CS,LOW);
  stat = readFromMAX7456(STATUS); // Access status register
  digitalWrite(MAX7456CS,HIGH);
  
  if(stat & (1<<0)) osdWriteString("PAL ",11,middleY-1,0,0);
  else              osdWriteString("    ",11,middleY-1,0,0);
  
  if(stat & (1<<1)) osdWriteString("NTSC",11,middleY,0,0);
  else              osdWriteString("    ",11,middleY,0,0);
  
  if(stat & (1<<2)) osdWriteString("LOS ",11,middleY+1,0,0);
  else              osdWriteString("    ",11,middleY+1,0,0);
}
