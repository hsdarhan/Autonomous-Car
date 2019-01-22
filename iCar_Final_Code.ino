  //Sepehr H, Ganesh Krishna, Harsimran
  //Monday January 15 2018
  //This program allows the iCar, a car built using an arduino microchip and LDR sensors, to navigate through a maze by distinguishing between electrical black tape (the line that the car must follow) and a white bristolboard surface.
  //Mr Wong
  
  //This enables the first pin, used for the left motor (wheel).
  int enablePin1 = 10;
  //This is the first pin used in the left wheel.
  int in1Pin1 = 7;
  //This is the second pin used in the left wheel.
  int in2Pin1 = 9;
  ////This enables the first pin, used for the right motor (wheel).
  int enablePin2 = 3;
  //This is the first pin used in the right wheel.
  int in1Pin2 = 4;
  //This is the second pin used in the right wheel.
  int in2Pin2 = 5;
  //This sets the left LDR as Analog 1 found on the Arduino.
  int LDR1 = A1;
  //This sets the middle LDR as Analog 2 found on the Arduino.
  int LDR2 = A2;
  //This sets the right LDR as Analog 3 found on the Arduino.
  int LDR3 = A3;
  //This is the maximum speed of the wheel which decides how fast the car will move straight, left, and right movements.
  int MAX_SPEED= 57;
  //This is the minimum speed of the wheel which decides how fast the car will move straight, left, and right movements.
  const int LOW_SPEED =55;
  //This variable is used to adjust the car back onto the black line incase the LDRs detect all white during the adjustment process.
  int temp=-1;
  //This is the counter used which acts as a timer for every instance that the car detects all white, so the car will know when it should make a counterclockwise spin back onto the path.
  int counter;
  
  //This method intializes all the pins for the motors as OUTPUT and all the pins for LDRs as INPUT.
  void setup()
  {
    Serial.begin(9600);  //  for debuging if needed
      
    //  Motor
    pinMode(in1Pin1, OUTPUT);
    pinMode(in2Pin1, OUTPUT);
    pinMode(enablePin1, OUTPUT);
    pinMode (LDR1, INPUT);
    pinMode (LDR2, INPUT);
    pinMode (LDR3, INPUT);
    pinMode(in1Pin2, OUTPUT);
    pinMode(in2Pin2, OUTPUT);
    pinMode(enablePin2, OUTPUT);
  }
  
  //This method moves the car straight by moving both the left and right motor forward simultaneously. 
  void straight(int durationInMilliSec)
  {
    analogWrite(enablePin1, MAX_SPEED);
    digitalWrite(in1Pin1, HIGH);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin1, LOW);  // CLOCKWISE (FAR LEFT BOTTOM CROSS)
    
    analogWrite (enablePin2, MAX_SPEED);
    digitalWrite(in1Pin2, HIGH);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin2, LOW);
      
  //  delay(durationInMilliSec);
  }
  
  
  //This method sets in1 and in2 to opposite values for each pin so that the car will move in reverse. This method is only used for CHECPOINT 1 (basic movements).
  void reverse(int durationInMilliSec)
  {
    analogWrite(enablePin1, MAX_SPEED);
    digitalWrite(in1Pin1, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin1, HIGH);  // CLOCKWISE (FAR LEFT BOTTOM CROSS)
    
    analogWrite (enablePin2, LOW_SPEED);
    digitalWrite(in1Pin2, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin2, HIGH);
      
    //delay(durationInMilliSec);
  }
  
  //This method sets all the pins to LOW so the motors will not operate. 
  void park (int durationInMilliSec)
  {
    analogWrite(enablePin1, MAX_SPEED);
    digitalWrite(in1Pin1, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin1, LOW);  // CLOCKWISE (FAR LEFT BOTTOM CROSS)
    
    analogWrite (enablePin2, MAX_SPEED);
    digitalWrite(in1Pin2, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin2, LOW);
      
    //delay(durationInMilliSec);
  }
  
  //This method spins the car on the spot and is called whenever the LDRs detect all white, so it can go back to completing the maze. 
  void spinRight (int durationInMilliSec)
  {
    analogWrite(enablePin2, 88);
    digitalWrite(in1Pin2, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin2,HIGH);  // CLOCKWISE (FAR LEFT BOTTOM CROSS)
    analogWrite(enablePin1, 88);
    digitalWrite(in1Pin1, HIGH);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin1, LOW);  // ANTI-CLOCKWISE
    
    delay(durationInMilliSec);
  }
  
  void spinLeft ()
  {
    analogWrite(enablePin2, 88);
    digitalWrite(in1Pin2, HIGH);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin2, LOW);  // CLOCKWISE (FAR LEFT BOTTOM CROSS)
    analogWrite(enablePin1, 88);
    digitalWrite(in1Pin1, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin1, LOW);  // ANTI-CLOCKWISE
  }
  
  //This method turns the car right by moving the right motor forward and the left motor back. This means that the car will turn right on its current position.
  void turnRight(int durationInMilliSec)
  {
    analogWrite(enablePin2, 99);
    digitalWrite(in1Pin2, HIGH);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin2,LOW);  // CLOCKWISE (FAR LEFT BOTTOM CROSS)
    analogWrite(enablePin1, 79);
    digitalWrite(in1Pin1, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin1, HIGH);  // ANTI-CLOCKWISE
    temp=1;
    
    delay(durationInMilliSec);
  }
  
  //This method turns the car left by moving the left motor forward and the right motor back. This means that the car will turn left on its current position.
  void turnLeft(int durationInMilliSec)
  {
    analogWrite(enablePin1, 75);
    digitalWrite(in1Pin1, HIGH);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin1, LOW);
    analogWrite(enablePin2, 75);
    digitalWrite(in1Pin2, LOW);    //   HIGH/LOW values have to be adjusted
    digitalWrite(in2Pin2,HIGH); 
    temp=2;
    delay(durationInMilliSec);
  }
  
  //This boolean function takes in the pass parameter numLDR which is used to distinguish between each LDR that the LDRS will use. If the method returns true, then it means the LDR inputted is detecting black (less than threshhold value means black) and if the method returns false, then the LDR inputted is detecting white (higher than threshold value means white).
  boolean check(int numLDR)
  {
    if (numLDR==1)
    {
      if (analogRead (LDR1) < 450)
        return false;
       else
        return true;
    }
    
    else if (numLDR==2)
    {
      if (analogRead (LDR2) < 500)
        return false;
       else
        return true;
    }
    else if (numLDR==3)
    {
      if (analogRead (LDR3) < 120)
        return false;
       else
        return true;
    }
    return false;
  }
  
  //This method controls the movement of the car depending on the LDR readings which are processed through the check(int x) method, for each separate case. If all the sensors are black, then the car will turn right. If all the sensors are white, then the car will spin counterclockwise. If the middle sensor is black while the left and right sensors are white, then the car will move straight. If the left and middle are white, while the left is black, then the car will move left and vice versa for right. The counter variable used in all white acts as a timer that records how long the car is on all white, so that the car will know when to spin. This counter is used incase the sensors read all white while it should be going straight, then the car will not spin as it should when it reaches the end of a path.  
  void LDRtest ()
  {
    
    if (check(1)==true && check(2)==false && check(3)==true)
    {
      straight (2);
      counter=0;
    }
   
    else if (check(1)==false && check(2)==true && check(3)==true)
    {
      turnLeft (2);
    }
    else if (check(1)==true && check(2)==false && check(3)==false)
    {
      turnRight (15);
    }
    else if (check(1)==true && check(2)==true && check(3)==false)
    {
      turnRight (15);
    }
    else if (check(1)==false && check(2)==false && check(3)==false)
    {
      turnRight(0);
    }
    else if (check(1)== false && check(2)==false && check(3)==true)
    {
      straight(1);
    }
   else if (check(1)== true && check(2)==true && check(3)==true)
    {
   counter++;
   
   if (counter>5 && counter<30)
   {
     park (0);
   }
   else if (counter > 30)
   {
     park(1000);
     spinRight(0);
   }
   else
   {
      if (temp==1)
      {
      turnRight (15);
      }
      else if (temp==2)
      {
      turnLeft (15);
      }
      else
      {
      turnRight (15);
      temp=-1;
      }
    }  
   }
  }
  
  //This method is a loop which constantly calls LDRtest() so that for each instance that the code is running it will check the position of the car, and what action it should take. 
  void loop()
  {
  LDRtest (); 
  }
  
  

