//
// Support for the DS3234 RTC (SPI)
//

#inherit "utils.inc"

#constant PIN_CLOCK_CS PA6
#constant PIN_SPI1_SDI PA7
#constant PIN_SPI1_SDO PA8
#constant PIN_SPI1_CLK PA9

#constant DS3234_REGISTER_READ      0x00
#constant DS3234_REGISTER_WRITE     0x80

#constant DS3234_REGISTER_SECONDS   0x00
#constant DS3234_REGISTER_MINUTES   0x01
#constant DS3234_REGISTER_HOURS     0x02
#constant DS3234_REGISTER_DAY       0x03
#constant DS3234_REGISTER_DATE      0x04
#constant DS3234_REGISTER_MONTH     0x05
#constant DS3234_REGISTER_YEAR      0x06
#constant DS3234_REGISTER_A1SEC     0x07
#constant DS3234_REGISTER_A1MIN     0x08
#constant DS3234_REGISTER_A1HR      0x09
#constant DS3234_REGISTER_A1DA      0x0A
#constant DS3234_REGISTER_A2MIN     0x0B
#constant DS3234_REGISTER_A2HR      0x0C
#constant DS3234_REGISTER_A2DA      0x0D
#constant DS3234_REGISTER_CONTROL   0x0E
#constant DS3234_REGISTER_STATUS    0x0F
#constant DS3234_REGISTER_XTAL      0x10
#constant DS3234_REGISTER_TEMPM     0x11
#constant DS3234_REGISTER_TEMPL     0x12
#constant DS3234_REGISTER_TEMPEN    0x13
#constant DS3234_REGISTER_RESERV1   0x14
#constant DS3234_REGISTER_RESERV2   0x15
#constant DS3234_REGISTER_RESERV3   0x16
#constant DS3234_REGISTER_RESERV4   0x17
#constant DS3234_REGISTER_SRAMA     0x18
#constant DS3234_REGISTER_SRAMD     0x19

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
    if (! SPI1_Init(SPI_SPEED3, SPI8_MODE_4))
        print("INIT parameter Invalid\n") ;
        errors += 1;
    endif

    return (errors);
endfunc

func DS3234_ReadTimeDate()
    var seconds, minutes, hours, day, date, month, year;

    pin_LO(PIN_CLOCK_CS);
    SPI1_Write(DS3234_REGISTER_READ);
    seconds := SPI1_Read();
    minutes := SPI1_Read();
    hours := SPI1_Read();
    day := SPI1_Read();
    date := SPI1_Read();
    month := SPI1_Read();
    year := SPI1_Read();
    pin_HI(PIN_CLOCK_CS);

    g_ds_seconds := BCD2DEC(seconds);
    g_ds_minutes := BCD2DEC(minutes);
    g_ds_hours := BCD2DEC(hours);
    g_ds_day := BCD2DEC(day);
    g_ds_date := BCD2DEC(date);
    g_ds_month := BCD2DEC(month);
    g_ds_year := BCD2DEC(year);

endfunc

func DS3234_SetTimeDate(var seconds, var m, var h, var day, var dd, var mm, var yy)
    pin_LO(PIN_CLOCK_CS);
    SPI1_Write(DS3234_REGISTER_WRITE);
    SPI1_Write(DEC2BCD(seconds));
    SPI1_Write(DEC2BCD(m));
    SPI1_Write(DEC2BCD(h));
    SPI1_Write(DEC2BCD(day));
    SPI1_Write(DEC2BCD(dd));
    SPI1_Write(DEC2BCD(mm));
    SPI1_Write(DEC2BCD(yy));
    pin_HI(PIN_CLOCK_CS);
endfunc

func DS3234_SetHour(var h)
    var bcd_hours;
    var write_reg;
    write_reg := 0x80 | DS3234_REGISTER_HOURS;
    bcd_hours := DEC2BCD(h);
    //txt_MoveCursor(12, 1);
    //print("bcd_hours = ", [HEX4]bcd_hours, "\n");
    //print("write_reg (manual)= ", [HEX4]write_reg, "\n");
    DS3234_WriteRegister(bcd_hours, write_reg);
endfunc

func DS3234_SetMinute(var m)
    DS3234_WriteRegister(DEC2BCD(m), DS3234_REGISTER_MINUTES);
endfunc

func DS3234_SetSecond(var s)
    DS3234_WriteRegister(DEC2BCD(s), DS3234_REGISTER_SECONDS);
endfunc

func DS3234_WriteRegister(var value, var register)
    var private dummy_read;
    pin_LO(PIN_CLOCK_CS);
    dummy_read := SPI1_Write(register);
    dummy_read := SPI1_Write(value);
    pin_HI(PIN_CLOCK_CS);
endfunc
/*
  SPI Notes

From DS3234 Datasheet
  If choosing clock idling low (CPOL=0):
    - Write --> SCLK Falling
    - Read --> SCLK Rising
  --> correspond to mode SPI8_MODE_4 if Diablo16 datasheet is correct (rev 2.2 19 Aug. 2019)

From https://forum.4dsystems.com.au/node/67716 (maybe outdated as Feb. 2020)
0 SPI8_MODE_0 sck idles low, SDO stable for Rising edge, SDI sampled middle high
1 SPI8_MODE_1 sck idles low, SDO stable for Falling edge, SDI sampled middle low
2 SPI8_MODE_2 sck idles high, SDO stable for Falling edge, SDI sampled middle high
3 SPI8_MODE_3 sck idles high, SDO stable for Rising edge, SDI sampled middle low
4 SPI8_MODE_4 sck idles low, SDO stable for Rising edge, SDI sampled end high
5 SPI8_MODE_5 sck idles low, SDO stable for Falling edge, SDI sampled end low
6 SPI8_MODE_6 sck idles high, SDO stable for Falling edge, SDI sampled end high
7 SPI8_MODE_7 sck idles high, SDO stable for Rising edge, SDI sampled end low

*/



