#include "..\headers\Ds1338.h"

// The i2c addresses
#define DS1338_READ  0xD1
#define DS1338_WRITE 0xD0

// The registers
#define DS1338_SECONDS_REG  (UINT8)(0x00)
#define DS1338_MINUTES_REG  (UINT8)(0x01)
#define DS1338_HOURS_REG    (UINT8)(0x02)
#define DS1338_DAYS_REG     (UINT8)(0x03)
#define DS1338_DATES_REG    (UINT8)(0x04)
#define DS1338_MONTHS_REG   (UINT8)(0x05)
#define DS1338_YEARS_REG    (UINT8)(0x06)
#define DS1338_CONTROLS_REG (UINT8)(0x07)

volatile ds1338_s ds1338;

typedef struct ds1338_seconds {
    union {
        struct {
            unsigned secondsl:4;
            unsigned secondsh:3;
            unsigned ch:1; // Clock Halt when set to 1 the oscillator is disabled
        };
        struct {
            unsigned seconds:7;
            unsigned :1;
        };
    };
} ds1338_seconds;

typedef struct ds1338_minutes {
    union {
        struct {
            unsigned minutesl:4;
            unsigned minutesh:3;
            unsigned :1;
        };
        struct {
            unsigned minutes:7;
            unsigned :1;
        };
    };
} ds1338_minutes;

typedef struct ds1338_hours {
    union {
        struct {
            unsigned hourl:4;
            unsigned hourh10:1;
            unsigned hourh20:1;
            unsigned clockMode:1;
            unsigned :1;
        };

        struct {
            unsigned hours24:6;
            unsigned :2;
        };
        struct {
            unsigned hours12:5;
            unsigned AMPM:1;
            unsigned :2;
        };
    };
} ds1338_hours;

typedef struct ds1338_day {
    unsigned day:3;
    unsigned :5;
} ds1338_day;

typedef struct ds1338_date {
    union {
        struct {
            unsigned datel:4;
            unsigned dateh:2;
            unsigned :2;
        };
        struct {
            unsigned date:6;
            unsigned :2;
        };
    };
} ds1338_date;

typedef struct ds1338_month {
    union {
        struct {
            unsigned monthl:4;
            unsigned monthh:1;
            unsigned :3;
        };
        struct {
            unsigned month:5;
            unsigned :3;
        };
    };
} ds1338_month;

typedef struct ds1338_year {
    union {
        struct {
            unsigned yearl:4;
            unsigned yearh:4;
        };
        struct {
            unsigned year:8;
        };
    };
} ds1338_year;

/*
 * Rate Select (RS1 and RS0): These bits control the frequency of the
 *   square-wave output when the square-wave output has been enabled.
 *
 *    -------------------------------------
 *   | OUT | RS1 | RS0 | SQW Output | SQWE |
 *    -------------------------------------
 *   |  X  |  0  |  0  |        1Hz |   1  |
 *   |  X  |  0  |  1  |   4.096kHz |   1  |
 *   |  X  |  1  |  0  |   8.192kHz |   1  |
 *   |  X  |  1  |  1  |  32.768kHz |   1  |
 *   |  0  |  X  |  X  |          0 |   0  |
 *   |  1  |  X  |  X  |          1 |   0  |
 *    -------------------------------------
 *
 * Square-Wave Enable (SQWE): When set to logic 1, this bit enables the
 *   oscillator output to operate with either VCC or VBAT applied.
 *
 * Oscillator Stop Flag (OSF): A logic 1 in this bit indicates that the
 *   oscillator has stopped or was stopped for some time period and can be used
 *   to judge the validity of the clock and calendar data.
 *
 * Output Control (OUT): Controls the output level of the SQW/OUT pin when the
 *   square-wave output is disabled. If SQWE = 0, the logic level on the SQW/OUT
 *   pin is 1 if OUT = 1; it is 0 if OUT = 0.
 */

typedef struct ds1338_control {
    union{
        struct{
            unsigned RS0 : 1;
            unsigned RS1 : 1;
            unsigned : 2;
            unsigned SQWE : 1;
            unsigned OSF : 1;
            unsigned : 1;
            unsigned OUT : 1;
        }bits;
        UINT8 reg;
    };
} ds1338_control;

void ds1338_init(ds1338_s* ds1338) {

    ds1338->seconds = 0x00;
    ds1338->minutes = 0x00;
    ds1338->hours   = 0x00;
    ds1338->day     = 0x00;
    ds1338->month   = 0x00;
    ds1338->year    = 0x00;



    Ds1338Send(DS1338_WRITE,DS1338_CONTROLS_REG, 0x00);
}

void ds1338_setDate(ds1338_s* ds1338, UINT8 year,
                                     UINT8 month,
                                     UINT8 date){
    ds1338_date d;
    ds1338_month m;
    ds1338_year y;

    d.date=date   & 0x3F;
    m.month=month & 0x1F;
    y.year=year   & 0xFF;

    Ds1338Send(DS1338_WRITE,DS1338_YEARS_REG, y.year);
    Ds1338Send(DS1338_WRITE,DS1338_MONTHS_REG, m.month);
    Ds1338Send(DS1338_WRITE,DS1338_DATES_REG, d.date);
}
void ds1338_setClock(ds1338_s* ds1338, UINT8 hours,
                                      UINT8 minutes,
                                      UINT8 seconds){
    ds1338_seconds s;
    ds1338_minutes m;
    ds1338_hours h;

    s.seconds=seconds;
    s.ch=0;

    m.minutes=minutes & 0x7F;

    h.hours24 = hours & 0x3F;
    h.clockMode = 0;

    Ds1338Send(DS1338_WRITE,DS1338_HOURS_REG ,h.hours24);
    Ds1338Send(DS1338_WRITE,DS1338_MINUTES_REG ,m.minutes);
    Ds1338Send(DS1338_WRITE,DS1338_SECONDS_REG ,s.seconds);
}

void ds1338_GetClock(ds1338_s* ds1338)
{
    UINT8 seconds;
    UINT8 minutes;
    UINT8 hours;

    Ds1338Receive(DS1338_WRITE,DS1338_SECONDS_REG,&seconds);
    Ds1338Receive(DS1338_WRITE,DS1338_MINUTES_REG,&minutes);
    Ds1338Receive(DS1338_WRITE,DS1338_HOURS_REG,&hours);

    ds1338->seconds = (seconds & 0x0F)+(((seconds & 0x70)>>4U)*10U);
    ds1338->minutes = (minutes & 0x0F)+(((minutes & 0x70)>>4U)*10U);
    ds1338->hours   = (hours & 0x0F)+(((hours & 0x10)>>4U)*10U)+(((hours & 0x20)>>5)*20U);
}

void ds1338_GetDate(ds1338_s* ds1338)
{
    UINT8 day;
    UINT8 month;
    UINT8 year;

    Ds1338Receive(DS1338_WRITE,DS1338_DATES_REG,&day);
    Ds1338Receive(DS1338_WRITE,DS1338_MONTHS_REG,&month);
    Ds1338Receive(DS1338_WRITE,DS1338_YEARS_REG,&year);

    ds1338->day = day;
    ds1338->month = month;
    ds1338->year = year;
}

void ds1338_EnableOscOutput(ds1338_s* ds1338,UINT8 Frequency)
{
    ds1338_control control_data;
    control_data.bits.SQWE = 1;
    control_data.bits.RS0 = (Frequency & 0x01);
    control_data.bits.RS1 = (Frequency & 0x02)>>1;


    Ds1338Send(DS1338_WRITE,DS1338_CONTROLS_REG ,control_data.reg);
}

void Ds1338Send(UINT8 ubAddress,UINT8 ubRegister, UINT8 ubData){
   UINT8 dataBuffer[3];
   INT8 err;
   dataBuffer[0] = ubAddress;
   dataBuffer[1] = ubRegister;
   dataBuffer[2] = ubData;

//   I2c.Slave7BitsAddressSendData(I2C5, dataBuffer[0], &dataBuffer[1], 2);

   while(I2c.Var.oI2cReadIsRunning[I2C5]);  // Wait for any I2C5 write sequence to end\n
   err = I2c.AddDataToFifoWriteQueue(I2C5, &dataBuffer[0], sizeof(dataBuffer), TRUE);
   if (err < 0)
   {
      LED_ERROR_ON;
   }

}

void Ds1338Receive(UINT8 ubAddressWrite, UINT8 ubRegister, UINT8* ubData)
{
  INT8 err;
    UINT8 dataBuffer[2];
    dataBuffer[0] = ubAddressWrite;
    dataBuffer[1] = ubRegister;

    while(I2c.Var.oI2cWriteIsRunning[I2C5]);  // Wait for any I2C5 write sequence to end
    I2c.AddDataToFifoReadQueue(I2C5, &dataBuffer[0], sizeof(dataBuffer), 1);

    while(I2c.Var.oI2cReadIsRunning[I2C5]);   // Wait for any I2C1 read sequence to end
    while(!I2c.Var.oRxDataAvailable[I2C5]);   // Wait for RX data to be available

    err = I2c.ReadRxFifo(I2C5, ubData, 1);
    if (err < 0)
    {
      LED_ERROR_ON;
    }
}
