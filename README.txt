///****Code Flow for Water ATM****///

Hardware 
->LCD 20x4 Display with i2c
->mrfc tag reader
->4x4 keypad
->arduino mega 2560 processor
->motordrivers x2

Integrations
->SMS Sender ID
->M-Pesa Payments Integration

Services offered by the ATM
->Water Dispensing
->Card Token Purchase
->Card Token Sambaza

Service Logic
1. Water Dispensing & Card Token Purchase
->Tap Tag or Press # for M-Pesa

a) Tap Tag
->Fetch Card Balance
->1 for Dispense, 2 for Top up
i) Dispense Option
->Enter Amount to Dispense
->Press # when done
->Check if available balance is enough to dispense
->Prompt user to select tap i.e 1 for tap 1, 2 for tap 2 etc
->Tap x selected and running
->Back to Home
ii)Top up Option
->Enter M-Pesa Mobile Number
->Press # when done
->Enter Amount of Token to Purchase
->Press # when done
->Waiting to Complete Transaction
->Transaction Successfull, New Balance ksh x or Transaction Failed
->Back to Home

b)M-Pesa Option
->Enter M-Pesa Mobile Number
->Press # when done
->Enter Amount
->Press # when done
->Waiting to Complete Transaction
->If transaction is successful go to next if failed prompt
transaction failed message and go back home
->Prompt user to select tap i.e 1 for tap 1, 2 for tap 2 etc
->Tap x selected and running
->Back to Home

2. Sambaza Token
->Enter shortcut code to enter sambaza token mode
->Enter ATM PIN (Attendant to Do this)
->Press # when done
->Enter Amount to Sambaza
->Press # when done
->Waiting for Tag to be Tapped
->If tag is tapped, complete transfer of tokens
->Back to Home