#include <Arduino.h>
#include <SoftwareSerial.h>

#define Rx D7
#define Tx D8

SoftwareSerial LoRa(Rx, Tx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait!
  }
  Serial.println("Serial bus ready!");

  LoRa.begin(115200);
  Serial.println("LoRa module ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  String cmd[7];
  cmd[0] = "AT\r\n";                    // +OK
  cmd[1] = "AT+IPR?\r\n";               // +IPR=115200
  cmd[2] = "AT+PARAMETER?\r\n";         // +PARAMETER=12,7,1,4
  cmd[3] = "AT+PARAMETER=7,3,4,5\r\n";  // Recommended
  cmd[4] = "AT+BAND?";
  cmd[5] = "AT+ADDRESS?";
  cmd[6] = "AT+NETWORKID?";


  for (int i=0; i<7; i++) {
    LoRa.print(cmd[i]); // 
    delay(1500);
    if (LoRa.available()) { // Module's response to AT command
      String response = LoRa.readString();
      Serial.print("Nodemcu sent <");
      Serial.print(cmd[i]);
      Serial.print(" > and RYLR890 Tx responded: <");
      Serial.print(response);
      Serial.println(">.");
    }
  }
}