#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2  //changed from 2 to 1
#define IN4 7

#define carSpeed 200  //Set the carSpeed to 200

int turnTime = 650;



// Define the commands
enum Command {
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_FORWARD,
  MOVE_BACK,
  STOP
};

// List of commands to be executed
Command commands[] = {
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_RIGHT,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_RIGHT,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_RIGHT,
  STOP,
  STOP,
  STOP,
  MOVE_LEFT,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_FORWARD,
  MOVE_RIGHT,
  MOVE_FORWARD,
  MOVE_FORWARD
};

// Pins and variables for the MQ-2 smoke sensor and the buzzer
int mq2SensorPin = A4;
int buzzerPin = A3;
int smokeLimit = 15;
int fireLimit = 500;

void setup() {
  Serial.begin(9600);
  pinMode(mq2SensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  executeCommands();
}

void executeCommands() {
  for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
    smokeAlarm();
    switch (commands[i]) {
      case MOVE_LEFT:
        left();
        delay(turnTime);
        stop();
        delay(200);
        break;
      case MOVE_RIGHT:
        right();
        delay(turnTime);
        stop();
        delay(200);
        break;
      case MOVE_FORWARD:
        forward();
        delay(500);
        stop();
        delay(200);
        break;
      case MOVE_BACK:
        back();
        delay(500);
        stop();
        delay(200);
        break;
      case STOP:
        stop();
        delay(1000);
    }
  }
}

const int sensorMin = 0;     //  sensor minimum
const int sensorMax = 1024;  // sensor maximum

void smokeAlarm() {
  int fireSensorValue = analogRead(A5);
  Serial.println("Fire sensor value:");
  Serial.println(fireSensorValue);


  int sensorValue = analogRead(mq2SensorPin);
  Serial.println(sensorValue);  // Optional: Print the sensor value

  if (sensorValue > smokeLimit) {
    alarm();  // If smoke is detected (value is above the limit), sound the buzzer
  } else {
    noTone(buzzerPin);  // Otherwise, stop the buzzer sound
  }

  if (fireSensorValue < fireLimit) {
    fireAlarm();
  } else {
    noTone(buzzerPin);
  }
  delay(100);
}

void alarm() {
  tone(buzzerPin, 2000, 200);
  delay(100);
  tone(buzzerPin, 1500, 200);
  delay(100);
  noTone(buzzerPin);  // Stop sound
  delay(100);         // Wait for 100ms
  tone(buzzerPin, 2000, 200);
  delay(100);
  tone(buzzerPin, 1500, 200);
  delay(100);
  noTone(buzzerPin);  // Stop sound
  delay(100);         // Wait for 100ms
  tone(buzzerPin, 2000, 200);
  delay(100);
  tone(buzzerPin, 1500, 200);
  delay(100);
  noTone(buzzerPin);  // Stop sound
  delay(100);         // Wait for 100ms
}

void fireAlarm() {
  tone(buzzerPin, 1200, 1000);
  delay(800);
  tone(buzzerPin, 3000, 1000);
  delay(800);
  tone(buzzerPin, 1200, 1000);
  delay(800);
  tone(buzzerPin, 3000, 1000);
  delay(800);
  tone(buzzerPin, 1200, 1000);
  delay(800);
  tone(buzzerPin, 3000, 1000);
  delay(800);
  tone(buzzerPin, 1200, 1000);
  delay(800);
  tone(buzzerPin, 3000, 1000);
  delay(800);

}


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

  Serial.println("Forward");
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
  Serial.println("Back");
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

  Serial.println("Left");
}

void right() {                 //right function
  analogWrite(ENA, carSpeed);  //Set the speed of ENA
  analogWrite(ENB, carSpeed);  //Set the speed of ENB
  //The right back
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //The left forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Right");
}

void stop() {              //stop function
  digitalWrite(ENA, LOW);  //Set the speed of ENA to low
  digitalWrite(ENB, LOW);  //Set the speed of ENB to low
  Serial.println("Stop!");
}