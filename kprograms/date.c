#include "../drivers/screen.h"
#include "../drivers/io.h"
#include "../drivers/types.h"
#include "../kernel/util.h"
#include "../libc/include/string.h"

// void read_rtc() {
//     // Enable updates
//     outb(0x70, 0x8A);      // Select Register B
//     inb(0x71);             // Read Register B to unlock updates
//     outb(0x70, 0x8B);      // Select Register B again
//     outb(0x71, 0x02);      // Disable NMI

//     // Read Time
//     outb(0x70, 0x00);      // Select seconds
//     uint8_t seconds = inb(0x71);

//     outb(0x70, 0x02);      // Select minutes
//     uint8_t minutes = inb(0x71);

//     outb(0x70, 0x04);      // Select hours
//     uint8_t hours = inb(0x71);

//     // Read Date
//     outb(0x70, 0x07);      // Select day of the month
//     uint8_t day = inb(0x71);

//     outb(0x70, 0x08);      // Select month
//     uint8_t month = inb(0x71);

//     outb(0x70, 0x09);      // Select year
//     uint8_t year = inb(0x71);

//     // Print the retrieved time and date (in BCD format)
//     // You may want to convert BCD to binary for easier use
//     kprint("\nTime:");
//     char* hour;
//     //convert to ascii
//     hex_to_ascii(hours, hour);
//     kprint(hour);
//     kprint(":");
//     kprint(minutes);
//     kprint(":");
//     kprint(seconds);
//     kprint("\n");
//     //kprint("Time: %02x:%02x:%02x\n", hours, minutes, seconds);
//     //kprint("Date: %02x/%02x/%02x\n", month, day, year + 1900);
// }

// #define RTC_INDEX_PORT 0x70
// #define RTC_DATA_PORT  0x71

// // RTC register addresses
// #define RTC_SECONDS_REG  0x00
// #define RTC_MINUTES_REG  0x02
// #define RTC_HOURS_REG    0x04
// #define RTC_DAY_REG      0x07
// #define RTC_MONTH_REG    0x08
// #define RTC_YEAR_REG     0x09


// // Read a register from the RTC
// uint8_t read_rtc_register(uint8_t reg) {
//     outb(RTC_INDEX_PORT, reg);
//     return inb(RTC_DATA_PORT);
// }

// // Get the current time
// void get_time() {
//     uint8_t *hours; uint8_t *minutes; uint8_t *seconds;
//     *seconds = read_rtc_register(RTC_SECONDS_REG);
//     *minutes = read_rtc_register(RTC_MINUTES_REG);
//     *hours   = read_rtc_register(RTC_HOURS_REG);

//     bcdToAscii(hours);

// }

// // Get the current date
// void get_date() {
//     uint8_t *day; uint8_t *month; uint16_t *year;
//     *day   = read_rtc_register(RTC_DAY_REG);
//     *month = read_rtc_register(RTC_MONTH_REG);
//     *year  = read_rtc_register(RTC_YEAR_REG) + 2000; // Assuming year is 2000+
// }

// void bcdToAscii(unsigned char bcd) {
//     char *ascii;
//     // Extract the high nibble and low nibble
//     unsigned char highNibble = (bcd >> 4) & 0x0F; // Get the high 4 bits
//     unsigned char lowNibble = bcd & 0x0F;         // Get the low 4 bits

//     // Convert to ASCII
//     ascii[0] = (highNibble + '0'); // Convert high nibble to ASCII
//     ascii[1] = (lowNibble + '0');  // Convert low nibble to ASCII
//     ascii[2] = '\0';                // Null-terminate the string
//     kprint("\n");
//     kprint(ascii);
//     kprint(":");
// }

// #define CURRENT_YEAR        2023                            // Change this each year!

// int century_register = 0x00;                                // Set by ACPI table parsing code if possible

// unsigned char second;
// unsigned char minute;
// unsigned char hour;
// unsigned char day;
// unsigned char month;
// unsigned int year;



// enum {
//       cmos_address = 0x70,
//       cmos_data    = 0x71
// };

// int get_update_in_progress_flag() {
//       outb(cmos_address, 0x0A);
//       return (inb(cmos_data) & 0x80);
// }

// unsigned char get_RTC_register(int reg) {
//       outb(cmos_address, reg);
//       return inb(cmos_data);
// }

// void read_rtc() {
//       unsigned char century;
//       unsigned char last_second;
//       unsigned char last_minute;
//       unsigned char last_hour;
//       unsigned char last_day;
//       unsigned char last_month;
//       unsigned char last_year;
//       unsigned char last_century;
//       unsigned char registerB;

//       // Note: This uses the "read registers until you get the same values twice in a row" technique
//       //       to avoid getting dodgy/inconsistent values due to RTC updates

//       while (get_update_in_progress_flag());                // Make sure an update isn't in progress
//       second = get_RTC_register(0x00);
//       minute = get_RTC_register(0x02);
//       hour = get_RTC_register(0x04);
//       day = get_RTC_register(0x07);
//       month = get_RTC_register(0x08);
//       year = get_RTC_register(0x09);
//       if(century_register != 0) {
//             century = get_RTC_register(century_register);
//       }

//       do {
//             last_second = second;
//             last_minute = minute;
//             last_hour = hour;
//             last_day = day;
//             last_month = month;
//             last_year = year;
//             last_century = century;

//             while (get_update_in_progress_flag());           // Make sure an update isn't in progress
//             second = get_RTC_register(0x00);
//             minute = get_RTC_register(0x02);
//             hour = get_RTC_register(0x04);
//             day = get_RTC_register(0x07);
//             month = get_RTC_register(0x08);
//             year = get_RTC_register(0x09);
//             if(century_register != 0) {
//                   century = get_RTC_register(century_register);
//             }
//       } while( (last_second != second) || (last_minute != minute) || (last_hour != hour) ||
//                (last_day != day) || (last_month != month) || (last_year != year) ||
//                (last_century != century) );

//       registerB = get_RTC_register(0x0B);

//       // Convert BCD to binary values if necessary

//       if (!(registerB & 0x04)) {
//             second = (second & 0x0F) + ((second / 16) * 10);
//             minute = (minute & 0x0F) + ((minute / 16) * 10);
//             hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
//             day = (day & 0x0F) + ((day / 16) * 10);
//             month = (month & 0x0F) + ((month / 16) * 10);
//             year = (year & 0x0F) + ((year / 16) * 10);
//             if(century_register != 0) {
//                   century = (century & 0x0F) + ((century / 16) * 10);
//             }
//       }

//       // Convert 12 hour clock to 24 hour clock if necessary

//       if (!(registerB & 0x02) && (hour & 0x80)) {
//             hour = ((hour & 0x7F) + 12) % 24;
//       }

//       // Calculate the full (4-digit) year

//       if(century_register != 0) {
//             year += century * 100;
//       } else {
//             year += (CURRENT_YEAR / 100) * 100;
//             if(year < CURRENT_YEAR) year += 100;
//       }
//       char *chours;
//       ctos(chours, hour);

//       char *cminute;
//       ctos(cminute, minute);

//       kprint("\n");
//       kprint(hour);
//       kprint(":");
//       kprint(minute);
// }

/* This code is an interface to the MC146818A-compatible real
   time clock found on PC motherboards.  See [MC146818A] for
   hardware details. */

typedef unsigned long time_t;

/* I/O register addresses. */
#define CMOS_REG_SET	0x70    /* Selects CMOS register exposed by REG_IO. */
#define CMOS_REG_IO	0x71    /* Contains the selected data byte. */

/* Indexes of CMOS registers with real-time clock functions.
   Note that all of these registers are in BCD format,
   so that 0x59 means 59, not 89. */
#define RTC_REG_SEC	0       /* Second: 0x00...0x59. */
#define RTC_REG_MIN	2       /* Minute: 0x00...0x59. */
#define RTC_REG_HOUR	4       /* Hour: 0x00...0x23. */
#define RTC_REG_MDAY	7	/* Day of the month: 0x01...0x31. */
#define RTC_REG_MON	8       /* Month: 0x01...0x12. */
#define RTC_REG_YEAR	9	/* Year: 0x00...0x99. */

/* Indexes of CMOS control registers. */
#define RTC_REG_A	0x0a    /* Register A: update-in-progress. */
#define RTC_REG_B	0x0b    /* Register B: 24/12 hour time, irq enables. */
#define RTC_REG_C	0x0c    /* Register C: pending interrupts. */
#define RTC_REG_D	0x0d    /* Register D: valid time? */

/* Register A. */
#define RTCSA_UIP	0x80	/* Set while time update in progress. */

/* Register B. */
#define	RTCSB_SET	0x80	/* Disables update to let time be set. */
#define RTCSB_DM	0x04	/* 0 = BCD time format, 1 = binary format. */
#define RTCSB_24HR	0x02    /* 0 = 12-hour format, 1 = 24-hour format. */

static int bcd_to_bin (uint8_t);
static uint8_t cmos_read (uint8_t index);

/* Returns number of seconds since Unix epoch of January 1,
   1970. */
time_t rtc_get_time (void)
{
  static const int days_per_month[12] =
    {
      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
  int sec, min, hour, mday, mon, year;
  time_t time;
  int i;

  /* Get time components.

     We repeatedly read the time until it is stable from one read
     to another, in case we start our initial read in the middle
     of an update.  This strategy is not recommended by the
     MC146818A datasheet, but it is simpler than any of their
     suggestions and, furthermore, it is also used by Linux.

     The MC146818A can be configured for BCD or binary format,
     but for historical reasons everyone always uses BCD format
     except on obscure non-PC platforms, so we don't bother
     trying to detect the format in use. */
  do
    {
      sec = bcd_to_bin (cmos_read (RTC_REG_SEC));
      min = bcd_to_bin (cmos_read (RTC_REG_MIN));
      hour = bcd_to_bin (cmos_read (RTC_REG_HOUR));
      mday = bcd_to_bin (cmos_read (RTC_REG_MDAY));
      mon = bcd_to_bin (cmos_read (RTC_REG_MON));
      year = bcd_to_bin (cmos_read (RTC_REG_YEAR));

      char *h; 
      int_to_ascii(hour,h);
      kprint("\n");
      kprint(hour);
      kprint(" : ");
      char *m;
      int_to_ascii(min, m);
      kprint(min);
    }
  while (sec != bcd_to_bin (cmos_read (RTC_REG_SEC)));

  /* Translate years-since-1900 into years-since-1970.
     If it's before the epoch, assume that it has passed 2000.
     This will break at 2070, but that's long after our 31-bit
     time_t breaks in 2038. */
  if (year < 70)
    year += 100;
  year -= 70;

  /* Break down all components into seconds. */
  time = (year * 365 + (year - 1) / 4) * 24 * 60 * 60;
  for (i = 1; i <= mon; i++)
    time += days_per_month[i - 1] * 24 * 60 * 60;
  if (mon > 2 && year % 4 == 0)
    time += 24 * 60 * 60;
  time += (mday - 1) * 24 * 60 * 60;
  time += hour * 60 * 60;
  time += min * 60;
  time += sec;

  return time;

}

/* Returns the integer value of the given BCD byte. */
static int bcd_to_bin (uint8_t x)
{
  return (x & 0x0f) + ((x >> 4) * 10);
}

/* Reads a byte from the CMOS register with the given INDEX and
   returns the byte read. */
static uint8_t cmos_read (uint8_t index)
{
  outb (CMOS_REG_SET, index);
  return inb (CMOS_REG_IO);
}