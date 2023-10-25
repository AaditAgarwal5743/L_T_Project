/* This program controls the orientation of s solar panel to face the sun. 
This will mean the solar panel will produce power at maximum efficiency. 
It does this by comparing how much light is hitting the top and bottom of the solar panel rotating the solar panel on the x-axis towards the light.
The light will be detected by light-dependent resisotors (LDR.
The same happens for the left and right-hand sides of the panel and rotating the solar panel in the z-axis. 
The tolerance between the sensors can be adjusted by a variable resistor to prevent the solar panel constantly trying to face the sun. 
The tolerance value is displayed on an LCD display.*/

// Revisons:

// Load in libary for the liquid crystal display
#include <LiquidCrystal.h> 
// load in libary for the servo motors
#include <Servo.h>

void UpDown();// initialize the functon to move the sensor up and down
void LeftRight();// initialize the functon to move the sensor up and down

Servo servo1;
Servo servo2;

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set up loop
void setup() {
  
  lcd.begin(16, 2); // Initialize the LCD with 16 characters long on each line and 2 lines.
  lcd.print("Tolerence: "); // Print "Tolerence on the first line of the LCD.
  servo1.attach(9);// conect servo 1 to interface pin 9
  servo2.attach(10); // conect servo 2 to interface pin 10
  
  servo1.write(90); // sets the angle of servo 1 to 90 degrees
  servo2.write(90); // sets the angle of servo 2 to 90 degrees
}

// main loop
void loop(){
 
 int Tolerence = 0;// set tolerence to 0
  
 int sensorTop = analogRead(A0);// set the top LDR input to analog pin 0
 int sensorBottom = analogRead(A1);// set the bottom LDR input to analog pin 1
 int sensorLeft = analogRead(A3);// set the left LDR input to analog pin 3
 int sensorRight = analogRead(A4);// set the right LDR input to analog pin 4

 int sensorTest1 = sensorTop - sensorBottom;// Compares the difference in top and bottom
 int sensorTest2 = sensorBottom - sensorTop;// Compares the difference in top and bottom
 int sensorTest3 = sensorLeft - sensorRight;// Compares the difference in left and right
 int sensorTest4 = sensorRight - sensorLeft;// Compares the difference in left and right
   
 int TolerenceValue = analogRead(A2);// Reads the variable resistor value to get tolerence
 Tolerence = (TolerenceValue * (5.0 / 1023.0))*2;// sets tolerence value and changes value between 1 and 10
    
 lcd.setCursor(0,1);// sets the lcd to write on the second line
 lcd.print(Tolerence);// write the tolerence value to the lcd.

 if ((sensorTest1 >= 0)&&(sensorTest1 >= Tolerence)) // checks to see if sensor test 1 is greater then or equal to the tolerance and that sensor test 1 is a positive number
 	{
  	 UpDown(sensorTop, sensorBottom);// calls function to move the solar panel up or down towards the sun. Also pass the values of top and bottom sensors
 	}	
  
 if((sensorTest2 >= 0)&&(sensorTest2 >= Tolerence)) // checks to see if sensor test 2 is greater then or equal to the tolerance and that sensor test 2 is a positive number
 	{
 	 UpDown(sensorTop, sensorBottom);// calls function to move the solar panel up or down towards the sun. Also pass the values of top and bottom sensors
 	}
 
 if((sensorTest3 >= 0)&&(sensorTest3 >= Tolerence)) // checks to see if sensor test 3 is greater then or equal to the tolerance and that sensor test 3 is a positive number
 	{
     LeftRight(sensorLeft, sensorRight);// calls function to move the solar panel left or right towards the sun. Also pass the values of left and right sensors
 	}
 
 if((sensorTest4 >= 0)&&(sensorTest4 >= Tolerence)) // checks to see if sensor test 4 is greater then or equal to the tolerance and that sensor test 4 is a positive number
  	{
  	LeftRight(sensorLeft, sensorRight);// calls function to move the solar panel Left or right towards the sun. Also pass the values of left and right sensors
  	} 
 
 delay(10); //wait 10 millie seconds before moving back to the start of the main loop.
}

// function to check what direction to move up or down and turn towards the sun. Also take the value of top and bottom from the main loop and return nothing.
void UpDown(int sensorTop, int sensorBottom){
  
  int pos1= servo1.read();// reads the current angle of servo 1
    
  if(sensorTop < sensorBottom) // checks to see if the bottom sensor is grater than the top tehn enter the loop.
    { 
     pos1 = --pos1; // change the angle by -1
    }
  	 else// if the bottom is not greater than the top then enter this loop
     {
      pos1 = ++pos1;// change the angle by +1
     }
  servo1.write(pos1); // write the new angle to servo 1
}

// function to check what direction to move left or right and turn towards the sun.Also take the value of left and right from the main loop and return nothing.
void LeftRight(int sensorLeft, int sensorRight){
  
 int pos2= servo2.read();// reads the current angle of servo 1
  
 if(sensorLeft < sensorRight)// checks to see if the left sensor is grater than the right tehn enter the loop.
   { 
    pos2 = --pos2;// change the angle by -1
   }
  	else// if the left is not greater than the right then enter this loop
    {
     pos2 = pos2 + 1;// change the angle by +1
    }
  servo2.write(pos2); // write the new angle to servo 1
}
