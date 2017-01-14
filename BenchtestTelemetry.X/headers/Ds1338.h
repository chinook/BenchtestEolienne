#ifndef __DS1338_H
#define	__DS1338_H


#include <string.h>
#include "Setup.h"

/*Frequency*/
#define FREQ_1HZ        0
#define FREQ_4_096KHZ   1
#define FREQ_8_192KHZ   2
#define FREQ_32_768KHZ  3

typedef struct{
    /*Time variables*/
    UINT8 seconds;
    UINT8 minutes;
    UINT8 hours;
    UINT8 day;
    UINT8 month;
    UINT8 year;

    /*Configuration*/
    UINT8 port;
}ds1338_s;

void ds1338_init(ds1338_s* ds1338);
void ds1338_setDate(ds1338_s* ds1338, UINT8 year,
                                     UINT8 month,
                                     UINT8 day);
void ds1338_setClock(ds1338_s* ds1338, UINT8 hours,
                                      UINT8 minutes,
                                      UINT8 seconds);

void ds1338_GetClock(ds1338_s* ds1338);

void ds1338_GetDate(ds1338_s* ds1338);

void ds1338_EnableOscOutput(ds1338_s* ds1338,UINT8 Frequency);

void Ds1338Send(UINT8 ubAddress,UINT8 ubRegister, UINT8 ubData);

void Ds1338Receive(UINT8 ubAddressWrite, UINT8 ubRegister, UINT8* ubData);

#endif // __DS1338_H
