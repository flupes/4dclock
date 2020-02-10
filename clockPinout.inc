#constant PIN_QENC_PUSH PA3
#constant PIN_QENC_CH_A PA4
#constant PIN_QENC_CH_B PA5

#constant PIN_SWITCH_1_A PA6
#constant PIN_SWITCH_1_B PA7
#constant PIN_SWITCH_2_A PA8
#constant PIN_SWITCH_2_B PA9

/*
    Configure the Diablo pins for the clock usage.
    Input: none
    Return: 0 if success, or number of errors
*/
func ConfigurePins()
    // ON-OFF-ON switches
    pin_Set(PIN_INP_HI, PIN_SWITCH_1_A);
    pin_Set(PIN_INP_HI, PIN_SWITCH_1_B);
    pin_Set(PIN_INP_HI, PIN_SWITCH_2_A);
    pin_Set(PIN_INP_HI, PIN_SWITCH_2_B);

    // Rotary encoder + push button
    pin_Set(PIN_INP_HI, PIN_QENC_CH_A);
    pin_Set(PIN_INP_HI, PIN_QENC_CH_B);
    pin_Set(PIN_INP_HI, PIN_QENC_PUSH);

    // Start quadrature encoder
    Qencoder1(PIN_QENC_CH_A, PIN_QENC_CH_B, 0);
endfunc


