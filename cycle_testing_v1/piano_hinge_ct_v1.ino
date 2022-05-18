#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <ezButton.h>
#include <Servo.h>

Servo myservo_1;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo_2;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int int_pos = 0;
int start_angle = 0;
int goal_angle = 100;

int cycles = 10;
int i = 1;

const int BUTTON_PIN = 7; // the number of the pushbutton pin
ezButton button(BUTTON_PIN); 
int cycleState = LOW;   // the current state of LED

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo_1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo_2.attach(10);  // attaches the servo on pin 9 to the servo object
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  myservo_1.write(int_pos);              // tell servo to go to position in variable 'pos'
  myservo_2.write(180-int_pos);
}

void loop() 
{
  
  button.loop(); // MUST call the loop() function first

  if(button.isPressed()) {
    Serial.println("The button is pressed");
    // toggle state of LED
    cycleState = !cycleState;
  }
  if (cycleState){
    Serial.println("Execute cycle");
    execution();
    i++;
  }
  if (i > cycles){
    Serial.println("Cycle testing ended");
    myservo_1.write(int_pos);              // tell servo to go to position in variable 'pos'
    myservo_2.write(180-int_pos);
    stop();
  }
}

void execution(){
  Serial.print("Cycle number: ");
  Serial.println(i);
  cycle(start_angle, goal_angle);
  
}

void cycle(int start, int goal){
  int pos = 0;
  for (pos = start; pos <= goal; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo_1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo_2.write(180-pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = goal; pos >= start; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo_1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo_2.write(180-pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void stop()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();  // Disable interrupts
  sleep_mode();
}
