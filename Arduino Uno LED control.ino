#include "arduinoFFT.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 4); // RX, TX
 
#define SAMPLES 64             //Must be a power of 2
#define SAMPLING_FREQUENCY 1000 //Hz, must be less than 10000 due to ADC
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];


int manualControl  = 1;               //Gives manual control over the lights. (1 = MANUAL | 2 = AUTO/FFT).
float backLight = 0.0;
float topLight  = 0.0;
float sideLight = 0.0;

int   spotlightRED    = 0;           //Controls both spot lights with RGB values. (No individual control of lights yet implemented).
int   spotlightBLUE   = 0;
int   spotlightGREEN  = 0;
int   minBackLightIntensity = 0;
int   minTopLightIntensity  = 0;
int   minSideLightIntensity = 0;
int   blMaxResponceVal  = 7;         //bl,tl,sl stand for backLight, topLight and sideLight respectively.
int   blMinResponceVal  = 4;         //These values set the max and min values that the lights will react too.
int   tlMaxResponceVal  = 3;         //Everything in between of these two values WILL be displayed.
int   tlMinResponceVal  = 1.5;       //Set these to personal preference or what seems to work best.
int   slMaxResponceVal  = 6;         //
int   slMinResponceVal  = 4;         //
int   lightIntensityMultiplier = 21; //This allows to calibrate the lights. (Using the value calculated from the vReal FFT bin values.)
                                     //backLight max theoretical value is: 15, Top and Side lights have a maximum theoretical value is: 15
                                     //21 appears to achieve good results, however set this value to personal preferrance.



void handleIncomingMsg(String msg){
    if(msg.charAt(1) == '1'){                                                           //If-Else statements provided a slight improvement in performance in this particular task over switch statement.
      minTopLightIntensity   = msg.substring(3, msg.length()).toInt();                  //Taking the incomingMsg var, asking to split it from the 3rd char until the max length of the String.
      minBackLightIntensity  = minTopLightIntensity;                                    //The .toInt() must be present to allow the correct convertion from String to Int.
      minSideLightIntensity  = minTopLightIntensity; 
    }
    else if(msg.charAt(1) == '2'){
      minTopLightIntensity  = msg.substring(3, msg.length()).toInt();
    }
    else if(msg.charAt(1) == '3'){
      minBackLightIntensity = msg.substring(3, msg.length()).toInt();
    }
    else if(msg.charAt(1) == '4'){
      minSideLightIntensity = msg.substring(3, msg.length()).toInt();
    }
    else if(msg.charAt(1) == '6'){
      blMaxResponceVal      = msg.substring(3, msg.length()).toInt();
    }
    else if(msg.charAt(1) == '7'){
      blMinResponceVal      = msg.substring(3, msg.length()).toInt();
    }
    else if(msg.charAt(1) == '8'){
      tlMaxResponceVal      = msg.substring(3, msg.length()).toInt();
    }
    else if(msg.charAt(1) == '9'){
      tlMinResponceVal      = msg.substring(3, msg.length()).toInt();
    }
    else if(msg.charAt(1) == 'A' && msg.charAt(2) == '0'){                            //charAt() must be set to 2, in order to include values higher than '9'.
      slMaxResponceVal      = msg.substring(4, msg.length()).toInt();                 //For example: "V10:123", chart(2) will only see the '0'.
    }                                                                                 //Methodology: V1-9, afterwards, VA1-9, and so forth, VB1-9, VD1-9.
    else if(msg.charAt(1) == 'A' && msg.charAt(2) == '1'){
      slMinResponceVal      = msg.substring(4, msg.length()).toInt();
    }
    else if(msg.charAt(1) == 'A' && msg.charAt(2) == '2'){
      lightIntensityMultiplier = msg.substring(4, msg.length()).toInt();
      Serial.println(lightIntensityMultiplier);
      Serial.println(minTopLightIntensity);
    }
    else if(msg.charAt(1) == 'A' && msg.charAt(2) == '3'){                            //Gives manual control over the lights. (1 = MANUAL | 2 = AUTO/FFT).
      if(msg.substring(4, msg.length()).toInt() == 1){
        manualControl = 1;
      }
      else{
        manualControl = 2;
      }
    }
    else if(msg.charAt(1) == 'A' && msg.charAt(2) == '4'){
      spotlightRED    = msg.substring(4, msg.length()).toInt();
      analogWrite(3, spotlightRED);
    }
    else if(msg.charAt(1) == 'A' && msg.charAt(2) == '5'){
      spotlightGREEN  = msg.substring(4, msg.length()).toInt();
      analogWrite(5, spotlightGREEN);
    }
    else if(msg.charAt(1) == 'A' && msg.charAt(2) == '6'){
      spotlightBLUE   = msg.substring(4, msg.length()).toInt();
      analogWrite(6, spotlightBLUE);
    }

    
}


void setup() {
    Serial.begin(2000000);
    mySerial.begin(9600);
    sampling_period_us = round(1000000*(1.0/10000)); //By replacing SAMPLING_FREQUENCY by a custom number (Max of 10,000), has improved the visual smoothness of the lights.
                                                     //10,000 value, provides a nicer more snappy flashing of the lights. KEEP this change.
}

 
void loop() {
    /*SAMPLING*/
    if(manualControl == 2){
     for(int i=0; i<SAMPLES; i++)
     {
        microseconds = micros();                      //Overflows after around 70 minutes!
        vReal[i] = analogRead(A0);
        vImag[i] = 0;
        while(micros() < (microseconds + sampling_period_us)){
        }
     }
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    //for(int i=0; i<(SAMPLES/2); i++)
    //{ 
        //Serial.println((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        //Serial.println(vReal[i], 1);                                        //View only this line in serial plotter to visualize the bins
        //Serial.println((vReal[i]/614)*lightIntensityMultiplier*1.65, 4);
        backLight = (((vReal[7]+vReal[7]+vReal[8]+vReal[9]+vReal[10]+vReal[10]+vReal[11]+vReal[12]+vReal[13]+vReal[14]+vReal[15]+vReal[16]+vReal[17]+vReal[19]+vReal[21])/614));     // 15 bins
        topLight  = (((vReal[30]+vReal[31]+vReal[32]+vReal[34]+vReal[35]+vReal[36]+vReal[37]+vReal[38]+vReal[39]+vReal[40]+vReal[41]+vReal[42]+vReal[44]+vReal[46]+vReal[48])/614)); // 15 bins
        sideLight = (((vReal[53]+vReal[54]+vReal[55]+vReal[56]+vReal[57]+vReal[58]+vReal[59]+vReal[60]+vReal[60]+vReal[61]+vReal[61]+vReal[62]+vReal[62]+vReal[63]+vReal[55])/614)); // 15 bins

        
        //Back BLUE stage Lights.
        if(backLight > blMaxResponceVal){
          analogWrite(9, backLight*lightIntensityMultiplier*1.6);
        }
        else if (backLight < blMinResponceVal){
          analogWrite(9, minBackLightIntensity);
        }
        else{
          analogWrite(9, backLight*lightIntensityMultiplier);
        }

        //Top Multi colours stage Lights.
        if(topLight > tlMaxResponceVal){
          analogWrite(10, topLight*lightIntensityMultiplier*1.6);
        }
        else if (topLight < tlMinResponceVal){
          analogWrite(10, minTopLightIntensity);
        }
        else{
          analogWrite(10, topLight*lightIntensityMultiplier);
        }

        //Side Multi Colours stage Lights.
        if(sideLight > slMaxResponceVal){
          analogWrite(11, sideLight*lightIntensityMultiplier*1.6);
        }
        else if (sideLight < slMinResponceVal){
          analogWrite(11, minSideLightIntensity);
        }
        else{
          analogWrite(11, sideLight*lightIntensityMultiplier);
        }
    }
    else{
      analogWrite(9,  minBackLightIntensity);
      analogWrite(10, minTopLightIntensity);
      analogWrite(11, minSideLightIntensity);  
    }
                                                                        //The else statement and the last if statement are placed here due to improvement in performance of response time.
                                                                        //It appeared to have made a difference at which sequence they executed at.
    if (mySerial.available()) {
    String incomingMsg = {mySerial.readStringUntil('\n')};
    if(incomingMsg.length() > 1){
      handleIncomingMsg(incomingMsg);
    }
  }
    //}
 
    //delay(0);  //Repeat the process every second OR:
    //while(1);       //Run code once
}
