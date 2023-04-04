#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

void setup() {

}

void loop() {
amg.readPixels(pixels);

Serial.print("[");
for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
  Serial.print(pixels[i-1]);
  Serial.print(", ");
  if( i%8 == 0 ) Serial.println();
}
Serial.println("]");
Serial.println();
}
