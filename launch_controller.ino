// Model Rocket Launch Controller - TravdogIO 08/2020
// Uses two buttons and a relay to ignite model rocket motors
// Arm button to be held for a set time, after which the device
// becomes 'armed'. Only then will the 'fire' button be enabled
// to open the relay and trigger ignition. Releasing the 'arm'
// button at any time will disarm the device and disable the
// 'fire' button.

#include <Adafruit_NeoPixel.h>

// Constants (Uncomment for Mega 2560)
//const int armButtonPin = 22;      // Grey 'arm' button
//const int fireButtonPin = 23;     // Red 'fire' button
//const int neoPixelPin = 6;        // NeoPixel signal
//const int relayPin = 9;           // Ignition relay

// Constants (Uncomment for Trinket 5v)
//const int armButtonPin = 3;      // Grey 'arm' button
//const int fireButtonPin = 4;     // Red 'fire' button
//const int neoPixelPin = 0;        // NeoPixel signal
//const int relayPin = 2;           // Ignition relay

// Constants (Uncomment for ESP32)
const int armButtonPin = 12;      // Grey 'arm' button
const int fireButtonPin = 27;     // Red 'fire' button
const int neoPixelPin = 25;        // NeoPixel signal
const int relayPin = 32;           // Ignition relay


const int NUMPIXELS = 1;          // Number of NeoPixels in strand

const long armDelay = 2000;       // How long to hold arm button to arm
const long fireDuration = 1500;   // How long to open the relay for firing

// Variables
int armButtonState = 0;           // Start with button off
int fireButtonState = 0;          // Start with button off

boolean armed = false;            // Start disarmed

unsigned long armedSince = 0;     // Stores last timer count

// Objects
Adafruit_NeoPixel pixels(NUMPIXELS, neoPixelPin, NEO_GRB + NEO_KHZ800);


void setup() {
  // Initialize outputs
  pinMode(neoPixelPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // Initialize inputs
  pinMode(armButtonPin, INPUT);
  pinMode(fireButtonPin, INPUT);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setPixelColor(0, pixels.Color(0, 20, 0));
  pixels.show();
  delay(1000);

}

void loop() {
  readButtonStates();

  // Begin arming sequence
  if (armButtonState == LOW) {     // If 'arm' button is not pressed
    armedSince =  millis();        // Reset arming timer
    armed = false;                 // Stay disarmed
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
  }
  if (millis() - armedSince > armDelay) {
    armed = true;                   // Arm after button hold delay
    pixels.setPixelColor(0, pixels.Color(40, 0, 0));
    pixels.show();
  }
  // End of arming sequence
  
  // Begin firing sequence
  if (armed == true && fireButtonState == HIGH) {
    digitalWrite(relayPin, HIGH);   // Open firing relay
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
    delay(fireDuration);            // Wait for the charge to ignite
    digitalWrite(relayPin, LOW);    // Close the relay
    armed = false;                  // Disarm controller
    armedSince = millis();          // Reset arming timer
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
  }
  
 // End firing sequence
  
  
}


// Functions

// Reads the button states
void readButtonStates() {
  armButtonState = digitalRead(armButtonPin);
  fireButtonState =  digitalRead(fireButtonPin);
}
