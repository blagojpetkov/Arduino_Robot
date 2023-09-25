
#include <Servo.h>
#define Trig 12 //Pin Tring connects to D12
#define Echo 13 //Pin Echo connects to D13
float cm; //Distance variable


int ENA = 5; 
int IN1 = 3; 
int IN2 = 4;

int ENB = 6; 
int IN3 = 2;
int IN4 = 7;

int Sensor1 = A1;//pin A1
int Sensor2 = A2;//pin A2

int SensorLeft;
int SensorRight;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup()
{
    myservo.attach(A0);  // attaches the servo on pin 9 to the servo object
    //Set the pin mode
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    pinMode(Sensor1, INPUT);
    pinMode(Sensor2, INPUT);
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
    Serial.begin(9600);
    myservo.write(100); 
}

void loop()
{
    cm = GetDistance();

    SensorLeft  =  digitalRead(Sensor1);//The sensor on the left
    SensorRight =  digitalRead(Sensor2);//The sensor on the Right
    
    // If the right sensor detects the signal, the left sensor does not detect the signal, 
    // the ultrasonic detection of the obstacle distance between 5cm to 20cm, turn to the right
    if (SensorLeft == HIGH && SensorRight == LOW && ( cm > 7 && cm < 20))
    {
        right();
    }
    else if(SensorLeft == LOW && SensorRight == HIGH&& ( cm > 7 && cm < 20))
    {
        left();
    }
    else  if(SensorLeft == HIGH && SensorRight == HIGH&&( cm > 11 && cm <20))
    {
        forward();
    }
    else if(SensorLeft == HIGH && SensorRight == HIGH && ( cm >30 || cm < 3))
    {
        stop();
    }
    else if(cm < 7 && cm > 0)
    {
        back();
    }

    if (SensorLeft == LOW)
    {
        myservo.write(180); 
    }
    else if (SensorRight == LOW)
    {
        myservo.write(60); 
    }
    else 
    {
        myservo.write(135); 
    }
    
}

/*
Function: obtain ultrasonic sensor ranging data
Parameters: Trig, Echo
Parameter description: sensor connected to the motherboard pin port A4,A5
Trig -------> pin D12
Echo -------> pin D13
*/
float GetDistance()
{
    float distance;
    // Send a low short pulse to Trig to trigger the ranging
    digitalWrite(Trig, LOW); //Send a low level to Trig
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    distance = pulseIn(Echo, HIGH) / 58.00;
    
    //Serial.print("Distance = ");
    //Serial.println(distance);//The serial output distance is converted into cm

	  return distance;
}

//turn left
void left(){
  //Set the speed of the motor
    analogWrite(ENA, 180);
    analogWrite(ENB, 180);
    //The right forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //The left STOP
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    Serial.println("left");
  }
//turn right
 void right(){
    //Set the speed of the motor
   analogWrite(ENA, 180);
   analogWrite(ENB, 180);
    //The right stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  //The left forward
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
     Serial.println("right");
  }
//turn forward
 void forward(){
    //FORWARD
    //Set the speed of the motor
     analogWrite(ENA, 200);
     analogWrite(ENB, 200);
     //The right forward
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2,LOW);
     //The left forward
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     Serial.println("forward");
  }

//stop
 void stop(){
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  //set IN1,IN2,IN3,IN4 to LOW
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
     Serial.println("stop");
  
  }
  //back up
   void back(){
    //Set the speed of the motor    
     analogWrite(ENA, 200);
     analogWrite(ENB, 200);
     //The right back
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, HIGH);
     //The left back
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
     Serial.println("back");
  }
