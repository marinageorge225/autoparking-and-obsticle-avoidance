#include <NewPing.h>
#include <Servo.h>


int enA = 2;
int enB = 7;
const int in1 = 3;
const int in2 = 4;
const int in3 = 5;
const int in4 = 6;

// Definitions for Mode 1
#define trigPin1 A1
#define echoPin1 A2
#define trigPin2 11 
#define echoPin2 10 
#define trigPin3 13
#define echoPin3 12
#define S 125
int space = 0;

// Definitions for Mode 2
#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trigPin1, echoPin1, maximum_distance); //sensor function
Servo servo_motor; //our servo name

// Button to switch modes
const int modeButtonPin = 9; 
boolean mode = false; // false for Mode 0, true for Mode 1

// Mode 1 and Mode 2 function prototypes
void Stop();
void MoveForward();
void MoveLeft();
void MoveBack();
void MoveRight();
int UFun(int triger, int echo);
void Park();
int Check();
void MoveBackFirst();

void setup() {
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Setup for Mode 1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  // Setup for Mode 2
  servo_motor.attach(8); 
  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);

  // Setup for mode button
  pinMode(modeButtonPin, INPUT_PULLUP); // pull-up button configuration
}

void loop() {
  // Check the button state and switch modes
  mode = digitalRead(modeButtonPin);

  if (mode == false) {
    Serial.println("Mode 0");
    // Mode 1 operations
    delay(2000);
    Serial.println("space 2bl");
    Serial.println(space);
    if (Check()==1&& space>35){//after trial and error to check the right value ,it's varied by the speed
      Serial.println("space ba3ddd");
      Serial.println(space);
      space=0;
      Stop();
      Serial.println("w2fnaa bs braaaaa");
      delay(1000);
      Park();
      exit(0);
      }
    else {
      if(UFun(trigPin1,echoPin1)>4&&UFun(trigPin3,echoPin3)>4)
      {
        Serial.println(" Forward Ultra odammm");
        Serial.println(UFun(trigPin1,echoPin1));
        Serial.println(" Forward Ultra wraaaaa");
        Serial.println(UFun(trigPin3,echoPin3));
        MoveForward();
      }
      else{
        Serial.println("w2fnaa");
        Stop();
        }
      }
  } else {
    // Mode 2 operations
    Serial.println("Mode 1");
    int distanceRight = 0;
    int  distanceLeft = 0;
    delay(50);
  
    if (distance <= 20){
      moveStop();
      delay(300);
      moveBackward();
      delay(400);
      moveStop();
      delay(300);
      distanceRight = lookRight();
      delay(300);
      distanceLeft  = lookLeft();
      delay(300);
  
      if (distance >= distanceLeft){
        turnRight();
        moveStop();
      }
      else{
        turnLeft();
        moveStop();
      }
    }
    else{
      moveForward(); 
    }
      distance = readPing();
  }
}

// Mode 1 and Mode 2 functions
void Park(){//Parking algorithm
  MoveBackFirst();
  delay(1000);
  Stop();
  delay(2000);
  MoveLeft();
  delay(1500);
  int distanceBack;
  bool i = true;
  while(i==true){
    distanceBack = UFun(trigPin1,echoPin1);
    if(distanceBack>8){
      MoveBack();
    }
    else{
      i = false;
    }
  }
  Stop();
  delay(2000);
  MoveRight();
  delay(1600);
  Stop();
 
  }
int Check(){//Chicking the sutable parking space for the car width
  int Flag =0;
  while(UFun(trigPin2,echoPin2)>15){
    Serial.println("da sensor ymeeen");
    Serial.println(UFun(trigPin2,echoPin2));
    MoveForward();
    space++;
    Flag =1;
    }
  return Flag;
  }
int UFun(int triger , int echo){//ultrasonic reading 
   long duration ;
   int distance;
        digitalWrite(triger,LOW);
        delayMicroseconds(2);
        digitalWrite(triger, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger,LOW);
    
        duration = pulseIn(echo,HIGH);
        distance = duration/2 /29.1 ; // 331.5 m/s ===> 0 C.....331.5 +0.6*temp....343.5*100/1000000=.03435cm/us
  return distance; 
  
  }

void MoveBackFirst(){
  // Turn on motor A
      
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
      
      
        analogWrite(enA, S-25);
      
        // Turn on motor B
      
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      
      
        analogWrite(enB, S-25);
  
  
  }
  
void MoveBack(){
  // Turn on motor A
  
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
      
      
        analogWrite(enA, S+100);
      
        // Turn on motor B
      
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      
      
        analogWrite(enB, S+100);
  
  
  }
void MoveLeft(){

  // Turn on motor A

  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);


  analogWrite(enA, S);

  // Turn on motor B

  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);

  analogWrite(enB, S);

  

  }
void MoveRight(){
      
    // Turn on motor A

  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);

  analogWrite(enA, S-10);

  // Turn on motor B

  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);

  analogWrite(enB, S-10);


     }
void Stop(){
  // Now turn off motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  }
void MoveForward() {
    // Turn on motor A

  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);

  analogWrite(enA, S);

  // Turn on motor B

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, S);


}

// functions for Mode 2
int  lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance =  readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int  lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int  readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in3,  LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in4,  LOW);
  digitalWrite(in2, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    
    digitalWrite(in1,  HIGH);
    digitalWrite(in3, HIGH);
  
    digitalWrite(in2,  LOW);
    digitalWrite(in4, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(in2, HIGH);
  digitalWrite(in4,  HIGH);
  
  digitalWrite(in1, LOW);
  digitalWrite(in3,  LOW);
  
}

void turnRight(){

  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(in1,  HIGH);
  digitalWrite(in4, HIGH);
  
  digitalWrite(in2,  LOW);
  digitalWrite(in3, LOW);
  
  delay(500);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  
  digitalWrite(in2, LOW);
  digitalWrite(in4,  LOW);
 
  
  
}

void turnLeft(){

  analogWrite(enA, 255);
  analogWrite(enB, 255);
  
  digitalWrite(in2,  HIGH);
  digitalWrite(in3, HIGH);
  
  digitalWrite(in1,  LOW);
  digitalWrite(in4, LOW);

  delay(500);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  
  digitalWrite(in2, LOW);
  digitalWrite(in4,  LOW);
}