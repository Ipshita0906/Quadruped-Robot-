#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
bool started = false;

#define SERVOMIN 150
#define SERVOMAX 600

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setServo(int channel, int angle) {
  pwm.setPWM(channel, 0, angleToPulse(angle));
}

// ================= BASE POSITIONS =================

// Front Left
int FL_coxa = 50, FL_femur = 75;

// Front Right
int FR_coxa = 25, FR_femur = 70;

// Rear Left
int RL_coxa = 50, RL_femur = 75;

// Rear Right
int RR_coxa = 90, RR_femur = 50;

// ================= DIRECTION =================

// Coxa
int dir_FL_coxa = -1;  // channel 2
int dir_FR_coxa = 1;
int dir_RL_coxa = -1;  // channel 1
int dir_RR_coxa = 1;

// Femur
int dir_FL_femur = 1;
int dir_FR_femur = 1;
int dir_RL_femur = +1; // channel 8 inverted
int dir_RR_femur = -1;  // channel 10 normal

// ================= INDIVIDUAL LIFT =================

int lift_FL = 55 ;
int lift_FR = 55;
int lift_RL = 40;
int lift_RR = 40;

int step=28;
int delayTime = 250;

// ================= LEG MOVE =================

void moveLeg(int coxa_ch, int femur_ch,
             int base_coxa, int base_femur,
             int dir_coxa, int dir_femur,
             int lift_val) {

  // Lift
  setServo(femur_ch, base_femur - dir_femur * lift_val);
  delay(delayTime);

  // Forward
  setServo(coxa_ch, base_coxa + dir_coxa * step);
  delay(delayTime);

  // Down
  setServo(femur_ch, base_femur);
  delay(delayTime);

  // Push
  setServo(coxa_ch, base_coxa - dir_coxa * step);
  delay(delayTime);

  // Neutral
  setServo(coxa_ch, base_coxa);
  delay(delayTime);
}

// ================= SETUP =================

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(50);

  delay(1000);

  // Initial pose
  setServo(2, FL_coxa);
  setServo(9, FL_femur);

  setServo(3, FR_coxa);
  setServo(11, FR_femur);

  setServo(1, RL_coxa);
  setServo(8, RL_femur);

  setServo(0, RR_coxa);
  setServo(10, RR_femur);
}


void loop() {
  if (!started) {
  delay(10000);
  started = true;
}

  // Crawl gait sequence

  moveLeg(2, 9, FL_coxa, FL_femur, dir_FL_coxa, dir_FL_femur, lift_FL);
  moveLeg(0, 10, RR_coxa, RR_femur, dir_RR_coxa, dir_RR_femur, lift_RR);
  moveLeg(3, 11, FR_coxa, FR_femur, dir_FR_coxa, dir_FR_femur, lift_FR);
  moveLeg(1, 8, RL_coxa, RL_femur, dir_RL_coxa, dir_RL_femur, lift_RL);
}
