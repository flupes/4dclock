#constant PIN_QENC_PUSH PA3
#constant PIN_QENC_CH_A PA4
#constant PIN_QENC_CH_B PA5

#constant PIN_SWITCH_1_A PA6
#constant PIN_SWITCH_1_B PA7
#constant PIN_SWITCH_2_A PA8
#constant PIN_SWITCH_2_B PA9

#constant PIN_CLOCK_CS PA10
#constant PIN_SPI1_SDI PA11
#constant PIN_SPI1_SDO PA12
#constant PIN_SPI1_CLK PA13

/*
    Configure the Diablo pins for the clock usage.
    Input: none
    Return: 0 if success, or number of errors
*/
func ConfigurePins()
    var errors := 0;

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

    // SPI-1 Bus
    pin_Set(PIN_OUT, PIN_CLOCK_CS);
    if (! SPI1_SDI_pin(PIN_SPI1_SDI))
        print("SDI Pin Invalid\n");
        errors += 1;
    endif
    if (! SPI1_SCK_pin(PIN_SPI1_CLK))
        print("SCK Pin Invalid\n");
        errors += 1;
    endif
    if (! SPI1_SDO_pin(PIN_SPI1_SDO))
        print("SDO Pin Invalid\n");
        errors += 1;
    endif
    if (! SPI1_Init(SPI_SPEED0, SPI16_MODE_1))
        print("INIT parameter Invalid\n") ;
        errors += 1;
    endif
    return (errors);
endfunc


