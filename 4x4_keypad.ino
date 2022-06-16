#include <Keypad.h>
//uint8_t buzz = 44; //pin 44 for the Buzzer

#define Master_Password_Length 5
#define Password_Length 5

char Password[Password_Length];
char Master[Password_Length];

uint8_t position_count;
uint8_t password_addr =7;
bool keypad_check = true;
bool password_entered = false;
bool password_created = false;

char Key;
char Array[15];



char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );

char getkey() {
  char key = keypad.getKey();
  if (key)
  {
    return key;
  }
  else
  {
    return NULL;
  }
  
}

void reset_data_array(uint8_t array_size) {             //This function clears the data array

  for (int i = 0; i < array_size; i++) {
    Array[i] = 0x00;
  }
  position_count = 0;
  keypad_check = true;
  lcd.clear();
}

// void copy_array_data(uint8_t array_size) {                      //This function copies data from the main array in the keypad_listen function
//   // to specific data arrays such as MPESANO etc
//   if (array_size == Password_Length && password_created == false) {

//     strcpy(Master, Array);                                      //Copy Data to the MASTER password array
//     Write_to_EEPROM(Master, Password_Length - 1, password_addr); //Write the password to the EEPROM
//     password_created = true;                                    //This flag helps to identify if the password has been created

//   } else if (array_size == Password_Length  && password_created == true ) {

//     strcpy(Password, Array);
//     password_entered = true;                        //This flag helps to identify if the password has been keyed in

//   } else if (array_size == Mpesano_length) {

//     strcpy(Mpesano, Array);

//   } else if (array_size == Mpesaamt_length) {

//     strcpy(Mpesaamt, Array);

//   } else if (array_size == Dispenseamt_length) {

//     strcpy(Dispenseamt, Array);

//   }

// }

void keypad_listen(uint8_t array_size, uint8_t cursor_pos) {
  Key = keypad.getKey();

  if (Key) {
    keypadbuzz();                //Feedback for the user
  }

  if (Key == 'D') {
    keypad_check = true;             //Listen to the keypad
    if (position_count == 0) {       //Do nothing to prevent the cursor from moving to an undesired position

    } else {
      position_count--;
      Array[position_count] = 0x00;   //Clear the position
      lcd_keypad_display(" ", position_count, cursor_pos);   //Display "Space" on the LCD
    }

  }
  else if (Key == 'C') {
    keypad_check = true;              //Listen to the keypad
    reset_data_array(array_size);     //Clear the data array
    create_password_screen();

  }

  else  if (Key && keypad_check == true) {          //if the the key pressed is not 'D' or 'C', fill up the array with the keyed in data

    Array[position_count] = Key;
    lcd_keypad_display(&Array[position_count], position_count, cursor_pos);     //display the key pressed
    position_count++;

  }

  else if ( position_count == array_size - 1 ) {
    keypad_check = false;                            //If the specified array size has been reached, Don't listen other keys other than #
    if (Key == '#') {
      lcd.clear();
      lcd_keypad_display("Data Saved!", 0, 0);
      delay(1000);
      // copy_array_data(array_size);                  //Copy the data to specifc arrays as illustrated in the function
      reset_data_array(array_size);                 //Clear the data array

    }
  }
}

boolean keypad_listen_specific(char listenkey) {
Key = keypad.getKey();

  if (Key) {
    keypadbuzz();                //Feedback for the user
  }

  if (Key == listenkey) {
    return true;
  }
  else {
    return false;
  }
}

char keypad_listen_return() {
Key = keypad.getKey();

  if (Key) {
    keypadbuzz();                //Feedback for the user
    return Key;
  }
  else {
    return NULL;
  }
}


void createpass() {

  create_password_screen();
  keypad_listen(Password_Length , 2);

}

void check_password() {

  enter_password_screen();
  keypad_listen(Password_Length , 2);

  if (password_entered == true ) {                                    //Only compare the two if the password has been keyed in
    Read_from_EEPROM(Master, Password_Length - 1, password_addr);    //Read password from the EEPROM

    Serial.println(Master);
    if (strcmp (Master, Password) == 0) {                             //compare the Master Password and the entered password
      lcd.clear();
      lcddisplay("WELCOME!", "", "", "");
      delay(1000);
      lcd.clear();

    } else  {    //Only compare the two if the password has been keyed in
      password_entered = false;
      lcd.clear();
      lcddisplay("INCORRECT PASSWORD!", "", "", "");
      delay(1000);
      lcd.clear();
    }
  }
}
