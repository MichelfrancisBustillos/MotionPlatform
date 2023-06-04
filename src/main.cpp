#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFiManager.h>
#include <WebServer.h>
using my_WebServer = WebServer;
#include "custom_servo.h"
#include "webHandler.h"

//Function Definitions
void serialIO();

//Pin Definitions
#define X_SERVO_PIN 32
#define Y_SERVO_PIN 33
#define LED_BUILTIN 2

//Global Variable and Object Definitions
custom_servo x_servo; //Custom servo object for x movement
custom_servo y_servo; //Custom servo object for y movement
WiFiManager wifi; //WiFiManager object
WiFiClient espClient;
std::unique_ptr<my_WebServer> server; //Create web server object

int movement;

void setup() {
  //Initialize Serial Coms
  Serial.begin(115200); //Open serial terminal at 115200 baud rate
  while (!Serial); //Wait until terminal opened
  Serial.println("Serial Initialized!");

  pinMode(LED_BUILTIN, OUTPUT); //Enable onboard LED for status output

  //Initialize Servos
  x_servo.pin = X_SERVO_PIN;
  y_servo.pin = Y_SERVO_PIN;
  y_servo.min = 0;
  y_servo.max = 160;
  y_servo.wait = 700;
  x_servo.min = 0;
  x_servo.max = 160;
  x_servo.wait = 700;
  Serial.println("Servos Initialized!");

  //Initialize Wifi
  WiFi.mode(WIFI_STA); //Set wifi to station (client) mode as desired end state
  wifi.setConfigPortalTimeout(300);
  Serial.println("Connecting to wifi...");
  if(!wifi.autoConnect("ESP32_Setup")) {  //Attempt autoConnect, on fail open portal and wait for connection or timeout
    Serial.println("Wifi failed to connect and hit timeout.");
      delay(3000);
      ESP.restart(); //If still not connected, restart ESP
      delay(5000);
  } else {
    Serial.println("Connected to wifi.");
  }
  server.reset(new my_WebServer(80));
  Serial.println("Wifi Initialized!");
  
  //Initialize WebServer
  server->on("/", handle_OnConnect);
  server->on("/test", handle_OnConnect);
  server->onNotFound(handle_NotFound);
  server->begin();
  Serial.println("Web Server Initialized!");
}

void loop() {
  serialIO();
  wifi.process();
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED); //Turn on onboard LED as wifi status indicator
  server->handleClient();
}

void serialIO(){
  String userInput = "";
  int output;
  if(Serial.available()){
    userInput = Serial.readStringUntil('\n');
    movement = userInput.toInt();
    x_servo.move(movement);
    y_servo.move(movement);
  }
}