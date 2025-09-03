
#include <IBusBM.h>
#define rf 5
#define rb 6
#define lb 11
#define lf 10

int ch1 = 0;
int ch2 = 0;
int ch3 = 0;
int ch4 = 0;
int ch5 = 0;
int ch6 = 0;



int leftmspeed = 0;
int rightmspeed = 0;
int rightm;
int leftm;
int leftmspeedf;
int rightmspeedf;
int leftmspeed1 = 0;
int rightmspeed1= 0;

IBusBM ibus;


 

int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 

bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup()
{
  
  Serial.begin(115200);
  ibus.begin(Serial1);

  pinMode (rb , OUTPUT);
  pinMode (rf , OUTPUT);
  pinMode (lf , OUTPUT);
  pinMode (lb , OUTPUT);

  
  
}
 
void loop() {
 
  
 
 ch1 = readChannel (0 , -100 , 100 , 0);
 ch2 = readChannel (1 , -100 , 100 , 0);
 ch3 = readChannel (2 , 0 , 155 , 0);
 ch4 = readChannel (3 , -100 , 100 , 0);
 ch5 = readChannel (4 , -100 , 100 , 0);
 ch6 = readSwitch (5 , false);

 Serial.print ("        ch1 =");
 Serial.print (ch1);
Serial.print ("        ch2 =");
 Serial.print (ch2);
 Serial.print ("        ch3 =");
 Serial.print (ch3);
Serial.print ("        ch4 =");
 Serial.print (ch4);
Serial.print ("        ch5 =");
 Serial.print (ch5);
Serial.print ("        ch6 =");
 Serial.println (ch6);
 
 leftmspeed = ch3;
 rightmspeed = ch3;
 
 
 if (ch6)                          //spin mode
 {

  Serial.println("Spin mode");
  
                                       
  if (ch4>10){
    analogWrite (lf, leftmspeed);
    analogWrite (lb , 0);              // right spin
    analogWrite (rb,rightmspeed );
    analogWrite (rf , 0);
  }

  else if (ch4<-10) {
    analogWrite (lf, 0);
    analogWrite (lb , leftmspeed);
    analogWrite (rf, rightmspeed);     // left spin
    analogWrite (rb , 0);
  }

   else if (ch4 <=10 && ch4>=-10 ){
     analogWrite (lf, 0);
    analogWrite (lb , 0);            // stop spin
    analogWrite (rf, 0);
    analogWrite (rb , 0); 
  }
  

  
  
  leftmspeed = leftmspeed + abs (ch4);         // spin mode speed
  rightmspeed = rightmspeed + abs (ch4); 
 

 }

 else                                       // normal mode
 {

   if (ch2>0)
   {
    analogWrite (lf, leftmspeed1);
    analogWrite (lb , 0);              // forward
    analogWrite (rb, 0 );
    analogWrite (rf , rightmspeed1);
   }

   else if (ch2<0){
    analogWrite (lf, 0);
    analogWrite (lb , leftmspeed1);              //backward
    analogWrite (rb, rightmspeed1);
    analogWrite (rf , 0);
   }

   else if (ch2==0){

    analogWrite (lf, 0);
    analogWrite (lb , 0);              // normal stop
    analogWrite (rb, 0 );
    analogWrite (rf , 0);
    
   }


   rightm = ch3 + abs (ch2);       
   leftm = ch3 + abs(ch2);

   rightmspeedf = leftm - ch1;       //left / right direction speed
   leftmspeedf= rightm + ch1;

 

    rightmspeed1 = constrain (rightmspeedf , 0 ,255);
    leftmspeed1 = constrain (leftmspeedf , 0 , 255);

//    Serial.print("left =");
//    Serial.print (leftmspeed1);
//    Serial.print ("     Right");
//    Serial.println (rightmspeed1);

 }

}
