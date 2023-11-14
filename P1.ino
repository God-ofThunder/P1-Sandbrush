#include <Wire.h>
#include <Zumo32U4.h> // nødvendige 

Zumo32U4ProximitySensors proxSensor;
Zumo32U4Motors motor;
Zumo32U4ButtonA buttonA;
Zumo32U4OLED display;

//Skal ændres
int min = 30;
int max = 40;

void setup() {
  proxSensor.initThreeSensors();
  proxSensor.setBrightnessLevels(70,700);//første er level, næste er count brightness
  buttonA.waitForButton(); //den er god at have med, fordi loopet starter først når der er trykket 
  buttonA.getSingleDebouncedRelease();
  while(buttonA.getSingleDebouncedRelease() == true){
    proxSensor.read();
    int proxRight = proxSensor.countsRightWithRightLeds ();
    display.clear();
    display.gotoXY(0,0); //levels aflæses før press A, når det er sat i whileloop i setup
    display.print(proxRight); 
  } 
  proxSensor.read();
  min = proxSensor.countsRightWithRightLeds();
  motor.setSpeeds(40,40);
  // put your setup code here, to run once:

}



void loop() {
  proxSensor.read();
  int proxRight = proxSensor.countsRightWithRightLeds ();
  display.clear();
  display.gotoXY(0,0);
  display.print(proxRight);

  if (proxRight > min && proxRight < max){
    proxSensor.read();
    motor.setSpeeds(50,80);// lav hastighed giver mindre overslag i ønsket distance (proportionel regulering)
    proxSensor.read();
  }

  else if (proxRight < min){
    proxSensor.read();
    motor.setSpeeds(80,50);
    proxSensor.read();
  }

  else if (proxRight > max){
    proxSensor.read();
    motor.setSpeeds(-60,60);
    proxSensor.read();
  }

  else if (proxRight == min){
    proxSensor.read();
    motor.setSpeeds(40,40);
    proxSensor.read();
  }
  // put your main code here, to run repeatedly:

}
