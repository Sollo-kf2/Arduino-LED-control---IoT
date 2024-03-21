#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

char auth[] = "AUTH CODE, OBTAINED FROM WITHIN BLYNK APP";
char ssid[] = "YOUR NETWORK NAME HERE";
char pass[] = "WIFI NETWORK PASSWORD HERE";

int pinValues[17]; // Array to store pin values

// Function to handle incoming messages from Blynk
void handleBlynkMessage(int pin, int value) {
  String toPrint = "V" + String(pin) + ":" + String(value);
  Serial.println(toPrint);
}

// Blynk virtual pin handlers
BLYNK_WRITE(V1) { pinValues[1] = param.asInt(); handleBlynkMessage(1, pinValues[1]); }
BLYNK_WRITE(V2) { pinValues[2] = param.asInt(); handleBlynkMessage(2, pinValues[2]); }
BLYNK_WRITE(V3) { pinValues[3] = param.asInt(); handleBlynkMessage(3, pinValues[3]); }
BLYNK_WRITE(V4) { pinValues[4] = param.asInt(); handleBlynkMessage(4, pinValues[4]); }
BLYNK_WRITE(V6) { pinValues[6] = param.asInt(); handleBlynkMessage(6, pinValues[6]); }
BLYNK_WRITE(V7) { pinValues[7] = param.asInt(); handleBlynkMessage(7, pinValues[7]); }
BLYNK_WRITE(V8) { pinValues[8] = param.asInt(); handleBlynkMessage(8, pinValues[8]); }
BLYNK_WRITE(V9) { pinValues[9] = param.asInt(); handleBlynkMessage(9, pinValues[9]); }
BLYNK_WRITE(V10) { pinValues[10] = param.asInt(); handleBlynkMessage(10, pinValues[10]); }
BLYNK_WRITE(V11) { pinValues[11] = param.asInt(); handleBlynkMessage(11, pinValues[11]); }
BLYNK_WRITE(V12) { pinValues[12] = param.asInt(); handleBlynkMessage(12, pinValues[12]); }
BLYNK_WRITE(V13) { pinValues[13] = param.asInt(); handleBlynkMessage(13, pinValues[13]); }
BLYNK_WRITE(V14) { pinValues[14] = param.asInt(); handleBlynkMessage(14, pinValues[14]); }
BLYNK_WRITE(V15) { pinValues[15] = param.asInt(); handleBlynkMessage(15, pinValues[15]); }
BLYNK_WRITE(V16) { pinValues[16] = param.asInt(); handleBlynkMessage(16, pinValues[16]); }

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
