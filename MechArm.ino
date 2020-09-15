#include <Servo.h>

const int servo1 = 10;      //servo#1 to digital 10~
const int servo2 = 11;      //servo#2 to digital 11~
const int servo3 = 9;       //servo#3 to digital 9~
const int servo4 = 3;       //servo#4 to digital 3~
const int joyB = 2;         //SW(switch) to digital 2
const int joyH = A4;        //x axis to A4
const int joyV = A3;        //y axis to A3
const int butt1 = 7;        //button1 to digital 7
const int butt2 = 8;        //button2 to digital 8

int servoVal;
int angle =90;              //establishes the position of the base
int anglestep =10;          // increment the base rotates
const int minAngle = 0;
const int maxAngle = 180;

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

void setup() {
  // Servo
  myservo1.attach(servo1);
  myservo2.attach(servo2);
  myservo3.attach(servo3);
  myservo4.attach(servo4);
  pinMode(joyB, INPUT_PULLUP);
  pinMode(butt1, INPUT_PULLUP);
  pinMode(butt2, INPUT_PULLUP);
  myservo4.write(angle);                                // initialize at angle

  // Initialize Serial
  Serial.begin(9600);
  
}

void loop() {
  //Display Joystick values using the serial monitor
  outputJoystick();

  // Read the horizontal joystick value (between 0 and 1023)
  servoVal = analogRead(joyH);                              // read the value given by the positioning of the joystick
  servoVal = map(servoVal, 0, 1023, 200, 50);               // scale it to use with the servo (result between 0 and 180);

  myservo1.write(servoVal);                                 // sets the servo postion according to the scaled value

  //Read the vertical joystick value (value between 0 and 1023)
  servoVal = analogRead(joyV);
  servoVal = map(servoVal, 0, 1023, 230, 50);

  myservo2.write(servoVal);

  //Read the button joystick
  servoVal = digitalRead(joyB);
  if(servoVal == LOW){
   myservo3.write(130);
  }
  else{
   myservo3.write(180);
  }
  
   //button 1 (incrementing angle)
   servoVal = digitalRead(butt1);
   if(servoVal == HIGH && angle <= maxAngle) {
    angle = angle + anglestep;
   }
   myservo4.write(angle);

   //button 2 (decreasing angle)
   servoVal = digitalRead(butt2);
   if(servoVal == HIGH && angle >= minAngle) {
    angle = angle - anglestep;
   }
   myservo4.write(angle);
   
 

  delay(50);
}


/**
* Display joystick values
*/
void outputJoystick(){

    Serial.print(analogRead(joyH));
    Serial.print ("---"); 
    Serial.print(analogRead(joyV));
    Serial.println ("----------------");
    Serial.print(digitalRead(joyB));
    Serial.print ("-------");
}
