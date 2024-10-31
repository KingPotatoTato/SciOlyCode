// define the pins for the right motor
int enRight = 3; // enable pin
int in1 = 2; // input pin 1
int in2 = 4; // input pin 2

// define the pins for the left motor
int enLeft = 5; // enable pin
int in3 = 6; // input pin 3
int in4 = 7; // input pin 4

// define the pins for the sensors
int superRightSensor = 11; // sensor on the far right
int superLeftSensor = 10; // sensor on the far left
int leftSensor  =  9; // sensor on the left
int rightSensor  =  8; // sensor on the right

// define the pin for the LED
int ledDebugPin = 12; // LED for debugging

// define the pin for the start button
int startButton = 13; // button to start the program

void setup() {

  // set the pin modes for the motors
  pinMode(enRight, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enLeft, OUTPUT);

  // set the pin modes for the sensors
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(superLeftSensor, INPUT);
  pinMode(superRightSensor, INPUT);

  // set the pin mode for the LED
  pinMode(ledDebugPin, OUTPUT);

  // set the pin mode for the start button
  pinMode(startButton, INPUT);

  // initialize the serial communication
  Serial.begin(9600);

  // turn off the motors
  off();

  // set the speed of the motors
  analogWrite(enRight, 130); // right motor speed
  analogWrite(enLeft, 160); // left motor speed 
}


void loop() {
  // check if the start button is pressed
  if (digitalRead(startButton) == HIGH) {
    
      end();
  }
  // end the loop program


}

// start defining functions

// function to turn left
void turnLeft() {
  // rotate the motors in opposite directions
  left();
  // wait for 355 milliseconds
  delay(410);
  tick();
}

// function to turn right
void turnRight() {
  // rotate the motors in opposite directions
  right();
  // wait for 355 milliseconds
  delay(410);
  tick();
}

// function to move forward for one block
void blockUp() {
  // move the motors forward
  foward();
  // loop for 1300 times
   for (int i = 0; i <= 1500; i++) {
    // check the sensors
    sensors();
    // wait for 1 millisecond
    delay(1);
   }
  tick();
}

// function to move forward for half a block
void blockUpHalf() {
  // move the motors forward
  foward();
  // loop for 650 times
  for (int i = 0; i <= 1000; i++) {
    // check the sensors
    sensors();
    // wait for 1 millisecond
    delay(1);
   }
  tick();
}

// function to move backward for one block
void blockBack() {
  // move the motors backward
  backward();
  // wait for 1300 milliseconds
  delay(1300);
  // doesn't check sensors since no sensors on back
  tick();
}

// function to check the sensors and adjust the direction
void sensors() {
  // if both sensors detect black, move backward
  if (digitalRead(rightSensor) == LOW && digitalRead(leftSensor) == LOW) {
    backward();
  }
  // if the right sensor detects black, turn left
  else if (digitalRead(rightSensor) == LOW) {
    Serial.println("Right");
   left();
  }
  // if the left sensor detects black, turn right
  else if (digitalRead(leftSensor) == LOW) {
    Serial.println("Left");
    right();
  }
  // if the super right sensor detects black, turn left
  else if (digitalRead(superRightSensor) == LOW) {
    Serial.println("Super Right");
   left();
  }
  // if the super left sensor detects black, turn right
  else if (digitalRead(superLeftSensor) == LOW) {
    Serial.println("Super Left");
    right();
  }
  // otherwise, move forward
  else {
    foward();
  }
}

// function to turn on the LED
void ledOn() {
  digitalWrite(ledDebugPin, HIGH);
}

// function to turn off the LED
void ledOff() {
  digitalWrite(ledDebugPin, LOW);
}

// function to stop the motors
void off() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// function to move the motors forward
void foward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// function to move the motors backward
void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// function to rotate the motors left
void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// function to rotate the motors right
void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// function to end the program
void end() {
  // stop the motors
  off();
  // blink led
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
  foward();

}

// function to set the speed to low
void lowSpeed() {
  // TODO: implement this function
}

// function to set the speed to medium
void medSpeed() {
  // TODO: implement this function
}

// function to set the speed to high
void highSpeed() {
  // TODO: implement this function
}
