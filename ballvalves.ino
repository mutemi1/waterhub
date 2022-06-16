uint8_t motor1_close_timer = 0;
uint8_t motor1_open_timer = 0;
uint8_t motor2_close_timer = 0;
uint8_t motor2_open_timer = 0;
uint8_t motor3_close_timer = 0;
uint8_t motor3_open_timer = 0;
uint8_t motor4_close_timer = 0;
uint8_t motor4_open_timer = 0;

bool motor1_close_state = false;
bool motor1_open_state = false;
bool motor2_close_state = false;
bool motor2_open_state = false;
bool motor3_close_state = false;
bool motor3_open_state = false;
bool motor4_close_state = false;
bool motor4_open_state = false;


void tap1_close() {
  motor1_close_timer = 0;
  motor1_close_state = true;
  digitalWrite(motor1_close, HIGH);
}

void tap1_open() {
  motor1_open_timer = 0;
  motor1_open_state = true;
  digitalWrite(motor1_open, HIGH);
}

void tap2_close() {
  motor2_close_state = true;
  motor2_close_timer = 0;
  digitalWrite(motor2_close, HIGH);
}

void tap2_open() {
  motor2_open_state = true;
  motor2_open_timer = 0;
  digitalWrite(motor2_open, HIGH);
}

void tap3_close() {
  motor3_close_state = true;
  motor3_close_timer = 0;
  digitalWrite(motor3_close, HIGH);
}

void tap3_open() {
  motor3_open_state = true;
  motor3_open_timer = 0;
  digitalWrite(motor3_open, HIGH);
}

void tap4_close() {
  motor4_close_state = true;
  motor4_close_timer = 0;
  digitalWrite(motor4_close, HIGH);
}

void tap4_open() {
  motor4_open_state = true;
  motor4_open_timer = 0;
  digitalWrite(motor4_open, HIGH);
}

void ballvalves_init() {

  pinMode(motor1_close, OUTPUT);
  pinMode(motor1_open, OUTPUT);
  pinMode(motor2_close, OUTPUT);
  pinMode(motor2_open, OUTPUT);
  pinMode(motor3_close, OUTPUT);
  pinMode(motor3_open, OUTPUT);
  pinMode(motor4_close, OUTPUT);
  pinMode(motor4_open, OUTPUT);

  tap1_close();
  tap2_close();
  tap3_close();
  tap4_close();
}
