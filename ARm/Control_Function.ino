String int_inString = "";
uint16_t integer;
int n = 0;
void get_data()
{
  while(Serial.available())
  {
    int inchar = Serial.read();
    if(isDigit(inchar)){int_inString+=(char)inchar;}
    
    if(inchar == ',')
    {
      integer = int_inString.toInt();
      data[n] = integer; n++;
      int_inString = "";
    }
    else if(inchar == '\n'){n=0; int_inString = "";}

    if(inchar == 'Q'){data[0]++;}
    else if(inchar == 'W'){data[1]++;}
    else if(inchar == 'E'){data[2]++;}
    else if(inchar == 'R'){data[3]++;}
    else if(inchar == 'T'){data[4]++;}
    else if(inchar == 'q'){data[0]--;}
    else if(inchar == 'w'){data[1]--;}
    else if(inchar == 'e'){data[2]--;}
    else if(inchar == 'r'){data[3]--;}
    else if(inchar == 't'){data[4]--;}
    
    
  }
}
