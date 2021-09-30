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

//ultrasonic sensor pins and other variables
int trigPin = 3;
int echoPin = 2;

float duration_us1, duration_us2, distance_cm, distance_down, distance_up;
float duration[10];
float left_side, right_side;
int number;

boolean side = true; //true = left, false = right
boolean down = true;

void setup() {
  s.begin();
  s.setPWMFreq(60);
  delay(10);
  Serial.begin(9600);
  delay(1000);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  duration_us1 = 0;
  homePos();
  delay(50);
  setUltrasonicSensor(45, 0);
  delay(200);

  distance_down = getDistance();
  Serial.print("distance_down: ");
  Serial.println(distance_down);
  
  if(distance_down > 24){
    forward(1);
    Serial.println("forward");
  }else{
    setUltrasonicSensor(90, 0);
    delay(200);
    distance_up = getDistance();
    Serial.print("distance_up: ");
    Serial.println(distance_up);
    if(distance_up < 47){
      backward(1);
      Serial.println("backward");
      delay(100);
      getSide();
      turn();
    }
  }
}

//----------------ultrasonic------------
void turn(){
  if(side == true){
    left(3);
  }else{
    right(3);
  }
}

void getSide(){
  setUltrasonicSensor(90, 65);
  delay(200);
  left_side = getDistance();
  Serial.print("left_side: ");
  Serial.println(left_side);
  delay(100);
  setUltrasonicSensor(90, -80);
  delay(200);
  right_side = getDistance();
  Serial.print("right_side: ");
  Serial.println(right_side);
  delay(100);
  if(right_side < left_side){
    side = true; //turn right
  }else{
    side = false; //turn left
  }
}

float getDistance(){
  delay(300);
  for(int i = 0; i < 10; i++){
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration[i] = pulseIn(echoPin, HIGH);
  }

  number = 0;

  for(int i = 0; i < 10; i++){
    if((duration[i] < 29400) || (duration[i] > 0)){
      duration_us1 +=duration[i];
      number++;
    }
  }
  
  //create the middle value
  duration_us2 = duration_us1 / number;

  // calculate the distance
  distance_cm = 0.017 * duration_us2;
  
  return distance_cm;
}

void setUltrasonicSensor(int angle7, int angle3){
  //ultrasonic sensor
  angle[7] = angle7;
  angle[3] = angle3;

  for(int i = 3; i < 8; i++){
    map_values(i);
  }

  for(int i = 3; i < 8; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

//----------------left side-------------
void left(int number){
  for(int i = 0; i < number; i++){
    homePos();
    delay(timeDelay);
    step4sr();
    delay(timeDelay);
    step3sr();
    delay(timeDelay);
    step2sr();
    delay(timeDelay);
    step1sr();
    delay(timeDelay);
  }
}

void step4sr(){
  //front right
  angle[4] = 230;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
  
  angle[5] = 59;
  angle[6] = 94;
  map_values(5);
  map_values(6);
  s.setPWM(5, 0, pwm[5]);
  s.setPWM(6, 0, pwm[6]);
  delay(200);

  angle[4] = 192;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
}

void step3sr(){
  //front right
  angle[8] = 230;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
  
  angle[9] = 59;
  angle[10] = 94;
  map_values(9);
  map_values(10);
  s.setPWM(9, 0, pwm[9]);
  s.setPWM(10, 0, pwm[10]);
  delay(200);

  angle[8] = 192;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
}

void step2sr(){
  //front right
  angle[12] = 235;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
  
  angle[13] = 59;
  angle[14] = 154;
  map_values(13);
  map_values(14);
  s.setPWM(13, 0, pwm[13]);
  s.setPWM(14, 0, pwm[14]);
  delay(200);

  angle[12] = 192;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
}

void step1sr(){
  //front right
  angle[0] = 235;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
  
  angle[1] = 59;
  angle[2] = 154;
  map_values(1);
  map_values(2);
  s.setPWM(1, 0, pwm[1]);
  s.setPWM(2, 0, pwm[2]);
  delay(200);

  angle[0] = 192;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
}


//----------------right side------------
void right(int number){
  for(int i = 0; i < number; i++){
    homePos();
    delay(timeDelay);
    step1sl();
    delay(timeDelay);
    step2sl();
    delay(timeDelay);
    step3sl();
    delay(timeDelay);
    step4sl();
    delay(timeDelay);
  }
}

void step4sl(){
  //front right
  angle[4] = 230;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
  
  angle[5] = 59;
  angle[6] = 154;
  map_values(5);
  map_values(6);
  s.setPWM(5, 0, pwm[5]);
  s.setPWM(6, 0, pwm[6]);
  delay(200);

  angle[4] = 192;
  map_values(4);
  s.setPWM(4, 0, pwm[4]);
  delay(200);
}

void step3sl(){
  //front right
  angle[8] = 230;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
  
  angle[9] = 59;
  angle[10] = 154;
  map_values(9);
  map_values(10);
  s.setPWM(9, 0, pwm[9]);
  s.setPWM(10, 0, pwm[10]);
  delay(200);

  angle[8] = 192;
  map_values(8);
  s.setPWM(8, 0, pwm[8]);
  delay(200);
}

void step2sl(){
  //front right
  angle[12] = 235;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
  
  angle[13] = 59;
  angle[14] = 94;
  map_values(13);
  map_values(14);
  s.setPWM(13, 0, pwm[13]);
  s.setPWM(14, 0, pwm[14]);
  delay(200);

  angle[12] = 192;
  map_values(12);
  s.setPWM(12, 0, pwm[12]);
  delay(200);
}

void step1sl(){
  //front right
  angle[0] = 235;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
  
  angle[1] = 59;
  angle[2] = 94;
  map_values(1);
  map_values(2);
  s.setPWM(1, 0, pwm[1]);
  s.setPWM(2, 0, pwm[2]);
  delay(200);

  angle[0] = 192;
  map_values(0);
  s.setPWM(0, 0, pwm[0]);
  delay(200);
}

//----------------backward--------------
void backward(int number){
  for(int i = 0; i < number; i++){
    pos1b();
    delay(timeDelay);
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
    homePos();
    delay(timeDelay * 5);
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
  for(int i = 0; i < number; i++){
    pos1();
    delay(timeDelay);
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
    homePos();
    delay(timeDelay * 5);
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

  //ultrasonic sensor
  angle[7] = 90;
  angle[3] = 0;

  for(int i = 0; i < 15; i++){
    map_values(i);
  }

  for(int i = 0; i < 15; i++){
    s.setPWM(i, 0, pwm[i]);
  }
}

// you probably have to change these values according to your motors
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

  //ultrasonic sensor
  if(index == 7)
    pwm[7] = map(angle[7], 45, 200, 100, 600);
  if(index == 3)
    pwm[3] = map(angle[3], -90, 65, 170, 650);

  //return a value
  return pwm[index];
}