/**
 * Logic For Cardpay
 * -> Query Card Balance
 * -> Listen to Callback for balance, if callback is
 * received go to next step
 * -> Select top up card or dispense water option
 *
 * -> If top up card is selected
 * -> Enter MPesa mobile number
 * -> Enter Amount in KES
 * -> Send STK and Query Phone if transaction successful,
 * show transaction success screen with new amount
 * -> Go back home
 *
 * -> If Dispense water option is selected
 * -> Enter Amount in KES
 * -> Compare if Amount is less or equal to Card Balance
 * -> If okay, select tap
 * -> If tap is selected, show tap running
 * -> Go back home
 * */

void cardpay()
{
    // getcardbalance();
    // delay(50);
    tagbalancequery();
    delay(50);
    card_payprompt_screen();
    delay(50);
    while (1)
    {
        char key = keypad_listen_return();
        if (key)
        {
            if (key == '1' || key == '2')
            {
                if (key == '1')
                {
                    Serial.println('Dispense Option Selected');
                    break;
                }
                else
                {
                    Serial.println('Top up Option Selected');
                    cardtopup();
                    break;
                }
            }
        }
    }
}

void cardtopup()
{
    homescreen();
}