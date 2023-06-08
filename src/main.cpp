#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFiManager.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "custom_servo.h"
#include "webHandler.h"

// Function Definitions
void serialIO();
void servoJog(String);
void servoHomeAll();

// Pin Definitions
#define X_SERVO_PIN 32
#define Y_SERVO_PIN 33
#define LED_BUILTIN 2

// Global Variable and Object Definitions
custom_servo x_servo;      // Custom servo object for x movement
custom_servo y_servo;      // Custom servo object for y movement
WiFiManager wifi;          // WiFiManager object
WiFiClient espClient;      // WiFiClient object
AsyncWebServer server(80); // Create web server object
int movement;              // Global variable for storing movement values

void setup()
{
  // Initialize Serial Coms
  Serial.begin(115200); // Open serial terminal at 115200 baud rate
  while (!Serial)
    ; // Wait until terminal opened
  Serial.println("Serial Initialized!");

  pinMode(LED_BUILTIN, OUTPUT); // Enable onboard LED for status output

  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("ERROR MOUNTING SPIFFS!");
  }
  else
  {
    Serial.println("SPIFFS Initialized!");
  }

  // Initialize Servos
  x_servo.pin = X_SERVO_PIN;
  y_servo.pin = Y_SERVO_PIN;
  y_servo.min = 0;
  y_servo.max = 160;
  y_servo.wait = 700;
  y_servo.home_position = y_servo.center;
  x_servo.min = 0;
  x_servo.max = 160;
  x_servo.home_position = x_servo.center;
  x_servo.wait = 700;
  servoHomeAll();
  Serial.println("Servos Initialized!");

  // Initialize Wifi
  WiFi.mode(WIFI_STA); // Set wifi to station (client) mode as desired end state
  wifi.setConfigPortalTimeout(300);
  Serial.println("Connecting to wifi...");
  if (!wifi.autoConnect("ESP32_Setup"))
  { // Attempt autoConnect, on fail open portal and wait for connection or timeout
    Serial.println("Wifi failed to connect and hit timeout.");
    delay(3000);
    ESP.restart(); // If still not connected, restart ESP
    delay(5000);
  }
  else
  {
    Serial.println("Wifi Initialized!");
  }

  // Initialize WebServer
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(SPIFFS, "/index.html", String(), false); // Load home page
            });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(SPIFFS, "/style.css", "text/css"); // Load CSS style sheet
            });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/script.js", "text/css"); });
  server.on("/action", HTTP_POST, action);
  server.onNotFound(pageNotFound);
  server.begin();
  Serial.println("Web Server Initialized!");

  Serial.println("SETUP COMPLETE!");
}

void loop()
{
  wifi.process();
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED); // Turn on onboard LED as wifi status indicator
  serialIO();
}

void serialIO()
{
  if (Serial.available())
  {
    String message_received = Serial.readString();
    Serial.print("Echo: ");
    Serial.println(message_received);
    servoJog(message_received);
    Serial.println("~");
  }
}

void servoJog(String direction)
{
  int jogStep = 1;
  if (direction == "Left")
  {
    x_servo.moveToStep(x_servo.current_position + jogStep);
  }
  else if (direction == "Right")
  {
    x_servo.moveToStep(x_servo.current_position - jogStep);
  }
  else if (direction == "Up")
  {
    y_servo.moveToStep(y_servo.current_position + jogStep);
  }
  else if (direction == "Down")
  {
    y_servo.moveToStep(y_servo.current_position - jogStep);
  }
  else if (direction == "Home")
  {
    servoHomeAll();
  }
}

void servoHomeAll()
{
  Serial.println("Homing all servos...");
  x_servo.home();
  y_servo.home();
}