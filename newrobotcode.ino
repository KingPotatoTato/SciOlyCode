#include <Stepper.h>

// Define the number of steps per revolution for your motor
const int stepsPerRevolution = 2048; // This value may vary depending on your motor

// Define the pins for the stepper motors
const int stepper1Pin1 = 2;
const int stepper1Pin2 = 3;
const int stepper1Pin3 = 4;
const int stepper1Pin4 = 5;

const int stepper2Pin1 = 6;
const int stepper2Pin2 = 7;
const int stepper2Pin3 = 8;
const int stepper2Pin4 = 9;

// Define the pins for the sensors
const int superRightSensor = 11; // sensor on the far right
const int superLeftSensor = 10; // sensor on the far left
const int leftSensor  =  9; // sensor on the left
const int rightSensor  =  8; // sensor on the right

// Define the pin for the LED
const int ledDebugPin = 12; // LED for debugging

// Define the pin for the start button
const int startButton = 13; // button to start the program

// Initialize the stepper motors
Stepper stepper1(stepsPerRevolution, stepper1Pin1, stepper1Pin3, stepper1Pin2, stepper1Pin4);
Stepper stepper2(stepsPerRevolution, stepper2Pin1, stepper2Pin3, stepper2Pin2, stepper2Pin4);

void setup() {
  // Set the speed of the stepper motors
  stepper1.setSpeed(10); // Adjust the speed as needed
  stepper2.setSpeed(10); // Adjust the speed as needed

  // Set the pin modes for the sensors
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(superLeftSensor, INPUT);
  pinMode(superRightSensor, INPUT);

  // Set the pin mode for the LED
  pinMode(ledDebugPin, OUTPUT);

  // Set the pin mode for the start button
  pinMode(startButton, INPUT);

  // Initialize the serial communication
  Serial.begin(9600);

  // Turn off the motors
  off();
}

void loop() {
  // Check if the start button is pressed
  if (digitalRead(startButton) == HIGH) {
    end();
  }
  // End the loop program
}

// Start defining functions

// Function to turn left
void turnLeft() {
  // Rotate the motors in opposite directions
  stepper1.step(-stepsPerRevolution / 8); // Adjust the steps as needed
  stepper2.step(stepsPerRevolution / 8); // Adjust the steps as needed
  delay(410);
  tick();
}

// Function to turn right
void turnRight() {
  // Rotate the motors in opposite directions
  stepper1.step(stepsPerRevolution / 8); // Adjust the steps as needed
  stepper2.step(-stepsPerRevolution / 8); // Adjust the steps as needed
  delay(410);
  tick();
}

// Function to move forward for one block
void blockUp() {
  // Move the motors forward
  stepper1.step(stepsPerRevolution / 2); // Adjust the steps as needed
  stepper2.step(stepsPerRevolution / 2); // Adjust the steps as needed
  for (int i = 0; i <= 1500; i++) {
    sensors();
    delay(1);
  }
  tick();
}

// Function to move forward for half a block
void blockUpHalf() {
  // Move the motors forward
  stepper1.step(stepsPerRevolution / 4); // Adjust the steps as needed
  stepper2.step(stepsPerRevolution / 4); // Adjust the steps as needed
  for (int i = 0; i <= 1000; i++) {
    sensors();
    delay(1);
  }
  tick();
}

// Function to move backward for one block
void blockBack() {
  // Move the motors backward
  stepper1.step(-stepsPerRevolution / 2); // Adjust the steps as needed
  stepper2.step(-stepsPerRevolution / 2); // Adjust the steps as needed
  delay(1300);
  tick();
}

// Function to check the sensors and adjust the direction
void sensors() {
  if (digitalRead(rightSensor) == LOW && digitalRead(leftSensor) == LOW) {
    blockBack();
  } else if (digitalRead(rightSensor) == LOW) {
    Serial.println("Right");
    turnLeft();
  } else if (digitalRead(leftSensor) == LOW) {
    Serial.println("Left");
    turnRight();
  } else if (digitalRead(superRightSensor) == LOW) {
    Serial.println("Super Right");
    turnLeft();
  } else if (digitalRead(superLeftSensor) == LOW) {
    Serial.println("Super Left");
    turnRight();
  } else {
    blockUp();
  }
}

// Function to turn on the LED
void ledOn() {
  digitalWrite(ledDebugPin, HIGH);
}

// Function to turn off the LED
void ledOff() {
  digitalWrite(ledDebugPin, LOW);
}

// Function to stop the motors
void off() {
  stepper1.step(0);
  stepper2.step(0);
}

// Function to end the program
void end() {
  off();
  while (true) {
    ledOn();
    delay(100);
    ledOff();
    delay(100);
  }
}

void tick() {
  off();
  ledOn();
  delay(100);
  ledOff();
  blockUp();
}
