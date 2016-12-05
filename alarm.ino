#define trigPin 13
#define echoPin 12
#define Rled 11
#define Bled 10
#define buzzer 8

int normalDistance = 200; //set the normal distance 200 mm
boolean triggered = false;

void setup(){
  Serial.begin (9600);
  pinMode(Rled, OUTPUT);
  pinMode(Bled, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  long duration, distance;

  digitalWrite(Rled, HIGH); // this indicates that the calibration is in process
  digitalWrite(Bled, HIGH);
  digitalWrite(buzzer, HIGH);

  while (millis() < 5000) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
    if (distance < normalDistance){
      normalDistance = distance;
    }
  }

  digitalWrite(Rled, LOW);
  digitalWrite(Bled, LOW);
  digitalWrite(buzzer, LOW);
 
}

void loop(){
  if (triggered){
    digitalWrite(Rled, HIGH);
    digitalWrite(Bled, LOW);
    tone(buzzer, 635);
    delay(500);
    digitalWrite(Rled, LOW);
    digitalWrite(Bled, HIGH);
    tone(buzzer, 912);
    delay(500);
  }else{
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
    if(distance < normalDistance - 10){
      triggered = true;
    }
    delay(20);
  }
}

