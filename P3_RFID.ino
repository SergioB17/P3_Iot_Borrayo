#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN  22    //Pin 22 para el reset del RC522
#define SS_PIN  21   //Pin 21 para el SS (SDA) del RC522
#define greenLed 17
#define redLed 16
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Lectura del UID");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Revisamos si hay nuevas tarjetas  presentes
  if( mfrc522.PICC_IsNewCardPresent()) 
  {  
    //Seleccionamos una tarjeta
    if( mfrc522.PICC_ReadCardSerial()) 
    {
      // Enviamos serialmentesu UID
      Serial.print("CardUID:");
      for(byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);   
    } 
    Serial.println();
    // Terminamos la lectura de la tarjeta  actual
    mfrc522.PICC_HaltA();         
    }      
  } 
  else Serial.println("No card... waiting for one");
  delay(1000);
}
