#include <Servo.h>

#define pinBase 8
#define pinShoulder 11
#define pinElbow 9
#define pinWrist 5
#define pinGriper 6

#define potX A0
#define potY A1

Servo base_servo;
Servo shoulder_servo;
Servo elbow_servo;
Servo wrist_servo;
Servo griper_servo;

int base_angle = 90;
int shoulder_angle = 152;
int elbow_angle = 180;
int wrist_angle = 22;
int griper_angle = 0;

const int min_base = 0;
const int min_shoulder = 0;
const int min_elbow = 0;
const int min_wrist = 0;
const int min_griper = 0;

const int max_base = 180;
const int max_shoulder = 180;
const int max_elbow = 200;
const int max_wrist = 180;
const int max_griper = 180;

int pos1, pos2, pos3, pos4;
float input_X, input_Y;

int run_time = 0;
int action = 0;
int data[10];

void setup() {
  Serial.begin(115200);
  base_servo.attach(pinBase);
  shoulder_servo.attach(pinShoulder);
  elbow_servo.attach(pinElbow);
  wrist_servo.attach(pinWrist);
  griper_servo.attach(pinGriper);

  base_servo.write(constrain(base_angle,min_base,max_base));
  shoulder_servo.write(constrain(shoulder_angle,min_shoulder,max_shoulder));
  elbow_servo.write(constrain(elbow_angle,min_elbow,max_elbow));
  wrist_servo.write(constrain(wrist_angle,min_wrist,max_wrist));
  griper_servo.write(constrain(griper_angle,min_wrist,max_wrist));

  data[0] = 0;
//  data[1] = shoulder_angle;
//  data[2] = elbow_angle;
//  data[3] = wrist_angle;
//  data[4] = griper_angle;
  
  delay(2000);

  pinMode(potX,INPUT);
  pinMode(potY,INPUT); 
}

void loop() {
  input_X = (float)analogRead(potX)*100/1023; 
  input_Y = (float)analogRead(potY)*100/1023;

//  get_data();
//  Serial.print(input_X); Serial.print(" , ");
//  Serial.print(input_Y); Serial.print(" , ");
//  Serial.print(data[0]); Serial.print(" , ");
//  Serial.print(data[1]); Serial.print(" , ");
//  Serial.print(data[2]); Serial.print(" , ");
//  Serial.print(data[3]); Serial.print(" , ");
//  Serial.print(data[4]); 
//  Serial.println(" , ");

  Trajectory();

//  moveServo(10, data[0], data[1], data[2], data[3], data[4]);

}
