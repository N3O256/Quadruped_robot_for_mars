#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver s = Adafruit_PWMServoDriver();

//Pins:
//front right: 0, 1, 2 
//front left: 8, 9, 10
//back right: 4, 5, 6
//back left: 12, 13, 14

//for the mapping of the values
int pwm[14]; //14 because of the pins (easier to remember)
int angle[14];

int timeDelay = 200; //milliseconds

void setup() {
  s.begin();
  s.setPWMFreq(60);
  delay(10);
  Serial.begin(9600);
}

void loop() {
  homePos();
  //forward(1);
  //backward(1);
}

//----------------backward---------------
void backward(int number){
  pos1b();
  delay(timeDelay);
  for(int i = 0; i < number; i++){
    step1b();
    delay(timeDelay);
    pos2b();
    delay(timeDelay);
    step2b();
    delay(timeDelay);
    pos3b();
    delay(timeDelay);
    step3b();
    delay(timeDelay);
    pos4b();
    delay(timeDelay);
    step4b();
    delay(timeDelay);
  }
}

void step4b(){
  //front right
  angle[8] = 230;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
  
  angle[9] = 69;
  angle[10] = 126;
  map_values(9);
  map_values(10);
  s.setPWM(9, 0, pwm[9]);
  s.setPWM(10, 0, pwm[10]);
  delay(200);

  angle[8] = 199;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
}

void pos4b(){
  //back right
  angle[6] = 119;
  angle[4] = 177;
  angle[5] = 55;

  //back left
  angle[14] = 108;
  angle[12] = 195;
  angle[13] = 62;

  //front right
  angle[2] = 141;
  angle[0] = 191;
  angle[1] = 59;

  //front left
  angle[10] = 144;
  angle[8] = 195;
  angle[9] = 96;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

void step3b(){
  //front right
  angle[4] = 230;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
  
  angle[5] = 69;
  angle[6] = 126;
  map_values(5);
  map_values(6);
  s.setPWM(5, 0, pwm[5]);
  s.setPWM(6, 0, pwm[6]);
  delay(200);

  angle[4] = 199;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
}

void pos3b(){
  //back right
  angle[6] = 94;
  angle[4] = 193;
  angle[5] = 60;

  //back left
  angle[14] = 141;
  angle[12] = 191;
  angle[13] = 59;

  //front right
  angle[2] = 109;
  angle[0] = 194;
  angle[1] = 62;

  //front left
  angle[10] = 119;
  angle[8] = 177;
  angle[9] = 55;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

void step2b(){
  //front right
  angle[0] = 235;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
  
  angle[1] = 64;
  angle[2] = 118;
  map_values(1);
  map_values(2);
  s.setPWM(1, 0, pwm[1]);
  s.setPWM(2, 0, pwm[2]);
  delay(200);

  angle[0] = 197;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
}

void pos2b(){
  //back right
  angle[6] = 85;
  angle[4] = 193;
  angle[5] = 60;

  //back left
  angle[14] = 148;
  angle[12] = 173;
  angle[13] = 55;

  //front right
  angle[2] = 140;
  angle[0] = 198;
  angle[1] = 86;

  //front left
  angle[10] = 153;
  angle[8] = 199;
  angle[9] = 73;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

void step1b(){
  //front right
  angle[12] = 235;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
  
  angle[13] = 77;
  angle[14] = 135;
  map_values(13);
  map_values(14);
  s.setPWM(13, 0, pwm[13]);
  s.setPWM(14, 0, pwm[14]);
  delay(200);

  angle[12] = 199;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
}

void pos1b(){
  //back right
  angle[6] = 119;
  angle[4] = 177;
  angle[5] = 55;

  //back left
  angle[14] = 108;
  angle[12] = 195;
  angle[13] = 62;

  //front right
  angle[2] = 141;
  angle[0] = 191;
  angle[1] = 59;

  //front left
  angle[10] = 126;
  angle[8] = 199;
  angle[9] = 69;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

//----------------forward---------------
void forward(int number){
  pos1();
  delay(timeDelay);
  for(int i = 0; i < number; i++){
    step1();
    delay(timeDelay);
    pos2();
    delay(timeDelay);
    step2();
    delay(timeDelay);
    pos3();
    delay(timeDelay);
    step3();
    delay(timeDelay);
    pos4();
    delay(timeDelay);
    step4();
    delay(timeDelay);
  }
}
  
void step4(){
  //front right
  angle[12] = 235;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
  
  angle[13] = 62;
  angle[14] = 108;
  map_values(13);
  map_values(14);
  s.setPWM(13, 0, pwm[13]);
  s.setPWM(14, 0, pwm[14]);
  delay(200);

  angle[12] = 195;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
}

void pos4(){
  //back right
  angle[6] = 119;
  angle[4] = 177;
  angle[5] = 55;

  //back left
  angle[14] = 135;
  angle[12] = 199;
  angle[13] = 77;

  //front right
  angle[2] = 141;
  angle[0] = 191;
  angle[1] = 59;

  //front left
  angle[10] = 126;
  angle[8] = 199;
  angle[9] = 69;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

void step3(){
  //front right
  angle[0] = 235;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
  
  angle[1] = 86;
  angle[2] = 140;
  map_values(1);
  map_values(2);
  s.setPWM(1, 0, pwm[1]);
  s.setPWM(2, 0, pwm[2]);
  delay(200);

  angle[0] = 198;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
}

void pos3(){
  //back right
  angle[6] = 85;
  angle[4] = 193;
  angle[5] = 60;

  //back left
  angle[14] = 148;
  angle[12] = 173;
  angle[13] = 55;

  //front right
  angle[2] = 118;
  angle[0] = 197;
  angle[1] = 64;

  //front left
  angle[10] = 153;
  angle[8] = 199;
  angle[9] = 73;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

void step2(){
  //front right
  angle[4] = 230;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
  
  angle[5] = 60;
  angle[6] = 94;
  map_values(5);
  map_values(6);
  s.setPWM(5, 0, pwm[5]);
  s.setPWM(6, 0, pwm[6]);
  delay(200);

  angle[4] = 193;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
}

void pos2(){
  //back right
  angle[6] = 126;
  angle[4] = 199;
  angle[5] = 69;

  //back left
  angle[14] = 141;
  angle[12] = 191;
  angle[13] = 59;

  //front right
  angle[2] = 109;
  angle[0] = 194;
  angle[1] = 62;

  //front left
  angle[10] = 119;
  angle[8] = 177;
  angle[9] = 55;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

void step1(){
  //front right
  angle[8] = 230;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
  
  angle[9] = 96;
  angle[10] = 144;
  map_values(9);
  map_values(10);
  s.setPWM(9, 0, pwm[9]);
  s.setPWM(10, 0, pwm[10]);
  delay(200);

  angle[8] = 195;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
}

void pos1(){
  //back right
  angle[6] = 119;
  angle[4] = 177;
  angle[5] = 55;

  //back left
  angle[14] = 108;
  angle[12] = 195;
  angle[13] = 62;

  //front right
  angle[2] = 141;
  angle[0] = 191;
  angle[1] = 59;

  //front left
  angle[10] = 126;
  angle[8] = 199;
  angle[9] = 69;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

void homePos(){
  //back right
  angle[6] = 124;
  angle[4] = 192;
  angle[5] = 59;

  //back left
  angle[14] = 124;
  angle[12] = 192;
  angle[13] = 59;

  //front right
  angle[2] = 124;
  angle[0] = 192;
  angle[1] = 59;

  //front left
  angle[10] = 124;
  angle[8] = 192;
  angle[9] = 59;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

// you have to change these values according to you motors
int map_values(int index){
  //front right
  if(index == 0)
    pwm[0] = map(angle[0], 20, 270, 550, 100);
  if(index == 1)
    pwm[1] = map(angle[1], 35, 325, 100, 680);
  if(index == 2)
    pwm[2] = map(angle[2], 35, 210, 130, 650);

  //front left
  if(index == 8)
    pwm[8] = map(angle[8], 20, 300, 100, 600);
  if(index == 9)
    pwm[9] = map(angle[9], 35, 320, 650, 100);
  if(index == 10)
    pwm[10] = map(angle[10], 45, 210, 650, 170);

  //back right
  if(index == 4)
    pwm[4] = map(angle[4], 40, 270, 180, 650);
  if(index == 5)
    pwm[5] = map(angle[5], 45, 320, 650, 100);
  if(index == 6)
    pwm[6] = map(angle[6], 85, 215, 650, 250);

  //back left
  if(index == 12)
    pwm[12] = map(angle[12], 20, 300, 650, 200);
  if(index == 13)
    pwm[13] = map(angle[13], 25, 325, 100, 650);
  if(index == 14)
    pwm[14] = map(angle[14], 80, 210, 100, 520);

  //return a value
  return pwm[index];
}