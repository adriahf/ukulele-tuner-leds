// library for Fast Fourier Transforms (FFT)
#include "arduinoFFT.h"
// library for controlling the LED ring
#include <Adafruit_NeoPixel.h>

// LED ring connected to pin 2
#define PIN 2
// number of pixels of the ring
#define NUMPIXELS 24 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// global variables for FFT
// SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno. For ATSAMD21G18 we use 512.
#define SAMPLES 512
// Ts = Based on Nyquist, must be 2 times the highest expected frequency.
#define SAMPLING_FREQUENCY 2048
// object for FFT
arduinoFFT FFT = arduinoFFT(); 
unsigned int samplingPeriod;
unsigned long microSeconds;
//create vector of size SAMPLES to hold real values
double vReal[SAMPLES];
//create vector of size SAMPLES to hold imaginary values
double vImag[SAMPLES];

// this function convers frequencies to colors
void frequency2color(double frequency) {
  // frequencies G4 = 392Hz, C4 = 261.6Hz, E4 = 329.6Hz, A4 = 440Hz
  // led step: 3Hz
  int LED_step = 3;
  // first string: G4 
  if ((frequency >= 360.8) && (frequency < 416)) {
      float led_positions[14] = {369.5, 372.5, 375.5, 378.5, 381.5, 384.5, 387.5, 390.5, 393.5, 398.5, 401.5, 404.5, 407.5};
      firstString(frequency, led_positions);
  }
  else if (frequency < 295.6) {
      float led_positions[14] = {239.1, 242.1, 245.1, 248.1, 251.1, 254.1, 257.1, 260.1, 263.1, 266.1, 269.1, 272.1, 275.1};
      secondString(frequency, led_positions);
  }
  else if ((frequency >= 295.6) && (frequency < 416)) {
      float led_positions[14] = {307.1, 310.1, 313.1, 316.1, 319.1, 322.1, 325.1, 328.1, 331.1, 334.1, 337.1, 340.1, 343.1};
      thirdString(frequency, led_positions);
  }
  else if (frequency >= 416) {
      float led_positions[14] = {417.5, 420.5, 423.5, 426.5, 429.5, 432.5, 435.5, 438.5, 441.5, 444.5, 447.5, 450.5, 453.5};
      fourthString(frequency, led_positions);
  }
}

// specific function for the first string
void firstString(double frequency, float led_positions[14]) {
  for (int i=0; i<NUMPIXELS; i++) {
        // set everything red
        pixels.setPixelColor(i, pixels.Color(30, 0, 0));
      }
  // shut down LED depending on the position (frequency)
  int led_position = shutdownLED(frequency, led_positions);
  pixels.setPixelColor(led_position, pixels.Color(0, 0, 0));
  // send the updated pixel colors to the hardware
  pixels.show();
}

// specific function for the second string
void secondString(double frequency, float led_positions[14]) {
  for (int i=0; i<NUMPIXELS; i++) {
        // set everything green
        pixels.setPixelColor(i, pixels.Color(0, 30, 0));
      }
  // shut down LED depending on the position (frequency)
  int led_position = shutdownLED(frequency, led_positions);
  pixels.setPixelColor(led_position, pixels.Color(0, 0, 0));
  // send the updated pixel colors to the hardware
  pixels.show();
}

// specific function for the third string
void thirdString(double frequency, float led_positions[14]) {
  for (int i=0; i<NUMPIXELS; i++) {
        // set everything to blue
        pixels.setPixelColor(i, pixels.Color(0, 0, 30));
      }
  // shut down LED depending on the position (frequency)
  int led_position = shutdownLED(frequency, led_positions);
  pixels.setPixelColor(led_position, pixels.Color(0, 0, 0));
  // send the updated pixel colors to the hardware
  pixels.show();
}

// specific function for the fourth string
void fourthString(double frequency, float led_positions[14]) {
  for (int i=0; i<NUMPIXELS; i++) {
        // set everything to white
        pixels.setPixelColor(i, pixels.Color(20, 20, 20));
      }
   // shut down LED depending on the position (frequency)
  int led_position = shutdownLED(frequency, led_positions);
  pixels.setPixelColor(led_position, pixels.Color(0, 0, 0));
  // send the updated pixel colors to the hardware
  pixels.show();
}

// function for getting the position of the shutdown LED
int shutdownLED(double frequency, float led_positions[14]) {
  int led_position = 0;
  for (int i=0; i<13; i++) {
    if (frequency > led_positions[i]) {
      SerialUSB.print(led_positions[i]);
      led_position = led_position + 1;
    }
  }
  return led_position;
}

void setup() {
    // neopixel setup
    pixels.begin();
    
    // sampling setup
    SerialUSB.begin(115200);
    SerialUSB.println("Start!");
    // period in microseconds
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
}
 
void loop() {
    // sample SAMPLES times
    for(int i=0; i<SAMPLES; i++)
    {
        // get microseconds
        microSeconds = micros();
        // reads the value from analog pin 0 (A0), quantize it and save it as a real term
        vReal[i] = analogRead(A0);
        // makes imaginary term 0 always
        vImag[i] = 0;

        // remaining wait time between samples if necessary
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    // perform FFT on samples
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    // find peak frequency and print peak
    double frequency = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    SerialUSB.println(frequency);     //Print out the most dominant frequency.

    // transform the frequency to color
    frequency2color(frequency);
}
