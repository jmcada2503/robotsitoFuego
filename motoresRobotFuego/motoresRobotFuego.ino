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

void setup(){
    Serial.begin(9600); 
    rightMotor.init(255, 11, 12, 13);
    leftMotor.init(200, 3, 2, 4);
}

void loop() {
    rightMotor.setSpeed(100);
    leftMotor.setSpeed(100);
    rightMotor.moveForward();
    leftMotor.moveForward();
}
