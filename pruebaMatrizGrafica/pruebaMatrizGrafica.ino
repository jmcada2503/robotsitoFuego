#include <Wire.h>
#include <SparkFun_GridEYE_Arduino_Library.h>

GridEYE grideye;




void readAMG() 
{
  for (unsigned char i = 0; i < 64; i++) 
  {
    Serial.print(grideye.getPixelTemperature(i));
    Serial.print(",");
  }
  Serial.println();

  
}

String myString = "";
Serial myPort;  
PFont f;
float split;
int q;

float[] show =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float[] temps =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void draw() { 
  if (myPort.available() > 64) {
    myString = myPort.readStringUntil(13);

    if (myString != "") {
      String splitString[] = splitTokens(myString, ",");


      // Map a temperature from AMG8233
      for (q = 0; q < 64; q++) {
        split = (float(splitString[q]));
        show[q] = float(splitString[q]) ;

        //Map a Red color pixel 
        if (split >= 28.5) {
          temps[q] = map(float(splitString[q]), 28.5, 35, 30, 0);
        }

        //Map a Orange color pixel 
        if ((split >= 27.50) && (split <= 28.2)) {
          temps[q] = map(float(splitString[q]), 27.50, 28.2, 50, 30);
        }

        //Map a Blue color pixel 
        if (split <= 27.250) {
          temps[q] = map(float(splitString[q]), 20, 27.25, 240, 180);
        }

        println(split);
      }
    }
  }

void setup() {
  Wire.begin();
  grideye.begin();
  Serial.begin(115200);
   
  size(600, 680);  
  f = createFont("Arial", 16, true);


  // Print a list of connected port in serial monitor processing
  printArray(Serial.list());

  //In this case, I using /dev/ttyUSB0 in linux
  //In serial monitor this processing show in array 32
  //If you windows user, please change Serial.list()[your number]
  myPort = new Serial(this, Serial.list()[32], 115200);
  myPort.clear();
  myString = myPort.readStringUntil(13);
  myString = null;
  // change to HSB color mode, this will make it easier to color
  // code the temperature data
  colorMode(HSB, 360, 100, 100);
}

  int x = 0;
  int y = 80;
  int i = 0;
  background(0);   // Clear the screen with a black background

  while (y < 630) {
    fill(0, 0, 0);
    rect(0, 0, 220, 80);
    textSize(40);
    fill(0, 0, 100); 
    text("CHIP PIKO", 15, 45);

    textSize(16);
    text("www.chippiko.com", 50, 65);

    fill(0, 0, 100);
    rect(225, 0, 600, 80);

    textAlign(LEFT, CENTER);
    textSize(16);
    fill(0, 0, 0); //HBS

    text("Thermal Camera Non Interpolation", 240, 11);
    line(220, 27, 600, 27);
    line(330, 27, 330, 55);
    line(460, 27, 460, 55); 
    text("Piksel : 8x8    Range : 0-80°C     Accuracy : ±2.5°C", 240, 39);

    line(220, 55, 600, 55);
    text("Labuhan Haji - Aceh , 8:57pm 2 November 2019", 240, 65);


    while (x < 550) {
      fill(temps[i], 100, 100);
      rect(x, y, 75, 75);

      //Show Temp Value
      textAlign(CENTER, CENTER);
      textFont(f, 11);
      fill(0);
      text((show[i]), (x+37.5), (y+37.5));

      //Show Pixel Digit
      textAlign(LEFT, LEFT);
      fill(100);
      text(i, (x+3), (y+12));

      x = x + 75;
      i++;
    }

    y = y + 75;
    x = 0;
  }
} 
