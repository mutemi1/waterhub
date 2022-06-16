#define motor_response_time 3.5
uint8_t main_timer = 0;
uint8_t motor_actuation_time = motor_response_time * 2;


void ballvalves_timer_check() {

  if (motor1_close_timer == motor_actuation_time && motor1_close_state == true) {

    motor1_close_state = false;
    motor1_close_timer = 0;
    digitalWrite(motor1_close, LOW);

  }

  if (motor1_open_timer == motor_actuation_time && motor1_open_state == true) {

    motor1_open_state = false;
    motor1_open_timer = 0;
    digitalWrite(motor1_open, LOW);

  }

  if (motor2_close_timer == motor_actuation_time && motor2_close_state == true) {

    motor2_close_state = false;
    motor2_close_timer = 0;
    digitalWrite(motor2_close, LOW);

  }
  if (motor2_open_timer == motor_actuation_time && motor2_open_state == true) {

    motor2_open_state = false;
    motor2_open_timer = 0;
    digitalWrite(motor2_open, LOW);

  }
  if (motor3_close_timer == motor_actuation_time && motor3_close_state == true) {

    motor3_close_state = false;
    motor3_close_timer = 0;
    digitalWrite(motor3_close, LOW);

  }
  if (motor3_open_timer == motor_actuation_time && motor3_open_state == true) {

    motor3_open_state = false;
    motor3_open_timer = 0;
    digitalWrite(motor3_open, LOW);

  }
  if (motor4_close_timer == motor_actuation_time && motor4_close_state == true) {

    motor4_close_state = false;
    motor4_close_timer = 0;
    digitalWrite(motor4_close, LOW);

  }
  if (motor4_open_timer == motor_actuation_time && motor4_open_state == true) {

    motor4_open_state = false;
    motor4_open_timer = 0;
    digitalWrite(motor4_open, LOW);
  }

}

void timer_init() {

  TCCR4A = 0;// set entire TCCR4A register to 0
  TCCR4B = 0;// same for TCCR4B
  TCNT4  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR4A = 7813;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR4B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK4 |= (1 << OCIE4A);
}

ISR(TIMER4_COMPA_vect) {  ///This timer is set at 500ms

  motor1_close_timer++;
  motor1_open_timer++;
  motor2_close_timer++;
  motor2_open_timer++;
  motor3_close_timer++;
  motor3_open_timer++;
  motor4_close_timer++;
  motor4_open_timer++;
  main_timer++;
  ballvalves_timer_check();

}
