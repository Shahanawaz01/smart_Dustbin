#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D7, D8);

int i = 0;

ESP8266WebServer server;

#define TRIGGER_PIN  5
#define ECHO_PIN 4

const char *ssid = "Hacker";
const char *pass = "12345678";

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(2400);
  Serial.begin(2400);
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);

  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);

WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi Connected");
    Serial.println(WiFi.localIP());
    server.on("/",[](){});
    server.begin();
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUILTIN_LED, OUTPUT);
    
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_BUILTIN, LOW);
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(200);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(100);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
  server.handleClient();
  String str = String(distance);
  client.println("Refresh: 5");

  if(distance <5){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

  server.send(200,"text/html","\t\t\t<br><br><h1 align = 'Center'>Welcome to Smart Garbage Monitoring System</h1><br> \n\n\t\t <h3 align = 'center'>Sensor Value is :  "+ str + "</h3>"+ "\n\t\t<br> <h2 align = 'center'>Dustbin is Full</h2>");

if(i==0){

  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+919819710721\"\r");
  delay(1000);
  mySerial.println("Dustbin is full please Clean it ..");
  delay(1000);
  mySerial.println((char)26);
  delay(1000);

  i = 2;
  

  
  } 
    }
    else{
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);

      server.send(200,"text/html","\t\t\t<br><br><h1 align = 'Center'>Welcome to Smart Garbage Monitoring System</h1><br> \n\n\t\t <h3 align = 'center'>Sensor Value is :  "+ str + "</h3>"+ "\n\t\t<br> <h2 align = 'center'>Dustbin is not Full</h2>");

      i = 0;


      
      }

      delay(500);
      delay(1000);
  
  
  

}
