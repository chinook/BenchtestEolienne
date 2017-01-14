//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : Setup.h
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the setup header for the system. It contains function
//           prototypes as well as macros and the public structure of
//           ChinookLib functions.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : For ChinookLib to be useable, it must be cloned on your hard
//           drive so the path
//               "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"
//           references an existing file.
//
//           Function names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef SETUP_H
#define	SETUP_H

//%%%%%%%%%%%%%%%%%%%%%%%%%
// ChinookLib files
//%%%%%%%%%%%%%%%%%%%%%%%%%
#include "../ChinookLib/ChinookLib.X/headers/ChinookLib.h"

extern volatile BOOL oNewAdcAvailable;
//==============================================================================
// State Machine public functions prototypes
//==============================================================================
void InitTimer        (void);
void InitPwm          (void);
void InitPorts        (void);
void InitCan          (void);
void InitSkadi        (void);
void InitSpi          (void);
void InitUart         (void);
void InitI2c          (void);
void InitWdt          (void);
void InitAdc          (void);
void InitInputCapture (void);
void StartInterrupts  (void);

//==============================================================================
// Macro definitions
//==============================================================================
#define INIT_TIMER          InitTimer()
#define INIT_PWM            InitPwm()
#define INIT_PORTS          InitPorts()
#define INIT_CAN            InitCan()
#define INIT_SPI            InitSpi()
#define INIT_UART           InitUart()
#define INIT_SKADI          InitSkadi()
#define INIT_I2C            InitI2c()
#define INIT_WDT            InitWdt()
#define INIT_ADC            InitAdc()
#define INIT_INPUT_CAPTURE  InitInputCapture()
#define START_INTERRUPTS    StartInterrupts()

//==============================================================================
// Define OUTPUT LED
//==============================================================================
#define LED_DEBG0           LATBbits.LATB11
#define LED_DEBG3           LATBbits.LATB13
#define LED_CAN             LATBbits.LATB15
#define LED_ERROR           LATGbits.LATG3
#define LED_STATUS          LATGbits.LATG2

#define LED_DEBG0_ON        Port.B.ClearBits(BIT_11)
#define LED_DEBG3_ON        Port.B.ClearBits(BIT_13)
#define LED_CAN_ON          Port.B.ClearBits(BIT_15)
#define LED_ERROR_ON        Port.G.ClearBits(BIT_3)
#define LED_STATUS_ON       Port.G.ClearBits(BIT_2)

#define LED_DEBG0_OFF       Port.B.SetBits(BIT_11)
#define LED_DEBG3_OFF       Port.B.SetBits(BIT_13)
#define LED_CAN_OFF         Port.B.SetBits(BIT_15)
#define LED_ERROR_OFF       Port.G.SetBits(BIT_3)
#define LED_STATUS_OFF      Port.G.SetBits(BIT_2)

#define LED_DEBG0_TOGGLE    Port.B.ToggleBits(BIT_11)
#define LED_DEBG3_TOGGLE    Port.B.ToggleBits(BIT_13)
#define LED_CAN_TOGGLE      Port.B.ToggleBits(BIT_15)
#define LED_ERROR_TOGGLE    Port.G.ToggleBits(BIT_3)
#define LED_STATUS_TOGGLE   Port.G.ToggleBits(BIT_2)
//==============================================================================
// Define INPUT SWITCH
//==============================================================================
#define SW1                 PORTEbits.RE5
#define SW2                 PORTEbits.RE6
#define SW3                 PORTEbits.RE7

//==============================================================================
// Define ANALOG INPUT
//==============================================================================
#define AI1                 PORTBbits.RB2   // AN2
#define AI2                 PORTBbits.RB3   // AN3
#define AI3                 PORTBbits.RB4   // AN4
#define AI4                 PORTBbits.RB5   // AN5
#define AI5                 PORTBbits.RB9   // AN9
#define AI6                 PORTBbits.RB10  // AN10

//==============================================================================
// Define ANALOG INPUT
//==============================================================================
#define DI1                 PORTDbits.RD4   // IC5
#define DI2                 PORTDbits.RD11  // IC4
#define DI3                 PORTDbits.RD10  // IC3
#define DI4                 PORTDbits.RD9   // IC2
#define DI5                 PORTDbits.RD8   // IC1

//==============================================================================
// Define SPI
//==============================================================================
#define SDCARD_CS           LATFbits.LATF3  //SPI3
#define SDCARD_SCLK         LATDbits.LATD1  //SPI3
#define SDCARD_MISO         LATDbits.LATD2  //SPI3
#define SDCARD_MOSI         PORTDbits.RD3   //SPI3

//==============================================================================
// Define UART
//==============================================================================
#define USB_RXD             PORTBbits.RB8   // UART5_RXD
#define USB_TXD             LATBbits.LATB14 // UART5_TXD

#define XBEE_RXD            PORTGbits.RG9   // UART6_RXD
#define XBEE_TXD            LATGbits.LATG6  // UART6_TXD

//==============================================================================
// Define I2C
//==============================================================================
#define RTC_SDA             LATFbits.LATF4  // SDA5
#define RTC_SCL             LATFbits.LATF5  // SCL5

#define EEPROM_SDA          LATGbits.LATG7  // SDA4
#define EEPROM_SCL          LATGbits.LATG8  // SCL4

//==============================================================================
// Define CAN
//==============================================================================
#define CAN_NB_CHANNEL      12               // 12 CAN channels
#define CAN_BUFFER_SIZE     8               // 8 message buffer

#define WIND_SPEED_ID     0x19
#define WIND_DIRECTION_ID 0x20
#define TURBINE_RPM_ID    0x21
#define WHEEL_RPM_ID      0x22
#define BOARD_ID_ID       0x70
#define BOARD_ID          0x60
#define DISCONNECT_ID     0x71

#define SEND_WIND_SPEED_TO_CAN        Can.SendFloat(CAN1, WIND_SPEED_ID, sSensor.avgWindSpeed)
#define SEND_WIND_DIRECTION_TO_CAN    Can.SendFloat(CAN1, WIND_DIRECTION_ID, sSensor.avgWindDirection)
#define SEND_TURBINE_RPM_TO_CAN       Can.SendFloat(CAN1, TURBINE_RPM_ID, sSensor.avgTurbineRpm)
#define SEND_WHEEL_RPM_TO_CAN         Can.SendFloat(CAN1, WHEEL_RPM_ID, sSensor.avgWheelRpm)
#define SEND_BOARD_ID                 Can.SendData(CAN1, BOARD_ID_ID, BOARD_ID)
#define SEND_DISCONNECT               Can.SendData(CAN1, DISCONNECT_ID, BOARD_ID)



BYTE    CanMessageFifoArea[CAN_NB_CHANNEL*CAN_BUFFER_SIZE*CAN_TX_RX_MESSAGE_SIZE_BYTES];

//==============================================================================
// Variable declarations
//==============================================================================
struct sChinook Chinook; // ChinookLib functions



#endif	/* SETUP_H */