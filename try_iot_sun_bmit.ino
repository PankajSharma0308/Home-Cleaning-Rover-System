
#define speed_fast 255

const int r_motor[3] = {15,14,13};                                   // [EN1, IN1, IN2]
const int l_motor[3] = {10,12,11};                                   // [EN2, IN3, IN4]
const int ultrasonic1[2] = {1,0};                               // TriggerPin 1, EchoPin 0
const int ultrasonic2[2] = {3,2};                               // TriggerPin 3, EchoPin 2

long duration[2] = {0,0};
long distance[2] = {0,0};

void setup() {
  
  // put your setup code here, to run once:
  
    pinMode(r_motor[1],OUTPUT);                                   // Sets right_motor_forward as output
    pinMode(r_motor[2],OUTPUT);                                   // Sets right_motor_backward as output
    pinMode(l_motor[1],OUTPUT);                                   // Sets left_motor_forward as output
    pinMode(l_motor[2],OUTPUT);                                   // Sets left_motor_bacakward as output

    pinMode(ultrasonic1[0], OUTPUT);                       // Sets the trigPin as an Output
    pinMode(ultrasonic1[1], INPUT);                        // Sets the echoPin as an Input

    pinMode(ultrasonic2[0], OUTPUT);                       // Sets the trigPin as an Output
    pinMode(ultrasonic2[1], INPUT);                        // Sets the echoPin as an Input

    Serial.begin(9600);                                           // Starts the serial communication


}

void loop() {

//  put your main code here, to run repeatedly:

  digitalWrite(ultrasonic1[0], LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(ultrasonic1[0], HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(ultrasonic1[0], LOW);

    
  duration[0] = pulseIn(ultrasonic1[1], HIGH);
  distance[0] = duration[0] * 0.01723 / 2;                        //  inches = 0.01723 * distance;
  

  Serial.print("======\nDistance FOR: ");
  Serial.println(distance[1]);

  
  digitalWrite(ultrasonic2[0], LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonic2[0], HIGH);
  delayMicroseconds(2);
  digitalWrite(ultrasonic2[0], LOW);

  duration[1] = pulseIn(ultrasonic2[1], HIGH);
  distance[1] = duration[1] * 0.01723 / 2;                        //  inches = 0.01723 * distance;
  
  Serial.print("\nDistance BACK: ");
  Serial.println(distance[0]);

  if(distance[0] > 10)
   { 
      analogWrite(r_motor[0], speed_fast);
      analogWrite(l_motor[0], speed_fast);
      moveForward();
   }
   else if(distance[0] > 5 && distance[0] < 10)
   {
      analogWrite(r_motor[0], speed_fast);
      analogWrite(l_motor[0], speed_fast);
      moveBackward();

      if(distance[1] > 5)
      { 
          analogWrite(r_motor[0], speed_fast);
          analogWrite(l_motor[0], speed_fast);
          moveBackward();
      }
      else
      {
        moveStop();  
      }
   }
   else
   {
      moveStop(); 
   }
}

/*  ...................................  FUNCTIONS  .................................... */

void moveStop()                                                 // Move Stop Function for Motor Driver.
{
  digitalWrite(r_motor[1], LOW);
  digitalWrite(r_motor[2], LOW);
  digitalWrite(l_motor[1], LOW);
  digitalWrite(l_motor[2], LOW);
}

void moveForward()                                              // Move Forward Function for Motor Driver.
{
  digitalWrite(r_motor[1], HIGH);
  digitalWrite(r_motor[2], LOW);
  digitalWrite(l_motor[1], HIGH);
  digitalWrite(l_motor[2], LOW);
}

void moveBackward()                                             // Move Forward Function for Motor Driver.
{
  digitalWrite(r_motor[1], LOW);
  digitalWrite(r_motor[2], HIGH);
  digitalWrite(l_motor[1], LOW);
  digitalWrite(l_motor[2], HIGH);
}
