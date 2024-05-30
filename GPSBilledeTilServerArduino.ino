// Lavet af Mathias Hoppe 24/5 - 2024, Taget inspiration fra Tomasz's k-type Thermocouple code.
//Connect with pin 18 and 19
// Arduino to GPS Pin setup
// 5V(3,3 virker også) to VCC
// GND to GND
// RX1(19) to TX
// TX1 (18) to RX
// Check EAGLE for Arduino to Raspberry
#include <SoftwareSerial.h>
#include <TinyGPS.h>
float lat, lon;  // floats som bruges til at holde latitude og longitude.
TinyGPS gps;     // create gps object

void setup() {
  Serial.begin(9600);                          // connect serial
  Serial.println("The GPS Received Signal:");  // fortæller at setup starter
  Serial1.begin(9600);                         // connect gps sensor
  Serial2.begin(9600);                         // Connect til raspberry til upload https://www.arduino.cc/reference/en/language/functions/communication/serial/

  delay(2000);  // Tid så dele kan starte ordenligt.
}

void loop() {
  while (Serial1.available()) {      // check for gps data
    if (gps.encode(Serial1.read()))  // encode gps data
    {
      gps.f_get_position(&lat, &lon);  // get latitude and longitude

      //Serial.print("Position: ");

      //Latitude
      Serial.print("Latitude: ");
      Serial.print(lat, 6);

      Serial.print(" , ");

      //Longitude
      Serial.print("Longitude: ");
      Serial.println(lon, 6);

      String data = String(lat, 6) + String(",") + String(lon, 6);
      Serial2.println(data); // sender data over UART
      Serial2.println("\n");
      Serial.println("Upload til Raspberry");
    }
  }
}
