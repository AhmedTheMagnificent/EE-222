#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_COUNT 4
#define SERVO_MIN_PULSE 150
#define SERVO_MAX_PULSE 600

void setup() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(60);
  int defaultAngles[SERVO_COUNT] = {75, 50, 50, 0};
  for (int i = 0; i < SERVO_COUNT; i++) {
    int pulseWidth = map(defaultAngles[i], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(i, 0, pulseWidth);
  }
}

void loop() {
  if (Serial.available() >= SERVO_COUNT) { 
    byte angleBytes[SERVO_COUNT];
    Serial.readBytes(angleBytes, SERVO_COUNT); 
    

    int servoAngles[SERVO_COUNT];
    for (int i = 0; i < SERVO_COUNT; i++) {
      servoAngles[i] = map(angleBytes[i], 0, 255, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
      pwm.setPWM(i, 0, servoAngles[i]);
    }

  }
}
