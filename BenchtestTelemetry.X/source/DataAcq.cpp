//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : DataAcq.c
// Author  : Mikael Ducharme
// Date    : 2015-04-20
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This code handles all the operations and functions related to the
//           Data Acquisition and processing
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : All the functions created here should be used in StateFunctions.c
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "../headers/DataAcq.h"


//==============================================================================
// Private functions prototypes
//==============================================================================


//==============================================================================
// Variable definitions
//==============================================================================

volatile sSensor_t sSensor;
volatile sSensorRawFreq_t sSensorRawFreq;

extern volatile UINT8 canGear;
extern volatile float canPitch;
extern volatile float canBatteryVoltage;
extern volatile float canBatteryCurrent;

//==============================================================================
// Functions
//==============================================================================


/**************************************************************
 * Function name  : DataStructInit
 * Purpose        : Initializes the data structure with 0s
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 DataStructInit(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  INT8 bError = 0;


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if(sSensor == NULL)
  {
    bError = -1;
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // CLEAR DATA STRUCTURE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else
  {
    /*Used inputs*/
    sSensor->fThrust = 0.0f;
    sSensor->fWindDirection = 0.0f;
    sSensor->fWindSpeed = 0.0f;
    sSensor->fTurbineRpm = 0.0f;
    sSensor->fWheelRpm = 0.0f;
    sSensor->fTorque = 0.0f;

    // Sum of Instant values for averaging
    sSensor->sumThrust = 0.0f;
    sSensor->sumWindDirection = 0.0f;
    sSensor->sumWindSpeed = 0.0f;
    sSensor->sumTurbineRpm = 0.0f;
    sSensor->sumWheelRpm = 0.0f;
    sSensor->sumTorque = 0.0f;

    // Summed values divided by number of samples
    sSensor->avgThrust = 0.0f;
    sSensor->avgWindDirection = 0.0f;
    sSensor->avgWindSpeed = 0.0f;
    sSensor->avgTurbineRpm = 0.0f;
    sSensor->avgWheelRpm = 0.0f;
    sSensor->avgTorque = 0.0f;
    
    sSensor->canGear = 0;
    sSensor->canTurbineDirection = 0.0f;
    sSensor->canPitch = 0.0f;
    sSensor->canBatteryVoltage = 0.0f;
    sSensor->canBatteryCurrent = 0.0f;

    sSensor->dataId = 0;

  }
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}



/**************************************************************
 * Function name  : GetThrust
 * Purpose        : Gets the Thrust value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetThrust(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;
    float adcValue;
    float processedValue;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET ADC VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    adcValue = Adc.Var.adcReadValues[2];

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // PROCESS ADC VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    processedValue = ((adcValue*THRUST_GAIN)+THRUST_OFFSET) * LBS_TO_NEWTON;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // STORE SENSOR VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sSensor->fThrust = processedValue;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}



/**************************************************************
 * Function name  : GetWindDirection
 * Purpose        : Gets the WindDirection value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetWindDirection(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;
    float adcValue;
    float processedValue;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET ADC VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    adcValue = Adc.Var.adcReadValues[3];

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // PROCESS ADC VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // *-1 added for logic : -180deg <- 0deg -> +180deg
    processedValue = ((adcValue * WIND_DIR_GAIN) + WIND_DIR_OFFSET - 180.0f)*(-1.0f);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF FOR EXTREMUM VALUES
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(processedValue < -180.0f)
    {
        sSensor->fWindDirection = -180.0f;
    }
    else if(processedValue > 180)
    {
        sSensor->fWindDirection = 180.0f;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // STORE SENSOR VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    else
    {
      sSensor->fWindDirection = processedValue;

    }


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}



/**************************************************************
 * Function name  : GetWindSpeed
 * Purpose        : Gets the WindSpeed value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetWindSpeed(sSensor_t* sSensor)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;
    float processedValue;
    float timeBetweenCaptures;
    float freq;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET INPUT CAPTURE VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      timeBetweenCaptures = InputCapture.GetTimeBetweenCaptures(IC5, SCALE_US);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // PROCESS INPUT CAPTURE VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      freq = 1/(timeBetweenCaptures * TIMER_SCALE_US);
      processedValue = freq * HZ_TO_MPH_WIND_SPEED * MPH_TO_MPS_WIND_SPEED;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF FOR VALUES UNDER 0.8 M/S and over 50 M/S
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(processedValue < 0.8f || processedValue > 50.0f)
    {
        sSensor->fWindSpeed = 0;
    }
    else
    {
      sSensor->fWindSpeed = processedValue;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}



/**************************************************************
 * Function name  : GetTurbineRpm
 * Purpose        : Gets the TurbineRpm value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetTurbineRpm(sSensor_t* sSensor)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;
    float processedValue;
    float timeBetweenCaptures;
    float freq;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET INPUT CAPTURE VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      timeBetweenCaptures = InputCapture.GetTimeBetweenCaptures(IC4, SCALE_US);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // PROCESS INPUT CAPTURE VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      freq = 1/(timeBetweenCaptures * TIMER_SCALE_US);
      processedValue = freq * HZ_TO_RPM_FUTEK_ENCODER;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF FOR VALUES UNDER 20 RPM and over 3000 RPM
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(processedValue < 20.0f || processedValue > 2200.0f)
    {
        sSensor->fTurbineRpm = 0;
    }
    else
    {
      sSensor->fTurbineRpm = processedValue;
    }
}



/**************************************************************
 * Function name  : GetWheelRpm
 * Purpose        : Gets the WheelRpm value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetWheelRpm(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;
    float processedValue;
    float timeBetweenCaptures;
    float freq;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET INPUT CAPTURE VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    timeBetweenCaptures = InputCapture.GetTimeBetweenCaptures(IC3, SCALE_US);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // PROCESS INPUT CAPTURE VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    freq = 1/(timeBetweenCaptures * TIMER_SCALE_US);
    if(freq < 39.0f || freq > 650)
    {
      freq = 0.0f;
    }

    processedValue = freq * HZ_TO_RPM_SKF_ENCODER;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF FOR VALUES UNDER 1 M/S
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    sSensor->fWheelRpm = processedValue;
    
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
 
}



/**************************************************************
 * Function name  : GetTorque
 * Purpose        : Gets the Torque value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetTorque(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;
    float adcValue;
    float processedValue;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET ADC VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    adcValue = Adc.Var.adcReadValues[4];

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // PROCESS ADC VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    processedValue = (adcValue * TORQUE_METER_GAIN) + TORQUE_METER_OFFSET;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Check the value to send |torque| with minimum value of 0.5 Nm
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(processedValue < 0.0f)   // check if processedValue in negative
    {
      processedValue *= -1.0f;  // changes processedValue to |processedValue|
    }
    if(processedValue < 0.5f)   // Values under 0.5 Nm become 0 Nm
    {
      processedValue = 0.0f;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // STORE SENSOR VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sSensor->fTorque = processedValue;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}


/**************************************************************
 * Function name  : GetCanGear
 * Purpose        : Gets the Gear value from CAN bus and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetCanGear(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET CAN VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sSensor->canGear = canGear;


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}

/**************************************************************
 * Function name  : GetCanBatteryVoltage
 * Purpose        : Gets the battery voltage value from CAN bus and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetCanBatteryVoltage(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET CAN VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sSensor->canBatteryVoltage = 0;
    sSensor->canBatteryVoltage = canBatteryVoltage;


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}

/**************************************************************
 * Function name  : GetCanBatteryCurrent
 * Purpose        : Gets the battery current value from CAN bus and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetCanBatteryCurrent(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET CAN VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sSensor->canBatteryCurrent = canBatteryCurrent; 


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}

/**************************************************************
 * Function name  : GetCanPitch
 * Purpose        : Gets the Pitch value from CAN bus and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetCanPitch(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    INT8 bError;

    bError = 0;
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // GET CAN VALUE
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sSensor->canPitch = canPitch;


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN ERROR BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return bError;
}


/**************************************************************
 * Function name  : PrintThrust
 * Purpose        : Prints the Thrust value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintThrust(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//    UINT16 sizeOfbString;
    sUartLineBuffer_t buffer = {0};
    INT8 err = 0;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(sSensor == NULL)
    {
        ubValid = FALSE;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF VALID, PRINT TO UART
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(ubValid)
    {
//      sprintf(bString, "\n\rThrust = %.2f N \n\r", sSensor->fThrust);
//      Uart.SendDataBuffer(UART5, bString, sizeof(bString));
      buffer.length = sprintf(buffer.buffer, "\n\rThrust = %.2f N \n\r", sSensor->avgThrust); // UART w/ interrupts
      do
      {
        Uart.PutTxFifoBuffer(UART5, &buffer);
      } while (err < 0);
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN VALIDATION BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return ubValid;
}



/**************************************************************
 * Function name  : PrintWindDirection
 * Purpose        : Prints the WindDirection value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWindDirection(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//    UINT16 sizeOfbString;
    sUartLineBuffer_t buffer = {0};
    INT8 err = 0;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(sSensor == NULL)
    {
        ubValid = FALSE;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF VALID, PRINT TO UART
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(ubValid)
    {
//      sizeOfbString = sprintf(bString, "\n\rWindDirection = %.2f DEG \n\r", sSensor->fWindDirection);
//      Uart.SendDataBuffer(UART5, bString, sizeOfbString);
      buffer.length = sprintf(buffer.buffer, "\n\rWindDirection = %.2f DEG \n\r", sSensor->fWindDirection); // UART w/ interrupts
      do
      {
        Uart.PutTxFifoBuffer(UART5, &buffer);
      } while (err < 0);
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN VALIDATION BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return ubValid;
}



/**************************************************************
 * Function name  : PrintWindSpeed
 * Purpose        : Prints the WindSpeed value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWindSpeed(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//    UINT16 sizeOfbString;
    sUartLineBuffer_t buffer = {0};
    INT8 err = 0;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(sSensor == NULL)
    {
        ubValid = FALSE;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF VALID, PRINT TO UART
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(ubValid)
    {
//      sizeOfbString = sprintf(bString, "\n\rWindSpeed = %.2f M/S \n\r", sSensor->fWindSpeed);
//      Uart.SendDataBuffer(UART5, bString, sizeOfbString);
      buffer.length = sprintf(buffer.buffer, "\n\rWindSpeed = %.2f M/S \n\r", sSensor->fWindSpeed); // UART w/ interrupts
      do
      {
        Uart.PutTxFifoBuffer(UART5, &buffer);
      } while (err < 0);
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN VALIDATION BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return ubValid;
}



/**************************************************************
 * Function name  : PrintTurbineRpm
 * Purpose        : Prints the TurbineRpm value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintTurbineRpm(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//    UINT16 sizeOfbString;
    sUartLineBuffer_t buffer = {0};
    INT8 err = 0;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(sSensor == NULL)
    {
        ubValid = FALSE;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF VALID, PRINT TO UART
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(ubValid)
    {
//      sizeOfbString = sprintf(bString, "\n\rTurbineRpm = %.2f RPM \n\r", sSensor->fTurbineRpm);
//      Uart.SendDataBuffer(UART5, bString, sizeOfbString);
      buffer.length = sprintf(buffer.buffer, "\n\rTurbineRpm = %.2f RPM \n\r", sSensor->fTurbineRpm); // UART w/ interrupts
      do
      {
        Uart.PutTxFifoBuffer(UART5, &buffer);
      } while (err < 0);
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN VALIDATION BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return ubValid;
}



/**************************************************************
 * Function name  : PrintWheelRpm
 * Purpose        : Prints the WheelRpm value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWheelRpm(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//    UINT16 sizeOfbString;
    sUartLineBuffer_t buffer = {0};
    INT8 err = 0;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(sSensor == NULL)
    {
        ubValid = FALSE;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF VALID, PRINT TO UART
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(ubValid)
    {
//      sizeOfbString = sprintf(bString, "\n\rWheelRpm = %.2f Hz \n\r", sSensor->fWheelRpm);
//      Uart.SendDataBuffer(UART5, bString, sizeOfbString);
      buffer.length = sprintf(buffer.buffer, "\n\rWheelRpm = %.2f RPM \n\r", sSensor->fWheelRpm); // UART w/ interrupts
      do
      {
        Uart.PutTxFifoBuffer(UART5, &buffer);
      } while (err < 0);
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN VALIDATION BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return ubValid;
}



/**************************************************************
 * Function name  : PrintTorque
 * Purpose        : Prints the Torque value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintTorque(sSensor_t* sSensor)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//    UINT16 sizeOfbString;
    sUartLineBuffer_t buffer = {0};
    INT8 err = 0;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(sSensor == NULL)
    {
        ubValid = FALSE;
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // IF VALID, PRINT TO UART
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(ubValid)
    {
//      sizeOfbString = sprintf(bString, "\n\rTorque = %.2f Nm \n\r", sSensor->fTorque);
//      Uart.SendDataBuffer(UART5, bString, sizeOfbString);
      buffer.length = sprintf(buffer.buffer, "\n\rTorque = %.2f Nm \n\r", sSensor->fTorque); // UART w/ interrupts
      do
      {
        Uart.PutTxFifoBuffer(UART5, &buffer);
      } while (err < 0);
    }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // RETURN VALIDATION BIT
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    return ubValid;
}


//
///**************************************************************
// * Function name  : PrintTurbineFreq
// * Purpose        : Prints the TurbineFreq value from the data structure to UART5
// * Arguments      : sSensorRawFreq_t* sSensorRawFreq
// * Returns        : 0 on success, -1 on failure.
// *************************************************************/
//UINT8 PrintTurbineFreq(sSensorRawFreq_t* sSensorRawFreq)
//{
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // VARIABLE DECLARATIONS
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // VALIDITY CHECK
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    if(sSensorRawFreq == NULL)
//    {
//        ubValid = FALSE;
//    }
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // IF VALID, PRINT TO UART
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    if(ubValid)
//    {
//      sprintf(bString, "\n\rTurbineFreq = %.2f N \n\r", sSensorRawFreq->fTurbineRpmRaw);
//      Uart.SendDataBuffer(UART5, bString, sizeof(bString));
//    }
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // RETURN VALIDATION BIT
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    return ubValid;
//}



///**************************************************************
// * Function name  : PrintWheelFreq
// * Purpose        : Prints the WheelFreq value from the data structure to UART5
// * Arguments      : sSensorRawFreq_t* sSensorRawFreq
// * Returns        : 0 on success, -1 on failure.
// *************************************************************/
//UINT8 PrintWheelFreq(sSensorRawFreq_t* sSensorRawFreq)
//{
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // VARIABLE DECLARATIONS
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // VALIDITY CHECK
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    if(sSensorRawFreq == NULL)
//    {
//        ubValid = FALSE;
//    }
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // IF VALID, PRINT TO UART
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    if(ubValid)
//    {
//      sprintf(bString, "\n\rWheelFreq = %.2f N \n\r", sSensorRawFreq->fWheelRpmRaw);
//      Uart.SendDataBuffer(UART5, bString, sizeof(bString));
//    }
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // RETURN VALIDATION BIT
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    return ubValid;
//}


//
///**************************************************************
// * Function name  : PrintWindSpeedFreq
// * Purpose        : Prints the WindSpeed raw frequency value from the data structure to UART5
// * Arguments      : sSensorRawFreq_t* sSensorRawFreq
// * Returns        : 0 on success, -1 on failure.
// *************************************************************/
//UINT8 PrintWindSpeedFreq(sSensorRawFreq_t* sSensorRawFreq)
//{
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // VARIABLE DECLARATIONS
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    UINT8 ubValid = TRUE;
//    INT8 bString[100] = {0};
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // VALIDITY CHECK
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    if(sSensorRawFreq == NULL)
//    {
//        ubValid = FALSE;
//    }
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // IF VALID, PRINT TO UART
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    if(ubValid)
//    {
//      sprintf(bString, "\n\rWindSpeedFreq = %.2f N \n\r", sSensorRawFreq->fWindSpeedRaw);
//      Uart.SendDataBuffer(UART5, bString, sizeof(bString));
//    }
//
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  // RETURN VALIDATION BIT
//  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    return ubValid;
//}

