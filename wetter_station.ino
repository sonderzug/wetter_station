
#include "BlueDot_BME280.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Fonts/FreeMono9pt7b.h>
#include "logo.h"

BlueDot_BME280 bme280 = BlueDot_BME280();
const int ledPin = 9;    // LED connected to digital pin 9
const int taster = 2;   //sCHALTER /Taster
          //const int ledIntern = 13; //interne led
          int index = 1; // Zählvariable


int i = 0;

//OLED define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(9600);
 
  pinMode(taster, INPUT_PULLUP);
  pinMode(13, OUTPUT);


  //Setup für das Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //display.setRotation(2);
 
  drawbitmap(); // (überflüsssiges) logo benötigt viel speicher,
  delay(2000);  // bei zu wenig ram entfernen

  display.clearDisplay();


  bme280.parameter.communication = 0;                  //Choose communication protocol
  bme280.parameter.I2CAddress = 0x76;                  //Choose I2C Address



  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************

  //Now choose on which mode your device will run
  //On doubt, just leave on normal mode, that's the default value

  //0b00:     In sleep mode no measurements are performed, but power consumption is at a minimum
  //0b01:     In forced mode a single measured is performed and the device returns automatically to sleep mode
  //0b11:     In normal mode the sensor measures continually (default value)

  bme280.parameter.sensorMode = 0b11;                   //Choose sensor mode



  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************

  //Great! Now set up the internal IIR Filter
  //The IIR (Infinite Impulse Response) filter suppresses high frequency fluctuations
  //In short, a high factor value means less noise, but measurements are also less responsive
  //You can play with these values and check the results!
  //In doubt just leave on default

  //0b000:      factor 0 (filter off)
  //0b001:      factor 2
  //0b010:      factor 4
  //0b011:      factor 8
  //0b100:      factor 16 (default value)

  // bme280.parameter.IIRfilter = 0b011;                    //Setup for IIR Filter
  bme280.parameter.IIRfilter = 0b001;


  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************

  //Next you'll define the oversampling factor for the humidity measurements
  //Again, higher values mean less noise, but slower responses
  //If you don't want to measure humidity, set the oversampling to zero

  //0b000:      factor 0 (Disable humidity measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

  bme280.parameter.humidOversampling = 0b101;            //Setup Humidity Oversampling



  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************

  //Now define the oversampling factor for the temperature measurements
  //You know now, higher values lead to less noise but slower measurements

  //0b000:      factor 0 (Disable temperature measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

  bme280.parameter.tempOversampling = 0b101;             //Setup Temperature Ovesampling



  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************

  //Finally, define the oversampling factor for the pressure measurements
  //For altitude measurements a higher factor provides more stable values
  //On doubt, just leave it on default

  //0b000:      factor 0 (Disable pressure measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

  bme280.parameter.pressOversampling = 0b101;            //Setup Pressure Oversampling



  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************

  //For precise altitude measurements please put in the current pressure corrected for the sea level
  //On doubt, just leave the standard pressure as default (1013.25 hPa)

  bme280.parameter.pressureSeaLevel = 1027;           //default value of 1013.25 hPa

  //Now write here the current average temperature outside (yes, the outside temperature!)
  //You can either use the value in Celsius or in Fahrenheit, but only one of them (comment out the other value)
  //In order to calculate the altitude, this temperature is converted by the library into Kelvin
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C)
  //Remember, leave one of the values here commented, and change the other one!
  //If both values are left commented, the default temperature of 15°C will be used
  //But if both values are left uncommented, then the value in Celsius will be used

  bme280.parameter.tempOutsideCelsius = 10;              //default value of 15°C



  //*********************************************************************
  //*************ADVANCED SETUP IS OVER - LET'S CHECK THE CHIP ID!*******

  if (bme280.init() != 0x60)
  {

    display.display();

    /* // Notwendig?
     * 
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 30);
      display.print("BME280 nicht gefunden");
      display.setCursor(46, 0);
      display.println("FEHLER");
      display.display();
      // delay (200);
        Serial.print(F("Ops! BME280 could not be found!"));
        Serial.println(F("Please check your connections."));
        Serial.println();
        while (1);
      }*/
  }

  else
  {
    Serial.println(F("BME280 detected!"));
  }
  Serial.println();
  Serial.println();


}

void loop() {


  // bool buttonState = digitalRead(pushButton);

  /* if (longPressed && buttonState) {
     Serial.println('2');
    }
    else {
     if (buttonState) {
       Serial.println('1');
       i = i + 1;
       if (i >= 4){
         longPressed = true;
       }
     } else {
       Serial.println('0');
       longPressed = false;
       i = 0;
    }
    }*/
  delay(500);        // delay in between reads for stability

  /*
    if(buttonState == LOW && index <4){
         index = index+1;
       } else if (buttonState == LOW && index ==4){
         delay(1000);
         index = index+1;
       }

      switch(index){
         case 1: zeigeTemperatur(); break;
         case 2: zeigeLuftfeuchtigkeit(); break;
         case 3: zeigeLuftdruck(); break;
         case 4: zeigeAlt(); break;

       }
  */

  //read the pushbutton value into a variable
  int sensorVal = digitalRead(taster);
  //print out the value of the pushbutton
  Serial.println(sensorVal);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }
  //    Serial.print(bme280.readPressure()); Serial.print("\t\t");    // Pressure in millibars
  //    Serial.print(bme280.readHumidity()); Serial.print("%\t\t\t\t");
  //    Serial.print(bme280.readTempC()); Serial.print(" °C\t\t\t");
  //    Serial.print(bme.getTemperature_F()); Serial.println(" °F");
  //

  zeigeLuftfeuchtigkeit();
  // digitalWrite(13, LOW);

  zeigeLuftdruck();
  // digitalWrite(13, LOW);

  zeigeTemperatur();
  // digitalWrite(13, LOW);

  zeigeAlt();
  digitalWrite(13, LOW);




}

void zeigeTemperatur() {

  int var = 0;
  int wertxx = 4;
  while (var < wertxx) {
    int knopf = digitalRead(taster);
    if (knopf == LOW) {
      wertxx = 100;

      digitalWrite(13, HIGH);
    }
    // Zähle Variable x um 1 hoch
    String tempC = String(bme280.readTempC()) + " C";
    displayText("Temperatur", tempC);
    schimmelCheck();
    delay(600);
    var++;


  }
}

void zeigeLuftfeuchtigkeit() {

  int var = 0;
  int wertxx = 4;
  while (var < wertxx) {
    int knopf = digitalRead(taster);
    if (knopf == LOW) {
      wertxx = 100;

      digitalWrite(13, HIGH);
    }
    String humidity = String(bme280.readHumidity()) + "%";
    displayText("Luftfeuchtigkeit", humidity);
    schimmelCheck();
    delay(600);
    var++;
  }
}

void zeigeLuftdruck() {
  int var = 0;
  int wertxx = 4;
  while (var < wertxx) {
    int knopf = digitalRead(taster);
    if (knopf == LOW) {
      wertxx = 100;

      digitalWrite(13, HIGH);
    }
    String pressure = String(bme280.readPressure()) + " hPa";
    displayText("Luftdruck", pressure);
    schimmelCheck();
    delay(600);
    var++;
  }
}

void zeigeAlt() {
  int var = 0;
  int wertxx = 4;
  while (var < wertxx) {
    int knopf = digitalRead(taster);
    if (knopf == LOW) {
      wertxx = 100;

      digitalWrite(13, HIGH);
    }
    String altitude = String(bme280.readAltitudeMeter()) + "m";
    displayText("Altitude", altitude);
    schimmelCheck();
    delay(600);
    var++;
  }
}

void schimmelCheck() {

  if (bme280.readHumidity() > 60 ) {
    // analogWrite(ledPin, bme280.readHumidity());
    schimmelAlarm();

    display.setCursor(15, 50);
    display.setTextSize(1);
    display.println("Schimmel Gefahr!");
    //  display.display();
  }
  else if (bme280.readHumidity() < 60) {
    analogWrite(ledPin, 0);
  }

  if (bme280.readHumidity() < 25) {
    display.setCursor(0, 50);
    display.setTextSize(1);
    display.println("Luft ist sehr trocken");
    //analogWrite(ledPin, 0);
  }
  //else if (bme280.readHumidity() < 60) {
  // analogWrite(ledPin, 0);}



}

void displayText(String row1, String row2) {
  delay(100);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  // display.setTextColor(BLACK, WHITE); //invertiert text
  display.setCursor(5, 0);
  display.println(row1);
  display.setCursor(5, 23);

  display.fillRoundRect(0, 16,  128, 30, 4, WHITE);
  display.setTextColor(BLACK);

  display.setTextSize(2);
  display.println(row2);
  display.display();
  display.setTextColor(WHITE);
  display.clearDisplay();

}


void drawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2 + 3,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}


void schimmelAlarm() {
  delay(50);

  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 5 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }

  // fade out from max to min in increments of 5 points:
  delay(50);
  for (int fadeValue = 255 ; fadeValue >= 5; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }
}
//void oledDisplay(int size, int x,int y, float value, String unit){
// int charLen=12;
// int xo=x+charLen*3.2;
// int xunit=x+charLen*3.6;
// int xval = x;
// display.setTextSize(size);
// display.setTextColor(WHITE);
//
// if (unit=="%"){
//   display.setCursor(x, y);
//   display.print(value,0);
//   display.print(unit);
// } else {
//   if (value>99){
//    xval=x;
//   } else {
//    xval=x+charLen;
//   }
//   display.setCursor(xval, y);
//   display.print(value,0);
//   display.drawCircle(xo, y+2, 2, WHITE);  // print degree symbols (  )
//   display.setCursor(xunit, y);
//   display.print(unit);
//
// }
//
//}
