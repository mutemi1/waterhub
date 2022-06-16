/**Keypad pins**/
/**these are not pins**/
const byte ROWS = 4;
const byte COLS = 4;
/**pins start below**/
byte rowPins[ROWS] = {8, 9, 10, 11};
byte colPins[COLS] = {4, 5, 6, 7};

/**Motorized Ball Valve Pins**/
const uint8_t motor1_close = 23;
const uint8_t motor1_open = 25;
const uint8_t motor2_close = 27;
const uint8_t motor2_open = 29;
const uint8_t motor3_close = 31;
const uint8_t motor3_open = 33;
const uint8_t motor4_close = 35;
const uint8_t motor4_open = 37;

/**Buzzer Pin**/
const uint8_t  buzz = 44;

/**Flowmeter pins**/
const byte flowmeter_1 = 2;
const byte flowmeter_2 = 18;
const byte flowmeter_3 = 19;
const byte flowmeter_4 = 3;


/**GSM Pin**/
const uint8_t gsm_reset = 22;

/**RFID Pins**/
#define SS_PIN 53
#define RST_PIN 12