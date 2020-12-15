#include <Adafruit_NeoPixel.h>

#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

//  Pulse sensor variables
//int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int PulseSensorPurplePin = 10;

// Neopixel variables
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino that is connected to the NeoPixels?
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 4

// Declare our NeoPixel strip object:
Adafruit_NeoPixel neo_strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Define the push button
int buttonApin = 12; 


void setup() {

  //Button
  pinMode(buttonApin, INPUT_PULLUP);  
  
  //Flora
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  //Pixels
  neo_strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  neo_strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  neo_strip.show();            // Turn OFF all pixels ASAP
}

void loop() {

 //generates temperature, measures pulse, & displays mood using color every 3 seconds
   moodDisplay();
   delay(1000); //display color for 3 seconds
   colorWipe(strip.Color(0, 0, 0), 1000); // Reset flora
   colorWipe(neo_strip.Color(0, 0, 0), 1000); // Reset neopixels
   delay(1000); //off for 3 seconds

}

void moodDisplay(){

  
// Send love feature based on button press
    if (digitalRead(buttonApin) == LOW){ //if btn is pressed
    Serial.println("\n 'Send love' button pressed.\n");
    for(int i=0; i<10; i++) { //10 cycles
        colorWipe(strip.Color(255, 75, 150), 1000); // Pink
        colorWipe(strip.Color(0,0,0), 1000); // Blank
      }
     return;
    }
  
    if (digitalRead(buttonApin) == HIGH){ //if btn not pressed
      //Serial.println(" 'Send love' button NOT pressed.");
      colorWipe(strip.Color(0, 0, 0), 1000); //Blank
    }


//get & print pulse
  ///int bpm = random_pulse(50,200); //random bpm
  int bpm = analogRead(PulseSensorPurplePin); //read from sensor
  Serial.print("\ncurrent pulse: ");
  Serial.print(bpm);
  Serial.print(" signal\n");

//get & print body temp
  float bodytemp = temp(97.6,99.2);
  Serial.print("current body temperature: ");
  Serial.print(bodytemp);
  Serial.print("°F\n");

    
 //calculate & display mood using color 
  if (bpm <= 100){
   
   //relaxed, lower temp
    if (bodytemp < 98.4){
      Serial.println("mood: relaxed, color: green");
      colorWipe(strip.Color(0, 255, 0), 1000); // Green
      colorWipe(neo_strip.Color(0, 255, 0), 1000); // Green
      return;
    }
 

  //happy, higher temp
    if (bodytemp > 98.4){
      Serial.println("mood: happiness, color: yellow");
      colorWipe(strip.Color(255, 255, 0), 1000); // Yellow
      colorWipe(neo_strip.Color(255, 255, 0), 1000); 
      return;
    }

  }

  else {
    
     //anger, higher temp
    if (bodytemp > 98.6){
      Serial.println("mood: angry, color: red");
      colorWipe(strip.Color(255, 0, 0), 1000); // Red
      colorWipe(neo_strip.Color(255, 0, 0), 1000); 
      return;
    }
 
   
  //sad, lower temp
     if (bodytemp < 98.0){
         Serial.println("mood: sad, color: blue");
         colorWipe(strip.Color(0, 0, 255), 1000); // Blue
         colorWipe(neo_strip.Color(0, 0, 255), 1000); 
         return;
   }
   
    else {
     
      //anxiety or fear, reg temp
        Serial.println("mood: anxiety/fear. color: purple");
        colorWipe(strip.Color(255, 0, 255), 1000); // Purple
        colorWipe(neo_strip.Color(255, 0, 255), 1000); 
        return;
    }
   }
  }


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<neo_strip.numPixels(); i++) {
      strip.setPixelColor(i, c); //set flora color
      strip.show();

      neo_strip.setPixelColor(i, c); //set neopixel color
      neo_strip.show();
      
      delay(wait);
  }
}


// Generates a random body temperature within a specified range
float temp(float min, float max) {
    return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}

//Generates a random pulse within a specific range
int random_pulse(int min, int max) {
    return (rand() % (max + 1 - min)) + min;

}
