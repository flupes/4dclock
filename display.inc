#inherit "ledDigitsDisplay-ve.inc"

#inherit "PrintDisk.inc"

#constant DISPLAY_DEBUG 0

var g_hstrings ; // Handle to access uSD strings, uncomment if required
var g_hFont1 ;   // Handle to access uSD font for year
var g_hFont2 ;   // Handle to access uSD font for month
var g_hFont3 ;   // Handle to access uSD font for date
var g_hFont4 ;   // Handle to access uSD font for day

var g_force_update := 0;

func LoadResources()
    g_hFont1 := file_LoadImageControl("clock.d01", "clock.g01", 1);
    g_hFont2 := file_LoadImageControl("clock.d02", "clock.g02", 1);
    g_hFont3 := file_LoadImageControl("clock.d03", "clock.g03", 1);
    g_hFont4 := file_LoadImageControl("clock.d04", "clock.g04", 1);
    g_hstrings := file_Open("clock.txf", 'r') ; // Open handle to access uSD strings

    hndl := file_LoadImageControl("clock.dat", "clock.gci", 1);
endfunc

func UpdateDots()
    gfx_CircleFilled(160, 72, 8, GRAY) ;
    gfx_CircleFilled(160, 108, 8, GRAY) ;
endfunc

func UpdateYear(var year)
    var private last_year := -1;
    year := year - 20;  // glyphs for year start at 2020!
    var updated := 0;
    if (year >= 0 && year < yearCount)
        if (year != last_year || g_force_update)
            // year 1.1 generated 04/02/2020 22:24:45
            txt_FontID(g_hFont1) ; // Font index correct at time of code generation
            txt_FGcolour(WHITE) ;
            txt_BGcolour(BLACK) ;
            gfx_MoveTo(4 , 0) ;
            PrintDisk(g_hstrings, yearStartH, yearStartL, yearSize, year) ;
            last_year := year;
            updated := 1;
        endif
    endif
    return (updated);
endfunc

func UpdateMonth(var month)
    var private last_month := -1;
    var updated := 0;
    month := month - 1; // index of glyphs start at 0, clock months start at 1
    if (month >= 0 && month < monthCount)
        if (month != last_month || g_force_update)
            // month 1.1 generated 04/02/2020 22:25:00
            txt_FontID(g_hFont2) ; // Font index correct at time of code generation
            txt_FGcolour(WHITE) ;
            txt_BGcolour(BLACK) ;
            gfx_MoveTo(84 , 0) ;
            PrintDisk(g_hstrings, monthStartH, monthStartL, monthSize, month) ;
            last_month := month;
            updated := 1;
        endif
    endif
    return (updated);
endfunc

func UpdateDate(var date)
    var private last_date := -1;
    var updated := 0;
    date := date - 1; // index of glyphs start at 0, clock date start at 1
    if (date >= 0 && date < dateCount)
        if (date != last_date || g_force_update)
            // date 1.1 generated 04/02/2020 22:26:08
            txt_FontID(g_hFont3) ; // Font index correct at time of code generation
            txt_FGcolour(WHITE) ;
            txt_BGcolour(BLACK) ;
            gfx_MoveTo(180 , 0) ;
            PrintDisk(g_hstrings, dateStartH, dateStartL, dateSize, date) ;
            last_date := date;
            updated := 1;
        endif
    endif
    return (updated);
endfunc

func UpdateDay(var day)
    var private last_day := -1;
    var updated := 0;
    day := day - 2; // glyphs start at 0 for Monday, clock day start at 1 on Sunday
    if ( day < 0 )
        day += 7;
    endif
    if (day >= 0 && day < dayCount)
        if (day != last_day || g_force_update)
            // day 1.1 generated 04/02/2020 22:26:14
            txt_FontID(g_hFont4) ; // Font index correct at time of code generation
            txt_FGcolour(WHITE) ;
            txt_BGcolour(BLACK) ;
            gfx_MoveTo(256 , 0) ;
            PrintDisk(g_hstrings, dayStartH, dayStartL, daySize, day) ;
            last_day := day;
            updated := 1;
        endif
    endif
    return (updated);
endfunc

func UpdateHours(var hours)
    var private last_hours := -1;
    var updated := 0;
    if (hours >= 0 && hours <100) // allow display of something non sensical (just for debugging)
        if (hours != last_hours || g_force_update)
            ledDigitsDisplay(hours, iihours, 5, 2, 1, 72, 1) ;
            last_hours := hours;
            updated := 1;
        endif
    endif
    return (updated);
endfunc

func UpdateMinutes(var minutes)
    var private last_minutes := -1;
    var updated := 0;
    if (minutes >= 0 && minutes < 100)
        if (minutes != last_minutes || g_force_update)
            ledDigitsDisplay(minutes, iiminutes, 173, 2, 1, 72, 0) ;
            last_minutes := minutes;
            updated := 1;
        endif
    endif
    return (updated);
endfunc

func UpdateSeconds(var seconds)
    var private last_seconds := -1;
    var updated := 0;
    if (seconds >= 0 && seconds < 100)
        if (seconds != last_seconds || g_force_update)
            ledDigitsDisplay(seconds, iiseconds, 124, 2, 1, 36, 0) ;
            last_seconds := seconds;
            updated := 1;
        endif
    endif
    return (updated);
endfunc

func UpdateCalendar(var year, var month, var date, var day)
    var updates := 0;
    updates += UpdateYear(year);
    updates += UpdateMonth(month);
    updates += UpdateDate(date);
    updates += UpdateDay(day);
    return (updates);
endfunc

func UpdateTime(var hours, var minutes, var seconds)
    var updates := 0;
    updates += UpdateHours(hours);
    updates += UpdateMinutes(minutes);
    updates += UpdateSeconds(seconds);
    return (updates);
endfunc

