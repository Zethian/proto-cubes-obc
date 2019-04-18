#include "RTClib.h"
#define REQUEST_TIME 60

/*
 * RTC_init
 * Initializes the RTC clock
 */
void RTC_init();

/*
 * RTC_get
 * Returns a datetime variable with the current time of request
 * 
 */
DateTime RTC_get(void);
/* RTC_time_since_last
 *  Returns a boolean if the time has passed the threshold of delaytime since last it triggered a true statement
 *  Input the delaytime required
 *  Can not be used for 2 timers simultaneous
 *  Non-blocking
 */
boolean RTC_time_since_last(int delaytime);

/*
 * RTC_get_seconds
 * Returns a long with the current time in unixtime (seconds since 1st of january 1970)
 */
long RTC_get_seconds(void);