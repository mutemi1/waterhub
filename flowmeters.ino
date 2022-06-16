unsigned long int *p1;
unsigned long int *p2;
unsigned long int *p3;
unsigned long int *p4;

unsigned long int  counter_A = 0;
unsigned long int  counter_B = 0;
unsigned long int  counter_C = 0;
unsigned long int  counter_D = 0;

// pulses to listen to for each tap, getters and setters
unsigned long int checkpulses_tap1 = 0;
unsigned long int checkpulses_tap2 = 0;
unsigned long int checkpulses_tap3 = 0;
unsigned long int checkpulses_tap4 = 0;
unsigned long int get_checkpulses_tap1() { return checkpulses_tap1; }
unsigned long int get_checkpulses_tap2() { return checkpulses_tap2; }
unsigned long int get_checkpulses_tap3() { return checkpulses_tap3; }
unsigned long int get_checkpulses_tap4() { return checkpulses_tap4; }
void set_checkpulses_tap1(unsigned long int pulses) { checkpulses_tap1 = pulses; }
void set_checkpulses_tap2(unsigned long int pulses) { checkpulses_tap2 = pulses; }
void set_checkpulses_tap3(unsigned long int pulses) { checkpulses_tap3 = pulses; }
void set_checkpulses_tap4(unsigned long int pulses) { checkpulses_tap4 = pulses; }

// tap statuses, getters and setters
bool tap1_running = false;
bool tap2_running = false;
bool tap3_running = false;
bool tap4_running = false;
boolean get_tap1_running() { return tap1_running; }
boolean get_tap2_running() { return tap2_running; }
boolean get_tap3_running() { return tap3_running; }
boolean get_tap4_running() { return tap4_running; }
void set_tap1_running(bool status) { tap1_running = status; }
void set_tap2_running(bool status) { tap2_running = status; }
void set_tap3_running(bool status) { tap3_running = status; }
void set_tap4_running(bool status) { tap4_running = status; }


void flowmeters_init() {
  pinMode(flowmeter_1_ISR, INPUT_PULLUP);
  pinMode(flowmeter_2_ISR, INPUT_PULLUP);
  pinMode(flowmeter_3_ISR, INPUT_PULLUP);
  pinMode(flowmeter_4_ISR, INPUT_PULLUP);
  
  stop_tap(flowmeter_1);
  stop_tap(flowmeter_2);
  stop_tap(flowmeter_3);
  stop_tap(flowmeter_4);

  p1 = &counter_A;
  p2 = &counter_B;
  p3 = &counter_C;
  p4 = &counter_D;
}

void start_tap(byte tap_number) {
  if (tap_number == 1)
  {
    tap1_running = true;
    attachInterrupt(digitalPinToInterrupt(tap_number), flowmeter_1_ISR, FALLING);
  }
  if (tap_number == 2)
  {
    tap2_running = true;
    attachInterrupt(digitalPinToInterrupt(tap_number), flowmeter_2_ISR, FALLING);
  }
  if (tap_number == 3)
  {
    tap3_running = true;
    attachInterrupt(digitalPinToInterrupt(tap_number), flowmeter_3_ISR, FALLING);
  }
  if (tap_number == 4)
  {
    tap4_running = true;
    attachInterrupt(digitalPinToInterrupt(tap_number), flowmeter_4_ISR, FALLING);
  }
}

void stop_tap(byte tap_number) {
  if (tap_number == 1)
  {
    tap1_running = false;
  }
  if (tap_number == 2)
  {
    tap2_running = false;
  }
  if (tap_number == 3)
  {
    tap3_running = false;
  }
  if (tap_number == 4)
  {
    tap4_running = false;
  }
  detachInterrupt(digitalPinToInterrupt(tap_number));
}

void flowmeter_1_ISR() {
  (*p1)++;
  Serial.println("P1++ : " + String(*p1));
}

void flowmeter_2_ISR() {
  (*p2)++;
  Serial.println("P2++ : " + String(*p2));
}

void flowmeter_3_ISR() {
  (*p3)++;
  Serial.println("P3++ : " + String(*p3));
}

void flowmeter_4_ISR() {
  (*p4)++;
  Serial.println("P4++ : " + String(*p4));
}

void dispense_check() {
  if (tap1_running && counter_A >= checkpulses_tap1) {
    stop_tap(flowmeter_1);
    tap1_close();
    *p1 = 0;
    counter_A = 0;
  }
  if (tap2_running && counter_B >= checkpulses_tap2) {
    stop_tap(flowmeter_2);
    tap2_close();
    *p2 = 0;
    counter_B = 0;
  }
  if (tap3_running && counter_C >= checkpulses_tap3) {
    stop_tap(flowmeter_3);
    tap3_close();
    *p3 = 0;
    counter_C = 0;
  }
  if (tap4_running && counter_D >= checkpulses_tap4) {
    stop_tap(flowmeter_4);
    tap4_close();
    *p4 = 0;
    counter_D = 0;
  }
}
