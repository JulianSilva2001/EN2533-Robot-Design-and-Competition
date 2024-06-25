#include <FFT.h>  // Include the FFT library

const int samplingFrequency = 10000; // Sample rate (must be higher than the highest expected frequency)
const int sampleWindow = 128;        // Sample window size for FFT, must be a power of 2

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[sampleWindow];
double vImag[sampleWindow];

void setup() {
  Serial.begin(115200);
  samplingPeriod = round(1000000 * (1.0 / samplingFrequency));
}

void loop() {
  microSeconds = micros();

  for (int i = 0; i < sampleWindow; i++) {
    vReal[i] = analogRead(A0); // A0 is the analog input pin
    vImag[i] = 0;
    while (micros() - microSeconds < samplingPeriod) {}
    microSeconds += samplingPeriod;
  }

  FFT.Windowing(vReal, sampleWindow, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, sampleWindow, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, sampleWindow);
  
  double peak = 0;
  int peakIndex = 0;
  
  for (int i = 2; i < sampleWindow/2; i++) {
    double magnitude = vReal[i];
    if (magnitude > peak) {
      peak = magnitude;
      peakIndex = i;
    }
  }

  double frequency = peakIndex * samplingFrequency / sampleWindow;
  
  if (frequency > 900 && frequency < 1100) { // Check if detected frequency is around 1000 Hz
    Serial.print("Detected frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");
    // Add your action here, e.g., trigger an output
  }
}
