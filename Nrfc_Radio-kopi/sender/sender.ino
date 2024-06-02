#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(1, 4); // CE, CSN
const byte address[6] = "00001";
int xAxis, yAxis;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS); // Set data rate to 250KBPS
  radio.setChannel(108); // Set the channel to 108
  radio.stopListening();
}

void loop() {
  xAxis = analogRead(A5); // Read Joysticks X-axis
  yAxis = analogRead(A7); // Read Joysticks Y-axis
  
  // Create a data array to send both X and Y values together
  int dataToSend[2] = {xAxis, yAxis};

  // Send the data
  bool result = radio.write(&dataToSend, sizeof(dataToSend));

  // Print the sent values and status for debugging
  Serial.println("Sent DATA: ");
  //Serial.print("X: ");
  //Serial.print(xAxis);
  //Serial.print(" Y: ");
  //Serial.print(yAxis);
  Serial.print(" Status: ");
  Serial.println(result ? "OK" : "Fail");

  delay(1000); // Delay for readability
}
