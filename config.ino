// FOR KEYPAD TEST
const char *testkey = "123ABCD";

uint8_t config_state_addr = 0;

bool config_check() {
  //Read_from_EEPROM(config_state,)


}

void valves_test() {
  /**
     This is a physical observation test
     Function for testing valves functionality
     Open all valves
     Give 10 seconds delay
     Close all valves
     Observe if all valves opened and closed successfully
   * */
  Serial.println("Opening all valves");
  delay(1000);
  tap1_open();
  tap2_open();
  tap3_open();
  Serial.println("All Valves Should be Open");
  delay(7000);
  Serial.println("Closing All Valves");
  tap1_close();
  tap2_close();
  tap3_close();
  Serial.println("All Valves Should be Closed");
}



bool keypad_test() {
  /**
     Test Keypad test
     1. Declare a Boolean with keypad functionality test
     Declare String variable to contain keyed in variables
     For each character in array, ask user to enter and verify
     Add the keyed value to string
     if loop is done compare the keyed in value with the array
     if keyed in string is same as keytest variable return true,
     else return false and inform user to check keypad connection

   * */
  bool keypad_result = false;
  String keyed;
  // loop through characters of testkey variables
  for (; *testkey; testkey++) {
    while (1) {
      char key = getkey();
      if (key)
      {
        keypadbuzz();
        Serial.println("Key Entered :" + String(key));
        // concatenate to keyed string
        keyed.concat(String(key));
        // break loop
        break;
      }
    }
  }
  // compare strings after loop
  if (keyed == String(testkey))
  {
    keypad_result = !keypad_result;
  }
  return keypad_result;
}


void firstrun() {
  // runs if it is system's first run
  /*
     Checks the following in the sequence specified
     1. LCD Display
     2. Buzzer
     3. RFID Tag Reader
     4. Keypad
     5. Motorized Ball Valves

  */
  // LCD Display Check
  lcd.clear();
  lcddisplay("UBUNTU WATER HUB", "--------------------", "---GETTING  READY---", "--------------------");
  // Buzzer Check
  Buzzer();
  // RFID Tag Reader Check
  lcd.clear();
  lcddisplay("UBUNTU WATER HUB", "--------------------", "----TAP ANY CARD---", "--------------------");
  bool tapped = false;
  while (!tapped) {
    tapped = rfid_test();
  }

  // Keypad Test
  lcd.clear();
  lcddisplay("UBUNTU WATER HUB", "--KEY  IN: 123ABCD--", "--------------------", "PRESS # WHEN DONE");
  bool keyed = false;
  while (!keyed) {
    keyed = keypad_test();
  }

  // Motorized Ball Valves Test
  lcd.clear();
  lcddisplay("UBUNTU WATER HUB", "--------------------", "---TESTING VALVES---", "--------------------");
  valves_test();

}
