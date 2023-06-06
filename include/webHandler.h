#ifndef webHandler_h
#define webHandler_h

extern void servoJog(String);

void pageNotFound(AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not Found");
}

void action(AsyncWebServerRequest *request) {
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter* p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
    servoJog(p->name().c_str());
  }
  request->send(SPIFFS, "/index.html", String(), false);
}

#endif