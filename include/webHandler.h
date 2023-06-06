#ifndef webHandler_h
#define webHandler_h

extern String sliderValue;
extern custom_servo x_servo;
extern custom_servo y_servo;

String processor(const String& var){
    String valuePlaceHolder = "";
    if(var == "X_SLIDER_VALUE"){
        return sliderValue;
    } else if (var == "X_SERVO_MAX"){
        valuePlaceHolder = x_servo.max;
        return valuePlaceHolder;
    } else if (var == "X_SERVO_MIN"){
        valuePlaceHolder = x_servo.min;
        return valuePlaceHolder;
    }
    return String();
}

void pageNotFound(AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not Found");
}

#endif