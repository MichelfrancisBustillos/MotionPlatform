#ifndef webHandler_h
#define webHandler_h

extern String sliderValue;
extern custom_servo x_servo;
extern custom_servo y_servo;

String processor(const String& var){
    if(var == "Y_SLIDER_VALUE"){
        return sliderValue;
    } else if (var == "Y_SERVO_MAX"){
        return String(y_servo.max);
    } else if (var == "Y_SERVO_MIN"){
        return String(y_servo.min);
    }
    return String();
}

void pageNotFound(AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not Found");
}

#endif