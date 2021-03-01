// This is v1 of the water immersion program.

#include <avr/sleep.h>

#define YELLOW_LED_PIN 2
#define GREEN_LED_PIN 3
#define BUTTON_PIN 4
//This is the LED output pin on the Arduino
#define PUMP_PIN 8
#define VALVE_PIN 9
//This is the LED output pin on the Arduino
#define SENSOR_PIN A1
// This is the water sensor input pin

int water_sensor_value = 0;
int cycles = 1;
int buttonState = 0;   
bool test = true;

void setup() 
{
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT); 
  pinMode(YELLOW_LED_PIN, OUTPUT);          // Sets that pin as an output
  pinMode(GREEN_LED_PIN, OUTPUT);      
  pinMode(PUMP_PIN, OUTPUT); 
  pinMode(VALVE_PIN, OUTPUT); 
  pinMode(BUTTON_PIN, INPUT);
  
  digitalWrite(YELLOW_LED_PIN, HIGH);     // Make sure the LED is switched off
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(PUMP_PIN, HIGH);     // Make sure the LED is switched off
  digitalWrite(VALVE_PIN, HIGH);
}

void loop() 
{
  if (test == true){
    Serial.println("This is a test run.");
  }
  buttonState = digitalRead(BUTTON_PIN);
  Serial.println("Waiting for button input...");
  while (buttonState == LOW){
    buttonState = digitalRead(BUTTON_PIN);
  }
  while (cycles <= 12) {
    Serial.print("This is cycle number: ");
    Serial.println(cycles);
    // pump the water in the upper tank
    digitalWrite(YELLOW_LED_PIN,LOW);
    pump();
    Serial.println("Finished pumping...");
    wait();
    drain();
    Serial.println("Finished draining...");
    wait();
    Serial.print("Cycle ");
    Serial.print(cycles);
    Serial.println(" is finished, starting next cycle.");
    cycles += 1;
  }
  //Cycle finishes
  Serial.println("All cycles are finished");
  Serial.println("Please press the reset button to start again.");
  digitalWrite(YELLOW_LED_PIN,HIGH);
  digitalWrite(GREEN_LED_PIN,LOW);
  
  stop();
}


void pump(){
  Serial.println("Pumping...");
  water_sensor_value = analogRead(SENSOR_PIN);
  while (water_sensor_value <= 700){
    digitalWrite(PUMP_PIN, LOW);
    water_sensor_value = analogRead(SENSOR_PIN);
  }
  digitalWrite(PUMP_PIN, HIGH);
}

void drain(){
  Serial.println("Draining...");
  digitalWrite(VALVE_PIN, LOW);
  if (test == true){
    delay(1000);
  }else{
    delay(10000);
  }
  digitalWrite(VALVE_PIN, HIGH);
}

void wait()
{
  if (test == true){
    delay(5000);
  }else{
    delay(60UL * 60UL * 1000UL);
  }
}

void stop()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();  // Disable interrupts
  sleep_mode();
}
