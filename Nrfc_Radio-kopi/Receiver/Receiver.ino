#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN
const byte address[6] = "00001";
int xAxis, yAxis;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS); // Set data rate to 250KBPS
  radio.setChannel(108); // Set the channel to 108
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    // Create an array to store the received data
    int receivedData[2] = {0, 0};

    // Read the data into the array
    radio.read(&receivedData, sizeof(receivedData));

    // Extract X and Y values from the array
    xAxis = receivedData[0];
    yAxis = receivedData[1];
    
    // Print the received values for debugging
    Serial.println("Received DATA ");
   // Serial.print(xAxis);
    //Serial.print(" Y: ");
    //Serial.println(yAxis);
  } else {
    Serial.println("No data available");
  }

  delay(1000); // Delay for readability
}


