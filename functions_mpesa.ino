/***
 * Algorithm for Mpesa Pay mode
 * ->while mpesano is less than 10 listen to keypad
 * -> when mpesano equals 10 break loop, show press # to
 * proceed, then enter next loop
 * -> while amount is less than 4 listen to keypad, if #
 * is pressed then go to next page and send mqtt string
 * -> while feedback is not received continue
 * running mqtt listen function
 * -> if transaction is successful, proceed to select tap
 * screen and run while loop until tap is selected
 * -> if tap is selected then open valve and show 5 sec
 * screen for tap ready
 * -> return to home screen
 **/

#define Mpesano_length 10
// assuming the highest denomination of top up is thousand i.e upto 9999
#define Mpesaamt_length 4

char Mpesano[Mpesano_length];
// Amount customer wishes to top up or pay
char Mpesaamt[Mpesaamt_length];

/// process flags
bool stkwaiting = false;
bool stksuccess = false;
bool mpesatrx_waiting = false;
bool mpesatrx_success = false;

/// process flags setters and getters
void set_stkwaiting(bool status) { stkwaiting = status; }
void set_stksuccess(bool status) { stksuccess = status; }
boolean get_stkwaiting() { return stkwaiting; }
boolean get_stksuccess() { return stksuccess; }
void set_mpesatrx_waiting(bool status) { mpesatrx_waiting = status; }
void set_mpesatrx_success(bool status) { mpesatrx_success = status; }
boolean get_mpesatrx_waiting() { return mpesatrx_waiting; }
boolean get_mpesatrx_success() { return mpesatrx_success; }

char *get_mpesa_no()
{
    return Mpesano;
}

char *get_mpesa_amt()
{
    return Mpesaamt;
}

void mpesapay()
{
    mpesascreen();
    while (position_count < Mpesano_length)
    {
        char key = keypad_listen_return();
        if (key)
        {
            Mpesano[position_count] = key;
            lcd.setCursor(position_count, 2);
            lcd.print(key);
            position_count++;
        }
    }
    position_count = 0;
    delay(500);
    while (1)
    {
        char key = keypad_listen_return();
        if (key)
        {
            if (key == '*')
            {
                /* cancel operation and go back home */
            }
            else if (key == '#')
            {
                // proceed to amount screen and break while loop
                amtscreen();
                break;
            }
        }
    }
    delay(500);
    while (1)
    {
        char key = keypad_listen_return();
        if (key)
        {
            if (key == '*' || key == '#')
            {
                if (key == '*')
                {
                    /* cancel operation and go back home */
                }
                else
                {
                    // proceed to amount screen and break while loop
                    mpesa_wait_screen();
                    break;
                }
            }
            else
            {
                if (position_count < Mpesaamt_length)
                {
                    Mpesaamt[position_count] = key;
                    lcd.setCursor(position_count + 5, 2);
                    lcd.print(key);
                    position_count++;
                }
            }
        }
    }
    position_count = 0;
    delay(500);
    mpesapayrequest();
    delay(500);
    /**
     * Wait for stk feedback
     * run mqtt_check loop to listen for any incoming mqtt messages
     * wait for stk push success
     * wait for transaction status
     */
    set_stkwaiting(true);
    while (stkwaiting == true)
    {
        mqtt_check();
    }
    if (get_stksuccess())
    {
        set_mpesatrx_waiting(true);
        while (mpesatrx_waiting == true)
        {
            mqtt_check();
        }
        if (get_mpesatrx_success())
        {
            mpesapay_success();
        }
    }
    else {
        mpesapay_error();       
    }
}

void mpesapay_success()
{
    tap_select_screen();
    char tap_selected;
    while (1)
    {
        char key = keypad_listen_return();
        if (key)
        {
            if (key == '1' || key == '2' || key == '3' || key == '4')
            {
                tap_selected = key;
                tap_ready_screen(key);
                break;
            }
        }
    }
    // count down for 5 seconds to give user time to get ready
    int countdown = 5;
    while (countdown > 0)
    {
        lcd_keypad_display(String(countdown).c_str(), 10, 1);
        countdown--;
        delay(1000);
    }
    start_tap((byte)(tap_selected));
    go_to_home();
}

void mpesapay_error()
{
    mpesa_error_screen();
    delay(5000);
    go_to_home();
}

void reset_variables() {
    memset(Mpesano, 0, sizeof Mpesano);
    memset(Mpesaamt, 0, sizeof Mpesaamt);
    stkwaiting = false;
    stksuccess = false;
    mpesatrx_waiting = false;
    mpesatrx_success = false;
}

void go_to_home() {
    reset_variables();
    homescreen();
}