#include <Wire.h>
#include <Zumo32U4.h> // nødvendige 

Zumo32U4ProximitySensors proxSensor; //sensore på side (to på side, en frem)
Zumo32U4Motors motor; //nødvendig for at zumo kan køre
Zumo32U4ButtonA buttonA; //for at sætte zumo igang
Zumo32U4OLED display; //der findes OLED og LCD

#define NUM_SENSORS 3
int proxSensorValues[NUM_SENSORS];

int min; // disse værdier kan ændres
int max = 80;

void printReadinToSerial(){
  char buffer[80];
  sprintf(buffer,"%4d %4d %4d\n",
  proxSensorValues[0],
  proxSensorValues[1],
  proxSensorValues[2]);
  Serial.print(buffer);
}

//void readProxSensors(){
 // proxSensor.read(proxSensorValues, QTR_EMITTERS_ON);
//}

void setup() {
  Serial.begin(9600);
  proxSensor.initThreeSensors();
  
  proxSensor.setBrightnessLevels(50,500);//første er level, næste er count brightness
  printReadinToSerial();
  
  //buttonA.waitForButton(); //den er god at have med, fordi loopet starter først når der er trykket 
  buttonA.getSingleDebouncedRelease();
  while(buttonA.getSingleDebouncedRelease() == false){
    proxSensor.read();
    
    int proxLeft = proxSensor.countsLeftWithLeftLeds();
    int proxRight = proxSensor.countsRightWithRightLeds();
    display.clear();
    display.gotoXY(0,1);
    display.print(proxLeft);
    display.print(" . ");
    display.print(proxRight);
    //int proxRight = proxSensor.countsRightWithRightLeds ();
    //display.clear();
    //display.gotoXY(0,0); //levels aflæses før press A, når det er sat i whileloop i setup
    //display.print(proxRight); 
  } 
  proxSensor.read();
  min = proxSensor.countsRightWithRightLeds();
  
  //motor.setSpeeds(50,50);
  // put your setup code here, to run once:

}



void loop() {
  proxSensor.read();
  int proxLeft = proxSensor.countsLeftWithLeftLeds();
  int proxRight = proxSensor.countsRightWithRightLeds();
  int proxFrontL = proxSensor.countsFrontWithLeftLeds();
  int proxFrontR = proxSensor.countsFrontWithRightLeds();
  display.clear();
  display.gotoXY(0,1);
  display.print(proxLeft);
  display.print(" . ");
  display.print(proxRight);
  display.gotoXY(0,0);
  display.print(proxFrontL);
  display.print(" . ");
  display.print(proxFrontR);

  if (proxFrontR >= 182 && proxRight >= 182){
    motor.setSpeeds(0,0);
    motor.setSpeeds(-60,-60);
    delay(200);
    motor.setSpeeds(-100,100);
    delay(900);
    motor.setSpeeds(60,60);
    
  }


  else if (proxRight >= min){
    
    motor.setSpeeds(70,60);// lav hastighed giver mindre overslag i ønsket distance (proportionel regulering)
   
  }

  else if (proxRight < min){
    
    motor.setSpeeds(60,70);
    
  }
  //else if (proxRight == proxFrontR){
    //motor.setSpeeds(70,70);
  //}

  
  
  

}
