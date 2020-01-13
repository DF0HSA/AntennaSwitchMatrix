
/* DL6FCD/ K1AFR 01/2020
 * Pin 3  RF GND
 * Pin 4  RF HOT
 * Pin 5  RF Ant 1
 * Pin 6  RF Ant 2
 * Pin 7  RF Ant 3
 * Pin 8  RF Ant 4
 * Pin 9  RF Ant 5
 * Pin 10 RF Ant 6
 */
#include <FranzCommand.h>
#define ComInterface Serial
uint16_t u16_timeout_s=90;
 
FranzCommand Fcmd;   // The demo SerialCommand object

void setup()
{  
	setup_fkt();
  Serial.begin(115200); 
	Fcmd.addCommand("*idn?", idn);    
  Fcmd.addCommand("rf:switch", rf_switch);  

  Fcmd.addCommand("heartbeat:timeout", hb_timeout);
  Fcmd.addCommand("heartbeat:beat", hb_beat); 
  Fcmd.addCommand("heartbeat:elapsed", hb_elapsed);
 
	Fcmd.addCommand("basic.pinmode", setPinmodeX);  
	Fcmd.addCommand("basic.setpin", setPinX);  
	Fcmd.addCommand("basic.readanalog", readAnalogX);  
	Fcmd.addCommand("basic.readpin", getPinValueX); 
	Fcmd.addDefaultHandler(unrecognized);  
  Serial.println("Ready");
}

void loop()
{  
  char c=Serial.read(); 
  Fcmd.readSerial(&c);     // We don't do much, just process serial commands
  if (time_since_last_loop()/1000 > u16_timeout_s){
      for(int8_t x=3;x<=10;x++){
        pinMode(x, OUTPUT);
        digitalWrite(x, 1);
      }
  }  
}
