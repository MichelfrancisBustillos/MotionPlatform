#ifndef webPage_h
#define webPage_h
#include <WebServer.h>
using my_WebServer = WebServer;

extern std::unique_ptr<my_WebServer> server;
String SendHTML();

void handle_OnConnect(){
    Serial.println("Client connected to web server...");
    server->send(200, "text/HTML", SendHTML());
}

void handle_NotFound(){
    Serial.println("Web Server: 404 Page not found.");
    server->send(404, "text/plain", "Not found");
}

String SendHTML(){
    String ptr = "<!DOCTYPE html>\n";
    ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr +="<title>PTZ Control</title>\n";

    return ptr;
}

#endif