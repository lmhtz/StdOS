#include "bsp_date.h"

#define FEBRUARY		2
#define STARTOFTIME		1970
#define SECDAY			86400L           /*  一天有多少s */
#define SECYR			(SECDAY * 365)
#define leapyear(year)		((year) % 4 == 0)
#define days_in_year(a) 	(leapyear(a) ? 366 : 365)
#define days_in_month(a) 	(month_days[(a) - 1])

/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia before 1917,
 * Britain & colonies before 1752, anywhere else before 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * WARNING: this function will overflow on 2106-02-07 06:28:16 on
 * machines were long is 32-bit! (However, as time_t is signed, we
 * will already get problems at other places on 2038-01-19 03:14:08)

 *ADD by fire：本函数在工程中的输入参数为北京时间，
所以在转换成时间戳时最后要从北京时间转换为标准时间的时间戳
 */
u32 mktimev(struct rtc_time *tm)
{
    if (0 >= (int)(tm->tm_mon -= 2))
    {	
         /* 1..12 -> 11,12,1..10 */
        tm->tm_mon += 12; /* Puts Feb last since it has leap day */
        tm->tm_year -= 1;
    } 

    return ((((u32)(tm->tm_year / 4-tm->tm_year / 100+tm->tm_year / 400+367 * tm->tm_mon / 12+tm->tm_mday) + tm->tm_year *365-719499) *24+tm->tm_hour /* now have hours */
    ) *60+tm->tm_min /* now have minutes */
    ) *60+tm->tm_sec - 8 * 60 * 60; /* finally seconds */
    /*Add by fire: -8*60*60 把输入的北京时间转换为标准时间，
    再写入计时器中，确保计时器的数据为标准的UNIX时间戳*/

}
