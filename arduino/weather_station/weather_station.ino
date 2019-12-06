#include<Wire.h>
#include<SPI.h>
#include<SFE_BMP180.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#define setPin 6

//data are organized in a structure
struct mydata {
  float temperature;
  float pressure;
};
typedef struct mydata MyData;
MyData data;


// Initialize BMP180 sensor
SFE_BMP180 bmp180;

// create HC-RF object
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

int sensorNum = 1;
String sensorType = "TEMP";

unsigned long seconds = 1000L; 
unsigned long minutes = seconds * 60;
int output;


byte incomingByte;
String readBuffer = "";

void setup() {

////  pinMode(setPin, OUTPUT);              // Output High for Transparent / Low for Command.
////  digitalWrite(setPin, HIGH);           // HC-12 normal, transparent mode.
//  delay(80);                            // 80 ms delay before operation per datasheet.
  
  Serial.begin(9600);                   // Open serial port to computer.
  HC12.begin(9600);                     // Open serial port to HC12.

  bool success = bmp180.begin();
  if (success) {
    Serial.println("succeed");
  }
  else {
    Serial.println("Not succed");
    while(1); // Pause forever
  }

}

 
void loop() {

  char status;
  double T, P;
  bool success = false;
  char output[7];
  
  status = bmp180.startTemperature();
  if (status != 0) {
    delay(status);
    status = bmp180.getTemperature(T);
    data.temperature = T;

    if (status != 0) {
      status = bmp180.startPressure(3);
      
      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);
        data.pressure = P;
      }
    }
  }
  
  Serial.print("Temperature: ");
  Serial.print(data.temperature);
  Serial.println(" C");
  
  Serial.print("absolute pressure: ");
  Serial.print(P,2);
  Serial.println(" mb, ");
  

  dtostrf(data.temperature,5, 2, output);
  HC12.write(output);                         // Send to the other module
  HC12.write("#");
  dtostrf(data.pressure,6, 2, output);
  HC12.write(output);                         // Send to the other module


  delay(3000);  
}
