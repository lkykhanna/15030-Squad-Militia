#include <SPI.h>
#include <MFRC522.h>
int play =6;
 
#define SS_PIN 5
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(play, OUTPUT);
  digitalWrite(play,LOW);
  Serial.println("Put your card to the reader for scanning ...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "4A 98 43 3F") 
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(play,HIGH);
    delay(12000);
    digitalWrite(play,LOW);
    
    
  }
 
 else   {
    Serial.println(" Access denied");
    delay(500);
    digitalWrite(play, LOW);
   
  }
}
