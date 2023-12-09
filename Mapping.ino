#include <Wire.h>
#include <Zumo32U4.h> // nødvendige 

Zumo32U4ProximitySensors proxSensor; //sensore på side (to på side, en frem)
Zumo32U4Motors motor; //nødvendig for at zumo kan køre
Zumo32U4ButtonA buttonA; //for at sætte zumo igang
Zumo32U4OLED display; //der findes OLED og lcd
Zumo32U4IMU imu;
Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;

float XArray[100];
float YArray[100];
int movementCommand = 0;   // used to select the command
int movementParameter = 0;   // used to select distance or angle
float wheelCirc = 13;
uint8_t XEllerY = 2;
float GemtX = 0;
float GemtY = 0;

uint32_t turnAngle = 0;
int16_t turnRate;
int16_t gyroOffset;
uint16_t gyroLastUpdate = 0;
float Scalar = 1.0023;

unsigned long StartTid = 0;

int countsL = encoders.getCountsLeft();
int countsR = encoders.getCountsRight();

float distanceL = countsL/900.0 * wheelCirc;
float distanceR = countsR/900.0 * wheelCirc;

int16_t CompleteAngle = 0;

int8_t stage = 0;

float getDistanceR(){
  int countsL = encoders.getCountsLeft();
  int countsR = encoders.getCountsRight();

  float distanceL = countsL/900.0 * wheelCirc;
  float distanceR = countsR/900.0 * wheelCirc;

  return(distanceR);
}

float getDistanceL(){
  int countsL = encoders.getCountsLeft();
  int countsR = encoders.getCountsRight();

  float distanceL = countsL/900.0 * wheelCirc;
  float distanceR = countsR/900.0 * wheelCirc;

  return(distanceL);
}

float NetDistance(){
  float a = 0.0;
  a = getDistanceL() + getDistanceR();
  a = a / 2;
  return(a);
}


void resetEncoders(){
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();
}

void TurnSensorSetup()
{
  Wire.begin();
  imu.init();
  imu.enableDefault();
  imu.configureForTurnSensing();

  display.clear();
  display.print(F("Gyro cal"));

  // Turn on the yellow LED in case the LCD is not available.
  ledYellow(1);

  // Delay to give the user time to remove their finger.
  delay(500);

  // Calibrate the gyro.
  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++)
  {
    // Wait for new data to be available, then read it.
    while(!imu.gyroDataReady()) {}
    imu.readGyro();

    // Add the Z axis reading to the total.
    total += imu.g.z;
  }
  ledYellow(0);
  gyroOffset = total / 1024;

  // Display the angle (in degrees from -180 to 180) until the
  // user presses A.
  display.clear();
  turnSensorReset();
}

void turnSensorReset()
{
  gyroLastUpdate = micros();
  turnAngle = 0;
}

void turnSensorUpdate()
{
  // Read the measurements from the gyro.
  imu.readGyro();
  turnRate = imu.g.z - gyroOffset;

  // Figure out how much time has passed since the last update (dt)
  uint16_t m = micros();
  uint16_t dt = m - gyroLastUpdate;
  gyroLastUpdate = m;

  // Multiply dt by turnRate in order to get an estimation of how
  // much the robot has turned since the last update.
  // (angular change = angular velocity * time)
  int32_t d = (int32_t)turnRate * dt;

  // The units of d are gyro digits times microseconds.  We need
  // to convert those to the units of turnAngle, where 2^29 units
  // represents 45 degrees.  The conversion from gyro digits to
  // degrees per second (dps) is determined by the sensitivity of
  // the gyro: 0.07 degrees per second per digit.
  //
  // (0.07 dps/digit) * (1/1000000 s/us) * (2^29/45 unit/degree)
  // = 14680064/17578125 unit/(digit*us)
  turnAngle += (int64_t)d * 14680064 / 17578125;
}

uint16_t i = 0;
void Plonk(){
  
  if(XEllerY % 4 == 0){
    XArray[i] = GemtX - NetDistance();
    YArray[i] = GemtY;
  }
  else if(XEllerY % 3 == 0){
    XArray[i] = GemtX;
    YArray[i] = NetDistance();
  }
  else if(XEllerY % 2 == 0){
    XArray[i] = NetDistance();
    YArray[i] = 0;
  }
  else{
    XArray[i] = GemtX;
    YArray[i] = GemtY - NetDistance();
  }
  i++;
}

void PrintArrays(){
  for(int k = 0; k <= i; k++){
    Serial.println(k);
    Serial.println(XArray[k]);
    Serial.println(YArray[k]);
  }
}

uint32_t TurnAngle(){
  turnSensorUpdate();
  // do some math and pointer magic to turn angle in seconds to angle in degree
  return (((uint32_t)turnAngle >> 16) * 360) >> 16;
}

void Bip(){
  buzzer.playNote(NOTE_D(5),20,15);
  delay(100);
}

void VictoryScreech(){
  motor.setSpeeds(0,0);
  buzzer.playNote(NOTE_D(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_D(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_E(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_F(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_D(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_C(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_C(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_A(4),20,15);
  delay(500);
  buzzer.playNote(NOTE_B(4),20,15);
  delay(1000);

  buzzer.playNote(NOTE_D(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_D(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_E(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_F(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_D(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_C(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_C(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_F(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_G(5),20,15);
  delay(1000);

  buzzer.playNote(NOTE_G(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_G(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_A(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_B_FLAT(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_G(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_F(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_F(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_D(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_E(5),20,15);
  delay(1000);

  buzzer.playNote(NOTE_G(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_G(5),20,15);
  delay(375);
  buzzer.playNote(NOTE_A(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_B_FLAT(5),20,15);
  delay(125);
  buzzer.playNote(NOTE_G(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_F(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_F(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_B_FLAT(5),20,15);
  delay(500);
  buzzer.playNote(NOTE_C(6),20,15);
  delay(1000);
}

void Onwards(){
  resetEncoders();
  motor.setSpeeds(80,80);
  unsigned long SidstePlonk = millis();
  while(NetDistance() < 50){
    if((SidstePlonk + 1000) < millis()){
      SidstePlonk = millis();
      Plonk();
      Bip();
    }
    while (getDistanceL() * Scalar < getDistanceR()){
    motor.setSpeeds(80,60);
    display.print(getDistanceL());
    display.gotoXY(0,1);
    display.print(getDistanceR());
    display.clear();
    
  }
  while (getDistanceR() < getDistanceL() * Scalar){
    motor.setSpeeds(60,80);
    display.print(getDistanceL());
    display.gotoXY(0,1);
    display.print(getDistanceR());
    display.clear();
  }
 }
 stage = 1;
}

void Turn(){
  motor.setSpeeds(0,0);
  Plonk();
  if(XEllerY == 2){
    GemtX = NetDistance();
  }
  else if(XEllerY == 3){
    GemtY = NetDistance();
  }
  else if(GemtX > 49){
    GemtX = GemtX - NetDistance();
  }
  
  TurnSensorSetup();
  turnSensorReset();
  motor.setSpeeds(-80,80);
  delay(50);
  while(TurnAngle() != 88){
    display.print(TurnAngle());
    motor.setSpeeds(-80,80);
    display.clear();
  }
  CompleteAngle = CompleteAngle + TurnAngle() + 2;
  if(350 < CompleteAngle && CompleteAngle < 370){
    stage = 2;
  }
  else{
    stage = 0;
  }
  XEllerY++;
  display.print(CompleteAngle);
}

void Stop(){
  motor.setSpeeds(0,0);
  VictoryScreech();
  delay(50);
  display.clear();
  unsigned long SlutTid = millis() - StartTid;
  SlutTid = SlutTid / 1000;
  display.print(SlutTid);
  while(buttonA.getSingleDebouncedRelease() == false){
  }
  delay(2000);
  display.clear();
  display.print("Printing");
  //Lave for loop der print arraysene ved hjælp af nummer på entry
  PrintArrays();
  while(buttonA.getSingleDebouncedRelease() == false){
  }
}


void setup() {
  Serial.begin(9600);
  TurnSensorSetup();
  proxSensor.initThreeSensors();
  
  proxSensor.setBrightnessLevels(50,500);//første er level, næste er count brightness

  int proxSensorReadings[2];

  const int minDistanse = proxSensorReadings[1];
  
  while(buttonA.getSingleDebouncedRelease() == false){
   display.print(TurnAngle());
   turnSensorUpdate();
   delay(50);
   display.clear();
  }
  StartTid = millis();
  motor.setSpeeds(0,0);
}


void loop() {
  switch(stage){
    case 0: Onwards();
    break;
    case 1: Turn();
    break;
    case 2: Stop();
    break;
  }
}
