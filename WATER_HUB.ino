/**
 * @file WATER_HUB.ino
 * @author Kevin Mutemi Mucheke && James Moki (www.waterhub.africa)
 * @brief 
 * @version 0.1
 * @date 2022-05-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pinouts.h"

void setup()
{
  /**
   * @brief
   * Initialization Sequence
   * -> Buzzer
   * -> LCD
   * -> timer
   * -> Flow meters
   * -> MBVs
   * -> RFID
   * -> MQtt
   */
  buzzerinit();
  delay(50);
  lcd_20x4_init();
  delay(50);
  timer_init();
  delay(50);
  flowmeters_init();
  delay(50);
  ballvalves_init();
  delay(50);
  rfid_init();
  delay(50);
  mqtt_init();
  delay(50);
  homescreen();
}

void loop()
{
  /**
   * @brief 
   * listen to # for mpesa pay
   * listen to rfid tag for cardpay
   * run dispense_check to check for any running taps
   * listen to shortcut code keyed in
   * listen to mqtt (run mqtt_check)
   */
  if (keypad_listen_specific('#'))
  {
    mpesapay();
  }
  // if (scan_card() != NULL)
  // {
  //   cardpay();
  // }
  if (keypad_listen_specific('*'))
  {
    cardpay();
  }
  dispense_check();
  mqtt_check();
  
  
  // if (password_created == false)
  // {
  //   createpass();
  // }
  // else if (password_created == true && password_entered == false)
  // {
  //   check_password();
  // }
}