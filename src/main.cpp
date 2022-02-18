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
  int number_get = 6;
  String cmd_get[number_get];
  cmd_get[0] = "AT\r\n";                    // +OK
  cmd_get[1] = "AT+IPR?\r\n";               // +IPR=115200
  cmd_get[2] = "AT+PARAMETER?\r\n";         // +PARAMETER=12,7,1,4
  cmd_get[3] = "AT+BAND?\r\n";              // 
  cmd_get[4] = "AT+ADDRESS?\r\n";           //
  cmd_get[5] = "AT+NETWORKID?\r\n";         //

  for (int i=0; i<number_get; i++) {
    LoRa.print(cmd_get[i]); // 
    delay(1500);
    if (LoRa.available()) { // Module's response to AT command
      String response = LoRa.readString();
      Serial.print("Nodemcu sent <");
      Serial.print(cmd_get[i]);
      Serial.print(" > and RYLR890 Tx responded: <");
      Serial.print(response);
      Serial.println(">.");
    }
  }

  bool debug = false; // CHange to false when ID configured or true to configure
  int number_set = 3;
  String cmd_set[3];
  cmd_set[0] = "AT+PARAMETER=7,3,4,5\r\n";
  cmd_set[1] = "AT+ADDRESS=120\r\n";
  cmd_set[2] = "AT+NETWORKID=6\r\n";

  if (debug) {
    for (int i=0; i<number_set; i++) {
      LoRa.print(cmd_set[i]); // 
      delay(1500);
      if (LoRa.available()) { // Module's response to AT command
        String response = LoRa.readString();
        Serial.print("Nodemcu sent <");
        Serial.print(cmd_set[i]);
        Serial.print(" > and RYLR890 Tx responded: <");
        Serial.print(response);
        Serial.println(">.");
      }
    }
  }
}