#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo myServo;
int servoPin = D2;       // The port of Servor Motor

const int trig = D1;     // The port of HC-SR04
const int echo = D0;     // The port of HC-SR04


char auth[] = "QpfWcHrq421b48bsVc1r2dnURdvOuPfE";//Enter Auth token
char ssid[] = "iPhone";                          //Enter WIFI name
char pass[] = "asd12345";                        //Enter WIFI password

float GetDistance(){
    unsigned long duration;    // Measure time
    int distanceCm;            // Measure distance
    
    /* Setting the trig */
    digitalWrite(trig,0);   // Turn off trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // Turn on trig
    delayMicroseconds(5);
    digitalWrite(trig,0);   // Turn off trig
    
    /* Measure time */
    // Measure the HIGH signal at echo pin. 
    duration = pulseIn(echo,HIGH);  
    // Measure distance to the object.
    distanceCm = int(duration/2/29.412);
    delay(200);
  
  return distanceCm;
}

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin); 
  myServo.write(180);
  pinMode(trig,OUTPUT);   // trig pin release a signal
  pinMode(echo,INPUT);    // echo pin catch the signal
  
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run(auth);
  
  long distance = GetDistance();
  Serial.println(distance);
  if (distance <= 0)
  {
    Serial.println("Overtime !!");
  }
  else
  {   
    Serial.print("Distance (cm): ");
    Serial.println(distance);
  }
 
  if (distance < 20) {
     runServo();
  }
}

void runServo() {
  myServo.write(40);  // Servo Motor start
  delay(4000);
  myServo.write(180); // Servo Motor back to position
  delay(1000);
}

BLYNK_WRITE(V0) {
   myServo.write(param.asInt());  // Control the Servo Motor through Blynk
}
