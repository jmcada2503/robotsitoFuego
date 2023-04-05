#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <vector>

Adafruit_AMG88xx amg;

class Camera {

    public:
        bool reversed;

        Motor(bool Reversed) {
            reversed = Reversed;
        }

        void init() {
            bool status;
            satus = amg.begin();
            if (!status) {
                Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
                while (1);
            }
            delay(100);
        }

        vector<vector<float>> getPixelValues {
            vector<vector<float>> values (AMG88xx_PIXEL_ARRAY_SIZE/8, vector<float>(AMG88xx_PIXEL_ARRAY_SIZE/8));

            if (reversed) {
                int row = 0;
                for(int i=0; i<AMG88xx_PIXEL_ARRAY_SIZE; i++){
                    values[row][i-((AMG88xx_PIXEL_ARRAY_SIZE/8)*row)] = pixels[AMG88xx_PIXEL_ARRAY_SIZE-1-i];
                    if( i%8 == 0 ) row++;
                }
                return values;
            }
            else {
                int row = 0;
                for(int i=0; i<AMG88xx_PIXEL_ARRAY_SIZE; i++){
                    values[row][i-((AMG88xx_PIXEL_ARRAY_SIZE/8)*row)] = pixels[i];
                    if( i%8 == 0 ) row++;
                }
            }

            return values;
        }

    private:
        float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

}

class Motor {

    public:
        int maxSpeed;
        int speedPin;
        int inputA;
        int inputB;

        Motor() {}

        void init(int MaxSpeed, int SpeedPin, int InputA, int InputB) {
            maxSpeed = MaxSpeed;
            speedPin = SpeedPin;
            inputA = InputA;
            inputB = InputB;
            pinMode(speedPin, OUTPUT);
            pinMode(inputA, OUTPUT);
            pinMode(inputB, OUTPUT);
        }

        void setSpeed(int percentage) {
            int speed = (maxSpeed*percentage)/100;
            analogWrite(speedPin,speed);
        }

        void moveForward() {
            digitalWrite(inputA, HIGH);
            digitalWrite(inputB, LOW);
        }
        
        void moveBackward() {
            digitalWrite(inputA, LOW);
            digitalWrite(inputB, HIGH);
        }
        
        void stop() {
            digitalWrite(inputA, LOW);
            digitalWrite(inputB, LOW);
        }

};

Motor rightMotor;
Motor leftMotor;
Camera camera(true);

void setup(){
    Serial.begin(9600); 
    rightMotor.init(255, 11, 12, 13);
    leftMotor.init(200, 3, 2, 4);
    camera.init();
}

void loop() {
    rightMotor.setSpeed(100);
    leftMotor.setSpeed(100);
    rightMotor.moveForward();
    leftMotor.moveForward();
}
