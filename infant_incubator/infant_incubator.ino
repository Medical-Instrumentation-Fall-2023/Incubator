
//color start
#define S0 2 // digital pin 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
int frequency = 0;
// color end

//temp start
#include <dht.h>        // Include library

#define outPin_1 7     // Defines digital pin number for the first sensor
#define outPin_2 8     // Defines digital pin number for the second sensor
dht DHT1;               // Creates a DHT object for the first sensor
dht DHT2;               // Creates a DHT object for the second sensor
//temp end

// us start
int trigger_pin = 9;
int echo_pin = 10;
int buzzer_pin = 11; 
int time;
int distance; 
//us end

// relay start
int RelayPin = 12; // digital pin 12
//relay end

void setup() {
  //color start
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  //color end 
  //us start
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  //us end
  //relay start
  pinMode(RelayPin, OUTPUT);
  //relay end
  Serial.begin(9600);
}

void loop() {
  //color start
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 128, 18, 0, 255);
  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(100);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 128, 17, 0, 255);
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(100);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 16, 110, 255, 0);
  Serial.print("B= ");
  Serial.print(frequency);
  Serial.println("");
  Serial.println("-------------------------------------");
  delay(500);
  //color end

  // temp start
  int readData_1 = DHT1.read11(outPin_1);
  int readData_2 = DHT2.read11(outPin_2);
  float t1 = DHT1.temperature;
  float h1 = DHT1.humidity;
  float t2 = DHT2.temperature;
  float h2 = DHT2.humidity;
  Serial.print("The Average Temperature = ");
  Serial.print((t1 + t2) / 2);
  Serial.print("°C | ");
  Serial.print((t1 * 9.0) / 5.0 + 32.0);
  Serial.println("°F ");
  Serial.print("The Average Humidity = ");
  Serial.print((h1 + h2) / 2);
  Serial.println("% ");
  Serial.println("");

  if ((t1 + t2) / 2 < 32) {
    digitalWrite(RelayPin, HIGH);
    digitalWrite(buzzer_pin, HIGH);
  } else {
    digitalWrite(RelayPin, LOW);
    digitalWrite(buzzer_pin, LOW);
  }
  Serial.println("-------------------------------------");
  //temp end

  //us start
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  time = pulseIn(echo_pin, HIGH);
  distance = (time * 0.034) / 2;

  if (distance >= 17) {
    digitalWrite(buzzer_pin, HIGH);
    delay(20);
  } else {
    digitalWrite(buzzer_pin, LOW);
    delay(20);
  }
  //us end

  delay(20);  
}
