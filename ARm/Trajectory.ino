int countObj[4];
void Trajectory()
{
  switch(run_time)
  {
    case 0: moveServo(20, 90, 152, 180, 22, 0); if(action > 0){run_time++;} break; //stanby
    case 1: moveServo(20, 160, 10, 180, 165, 0); if(action > 0){run_time++;} break; //obj position
    case 2: moveServo(20, 160, 6, 154, 144, 0); if(action > 0){run_time++;} break; //obj ready
    case 3: moveServo(20, 160, 6, 154, 144, 90); if(action > 0){run_time++;} break; //get object
    case 4: moveServo(20, 160, 45, 180, 135, 90); if(action > 0){run_time++;} break; //put object
    case 5: if(action == 1){run_time = 6;} //choice goal position
            else if(action == 2){run_time = 7;}
            else if(action == 3){run_time = 8;}
            break;
            
    case 6: moveServo(20, 20, 45, 180, 135, 90); if(action > 0){run_time = 9;} break; //goal position 1
    case 7: moveServo(20, 40, 45, 180, 135, 90); if(action > 0){run_time = 10;} break; //goal position 2
    case 8: moveServo(20, 60, 45, 180, 135, 90); if(action > 0){run_time = 11;} break; //goal position 3

    case 9: moveServo(20, 20, 10, 180, 165, 90); if(action > 0){run_time = 12;} break; //goal 1
    case 10: moveServo(20, 40, 10, 180, 165, 90); if(action > 0){run_time = 13;} break; //goal 2
    case 11: moveServo(20, 60, 10, 180, 165, 90); if(action > 0){run_time = 14;} break; //goal 3

    case 12: moveServo(20, 20, 0, 119, 108, 90); if(action > 0){run_time = 15;} break; //push 1
    case 13: moveServo(20, 40, 0, 119, 108, 90); if(action > 0){run_time = 16;} break; //push 2
    case 14: moveServo(20, 60, 0, 119, 108, 90); if(action > 0){run_time = 17;} break; //push 3

    case 15: moveServo(20, 20, 0, 119, 108, 0); action = run_time = 0; break; //take 1
    case 16: moveServo(20, 40, 0, 119, 108, 0); action = run_time = 0; break; //take 2
    case 17: moveServo(20, 60, 0, 119, 108, 0); action = run_time = 0; break; //take 3
  }
  if(run_time > 0){delay(1000);}
  else
  {
      while(Serial.available())
      {
          char vision = Serial.read();
          if(vision == '0'){countObj[0]++;}
          else if(vision == '1'){countObj[1]++; countObj[0]=0;}
          else if(vision == '2'){countObj[2]++; countObj[0]=0;}
          else if(vision == '3'){countObj[3]++; countObj[0]=0;}
    
          if(countObj[0] > 3){action = countObj[1] =countObj[2] =countObj[3] = 0;}
          else if(countObj[1] > 10){action = 1;}
          else if(countObj[2] > 10){action = 2;}
          else if(countObj[3] > 10){action = 3;}
      }
   }
}
