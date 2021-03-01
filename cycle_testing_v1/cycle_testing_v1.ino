// v1 has the capability to control when to start the cycle testing by pressing the start button.
// However, if you want to stop, you will need to press the reset button. This does not continue recording after reset. 

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <ezButton.h>

int solenoid1Pin = 12;//This is the output pin on the Arduino
int solenoid2Pin = 13;//This is the output pin on the Arduino
int cycles = 10000;
int i = 9242 ;
const int BUTTON_PIN = 7; // the number of the pushbutton pin
ezButton button(BUTTON_PIN); 
int cycleState = LOW;   // the current state of LED

void setup() 
{
  Serial.begin(9600);
  pinMode(solenoid1Pin, OUTPUT);          //Sets that pin as an output
  pinMode(solenoid2Pin, OUTPUT); 
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() 
{
  button.loop(); // MUST call the loop() function first

  if(button.isPressed()) {
//    Serial.println("The button is pressed");
    // toggle state of LED
    cycleState = !cycleState;
  }
  if (cycleState){
//    Serial.println("Execute cycle");
    execution();
    i++;
  }
  if (i > cycles){
//    Serial.println("Cycle testing ended");
    stop();
  }
}

void execution(){
  Serial.print("Cycle number: ");
  Serial.println(i);
  digitalWrite(solenoid1Pin, LOW); 
  digitalWrite(solenoid2Pin, LOW); 
  open_latch();
  close_latch();
}
void open_latch(){
//  Serial.println("Open latch");
  digitalWrite(solenoid1Pin, HIGH);
  delay(1500);
//  Serial.println("Retract trigger push");
  digitalWrite(solenoid1Pin, LOW);
  delay(500);
}

void close_latch(){
//  Serial.println("Close latch");

//  Serial.println("Bolt push");
  digitalWrite(solenoid2Pin, HIGH);
  delay(3400);

//  Serial.println("Retract latch push");
  digitalWrite(solenoid2Pin, LOW);
  delay(500);
}
void stop()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();  // Disable interrupts
  sleep_mode();
}
