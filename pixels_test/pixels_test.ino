// Funciona para leer la matriz de puntos de la cámara

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {
    Serial.begin(9600);
    Serial.println(F("AMG88xx pixels"));

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
}


void loop() { 
    //read all the pixels
    amg.readPixels(pixels);

    Serial.println("[");
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      if (pixels[i-1] >= 40) {
        Serial.print("%");
      }
      else {
        Serial.print(".");
      }
      Serial.print(" ");
      if( i%8 == 0 ) Serial.println();
    }
    Serial.println("]");;
    Serial.write(12);
}
