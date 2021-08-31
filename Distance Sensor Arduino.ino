const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const int buzzerPin = 5;
const int redLED = 2;
const int yellowLED = 7;
const int blueLED = 4;

const unsigned int MAX_DIST = 23200;

const int minSoundDelay = 50;   //how fast at 0
const int maxSoundDelay = 2000;  //how fast at 400cm

long timeOfLastSound = 0;

const int redLine = 100;      //distance in cm to turn on a certain led
const int yellowLine = 200;

void setup() {  
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);    
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;


  digitalWrite(TRIG_PIN, HIGH);  //takemeasurement
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

 
  while ( digitalRead(ECHO_PIN) == 0 );

 
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;
  
  if ( pulse_width > MAX_DIST ) {
    Serial.println("Out of range");
  } 
  else {
      if (cm <= redLine) {
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
    }
  
      if (cm > redLine &&cm <= yellowLine) {
        digitalWrite(blueLED, LOW);
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED, LOW);
     }
  
      if (cm > yellowLine) {
        digitalWrite(blueLED, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);
      }
  
      Serial.print(cm);
      Serial.print(" cm \t");
      Serial.print(inches);
      Serial.println(" in");
    
      long soundDelay = map(cm, 0, 400, minSoundDelay, maxSoundDelay);  //turns beep on based on how far away how long beep delay
   
    
      if (millis() > timeOfLastSound + soundDelay) {     //takes delay and if long enough plays sound
        tone(buzzerPin, 1000, 50);
        timeOfLastSound = millis();
      }
    
  }
  
  delay(50);
}
