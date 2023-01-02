#include <Servo.h>
#define joystick_x A0
#define joystick_y A1
#define servo_x_pin 5
#define servo_y_pin 6

short x_axis, y_axis;
unsigned long current_servo_x_time = 0, current_servo_y_time = 0;
unsigned long current_servo_x_angle = 90, current_servo_y_angle = 90;

Servo servo_x, servo_y;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);
  servo_x.attach(servo_x_pin);
  servo_y.attach(servo_y_pin);
  servo_x.write(90);
  servo_y.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long time_now = millis();
  x_axis = map(analogRead(joystick_x), 256, 1024, 70, 110);
  y_axis = map(analogRead(joystick_y), 256, 1024, 70, 110);
  
  Serial.print("X: "); Serial.print(x_axis);
  Serial.print("  Y: "); Serial.println(y_axis);

  if (x_axis > current_servo_x_angle) {
      for (current_servo_x_angle; current_servo_x_angle < x_axis && time_now - current_servo_x_time >= 5; ++current_servo_x_angle, current_servo_x_time = time_now) 
        servo_x.write(current_servo_x_angle);
  } else if (x_axis < current_servo_x_angle) {
      for (current_servo_x_angle; current_servo_x_angle > x_axis && time_now - current_servo_x_time >= 5; --current_servo_x_angle, current_servo_x_time = time_now)
        servo_x.write(current_servo_x_angle);
  } else servo_x.write(current_servo_x_angle);
    
  if (y_axis > current_servo_y_angle) {
      for (current_servo_y_angle; current_servo_y_angle < y_axis && time_now - current_servo_y_time >= 5; ++current_servo_y_angle, current_servo_y_time = time_now) 
        servo_y.write(current_servo_y_angle);
  } else if (y_axis < current_servo_y_angle) {
      for (current_servo_y_angle; current_servo_y_angle > y_axis && time_now - current_servo_y_time >= 5; --current_servo_y_angle, current_servo_y_time = time_now)
        servo_y.write(current_servo_y_angle);
  } else servo_y.write(current_servo_y_angle);
}
