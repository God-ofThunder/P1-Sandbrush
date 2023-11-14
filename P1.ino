
#include <Wire.h>
#include <Zumo32U4.h> // nødvendige 


Zumo32U4ProximitySensors proxSensor; // sensore på siden
Zumo32U4Motors motor; // nødvendig for at zumo kan kører
Zumo32U4ButtonA buttonA; // 
Zumo32U4OLED display;


void setup() {
  proxSensor.initThreeSensors();
  proxSensor.setBrightnessLevels(50,500);//første er level, næste er count brightness
    while(buttonA.isPressed() != 1){//når bA ikke er trykket ned, så kører den i wloop.
    proxSensor.read();
    int proxRight = proxSensor.countsRightWithRightLeds();
    display.clear();
    display.gotoXY(0,0); //levels aflæses før press A, når det er sat i whileloop i setup
    display.print(proxRight); 
  }
  //buttonA.getSingleDebouncedPress(); //den er god at have med, fordi loopet starter først når der er trykket 
  motor.setSpeeds(100,100);
  // put your setup code here, to run once:

}



void loop() {
  proxSensor.read();
  int proxRight = proxSensor.countsRightWithRightLeds ();
  display.clear();
  display.gotoXY(0,0);
  display.print(proxRight);
  if (proxRight >=30){
    motor.setSpeeds(50,80);// lav hastighed giver mindre overslag i ønsket distance (proportionel regulering)
   
    

    
  }
  else if (proxRight <30){
    motor.setSpeeds(80,50);
    
    
  }
  else if (proxRight == 30){
    motor.setSpeeds(50,50);
    
  }
  // put your main code here, to run repeatedly:

}
