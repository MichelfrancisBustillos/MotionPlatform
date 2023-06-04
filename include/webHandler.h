#ifndef webPage_h
#define webPage_h
#include <WebServer.h>
using my_WebServer = WebServer;

extern std::unique_ptr<my_WebServer> server;
extern bool status_led;
String SendHTML(bool);

void handle_OnConnect(){
    Serial.println("Client connected to web server...");
    server->send(200, "text/HTML", SendHTML(status_led));
}

void handle_NotFound(){
    Serial.println("Web Server: 404 Page not found.");
    server->send(404, "text/plain", "Not found");
}

void handle_LedOn(){
    Serial.println("LED ON");
    status_led = 1;
    digitalWrite(2, HIGH);
    server->send(200, "text/HTML", SendHTML(status_led));
}

void handle_LedOff(){
    Serial.println("LED OFF");
    status_led = 0;
    digitalWrite(2, LOW);
    server->send(200, "text/HTML", SendHTML(status_led));
}

String SendHTML(bool status_led){
    String ptr = "<!DOCTYPE html>\n";
    ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr +="<title>PTZ Control</title>\n";
    ptr +="<h1>PTZ Control</h1>\n";
    ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr +=".button-on {background-color: #3498db;}\n";
    ptr +=".button-on:active {background-color: #2980b9;}\n";
    ptr +=".button-off {background-color: #34495e;}\n";
    ptr +=".button-off:active {background-color: #2c3e50;}\n";
    ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr +="</style>\n";
    ptr +="</head>\n";
    ptr +="<body>\n";
    if(status_led)
    {ptr +="<p>LED Status: ON</p><a class=\"button button-off\" href=\"/led_off\">OFF</a>\n";}
    else
    {ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/led_on\">ON</a>\n";}

    ptr +="</body>\n";
    ptr +="</html>\n";
    return ptr;
}

#endif