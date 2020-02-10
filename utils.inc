func DEC2BCD(var dec)
    return ( ( dec / 10 ) * 0x10 ) + ( dec % 10 );
endfunc

func BCD2DEC(var bcd)
    return ( ( bcd / 0x10) * 10 ) + ( bcd % 0x10 );
endfunc

