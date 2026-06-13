#include "WiFi.h"
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
const char* ssid="Energy 0.2";
const char* password="wififiber";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32test");
  Serial.println("The device started, now you ca pair it with bluetooth");
  WiFi.begin(ssid, password);
  while (WiFi.status()!=WL_CONNECTED){
  delay(500);
  Serial.println("Connecting to WiFi...");
}
  Serial.println("Connected to the WiFi network");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()){
    Serial.write(SerialBT.read());
  }
  delay(20);
}
