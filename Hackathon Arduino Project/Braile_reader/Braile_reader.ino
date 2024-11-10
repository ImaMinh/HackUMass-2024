#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;


// Define Braille patterns for A-Z using a 2D array
const int braillePatterns[26][6] = {
    {1,0,0,0,0,0},  // A
    {1,0,1,0,0,0},  // B
    {1,1,0,0,0,0},  // C
    {1,1,0,1,0,0},  // D
    {1,0,0,1,0,0},  // E
    {1,1,1,0,0,0},  // F
    {1,1,1,1,0,0},  // G
    {1,0,1,1,0,0},  // H
    {0,1,1,0,0,0},  // I
    {0,1,1,1,0,0},  // J
    {1,0,0,0,1,0},  // K
    {1,0,1,0,1,0},  // L
    {1,1,0,0,1,0},  // M
    {1,1,0,1,1,0},  // N
    {1,0,0,1,1,0},  // O
    {1,1,1,0,1,0},  // P
    {1,1,1,1,1,0},  // Q
    {1,0,1,1,1,0},  // R
    {0,1,1,0,1,0},  // S
    {0,1,1,1,1,0},  // T
    {1,0,0,0,1,1},  // U
    {1,0,1,0,1,1},  // V
    {0,1,1,1,0,1},  // W
    {1,1,0,0,1,1},  // X
    {1,1,0,1,1,1},  // Y
    {1,0,0,1,1,1}   // Z
};

// Define the pins for each Braille dot
int dots[6] = {3, 5, 6, 10, 11};

void setup() {
  servo1.attach(3);  // Attach servo1 to pin 3
  servo2.attach(5);  // Attach servo2 to pin 5
  servo3.attach(6);  // Attach servo3 to pin 6
  servo4.attach(9);  // Attach servo4 to pin 9
  servo5.attach(10); // Attach servo5 to pin 10
  servo6.attach(11); // Attach servo6 to pin 11

  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
      pinMode(dots[i], OUTPUT);
  }
}

// Function to get the Braille pattern for a given letter
const int* getBraillePattern(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return braillePatterns[letter - 'A'];
    } else if (letter >= 'a' && letter <= 'z') {
        return braillePatterns[letter - 'a'];
    }
    return nullptr; // Return null if the character is not a valid letter
}

void resetServos() {
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    servo4.write(0);
    servo5.write(10);
    servo6.write(0);
}

void servo_speed(Servo &servo, int targetAngle){
    for(int i = 0; i <= targetAngle; i++){
      servo.write(i);
      delay(3);
    }
}

void setBraillePattern(const int pattern[6]) {
    // servo1.write(pattern[0] == 1 ? 360 : 0);
    // servo2.write(pattern[1] == 1 ? 360 : 0);
    // servo3.write(pattern[2] == 1 ? 360 : 0);
    // servo4.write(pattern[3] == 1 ? 360 : 0);
    // servo5.write(pattern[4] == 1 ? 360 : 0);
    // servo6.write(pattern[5] == 1 ? 360 : 0);
    servo_speed(servo1, pattern[0] == 1 ? 50 : 0);
    servo_speed(servo2, pattern[1] == 1 ? 30 : 0);
    servo_speed(servo3, pattern[2] == 1 ? 30 : 0);
    servo_speed(servo4, pattern[3] == 1 ? 30 : 0);
    servo_speed(servo5, pattern[4] == 1 ? 40 : 10);
    servo_speed(servo6, pattern[5] == 1 ? 50 : 0);
}

void loop() {
    // Wait for a character from Serial input
    resetServos();
    if (Serial.available() > 0) {
        char letter = Serial.read();
        const int* pattern = getBraillePattern(letter); // pattern is the list of servo elements in 0s and 1s

        if (pattern != nullptr) {
            setBraillePattern(pattern);
            delay(1800);  // Brief pause to display the letter
            resetServos();
            delay(500);
            Serial.print("Input successfull. Next letter!");
        }
    }
}


