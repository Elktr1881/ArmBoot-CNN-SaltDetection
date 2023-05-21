// Deklarasi variabel panjang lengan (dalam mm)
float l1 = 10;  // Panjang lengan basis
float l2 = 10;   // Panjang lengan pertama
float l3 = 10;   // Panjang lengan kedua
float l4 = 10;   // Panjang lengan gripper

// Deklarasi variabel sudut (dalam derajat)
float theta1 = 0;    // Sudut servo base
float theta2 = 0;    // Sudut servo lengan pertama
float theta3 = 0;    // Sudut servo lengan kedua
float theta4 = 0;    // Sudut servo lengan ketiga
float theta5 = 0;    // Sudut servo gripper

// Fungsi konversi sudut dari derajat ke radian
float toRadian(float degree) {
  return degree * PI / 180.0;
}

void mainOfKinemematics(float kX, float kY, float kZ)
{
    // Input the x, y, and z coordinates
    float x = kX; // Contoh nilai x
    float y = kY; // Contoh nilai y
    float z = kZ; // Contoh nilai z
    
    // Hitung sudut-sudut servo dengan metode inverse kinematik
    float d = sqrt(pow(x, 2) + pow(y, 2) + pow((z-l1), 2));
    
    // Perhitungan sudut wrist_roll
    float wrist_roll_radians = acos((pow(l2,2) + pow(l3,2) - pow(l4,2) - pow(d,2))/(-2*l4*d));
    float wrist_pitch_radians = atan2(z - l1 - l3*sin(wrist_roll_radians), sqrt(x*x + y*y)) - atan2(l3*cos(wrist_roll_radians), l2 + l3*sin(wrist_roll_radians));
    float wrist_yaw_radians = atan2(y, x);
    
    // Perhitungan sudut elbow
    float elbow_radians = acos((pow(d,2) - pow(l2,2) - pow(l3,2))/(2*l2*l3)) - atan2(sqrt(pow(x,2) + pow(y,2) - pow(l2,2)), l2 + l3*cos(elbow_radians));
    
    // Perhitungan sudut shoulder
    float shoulder_radians = atan2(z - l1, sqrt(pow(x,2) + pow(y,2))) - atan2(l3*sin(elbow_radians + wrist_roll_radians), l2 + l3*cos(elbow_radians + wrist_roll_radians));
    
    // Perhitungan sudut base
    float base_radians = atan2(y, x);
    
    // Konversi dari radian ke derajat
    float base_angle = base_radians * 180 / PI;
    float shoulder_angle = shoulder_radians * -180 / PI;
    float elbow_angle = elbow_radians * 180 / PI;
    float wrist_angle = (wrist_pitch_radians + wrist_roll_radians) * 180 / PI;

    // Mengirim sudut-sudut servo ke servo motor
//    base_servo.write(constrain(0,min_base,max_base));
//    shoulder_servo.write(constrain(0,min_shoulder,max_shoulder));
//    elbow_servo.write(constrain(0,min_elbow,max_elbow));
//    wrist_servo.write(constrain(0,min_wrist,max_wrist));
    
    Serial.print(x); Serial.print(" , ");
    Serial.print(y); Serial.print(" , ");
    Serial.print(z); Serial.print(" || ");
    
    pos1 = map(base_angle, -90, 90, 0, 180);
    pos2 = map(shoulder_angle, 90, -90, 0, 180);
    pos3 = map(elbow_angle, -90, 90, 0, 180);
    pos4 = map(wrist_angle, 90, -90, 0, 180);
    
    Serial.print(pos1); Serial.print(" , ");
    Serial.print(pos2); Serial.print(" , ");
    Serial.print(pos3); Serial.print(" , ");
    Serial.print(pos4); Serial.print(" \n ");
}

// Fungsi menggerakkan servo ke sudut yang ditentukan
void moveServo(int posDelay, float angle1, float angle2, float angle3, float angle4, float angle5){

    float posAngel[5];
    posAngel[0] = (float)base_angle;
    posAngel[1] = (float)shoulder_angle;
    posAngel[2] = (float)elbow_angle;
    posAngel[3] = (float)wrist_angle;
    posAngel[4] = (float)griper_angle;
  
    float totalMove[5]; float time_step;
    totalMove[0] = (angle1 - posAngel[0]);
    totalMove[1] = (angle2 - posAngel[1]);
    totalMove[2] = (angle3 - posAngel[2]);
    totalMove[3] = (angle4 - posAngel[3]);
    totalMove[4] = (angle5 - posAngel[4]);

    time_step = abs(totalMove[0]);
    if(time_step < abs(totalMove[1])){time_step = abs(totalMove[1]);}
    if(time_step < abs(totalMove[2])){time_step = abs(totalMove[2]);}
    if(time_step < abs(totalMove[3])){time_step = abs(totalMove[3]);}
    if(time_step < abs(totalMove[4])){time_step = abs(totalMove[4]);}
    
    for(int a=0; a<5; a++){totalMove[a] /= time_step;}
  
    for(int i=0; i<time_step; i++){
      for(int j=0; j<5; j++){
        posAngel[j] += totalMove[j];
        //Serial.print((int)posAngel[j]); Serial.print(",");
        }
//        Serial.print(run_time);Serial.print(",");
//        Serial.print(action);Serial.print(",");
//        Serial.println();
        
    base_angle      = (int)posAngel[0];
    shoulder_angle  = (int)posAngel[1];
    elbow_angle     = (int)posAngel[2];
    wrist_angle     = (int)posAngel[3];
    griper_angle    = (int)posAngel[4];

    base_servo.write(constrain(base_angle,min_base,max_base));
    shoulder_servo.write(constrain(shoulder_angle,min_shoulder,max_shoulder));
    elbow_servo.write(constrain(elbow_angle,min_elbow,max_elbow));
    wrist_servo.write(constrain(wrist_angle,min_wrist,max_wrist));
    griper_servo.write(constrain(griper_angle,min_wrist,max_wrist));
  
    delay(posDelay);
  }
}
