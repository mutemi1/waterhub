///RFID///
#include <SPI.h>
#include <MFRC522.h>

// Create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN);

// check system status if a card has been tapped
bool cardtapped = false;
char* cardid;
String cardidval = "";

// variable getters and setters
String get_cardid() { return cardidval; }

/**RFID FUNCTIONS**/
void rfid_init() {
  SPI.begin();
  mfrc522.PCD_Init();
}

bool rfid_test() {
  bool tapped = false;
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return tapped;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return tapped;
  }
  Serial.print("UID tag :");
  String content = "";

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
    cardidval.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  cardid = &content[0];
  if (cardid != "")
  {
    Serial.println();
    Serial.println(cardid);
    tapped = !tapped;
  }

  return tapped;
}

char scan_card() {
  bool tapped = false;
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return tapped;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return tapped;
  }
  Serial.print("UID tag :");
  String content = "";

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
    cardidval.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  cardid = &content[0];
  if (cardid != "")
  {
    return cardid;
  }
  else {
    return NULL;
  }
}
//void tagcheck() {
//  if (!cardtapped) {
//  // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent())
//  {
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial())
//  {
//    return;
//  }
//  //Show UID on serial monitor
//  Serial.print("UID tag :");
//  String content="";
//
//  for (byte i = 0; i < mfrc522.uid.size; i++)
//  {
//    content.concat(String(mfrc522.uid.uidByte[i], HEX));
//    cardidval.concat(String(mfrc522.uid.uidByte[i], HEX));
//  }
//  cardid = &content[0];
//  Serial.println();
//  Serial.println(cardid);
//
//  //  // if system is at init state
//  if (initstate) {
//    // select tag mode
//    /*
//     * If card has been tapped and system is in init state
//     * Set cardtapped flag to true
//     * Serial.print that card option has been selected
//     * run cardpayoption function
//     */
//    cardtapped = !cardtapped;
//    Serial.println("Card Option Selected");
////    cardoption();
//    tagbalancequery();
//  }
//  else {
//    if (paymodeselected == 1) {
//      tagpay('T');
//    }
//    else if (paymodeselected == 2) {
//      mpesapay('T');
//    }
//    else {
//      Serial.println("Payment Option Not Selected Yet");
//    }
//  }
//  }
//}
/*****************************************RFID FUNCTIONS*****************************************/