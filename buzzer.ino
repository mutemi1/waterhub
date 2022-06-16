void buzzerinit() {
pinMode(buzz, OUTPUT);
}

void Buzzer() {
  digitalWrite(buzz, HIGH);
  delay(1000);
  digitalWrite(buzz, LOW);
  delay(1000);
}

void keypadbuzz() {
  digitalWrite(buzz, HIGH);
  delay(3);
  digitalWrite(buzz, LOW);
  delay(3);
}

void GSM_Net_Connect_Buzz() {    //Indicate that a connection to the GSM network has been established
  digitalWrite(buzz, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(buzz, LOW);    // turn the LED off by making the voltage LOW
  delay(50);

}
void Mqtt_Broker_Connect_Buzz() {      //Indicate that a connection to the broker has been established
  for (int x = 0; x < 3; x++) {
    digitalWrite(buzz, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(40);                       // wait for a second
    digitalWrite(buzz, LOW);    // turn the LED off by making the voltage LOW
    delay(20);
  }
}