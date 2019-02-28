int pin_LEDgreen = 13;
int pin_LEDyellow = 12;
int pin_LEDred = 11;

int pin_switch = 5;

// variables to hold the new and old switch states
boolean oldSwitchState = LOW;
boolean newSwitchState1 = LOW;
boolean newSwitchState2 = LOW;
boolean newSwitchState3 = LOW;

byte state = 0;
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
int count = 0;
void setup(void)
{
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");

  pinMode(pin_LEDgreen, OUTPUT);    digitalWrite(pin_LEDgreen, LOW);
  pinMode(pin_LEDyellow, OUTPUT);   digitalWrite(pin_LEDyellow, LOW);
  pinMode(pin_LEDred, OUTPUT);      digitalWrite(pin_LEDred, LOW);

  pinMode(pin_switch, INPUT);
  Serial.println("Magnetometer Test"); Serial.println("");

  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1);
  }
}

void loop(void)
{
  newSwitchState1 = digitalRead(pin_switch);
  delay(1);
  newSwitchState2 = digitalRead(pin_switch);
  delay(1);
  newSwitchState3 = digitalRead(pin_switch);

  // if all 3 values are the same we can continue
  if (  (newSwitchState1 == newSwitchState2) && (newSwitchState1 == newSwitchState3) )
  {

    if ( newSwitchState1 != oldSwitchState )
    {

      // has the button switch been closed?
      if ( newSwitchState1 == HIGH )
      {
        // increase the value of state
        state++;
        if (state > 3) {
          state = 0;
        }

        // turn all LEDs off. Doing it this way means we do not need to care about the individual LEDs
        // simply turn them all off and then turn on the correct one.
        digitalWrite(pin_LEDgreen, LOW);
        digitalWrite(pin_LEDyellow, LOW);
        digitalWrite(pin_LEDred, LOW);

        // Turn on the next LED
        // Because the value of state does not change while we are testing it we don't need to use else if
        if (state == 1) {
          digitalWrite(pin_LEDgreen, HIGH);
          Serial.println("green");
        }
        if (state == 2) {
          digitalWrite(pin_LEDyellow, HIGH);
          Serial.println("yellow");
        }
        if (state == 3) {
          digitalWrite(pin_LEDred, HIGH);
          Serial.println("red");
        }

      }
      oldSwitchState = newSwitchState1;
    }
  }
  if (count >= 100) {
    sensors_event_t event;
    mag.getEvent(&event);

    float Pi = 3.141592653238;

    // Calculate the angle of the vector y,x
    float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;

    // Normalize to 0-360
    if (heading < 0)
    {
      heading = 360 + heading;
    }
    Serial.print("Compass Heading: ");
    Serial.println(heading);
    count=0;
  }
  count++;
  delay(1);
}
