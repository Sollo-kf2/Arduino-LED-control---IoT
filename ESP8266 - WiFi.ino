#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = "AUTH CODE, OBTAINED FROM WITHIN BLYNK APP";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YOUR NETWORK NAME HERE";
char pass[] = "WIFI NETWORK PASSWORD HERE";
int pinValue1;
int pinValue2;
int pinValue3;
int pinValue4;
int pinValue6;
int pinValue7;
int pinValue8;
int pinValue9;
int pinValue10;
int pinValue11;
int pinValue12;
int pinValue13;
int pinValue14;
int pinValue15;
int pinValue16;
int pinValue17;//Un-used.


BLYNK_WRITE(V1)
{
  pinValue1 = param.asInt(); // assigning incoming value from pin V1 to a variable
  String toPrint = String("V1:")+String(pinValue1);
  Serial.println(toPrint);
}
BLYNK_WRITE(V2)
{
  pinValue2 = param.asInt(); // assigning incoming value from pin V2 to a variable
  String toPrint = String("V2:")+String(pinValue2);
  Serial.println(toPrint);
}

BLYNK_WRITE(V3)
{
  pinValue3 = param.asInt(); // assigning incoming value from pin V3 to a variable
  String toPrint = String("V3:")+String(pinValue3); 
  Serial.println(toPrint);
}

BLYNK_WRITE(V4)
{
  pinValue4 = param.asInt(); // assigning incoming value from pin V4 to a variable
  String toPrint = String("V4:")+String(pinValue4);
  Serial.println(toPrint);
}

BLYNK_WRITE(V6)
{
  pinValue6 = param.asInt(); // assigning incoming value from pin V6 to a variable
  String toPrint = String("V6:")+String(pinValue6);
  Serial.println(toPrint);
}
BLYNK_WRITE(V7)
{
  pinValue7 = param.asInt(); // assigning incoming value from pin V7 to a variable
  String toPrint = String("V7:")+String(pinValue7);
  Serial.println(toPrint);
  
}
BLYNK_WRITE(V8)
{
  pinValue8 = param.asInt(); // assigning incoming value from pin V8 to a variable
  String toPrint = String("V8:")+String(pinValue8);
  Serial.println(toPrint);
}
BLYNK_WRITE(V9)
{
  pinValue9 = param.asInt(); // assigning incoming value from pin V9 to a variable
  String toPrint = String("V9:")+String(pinValue9);
  Serial.println(toPrint);
}
BLYNK_WRITE(V10)
{
  pinValue10 = param.asInt(); // assigning incoming value from pin V10 to a variable
  String toPrint = String("VA0:")+String(pinValue10);
   Serial.println(toPrint);
}
BLYNK_WRITE(V11)
{
  pinValue11 = param.asInt(); // assigning incoming value from pin V11 to a variable
  String toPrint = String("VA1:")+String(pinValue11);
   Serial.println(toPrint);
}
BLYNK_WRITE(V12)
{
  pinValue12 = param.asInt(); // assigning incoming value from pin V12 to a variable
  String toPrint = String("VA2:")+String(pinValue12);
  Serial.println(toPrint);
}
BLYNK_WRITE(V13)
{
  pinValue13 = param.asInt(); // assigning incoming value from pin V13 to a variable
  String toPrint = String("VA3:")+String(pinValue13);
  Serial.println(toPrint);
}
BLYNK_WRITE(V14)
{
  pinValue14 = param.asInt(); // assigning incoming value from pin V14 to a variable
  String toPrint = String("VA4:")+String(pinValue14);
  Serial.println(toPrint);
}
BLYNK_WRITE(V15)
{
  pinValue15 = param.asInt(); // assigning incoming value from pin V15 to a variable
  String toPrint = String("VA5:")+String(pinValue15);
  Serial.println(toPrint);
}
BLYNK_WRITE(V16)
{
  pinValue16 = param.asInt(); // assigning incoming value from pin V16 to a variable
  String toPrint = String("VA6:")+String(pinValue16);
  Serial.println(toPrint);
}



void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
