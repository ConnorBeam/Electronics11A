#include <Wire.h>
#include <SI114X.h>
#include <TimerOne.h>
#include <Encoder.h>
#include <SeeedOLED.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHT11_PIN A0
DHT dht(DHT11_PIN, DHTTYPE);
SI114X SI1145 = SI114X();

int moisture, moisturethreshold;
int moisturePin = A1;
int moistureValue = 0;
int index_LED;
float uvIndex;

void setup() {
  Wire.begin();
  SeeedOled.init();
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(4, INPUT);
  encoder.Timer_init();
  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0, 0);         //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("0 moisture");
  while (digitalRead(4) == LOW) {
    if (encoder.rotate_flag == 1)
    {
      if (encoder.direct == 1)
      {
        index_LED++;
        if (index_LED > 100) {
          index_LED = 100;
        }
        Serial.println(index_LED);
        SeeedOled.setTextXY(0, 0);
        SeeedOled.putNumber(index_LED);
        SeeedOled.putString(" moisture");
        SeeedOled.setTextXY(1, 0);
        SeeedOled.putString("Water Pump Test");
      }
      else
      {
        index_LED--;
        if (index_LED < 0) {
          index_LED = 0;
        }
        Serial.println(index_LED);
        SeeedOled.setTextXY(0, 0);
        SeeedOled.putNumber(index_LED);
        SeeedOled.putString(" moisture");
        SeeedOled.setTextXY(1, 0);
        SeeedOled.putString("Water Pump Test");
      }
      encoder.rotate_flag = 0;
    }
  }
  SeeedOled.clearDisplay();
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("Threshold Set");
  SeeedOled.setTextXY(1, 0);
  SeeedOled.putString("To ");
  SeeedOled.putNumber(index_LED);
  SeeedOled.putString(" percent");
}

void loop() {
  moisture = map(analogRead(moisturePin), 0, 1023, 0, 100);
  if (index_LED <= moisture) {
    Serial.println("threshold broken");
    SeeedOled.setNormalDisplay();       //Set display to Normal mode
    SeeedOled.clearDisplay();
    SeeedOled.setPageMode();
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("For ");
    SeeedOled.putNumber(2);
    SeeedOled.putString(" Seconds");
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("Pumping water");
    delay(20);
    digitalWrite(6, HIGH);
    Serial.print("Pumping water for ");
    Serial.print("2");
    Serial.println(" Second(s)");
    delay(2000);
    digitalWrite(6, LOW);
    delay(20);
    moisture = map(analogRead(moisturePin), 0, 1023, 0, 100);
    Serial.print("Moisture = " );
    Serial.println(moisture);
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("Threshold Set");
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("To ");
    SeeedOled.putNumber(index_LED);
    SeeedOled.putString(" percent");
  }
  if (digitalRead(4) == HIGH) {
    delay(500);
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("Set new");
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("Threshold");
    while (digitalRead(4) == LOW) {
      if (encoder.rotate_flag == 1)
      {
        if (encoder.direct == 1)
        {
          index_LED++;
          if (index_LED > 100) {
            index_LED = 100;
          }
          Serial.println(index_LED);
          SeeedOled.setTextXY(0, 0);
          SeeedOled.putNumber(index_LED);
          SeeedOled.putString(" moisture");
          SeeedOled.setTextXY(1, 0);
          SeeedOled.putString("Water Pump Test");
        }
        else
        {
          index_LED--;
          if (index_LED < 0) {
            index_LED = 0;
          }
          Serial.println(index_LED);
          SeeedOled.setTextXY(0, 0);
          SeeedOled.putNumber(index_LED);
          SeeedOled.putString(" moisture");
          SeeedOled.setTextXY(1, 0);
          SeeedOled.putString("Water Pump Test");
        }
        encoder.rotate_flag = 0;
      }
    }
    delay(500);
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("Threshold Set");
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("To ");
    SeeedOled.putNumber(index_LED);
    SeeedOled.putString(" percent");
  }
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  uvIndex = SI1145.ReadUV() / 100;
  if (uvIndex >= 7) {
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("HIGH UV ");
    SeeedOled.putNumber(uvIndex);
  }
  if (uvIndex < 7) {
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("           ");
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("UV ");
    SeeedOled.putNumber(uvIndex);
  }
  SeeedOled.setTextXY(3, 0);
  SeeedOled.putString("Humid:");
  SeeedOled.putNumber(h);
  SeeedOled.putString(" Temp:");
  SeeedOled.putNumber(t);
  moisture = map(analogRead(moisturePin), 0, 1023, 0, 100);
  SeeedOled.setTextXY(4, 0);
  SeeedOled.putString("Moisture: ");
  SeeedOled.putNumber(moisture);
  SeeedOled.putString("%");
  SeeedOled.setTextXY(5, 0);
  SeeedOled.putString("Hold button to");
  SeeedOled.setTextXY(6, 0);
  SeeedOled.putString("Change threshold");
}
