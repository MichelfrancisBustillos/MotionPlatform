# Custom Servo Class Description and Notes

## Variables

- *servo*: object of the Servo class from ESP32Servo library. Can be used to chain commands directly to the servo (i.e. custom_servo.servo.write(stepValue))
- *max*: Maximum stepper value
- *min*: Minimum stepper value
- *pin*: GPIO pin number. Used for *attach* and *detach* commands.
- *wait*: Time to wait between servo moves in milliseconds. Allows servo to reach desired position before moving on to the next command.
- *current_position*: A placeholder for storing the current position of the servo. Especially useful when sensor feedback is not available. Ideally, used with the *home()* function to ensure accurate starting value. Avoid talking to the servo directly (i.e. via *servo.write()*) to ensure position remains accurate.
- Center: Center of the servos range. Calculated by *(max + min) / 2*. Can be useful when homing.
- *home_position*: Step value desired position of the servo when homing

## Functions

- *moveToStep(int)*: Takes an integer value and moves the stepper to that value. Includes safety to ensure that value is in range before moving as well as updates *current_position* to new value.
- *home()*: Moves stepper to the value defined by *home_position*
