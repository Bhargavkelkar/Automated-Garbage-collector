#include <Arduino.h>
#include <Servo.h>

const int BASE_PIN      =3;  //  0-180 degree
const int SHOULDER_PIN  =5;  // rotates  joint 
const int ELBOW_PIN    =6;  //Forward back
const int GRIPPER_PIN  =9;  // claw open 

Servo baseServo;
Servo shoulderServo;
Servo elbowsServo;
Servo gripperServo;

int currentBase  =90;
int curentshoulder=90;
int currentElbow=90;
int currentGripper=90;

void moveServoSmooth(Servo &servo, int &currentAngle, int targetAngle, int stepDelayMs = 15) {
  targetAngle = constrain(targetAngle, 0, 180);
  
  if (targetAngle > currentAngle) {
    for (int pos = currentAngle; pos<= targetAngle; pos++) {
    servo.write(pos);
    delay(stepDelayMs);
    }
  } else{
    for (int pos = currentAngle; pos>= targetAngle; pos--) { 
      servo.write(pos);
      delay(stepDelayMs);
    }
  }
  currentAngle = targetAngle;
}
void setup() {
  Serial.begin(9600);

// uno pins
  baseServo.attach(BASE_PIN);
  shoulderServo.attach(SHOULDER_PIN);
  elbowsServo.attach(ELBOW_PIN);
  gripperServo.attach(GRIPPER_PIN);

  // Home position
  baseServo.write(currentBase);
  shoulderServo.write(curentshoulder);
  elbowsServo.write(currentElbow);
  gripperServo.write(currentGripper);

  delay(1000);
  Serial.println("STATUS: READY");
}

void loop (){
  //  open claw
  moveServoSmooth(gripperServo, currentGripper, 90);
  delay(500);

  // lower shoulder and extend elbow
  moveServoSmooth(shoulderServo, curentshoulder, 60);
  moveServoSmooth(elbowsServo, currentElbow, 120);
  delay(500);
  // close gripper
  moveServoSmooth(gripperServo, currentGripper, 110);
  delay(500);
  //lift
  moveServoSmooth(shoulderServo, curentshoulder, 90);
  moveServoSmooth(elbowsServo, currentElbow, 90);
  delay(500);
  // rotate base to new loction
  moveServoSmooth(baseServo, currentBase, 150);
  delay(500);
  // lower arm and release obj
  moveServoSmooth(shoulderServo, curentshoulder, 60);
  moveServoSmooth(gripperServo,currentGripper, 40);
  delay(500);
// reset arm
moveServoSmooth(shoulderServo, curentshoulder,90);
moveServoSmooth(baseServo,currentBase,90);
moveServoSmooth(gripperServo, currentGripper,90);
// pause 
delay(4000); 
}