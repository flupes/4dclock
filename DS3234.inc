//
// Support for the DS3234 RTC (SPI)
//

#inherit "utils.inc"

#constant PIN_CLOCK_CS PA6
#constant PIN_SPI1_SDI PA7
#constant PIN_SPI1_SDO PA8
#constant PIN_SPI1_CLK PA9

#constant DS3234_DEBUG 0

#DATA
    byte DS3234_REGISTER_SECONDS
    0x00
    byte DS3234_REGISTER_MINUTES
    0x01
#END

var g_ds_seconds := 0;
var g_ds_minutes := 0;
var g_ds_hours := 0;
var g_ds_day := 0;
var g_ds_date := 0;
var g_ds_month := 0;
var g_ds_year := 0;

func DS3234_Init()
    var errors := 0;

    pin_Set(PIN_OUT, PIN_CLOCK_CS);
    pin_HI(PIN_CLOCK_CS);

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
    if (! SPI1_Init(SPI_SPEED7, SPI8_MODE_5))
        print("INIT parameter Invalid\n") ;
        errors += 1;
    endif

    return (errors);
endfunc

func DS3234_Read()
    var private seconds, minutes, hours, day, date, month, year, counter := 0;

    pin_LO(PIN_CLOCK_CS);
    SPI1_Write(0x00);
    seconds := SPI1_Read();
    minutes := SPI1_Read();
    hours := SPI1_Read();
    day := SPI1_Read();
    date := SPI1_Read();
    month := SPI1_Read();
    year := SPI1_Read();
    pin_HI(PIN_CLOCK_CS);

    counter++;
    g_ds_seconds := BCD2DEC(seconds);
    g_ds_minutes := BCD2DEC(minutes);
    g_ds_hours := BCD2DEC(hours);
    g_ds_day := BCD2DEC(day);
    g_ds_date := BCD2DEC(date);
    g_ds_month := BCD2DEC(month);
    g_ds_year := BCD2DEC(year);

    if (DS3234_DEBUG == 1)
        txt_MoveCursor(1, 1);
        print("counter = ", [HEX4]counter, "\n");
        print("seconds = ", [HEX4]seconds, " -> ", [DEC2Z]g_ds_seconds, "\n");
        print("minutes = ", [HEX4]minutes, " -> ", [DEC2Z]g_ds_minutes, "\n");
        print("hours = ", [HEX4]hours, " -> ", [DEC2Z]g_ds_hours, "\n");
        print("day = ", [HEX4]day, " -> ", [DEC2Z]g_ds_day, "\n");
        print("date = ", [HEX4]date, " -> ", [DEC2Z]g_ds_date, "\n");
        print("month = ", [HEX4]month, " -> ", [DEC2Z]g_ds_month, "\n");
        print("year = ", [HEX4]year, " -> ", [DEC2Z]g_ds_year, "\n");
    endif

 endfunc

/*
  SPI Notes

From DS3234 Datasheet
  If choosing clock idling low (CPOL=0):
    - Write --> SCLK Falling
    - Read --> SCLK Rising
  --> correspond to mode 5 below (Diablo16 datasheet wrong)

From https://forum.4dsystems.com.au/node/67716
0 SPI8_MODE_0 sck idles low, SDO stable for Rising edge, SDI sampled middle high
1 SPI8_MODE_1 sck idles low, SDO stable for Falling edge, SDI sampled middle low
2 SPI8_MODE_2 sck idles high, SDO stable for Falling edge, SDI sampled middle high
3 SPI8_MODE_3 sck idles high, SDO stable for Rising edge, SDI sampled middle low
4 SPI8_MODE_4 sck idles low, SDO stable for Rising edge, SDI sampled end high
5 SPI8_MODE_5 sck idles low, SDO stable for Falling edge, SDI sampled end low
6 SPI8_MODE_6 sck idles high, SDO stable for Falling edge, SDI sampled end high
7 SPI8_MODE_7 sck idles high, SDO stable for Rising edge, SDI sampled end low
*/

