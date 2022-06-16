#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
uint8_t signalindicator_1[8] = {B00011, B00011, B11011, B11011, B11011, B11011, B11011, B11011};
uint8_t signalindicator_2[8] = {B00000, B00000, B00000, B00000, B00011, B00011, B11011, B11011};

void lcd_20x4_init()
{
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, signalindicator_1);
  lcd.createChar(1, signalindicator_2);
}

void lcd_keypad_display(char *message, uint8_t x, uint8_t y)
{ // This is a dynamic LCD display function that can take a pointer variable as a message and display it on the x and y parameters of the LCD
  lcd.setCursor(x, y);
  lcd.print(message);
}
void lcddisplay(String firstline, String secondline, String thirdline, String fourthline)
{
  lcd.setCursor(0, 0);
  if (firstline == "")
  {
    lcd.print(" ");
  }
  else
  {
    lcd.print(firstline);
  }

  lcd.setCursor(0, 1);
  if (secondline == "")
  {
    lcd.print("");
  }
  else
  {
    lcd.print(secondline);
  }

  lcd.setCursor(0, 2);
  if (thirdline == "")
  {
    lcd.print("");
  }
  else
  {
    lcd.print(thirdline);
  }

  lcd.setCursor(0, 3);
  if (fourthline == "")
  {
    lcd.print("");
  }
  else
  {
    lcd.print(fourthline);
  }
}

void blankscreen()
{
  /*************Custom Character Screens******************/
  lcd.setCursor(19, 0);
  lcd.write(0);
  lcd.setCursor(18, 0);
  lcd.write(1);
  /*************Custom Character Screens******************/
}

void clearscreen()
{
  lcd.clear();
  delay(500);
  blankscreen();
}

void create_password_screen()
{
  lcddisplay("Create a 4 Digit Pin", "Then Press #", "", "");
}

void enter_password_screen()
{
  lcddisplay("Enter 4 Digit Pin", "Then Press #", "", "");
}



void homescreen()
{
  clearscreen();
  lcddisplay("", "Tap Tag Here", "Press # for M-Pesa", "");
}

/****Mpesa Pay Screens****/
void mpesascreen()
{
  clearscreen();
  lcddisplay("", "Enter M-Pesa Number", "", "*>Cancel       #>Ok");
}

void amtscreen()
{
  clearscreen();
  lcddisplay("", "Enter Amount", "KES: ", "*>Cancel       #>Ok");
}

void mpesa_wait_screen() {
  clearscreen();
  lcddisplay("PROCESSING", "TRANSACTION", "", "PLEASE WAIT...");
}

void mpesa_error_screen() {
  clearscreen();
  lcddisplay("COULD NOT COMPLETE", "TRANSACTION", "", "TRY AGAIN...");
}

void tap_select_screen() {
  clearscreen();
  lcddisplay("SELECT TAP:", "TAP 1 -> PRESS 1", "TAP 2 -> PRESS 2", "TAP 3 -> PRESS 3");
}

void tap_ready_screen(char tapselected) {
  clearscreen();
  lcddisplay("TAP " + String(tapselected) + " READY IN", "", "", "PRESS * TO CANCEL");
}
/****Mpesa Pay Screens****/

/****Card Pay Screens****/
void card_payprompt_screen() {
  clearscreen();
  lcddisplay("SELECT:", "1 -> TO DISPENSE", "2 -> TO TOP UP", "PRESS * TO CANCEL");
}
/****Card Pay Screens****/
