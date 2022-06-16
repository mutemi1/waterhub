#include <EEPROM.h>

void Write_to_EEPROM(char data[], uint8_t array_size, uint8_t start_address){
  
    for (int i = 0; i < array_size; i++) {
      
     // EEPROM.write(start_address, data[i]);
      delay(10);
      start_address++;
    }

}

void Read_from_EEPROM(char data[], uint8_t array_size, uint8_t start_address){
  
    for (int i = 0; i < array_size; i++) {
      
      data[i]= EEPROM.read(start_address);
      start_address++;
      
    }
}
