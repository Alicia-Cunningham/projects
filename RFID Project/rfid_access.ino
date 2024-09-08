
 
#include <Wire.h>
#include <Adafruit_PN532.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define SDA_PIN 2
#define SCL_PIN 3
#define LED_PIN 13
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
 
void setup() 
{
  pinMode(13,1);
  pinMode(6,1);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  PN532.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! PN532.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! PN532.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < PN532.uid.size; i++) 
  {
     Serial.print(PN532.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(PN532.uid.uidByte[i], HEX);
     content.concat(String(PN532.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(PN532.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "F9 D1 F3 6E") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(3000);
    digitalWrite(6,1);
    delay(200);
    digitalWrite(6,0);
    delay(200);
    digitalWrite(6,1);
    delay(200);
    digitalWrite(6,0);
    delay(200);
    digitalWrite(6,1);
    delay(200);
    digitalWrite(6,0);
    delay(1000);
  }
  else 
  {
    Serial.println(" Access denied");
    Serial.println();
    //delay(3000);
    digitalWrite(13,1);
    delay(200);
    digitalWrite(13,0);
    delay(200);
    digitalWrite(13,1);
    delay(200);
    digitalWrite(13,0);
    delay(200);
    digitalWrite(13,1);
    delay(200);
    digitalWrite(13,0);
    delay(1000);
  }
 
 
} 
