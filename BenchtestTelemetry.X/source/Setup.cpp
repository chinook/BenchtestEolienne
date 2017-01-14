//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : Setup.c
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the C file for the setup of the system. It contains the
//           initialization functions.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : For ChinookLib to be useable, it must be cloned on your hard
//           drive so the path
//               "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"
//           references an existing file.
//
//           Function names can and should be renamed by the user to improve the
//           readability of the code. Also, the LED used for testing errors in
//           TimerInit is a LED on the MAX32 development board. Developpers
//           should test for errors by the means (hardware of software) they
//           judge are the best.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\Setup.h"
#include "..\headers\Interrupts.h"
#include "..\headers\SkadiFunctions.h"


//==============================================================================
//	Variable Declaration
//==============================================================================

/***********************************
 * Table of functions used in Skadi
 **********************************/
sSkadiCommand_t skadiCommandTable[] =
{
   {"LedDebug"    , LedDebug    , 1, "Usage : flash Led DEBUG"}   // 1 argument
  ,{"LedCan"      , LedCan      , 1, "Usage : flash Led CAN"}     // 1 argument
  ,{"ReInitSystem", ReInitSystem, 0, "Redo StateInit()"}          // 0 argument
};

//==============================================================================
//	INIT FUNCTIONS
//==============================================================================

//===========================
//	INIT TIMERS
//===========================
void InitTimer(void)
{

  INT32 timerCounterValue = 0;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	Open timers
//%%%%%%%%%%%%%%%%%%%%%%%%%%%
  timerCounterValue = Timer.Open(TIMER_1, 500, SCALE_MS);   // Open Timer 1 with a period of 500 ms
  if (timerCounterValue < 0)
  {
//    Port.A.SetBits(BIT_3);    // LED4 on MAX32
  }
  timerCounterValue = Timer.Open(TIMER_2, 100, SCALE_US);   // Open Timer 2 with a period of 100 us, used for IC
  if (timerCounterValue < 0)
  {
//    Port.B.ClearBits(BIT_13);    // LED4 on MAX32
  }
  timerCounterValue = Timer.Open(TIMER_3, 300, SCALE_US);   // Open Timer 3 with a period of 300 us, used for ADC
  if (timerCounterValue < 0)
  {
//    Port.A.SetBits(BIT_3);    // LED4 on MAX32
  }
  timerCounterValue = Timer.Open(TIMER_4, 500, SCALE_MS);   // Open Timer 4 with a period of 500 ms
  if (timerCounterValue < 0)
  {
//    Port.A.SetBits(BIT_3);    // LED4 on MAX32
  }
  timerCounterValue = Timer.Open(TIMER_5, 100, SCALE_US);   // Open Timer 5 with a period of 100 us, used for averaging state
  if (timerCounterValue < 0)
  {
//    Port.A.SetBits(BIT_3);    // LED4 on MAX32
  }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	Configure timer interrupts
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  Timer.ConfigInterrupt(TIMER_1, TIMER1_INTERRUPT_PRIORITY, TIMER1_INTERRUPT_SUBPRIORITY); // Sets the priority of the TIMER_1 to the values specified in Interrupt.h
  Timer.ConfigInterrupt(TIMER_2, TIMER2_INTERRUPT_PRIORITY, TIMER2_INTERRUPT_SUBPRIORITY); // Sets the priority of the TIMER_2 to the values specified in Interrupt.h
  Timer.ConfigInterrupt(TIMER_3, TIMER3_INTERRUPT_PRIORITY, TIMER3_INTERRUPT_SUBPRIORITY); // Sets the priority of the TIMER_3 to the values specified in Interrupt.h
  Timer.ConfigInterrupt(TIMER_4, TIMER4_INTERRUPT_PRIORITY, TIMER4_INTERRUPT_SUBPRIORITY); // Sets the priority of the TIMER_4 to the values specified in Interrupt.h
  Timer.ConfigInterrupt(TIMER_5, TIMER5_INTERRUPT_PRIORITY, TIMER5_INTERRUPT_SUBPRIORITY); // Sets the priority of the TIMER_5 to the values specified in Interrupt.h

}

//===========================
//	INIT SPI
//===========================
void InitSpi(void)
{
  INT8 err = 0;
  SpiOpenFlags_t oMasterFlags =   SPI_MASTER_MODE
                                | SPI_MASTER_SS
                                | SPI_16_BITS_CHAR
                                | SPI_ENHANCED_BUFFER_MODE
                                | SPI_TX_EVENT_BUFFER_EMPTY
                                | SPI_RX_EVENT_BUFFER_NOT_EMPTY
                ;

  err = Spi.Open(SPI3, oMasterFlags, 5e6);   // Open the SPI3 as a master at a bitrate of 5 MHz
  if (err < 0)                // Check for errors
  {
//    Port.C.SetBits(BIT_1);    // Turn on the LD5 on MAX32
  }

  // SPI interrupts not functionnal as of yet
//  Spi.ConfigInterrupt(SPI3, SPI3_INTERRUPT_PRIORITY, SPI4_INTERRUPT_SUBPRIORITY);  // Configure Interrupt for SPI3
}

//===========================
//	INIT SKADI
//===========================
void InitSkadi(void)
{
//  Skadi.Init(skadiCommandTable, sizeof(skadiCommandTable)/sizeof(sSkadiCommand_t), UART5, FALSE);
  Skadi.Init(skadiCommandTable, sizeof(skadiCommandTable)/sizeof(sSkadiCommand_t), UART5, TRUE);    // TRUE ==> Use interrupts
}


//===========================
//	INIT PWM
//===========================
void InitPwm(void)
{

  // Open PWM1 using Timer3 with 50% duty cycle and 0% offset
  Pwm.Open(PWM_1);
  Pwm.SetDutyCycle  (PWM_1, 50);
  Pwm.SetPulseOffset(PWM_1,  0);

  // Open PWM2 using Timer3 with 50% duty cycle and 0% offset
  Pwm.Open(PWM_2);
  Pwm.SetDutyCycle  (PWM_2, 50);
  Pwm.SetPulseOffset(PWM_2,  0);

  // Open PWM3 using Timer3 with 50% duty cycle and 0% offset
  Pwm.Open(PWM_3);
  Pwm.SetDutyCycle  (PWM_3, 50);
  Pwm.SetPulseOffset(PWM_3,  0);

  // Open PWM4 using Timer3 with 50% duty cycle and 0% offset
  Pwm.Open(PWM_4);
  Pwm.SetDutyCycle  (PWM_4, 50);
  Pwm.SetPulseOffset(PWM_4,  0);

  // Open PWM5 using Timer3 with 50% duty cycle and 0% offset
//  Pwm.Open(PWM_5);
//  Pwm.SetDutyCycle  (PWM_5, 50);
//  Pwm.SetPulseOffset(PWM_5,  0);

}

//===========================
//	INIT PORTS
//===========================
void InitPorts(void)
{
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Set unused pins as input to protect the pins of the microcontroller
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  Port.A.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3      // RA8, RA11-13 non existent
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_9  | BIT_10 | BIT_14 | BIT_15 );

  Port.B.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_8  | BIT_9  | BIT_10 | BIT_11
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );

  Port.C.CloseBits  ( BIT_1  | BIT_2  | BIT_3  | BIT_4      // RC0, RC5-11 non existent
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );

  Port.D.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_8  | BIT_9  | BIT_10 | BIT_11
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );

  Port.E.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3      // RE10-15 non existent
                    | BIT_4  | BIT_5  | BIT_6  | BIT_7
                    | BIT_8  | BIT_9  );

  Port.F.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3      // RF6-7, RF9-11, RF14-15 non existent
                    | BIT_4  | BIT_5  | BIT_8  | BIT_12
                    | BIT_13 );

  Port.G.CloseBits  ( BIT_0  | BIT_1  | BIT_2  | BIT_3      // RG4-5, RG10-11 non existent
                    | BIT_6  | BIT_7  | BIT_8  | BIT_9
                    | BIT_12 | BIT_13 | BIT_14 | BIT_15 );


  /* Setup IO LED */
  Port.B.SetPinsDigitalOut(BIT_11);     // LED_DEBG0
  Port.B.SetPinsDigitalOut(BIT_13);     // LED_DEBG3
  Port.B.SetPinsDigitalOut(BIT_15);     // LED_CAN
  Port.G.SetPinsDigitalOut(BIT_3);      // LED_ERROR
  Port.G.SetPinsDigitalOut(BIT_2);      // LED_STATUS

  /* Setup IO SWITCH */
  Port.E.SetPinsDigitalIn(BIT_5);       // SW1
  Port.E.SetPinsDigitalIn(BIT_6);       // SW2
  Port.E.SetPinsDigitalIn(BIT_7);       // SW3

  /* Setup ANALOG INPUT */
  Port.B.SetPinsAnalogIn(BIT_2);        // AI1
  Port.B.SetPinsAnalogIn(BIT_3);        // AI2
  Port.B.SetPinsAnalogIn(BIT_4);        // AI3
  Port.B.SetPinsAnalogIn(BIT_5);        // AI4
  Port.B.SetPinsAnalogIn(BIT_9);        // AI5
  Port.B.SetPinsAnalogIn(BIT_10);       // AI6

  /* Setup DIGITAL INPUT */
  Port.D.SetPinsDigitalIn(BIT_4);        // IC5
  Port.D.SetPinsDigitalIn(BIT_11);       // IC4
  Port.D.SetPinsDigitalIn(BIT_10);       // IC3
  Port.D.SetPinsDigitalIn(BIT_9);        // IC2
  Port.D.SetPinsDigitalIn(BIT_8);        // IC1

  /* Setup SPI IOs */
  Port.F.SetPinsDigitalOut(BIT_3);      // SDCARD_CS
  Port.D.SetPinsDigitalOut(BIT_1);      // SDCARD_SCLK
  Port.D.SetPinsDigitalIn(BIT_2);       // SDCARD_MISO
  Port.D.SetPinsDigitalOut(BIT_3);      // SDCARD_MOSI

  /* Setup UART IOs */
  Port.B.SetPinsDigitalIn(BIT_8);       // USB_RXD
  Port.B.SetPinsDigitalOut(BIT_14);     // USB_TXD

  Port.G.SetPinsDigitalIn(BIT_9);       // XBEE_RXD
  Port.G.SetPinsDigitalOut(BIT_6);      // XBEE_TXD

  /* Setup I2C IOs */
  Port.F.SetPinsDigitalOut(BIT_4);      // RTC_SDA
  Port.F.SetPinsDigitalOut(BIT_5);      // RTC_SCL

  Port.G.SetPinsDigitalOut(BIT_7);      // EEPROM_SDA
  Port.G.SetPinsDigitalOut(BIT_8);      // EEPROM_SCL

}

//===========================
//	INIT UART
//===========================
void InitUart (void)
{

  UartConfig_t       oConfig      = UART_ENABLE_PINS_TX_RX_ONLY;
  UartConfig_t       oConfigXbee      = UART_ENABLE_PINS_TX_RX_ONLY; //| UART_ENABLE_HIGH_SPEED;
  UartFifoMode_t     oFifoMode    = UART_INTERRUPT_ON_TX_BUFFER_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY;
  UartLineCtrlMode_t oLineControl = UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1;

  Uart.Open(UART5, BAUD9600, oConfig, oFifoMode, oLineControl);   // Open UART 5 as : 9600 BAUD, 1 stop bit, no parity and 8 bits data
  Uart.Open(UART6, BAUD9600, oConfigXbee, oFifoMode, oLineControl);   // Open UART 6 as : 9600 BAUD, 1 stop bit, no parity and 8 bits data

  Uart.EnableRx(UART5);
  Uart.EnableRx(UART6);

  Uart.EnableTx(UART5);
  Uart.EnableTx(UART6);

  Uart.ConfigInterrupt(UART5, UART5_INTERRUPT_PRIORITY, UART5_INTERRUPT_SUBPRIORITY);
  Uart.ConfigInterrupt(UART6, UART6_INTERRUPT_PRIORITY, UART6_INTERRUPT_SUBPRIORITY);

}

//===========================
//	INIT CAN BUS
//===========================
void InitCan(void)
{
  Can.Initialize(CAN1, CanMessageFifoArea, CAN_NB_CHANNEL, CAN_BUFFER_SIZE, FALSE);

  Can.SetChannel(CAN1, CAN_CHANNEL0, CAN_BUFFER_SIZE, TX);    // WINDSPEED
  Can.SetChannel(CAN1, CAN_CHANNEL1, CAN_BUFFER_SIZE, TX);    // WINDIRECTION
  Can.SetChannel(CAN1, CAN_CHANNEL2, CAN_BUFFER_SIZE, TX);    // TURBINE RPM
  Can.SetChannel(CAN1, CAN_CHANNEL3, CAN_BUFFER_SIZE, TX);    // WHEEL RPM
  Can.SetChannel(CAN1, CAN_CHANNEL9, CAN_BUFFER_SIZE, TX);    // BOARD ID
  Can.SetChannel(CAN1, CAN_CHANNEL10, CAN_BUFFER_SIZE, TX);   // DISCONNECT ID

  Can.SetChannel(CAN1, CAN_CHANNEL4, CAN_BUFFER_SIZE, RX);    // STEERING WHEEL BUTTON STATE
  Can.SetChannel(CAN1, CAN_CHANNEL5, CAN_BUFFER_SIZE, RX);    // PITCH
  Can.SetChannel(CAN1, CAN_CHANNEL6, CAN_BUFFER_SIZE, RX);    // GEAR
  Can.SetChannel(CAN1, CAN_CHANNEL7, CAN_BUFFER_SIZE, RX);    // BATTERY VOLTAGE
  Can.SetChannel(CAN1, CAN_CHANNEL8, CAN_BUFFER_SIZE, RX);    // BATTERY CURRENT

  Can.SetChannelMask(CAN1, CAN_CHANNEL4, CAN_FILTER0, 0x42, CAN_FILTER_MASK0, 0x7FF);   // STEERING WHEEL BUTTON STATE
  Can.SetChannelMask(CAN1, CAN_CHANNEL5, CAN_FILTER1, 0x13, CAN_FILTER_MASK0, 0x7FF);   // PITCH
  Can.SetChannelMask(CAN1, CAN_CHANNEL6, CAN_FILTER2, 0x23, CAN_FILTER_MASK0, 0x7FF);   // GEAR
  Can.SetChannelMask(CAN1, CAN_CHANNEL7, CAN_FILTER3, 0x72, CAN_FILTER_MASK0, 0x7FF);   // BATTERY VOLTAGE
  Can.SetChannelMask(CAN1, CAN_CHANNEL8, CAN_FILTER4, 0x73, CAN_FILTER_MASK0, 0x7FF);   // BATTERY CURRENT

  Can.ConfigInterrupt(CAN1, CAN1_INTERRUPT_PRIORITY, CAN1_INTERRUPT_SUBPRIORITY);

  Can.EnableInterrupt(CAN1);


}

//===========================
//	INIT I2C
//===========================
void InitI2c(void)
{
  INT8 err;
 
//  I2c.Open(I2C4, I2C_FREQ_400K);
//  err = I2c.ConfigInterrupt(I2C4, I2C4_INTERRUPT_PRIORITY, I2C4_INTERRUPT_SUBPRIORITY);
//  if (err < 0)
//  {
////    LED_ERROR_ON;
//  }

  I2c.Open(I2C5, I2C_FREQ_100K);
  err = I2c.ConfigInterrupt(I2C5, I2C5_INTERRUPT_PRIORITY, I2C5_INTERRUPT_SUBPRIORITY);
  if (err < 0)
  {
//    LED_ERROR_ON;
  }
}

//===========================
//	INIT WATCHDOG TIMER
//===========================
void InitWdt(void)
{
  return;
}

//===========================
//	INIT ADC
//===========================
void InitAdc(void)
{
  oNewAdcAvailable = 0;
    // Mode of operation. Uncomment the one you need.
  //================================================
  UINT32 samplingClk = ADC_CLK_TMR;     // Timer3 used for sampling
//  UINT32 samplingClk = ADC_CLK_AUTO;    // Internal counter used for sampling
//  UINT32 samplingClk = ADC_CLK_INT0;    // Active transition on INT0 used for sampling
//  UINT32 samplingClk = ADC_CLK_MANUAL;  // Manual sampling.
  //================================================

  // Hardware config. These are exemples.
  //================================================
  UINT32 configHardware = ADC_VREF_AVDD_AVSS      // Vref+ is AVdd and Vref- is AVss
//                        | ADC_SAMPLES_PER_INT_16; // 16 samples/interrupt
//  UINT32 configHardware = ADC_VREF_EXT_AVSS       // Vref+ is External and Vref- is AVss
                        | ADC_SAMPLES_PER_INT_3; // 1 sample/interrupt => used in manual mode
  //================================================

  // Port config. These are exemples.
  //================================================
//  UINT32 configPort = ENABLE_ALL_ANA; // Enable AN0-AN15 in analog mode
//  UINT32 configScan = 0; // Scan all ANs

  UINT32 configPort = ENABLE_AN2_ANA
                    | ENABLE_AN3_ANA
                    | ENABLE_AN4_ANA; // Enable AN2, AN3 and AN4 in analog mode
  UINT32 configScan = SKIP_SCAN_AN0
                    | SKIP_SCAN_AN1
                    | SKIP_SCAN_AN5
                    | SKIP_SCAN_AN6
                    | SKIP_SCAN_AN7
                    | SKIP_SCAN_AN8
                    | SKIP_SCAN_AN9
                    | SKIP_SCAN_AN10
                    | SKIP_SCAN_AN11
                    | SKIP_SCAN_AN12
                    | SKIP_SCAN_AN13
                    | SKIP_SCAN_AN14
                    | SKIP_SCAN_AN15; // Don't scan the channels that are not enabled by configPort
  //================================================

  // Open ADC with parameters above
  Adc.Open(samplingClk, configHardware, configPort, configScan);

  Adc.ConfigInterrupt(ADC_INTERRUPT_PRIORITY, ADC_INTERRUPT_SUBPRIORITY);
  return;
}

//===========================
//	INIT INPUT CAPTURE
//===========================
void InitInputCapture(void)
{
  // Capture every rising edge, 1 interrupt each capture, use the 16 bits Timer 2, capture the first rising edge, Input Capture ON
  UINT16 config = IC_EVERY_RISE_EDGE | IC_INT_1CAPTURE | IC_TIMER3_SRC | IC_CAP_16BIT | IC_FEDGE_RISE | IC_ON;

  // Capture every rising edge, 1 interrupt each capture, use the 32 bits Timer 23, capture the first rising edge, Input Capture ON
//  UINT16 config = IC_EVERY_RISE_EDGE | IC_INT_1CAPTURE | IC_CAP_32BIT | IC_FEDGE_RISE | IC_ON;

//  InputCapture.Open(IC1, config);
//  InputCapture.Open(IC2, config);
  InputCapture.Open(IC3, config);
  InputCapture.Open(IC4, config);
  InputCapture.Open(IC5, config);

//  InputCapture.ConfigInterrupt(IC1, IC1_INTERRUPT_PRIORITY, IC1_INTERRUPT_SUBPRIORITY);
//  InputCapture.ConfigInterrupt(IC2, IC2_INTERRUPT_PRIORITY, IC2_INTERRUPT_SUBPRIORITY);
  InputCapture.ConfigInterrupt(IC3, IC3_INTERRUPT_PRIORITY, IC3_INTERRUPT_SUBPRIORITY);
  InputCapture.ConfigInterrupt(IC4, IC4_INTERRUPT_PRIORITY, IC4_INTERRUPT_SUBPRIORITY);
  InputCapture.ConfigInterrupt(IC5, IC5_INTERRUPT_PRIORITY, IC5_INTERRUPT_SUBPRIORITY);

}


//===========================
//	START INTERRUPTS
//===========================
void StartInterrupts(void)
{

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Enable timer interrupts
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  Timer.EnableInterrupt(TIMER_1);
  Timer.EnableInterrupt(TIMER_2);
  Timer.EnableInterrupt(TIMER_3);
  Timer.EnableInterrupt(TIMER_4);
  Timer.EnableInterrupt(TIMER_5);


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Enable UART interrupts             // Not functionnal yet
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  Uart.EnableRxInterrupts(UART5);   // Enable RX Interrupts for UART5
  Uart.DisableTxInterrupts(UART5);   // Enable TX Interrupts for UART5

  Uart.EnableRxInterrupts(UART6);   // Enable RX Interrupts for UART6
  Uart.DisableTxInterrupts(UART6);   // Enable TX Interrupts for UART6


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Enable SPI interrupts             // Not functionnal yet
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//#ifdef __32MX795F512L__   // SPI1 only on this device
//  Spi.EnableRxInterrupts(SPI1);   // Enable RX Interrupts for SPI1
//  Spi.EnableTxInterrupts(SPI1);   // Enable TX Interrupts for SPI1
//#endif
//
//  Spi.EnableRxInterrupts(SPI2);   // Enable RX Interrupts for SPI2
//  Spi.EnableTxInterrupts(SPI2);   // Enable TX Interrupts for SPI2
//
//  Spi.EnableRxInterrupts(SPI3);   // Enable RX Interrupts for SPI3
//  Spi.EnableTxInterrupts(SPI3);   // Enable TX Interrupts for SPI3
//
//  Spi.EnableRxInterrupts(SPI4);   // Enable RX Interrupts for SPI4
//  Spi.EnableTxInterrupts(SPI4);   // Enable TX Interrupts for SPI4


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Enable ADC interrupts
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  Adc.EnableInterrupts();   // Works only when not in manual mode


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Enable InputCapture interrupts
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  InputCapture.EnableInterrupt(IC1);
  InputCapture.EnableInterrupt(IC2);
  InputCapture.EnableInterrupt(IC3);
  InputCapture.EnableInterrupt(IC4);
  InputCapture.EnableInterrupt(IC5);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Enable I2C interrupts
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  INT8 err;

  err = I2c.EnableInterrupt (I2C5, I2C_MASTER_INTERRUPT);
  if (err < 0)
  {
//    LED_ERROR_ON;
  }
  err = I2c.DisableInterrupt(I2C5, I2C_SLAVE_INTERRUPT);
  if (err < 0)
  {
//    LED_ERROR_ON;
  }
  err = I2c.DisableInterrupt(I2C5, I2C_BUS_COLLISION_INTERRUPT);
  if (err < 0)
  {
//    LED_ERROR_ON;
  }

//  err = I2c.EnableInterrupt (I2C4, I2C_MASTER_INTERRUPT);
//  if (err < 0)
//  {
////    LED_ERROR_ON;
//  }
//  err = I2c.DisableInterrupt(I2C4, I2C_SLAVE_INTERRUPT);
//  if (err < 0)
//  {
////    LED_ERROR_ON;
//  }
//  err = I2c.DisableInterrupt(I2C4, I2C_BUS_COLLISION_INTERRUPT);
//  if (err < 0)
//  {
////    LED_ERROR_ON;
//  }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Enable multi-vector interrupts
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
  INTEnableInterrupts();

}
