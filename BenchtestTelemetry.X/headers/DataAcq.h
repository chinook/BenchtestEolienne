//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : DataAcq.h
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


#ifndef DATA_ACQ_H
#define	DATA_ACQ_H

#include "Setup.h"

//==============================================================================
// Macro definitions
//==============================================================================

#define WIND_DIR_GAIN 0.50704225f     // obtained from max and min bit values
#define WIND_DIR_OFFSET -65.915493f   // obtained from max and min bit values

#define HZ_TO_MPH_WIND_SPEED 0.31f               // Inspeed Specs
#define MPH_TO_MPS_WIND_SPEED 0.44704f           // Conversion from MPH to M/S

#define HZ_TO_RPM_FUTEK_ENCODER 0.166666667f  //60Hz per rotation / 360 pulses per rotation

#define HZ_TO_RPM_SKF_ENCODER   1.25f         //60Hz per rotation / 48 pulses per rotation

#define TORQUE_METER_GAIN     0.1953125f    // obtained from max and min bit values
#define TORQUE_METER_OFFSET   -100.78125f   // Obtained from max and min bit values
                                            // 4    bits   |   -100.00  Nm
                                            // 516  bits   |   ±000.00  Nm
                                            // 1023 bits   |   +099.02  Nm
#define LBS_TO_NEWTON   4.448221628f  // Conversion from lbs to Newton
#define THRUST_GAIN     -0.2834792f   // Obtained from 0 lbs to 120 lbs bit values
#define THRUST_OFFSET   237.3871093f  // Obtained from 0 lbs to 120 lbs bit values
                                      //  838 bits    |    0   lbs
                                      //  696 bits    |    40  lbs
                                      //  554 bits    |    80  lbs
                                      //  415 bits    |    120 lbs
#define THRUST_PRELOAD  -320.0f          // needs to be set each time the load cell is installed


//==============================================================================
// Variable declarations
//==============================================================================

/***********************************
 * Template structure
 **********************************/



/***********************************
 * Global struct
 **********************************/
/*General structure to stock sensor values*/
typedef struct Sensor
{
    // Instant values
    float fThrust;
    float fWindDirection;
    float fWindSpeed;
    float fTurbineRpm;
    float fWheelRpm;
    float fTorque;

    // Sum of Instant values for averaging
    float sumThrust;
    float sumWindDirection;
    float sumWindSpeed;
    float sumTurbineRpm;
    float sumWheelRpm;
    float sumTorque;

    // Summed values divided by number of samples
    float avgThrust;
    float avgWindDirection;
    float avgWindSpeed;
    float avgTurbineRpm;
    float avgWheelRpm;
    float avgTorque;

    // Can values
    UINT8 canGear;
    float canTurbineDirection;
    float canPitch;
    float canBatteryVoltage;
    float canBatteryCurrent;

    // ID for data packets
    UINT32 dataId;



}sSensor_t;

typedef struct SensorRawFreq
{
    float fWheelRpmRaw;
    float fTurbineRpmRaw;
    float fWindSpeedRaw;
}sSensorRawFreq_t;

//==============================================================================
// Public functions prototypes
//==============================================================================

/**************************************************************
 * Function name  : DataStructInit
 * Purpose        : Initializes the data structure with 0s
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 DataStructInit(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetThrust
 * Purpose        : Gets the Thrust value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetThrust(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetWindDirection
 * Purpose        : Gets the WindDirection value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetWindDirection(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetWindSpeed
 * Purpose        : Gets the WindSpeed value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetWindSpeed(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetTurbineRpm
 * Purpose        : Gets the TurbineRpm value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetTurbineRpm(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetWheelRpm
 * Purpose        : Gets the WheelRpm value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetWheelRpm(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetTorque
 * Purpose        : Gets the Torque value and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetTorque(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetCanGear
 * Purpose        : Gets the gear value from CAN bus and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetCanGear(sSensor_t* sSensor);

/**************************************************************
 * Function name  : GetCanPitch
 * Purpose        : Gets the pitch value from CAN bus and stores it in data structure
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
INT8 GetCanPitch(sSensor_t* sSensor);



/**************************************************************
 * Function name  : PrintThrust
 * Purpose        : Prints the Thrust value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintThrust(sSensor_t* sSensor);

/**************************************************************
 * Function name  : PrintWindDirection
 * Purpose        : Prints the WindDirection value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWindDirection(sSensor_t* sSensor);

/**************************************************************
 * Function name  : PrintWindSpeed
 * Purpose        : Prints the WindSpeed value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWindSpeed(sSensor_t* sSensor);

/**************************************************************
 * Function name  : PrintTurbineRpm
 * Purpose        : Prints the TurbineRpm value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintTurbineRpm(sSensor_t* sSensor);

/**************************************************************
 * Function name  : PrintWheelRpm
 * Purpose        : Prints the WheelRpm value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWheelRpm(sSensor_t* sSensor);

/**************************************************************
 * Function name  : PrintTorque
 * Purpose        : Prints the Torque value from the data structure to UART5
 * Arguments      : sSensor_t* sSensor
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintTorque(sSensor_t* sSensor);

/**************************************************************
 * Function name  : PrintTurbineFreq
 * Purpose        : Prints the TurbineFreq value from the data structure to UART5
 * Arguments      : sSensorRawFreq_t* sSensorRawFreq
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintTurbineFreq(sSensorRawFreq_t* sSensorRawFreq);

/**************************************************************
 * Function name  : PrintWheelFreq
 * Purpose        : Prints the WheelFreq value from the data structure to UART5
 * Arguments      : sSensorRawFreq_t* sSensorRawFreq
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWheelFreq(sSensorRawFreq_t* sSensorRawFreq);

/**************************************************************
 * Function name  : PrintWindSpeedFreq
 * Purpose        : Prints the WindSpeed raw frequency value from the data structure to UART5
 * Arguments      : sSensorRawFreq_t* sSensorRawFreq
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
UINT8 PrintWindSpeedFreq(sSensorRawFreq_t* sSensorRawFreq);




#endif	/* DATA_ACQ_H */

