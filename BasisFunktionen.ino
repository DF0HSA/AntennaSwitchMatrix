void setup_fkt()
{
  for(int8_t x=3;x<=10;x++)
  {
    pinMode(x, OUTPUT);
    digitalWrite(x, 1);
  }
}

void idn()
{
  ComInterface.println("RF Switch V 1.0");
}


static unsigned long last_loop;
uint32_t time_since_last_loop() {
  unsigned long current = millis();
  if (current < last_loop) {
    return 0xFFFFFFFF-(last_loop - current);
  }
  else {
    return current - last_loop;
  }
}

void hb_elapsed()
{
  Serial.println(time_since_last_loop());
}

void hb_timeout()
{
  u16_timeout_s=(unsigned char)parsedec2int();
  
  Serial.println("HB timeout set...done"); 
}

void hb_beat()
{
  last_loop=millis();
  Serial.println("HB beat...done"); 
}

void rf_switch()
{
  hb_beat();
  unsigned char on;
  unsigned char ant;
  on=(unsigned char)parsedec2int();
  ant=(unsigned char)parsedec2int();
  
  if (on==1){  //if RF is enabled
    digitalWrite(3, 0); //  RF GND conncted
    delay(100);
    digitalWrite(4, 0); // RF Hot connected
     for(int8_t x=5;x<=10;x++){ // disconnect all Antennas
        pinMode(x, OUTPUT);
        digitalWrite(x, 1);
     }
    delay(100);
    switch(ant) {
      case 1:
        digitalWrite(5, 0); // Ant 1 connected
        break;
      case 2:
        digitalWrite(6, 0); // Ant 2 connected
        break;
      case 3:
        digitalWrite(7, 0); // Ant 3 connected
        break;
      case 4:
        digitalWrite(8, 0); // Ant 4 connected
        break;
      case 5:
        digitalWrite(9, 0); // Ant 5 connected
        break;
      case 6:
        digitalWrite(10, 0); // Ant 6 connected
        break;
      default:
        break;
    }
    }
  else{ // if RF is disabled
    digitalWrite(4, 1); //  RF Hot disconnect
    delay(100);
    digitalWrite(3, 1); // RF GND disconnect
    for(int8_t x=5;x<=10;x++){ // disconnect all Antennas
      pinMode(x, OUTPUT);
      digitalWrite(x, 1);
    }
    }
  Serial.println("RFSwitching...done"); 
}
void setPinmodeX()
{
// first parameter pin number
// second parameter INPUT 0x0 OUTPUT 0x1 INPUT_PULLUP 0x2
unsigned char ch;
unsigned char mode;
ch=(unsigned char)parsedec2int();
mode=(unsigned char)parsedec2int();
pinMode(ch, mode);
}

void setPinX()
{
unsigned char ch;
unsigned char mode;
ch=(unsigned char)parsedec2int();
mode=(unsigned char)parsedec2int();
digitalWrite(ch, mode);
Serial.println("SetPinDone"); 
}
char getPinX()
{
unsigned char ch;
ch=(unsigned char)parsedec2int();
ch=digitalRead(ch);
return ch;
}

unsigned int getADCvalue()
{
unsigned char ch;
unsigned int val;
ch=(unsigned char)parsedec2int();
val=analogRead(ch);
return val;
}

int parsedec2int(){
int ch;  
char *arg; 
arg = Fcmd.next(); 
  if (arg != NULL) 
  {
    ch=atoi(arg);   
    return ch;
  }
}

 int parsehex2int(){
int ch;  
char *arg; 
  arg = Fcmd.next(); 
  if (arg != NULL) 
  {
    sscanf(arg, "%x", &ch);
    return ch;
  }
}

float parse2float(){
float res;  
char *arg; 
  arg = Fcmd.next(); 
  if (arg != NULL) 
  {
    res=atof(arg);
    return res;
  }
}


void unrecognized(){ComInterface.println("Error: unkonwn command");}

void readAnalogX()
{
  unsigned int val;
  val=getADCvalue();
  ComInterface.println(val);
}

void getPinValueX()
{
  unsigned char val;
  val=getPinX();
  ComInterface.println(val);
}
