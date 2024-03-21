#include "arduinoFFT.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 4); // RX, TX
 
#define SAMPLES 64                  // Must be a power of 2
#define SAMPLING_FREQUENCY 1000     // Hz, must be less than 10000 due to ADC

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

// Light control variables
int manualControl = 1;
float backLight = 0.0;
float topLight = 0.0;
float sideLight = 0.0;

int spotlightRED = 0;
int spotlightBLUE = 0;
int spotlightGREEN = 0;
int minBackLightIntensity = 0;
int minTopLightIntensity = 0;
int minSideLightIntensity = 0;
int blMaxResponseVal = 7;
int blMinResponseVal = 4;
int tlMaxResponseVal = 3;
int tlMinResponseVal = 1.5;
int slMaxResponseVal = 6;
int slMinResponseVal = 4;
int lightIntensityMultiplier = 21;

void handleIncomingMsg(String msg) {
    int val = msg.substring(3).toInt();
    int val2 = msg.substring(4).toInt();
    switch (msg.charAt(1)) {
        case '1':
            minTopLightIntensity = val;
            minBackLightIntensity = val;
            minSideLightIntensity = val;
            break;
        case '2':
            minTopLightIntensity = val;
            break;
        case '3':
            minBackLightIntensity = val;
            break;
        case '4':
            minSideLightIntensity = val;
            break;
        case '6':
            blMaxResponseVal = val;
            break;
        case '7':
            blMinResponseVal = val;
            break;
        case '8':
            tlMaxResponseVal = val;
            break;
        case '9':
            tlMinResponseVal = val;
            break;
        case 'A':
            if (msg.charAt(2) == '0') {
                slMaxResponseVal = val2;
            } else if (msg.charAt(2) == '1') {
                slMinResponseVal = val2;
            } else if (msg.charAt(2) == '2') {
                lightIntensityMultiplier = val2;
            } else if (msg.charAt(2) == '3') {
                manualControl = (val2 == 1) ? 1 : 2;
            } else if (msg.charAt(2) == '4') {
                spotlightRED = val2;
                analogWrite(3, spotlightRED);
            } else if (msg.charAt(2) == '5') {
                spotlightGREEN = val2;
                analogWrite(5, spotlightGREEN);
            } else if (msg.charAt(2) == '6') {
                spotlightBLUE = val2;
                analogWrite(6, spotlightBLUE);
            }
            break;
    }
}

void setup() {
    Serial.begin(2000000);
    mySerial.begin(9600);
    sampling_period_us = round(1000000 * (1.0 / 10000));
}

void loop() {
    if (manualControl == 2) {
        for (int i = 0; i < SAMPLES; i++) {
            microseconds = micros();
            vReal[i] = analogRead(A0);
            vImag[i] = 0;
            while (micros() < (microseconds + sampling_period_us)) {}
        }

        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

        backLight = ((vReal[7] + vReal[7] + vReal[8] + vReal[9] + vReal[10] + vReal[10] + vReal[11] + vReal[12] + vReal[13] + vReal[14] + vReal[15] + vReal[16] + vReal[17] + vReal[19] + vReal[21]) / 614);
        topLight = ((vReal[30] + vReal[31] + vReal[32] + vReal[34] + vReal[35] + vReal[36] + vReal[37] + vReal[38] + vReal[39] + vReal[40] + vReal[41] + vReal[42] + vReal[44] + vReal[46] + vReal[48]) / 614);
        sideLight = ((vReal[53] + vReal[54] + vReal[55] + vReal[56] + vReal[57] + vReal[58] + vReal[59] + vReal[60] + vReal[60] + vReal[61] + vReal[61] + vReal[62] + vReal[62] + vReal[63] + vReal[55]) / 614);

        if (backLight > blMaxResponseVal) {
            analogWrite(9, backLight * lightIntensityMultiplier * 1.6);
        } else if (backLight < blMinResponseVal) {
            analogWrite(9, minBackLightIntensity);
        } else {
            analogWrite(9, backLight * lightIntensityMultiplier);
        }

        if (topLight > tlMaxResponseVal) {
            analogWrite(10, topLight * lightIntensityMultiplier * 1.6);
        } else if (topLight < tlMinResponseVal) {
            analogWrite(10, minTopLightIntensity);
        } else {
            analogWrite(10, topLight * lightIntensityMultiplier);
        }

        if (sideLight > slMaxResponseVal) {
            analogWrite(11, sideLight * lightIntensityMultiplier * 1.6);
        } else if (sideLight < slMinResponseVal) {
            analogWrite(11, minSideLightIntensity);
        } else {
            analogWrite(11, sideLight * lightIntensityMultiplier);
        }
    } else {
        analogWrite(9, minBackLightIntensity);
        analogWrite(10, minTopLightIntensity);
        analogWrite(11, minSideLightIntensity);
    }

    if (mySerial.available()) {
        String incomingMsg = {mySerial.readStringUntil('\n')};
        if (incomingMsg.length() > 1) {
            handleIncomingMsg(incomingMsg);
        }
    }
}
