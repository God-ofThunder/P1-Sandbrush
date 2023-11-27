#include <Wire.h>
#include <Zumo32U4.h> // nødvendige 

Zumo32U4ProximitySensors proxSensor; //sensore på side (to på side, en frem)
Zumo32U4Motors motor; //nødvendig for at zumo kan køre
Zumo32U4ButtonA buttonA; //for at sætte zumo igang
Zumo32U4OLED display; //der findes OLED og LCD

#define NUM_SENSORS 3
int proxSensorValues[NUM_SENSORS];

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

void waitForStartSignal(int *proxSensorReadings){ 
  //buttonA.waitForButton(); //den er god at have med, fordi loopet starter først når der er trykket 
  buttonA.getSingleDebouncedRelease();
  while(buttonA.getSingleDebouncedRelease() == false){
	  readProxSensors(proxSensorReadings);
	  printProxSensorReadings(proxSensorReadings);
  } 
}

void readProxSensors(int *readings){
	proxSensor.read();
	readings[0] = proxSensor.countsLeftWithLeftLeds();
	readings[1] = proxSensor.countsFrontWithRightLeds();
}

void printProxSensorReadings(int *readings){
	display.clear();
	display.gotoXY(0,1);
	display.print(readings[0]);
	display.print("--");
	display.print(readings[1]);
}

void sharpTurn(){
    motor.setSpeeds(0,0);
    motor.setSpeeds(-60,-60);
    delay(300);
    motor.setSpeeds(-100,100);
    delay(830);
    motor.setSpeeds(60,60);
}

void followWall(int *readings, int minDistanse){	
	printProxSensorReadings(readings);
	if (readings[1] >= minDistanse){ 
		motor.setSpeeds(80,60);// lav hastighed giver mindre overslag i ønsket distance (proportionel regulering)
	}
	else if (readings[1] < minDistanse){ 
		motor.setSpeeds(60,80);
	}
}

void followEdgeOfSandbox(int *readings, int minDistanse){
	if (readings[1] <= 0 && readings[0] >= 15){
		sharpTurn();
	}
	else{
		followWall(readings, minDistanse);
	}
}

void setup() {
	Serial.begin(9600);
	proxSensor.initThreeSensors();
  
	proxSensor.setBrightnessLevels(50,500);//første er level, næste er count brightness
	printReadinToSerial();

	int proxSensorReadings[2];
	waitForStartSignal(proxSensorReadings);

	readProxSensors(proxSensorReadings);
	const int minDistanse = proxSensorReadings[1];
	
	while(true){
		readProxSensors(proxSensorReadings);
		followEdgeOfSandbox(proxSensorReadings, minDistanse);
	}
	motor.setSpeeds(0,0);
}



void loop() {

}
