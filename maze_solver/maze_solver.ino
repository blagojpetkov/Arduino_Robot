// #include <Servo.h>  //servo library
// Servo myservo;      // create servo object to control servo


int Echo = 13;  //Pin to D13
int Trig = 12;  //Pin to D12


#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2  //changed from 2 to 1
#define IN4 7


#define carSpeed 200  //Set the carSpeed to 200
int Sensor1;
int Sensor2;
int Sensor3;
int Sensor4;
// int soundSensorPin = 2;
int turnTime = 600;
int SensorLeft;
int SensorRight;
int rightDistance = 0, leftDistance = 0, middleDistance = 0;
int turnDistance = 20;
// bool canMove = false;
// unsigned long lastSoundTime = 0;
// const unsigned long debounceTime = 300;

void forward() {  //forward function
  // if (!canMove) { return; } // TODO
  analogWrite(ENA, carSpeed);  //Set the speed of ENA
  analogWrite(ENB, carSpeed);  //Set the speed of ENB
    //The right forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //The left forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Serial.println("Forward");
}

void back() {                  //back function
  analogWrite(ENA, carSpeed);  //Set the speed of ENA
  analogWrite(ENB, carSpeed);  //Set the speed of ENB
  //The rihgt back
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //The left back
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Serial.println("Back");
}

void left() {                  //left function
  analogWrite(ENA, carSpeed);  //Set the speed of ENA
  analogWrite(ENB, carSpeed);  //Set the speed of ENB
                               //The right forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //The left back
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // Serial.println("Left");
}

void right() {                 //right function
  analogWrite(ENA, carSpeed);  //Set the speed of ENA
  analogWrite(ENB, carSpeed);  //Set the speed of ENB
  //The rihgt back
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //The left forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Serial.println("Right");
}

void stop() {              //stop function
  digitalWrite(ENA, LOW);  //Set the speed of ENA to low
  digitalWrite(ENB, LOW);  //Set the speed of ENB to low
  // Serial.println("Stop!");
}

float GetDistance() {
  float distance;
  // Send a low short pulse to Trig to trigger the ranging
  digitalWrite(Trig, LOW);  //Send a low level to Trig
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  distance = pulseIn(Echo, HIGH) / 58.00;
  Serial.print("Distance = ");
  Serial.println(distance);  //The serial output distance is converted into cm
  return distance;
}

// void toggleCanMove() {
// unsigned long currentMillis = millis();
// if (currentMillis - lastSoundTime > debounceTime) {
// canMove = !canMove;
// lastSoundTime = currentMillis;
// }
// }

void setup() {
  // myservo.attach(A0, 700, 2400);  // attach servo on pin 3 to servo object
  Serial.begin(9600);

  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // tracking pins
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  // pinMode(soundSensorPin, INPUT);
  // attachInterrupt(digitalPinToInterrupt(soundSensorPin), toggleCanMove, RISING);  // Attach an interrupt to pin 2
  stop();
  delay(100);
}

void loop() {

  // if(!canMove){
  // stop();
  // }

  SensorLeft = digitalRead(A1);   //The sensor on the left
  SensorRight = digitalRead(A2);  //The sensor on the Right

  middleDistance = GetDistance();  //getDistance();
  // Serial.println(middleDistance);
  // !SensorX means that there is something blocking the X sensor

  if (middleDistance <= turnDistance && middleDistance > 0 && SensorLeft && !SensorRight) {
    // No wall on left, wall on front, wall on right
    // Turning left
    // Serial.println("Turning left");
    stop();
    delay(500);
    left();
    delay(turnTime);
    stop();
    delay(1000);
    forward();
    delay(250);
  } else if (middleDistance <= turnDistance && middleDistance > 0 && !SensorLeft && SensorRight) {
    // Wall on left, wall on front, no wall on right
    // Turning right
    // Serial.println("Turning right");
    stop();
    delay(500);
    right();
    delay(turnTime);
    stop();
    delay(1000);
    forward();
    delay(250);
  } else if (middleDistance <= turnDistance && middleDistance > 0 && !SensorLeft && !SensorRight) {
    // Wall on left, wall on front, wall on right
    stop();
    delay(500);
  } else {
    Sensor1 = digitalRead(8);
    Sensor2 = digitalRead(9);
    Sensor3 = digitalRead(10);
    Sensor4 = digitalRead(11);
    if(Sensor1  == HIGH || Sensor2  == HIGH || Sensor3  == HIGH || Sensor4 == HIGH){
      stop();
      delay(50000);
    }
    else{
      forward();
      delay(100);
    }
  }
}