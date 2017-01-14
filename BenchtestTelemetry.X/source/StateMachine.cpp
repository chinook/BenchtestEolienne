//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : StateMachine.c
// Author  : Mikael Ducharme
// Date    : 2015-02-25
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the C file for the state machine of the system.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : State names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\StateMachine.h"
#include "..\headers\DataAcq.h"
#include "..\headers\Ds1338.h"
#include "..\headers\Interrupts.h"
#include "..\headers\SkadiFunctions.h"

//==============================================================================
// VARIABLE DECLARATIONS
//==============================================================================
extern volatile sSensor_t sSensor;
extern volatile sSensorRawFreq_t sSensorRawFreq;
extern volatile ds1338_s ds1338;

float sensTelPacket[14] = {0};
float packetHeader = -898989.0f; //0xC95B7AD0
float packetFooter = -909090.0f; //0xC95DF220

UINT16 countTo50Ms  = 0;
UINT16 countTo1S    = 0;
UINT16 countTo1Ms   = 0;
UINT16 countTo100Ms = 0;
UINT32 dataId    = 0;
UINT8  samplesCount = 0;
float temp = 0.0f;

extern volatile BOOL oCapture5;
extern volatile BOOL oCapture4;
extern volatile BOOL oCapture3;

extern volatile BOOL oNewCanGear;
extern volatile BOOL oNewCanPitch;
extern volatile BOOL oNewCanBatteryVoltage;
extern volatile BOOL oNewCanBatteryCurrent;

extern volatile BOOL oNewAdcAvailable;

BOOL oStartTelemetry = FALSE;
UINT32 startTelemetryMessage = 0xDEADBEEF;

//==============================================================================
//	STATES OF STATE MACHINE
//==============================================================================

//===============================================================
// Name     : StateScheduler
// Purpose  : Decides which state is next depending on current
//            state and flags. Used as a function
//===============================================================
void StateScheduler(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state = StateInit
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if (pState == &StateInit)
  {
    if (INIT_2_DATAACQ)
    {
      pState = &StateDataAcq;  // Transition to DataAcq
    }
    else if(INIT_2_INITRTC)
    {
      pState = &StateInitRtc; // Transition to InitRtc
    }
    else
    {
      pState = &StateInit; // Stay on current state
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state = StateInitRtc
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if (pState == &StateInitRtc)
  {
    if (INIT_2_DATAACQ)
    {
      pState = &StateDataAcq;  // Transition to Data Acq
    }
    else
    {
       pState = &StateInitRtc; // Stay on current state
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state = StateDataAcq
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateDataAcq)
  {
    if (DATAACQ_2_DATAAVG)
    {
      pState = &StateDataAvg;  // Transition to DataOutput
    }
    else
    {
      pState = &StateDataAcq;  //Stay on current state
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state = StateDataAvg
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateDataAvg)
  {
    if (DATAAVG_2_DATAOUTPUT)
    {
      pState = &StateDataOutput;  // Transition to DataOutput
    }
    else
    {
      pState = &StateDataAvg;  //Stay on current state
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state = StateDataOutput
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateDataOutput)
  {
    if (DATAOUTPUT_2_DATAACQ)
    {
      pState = &StateDataAcq;  // Transition to DataAcq
    }
    else
    {
      pState = &StateDataOutput;  // Stay on current state
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state = undetermined
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else
  {
    pState = &StateInit;   // Go to Init state by default
  }
  /*
   * DEVELOPPER CODE HERE
   */

}

//===============================================================
// Name     : StateInit
// Purpose  : Initialization of the system.
//===============================================================
void StateInit(void)
{

  INTDisableInterrupts();   // Disable all interrupts of the system.

  INIT_PORTS;
//  INIT_SPI;
//  INIT_WDT;
  INIT_TIMER;
  INIT_INPUT_CAPTURE;
//  INIT_PWM;
  INIT_ADC;
  INIT_UART;
  INIT_SKADI;
  INIT_CAN;
  INIT_I2C;
  START_INTERRUPTS;

  SEND_BOARD_ID;  // Send board ID via CAN BUS to backplane

  DataStructInit((sSensor_t *) &sSensor);

  initFlag = 1;
}

//===============================================================
// Name     : StateInitRtc
// Purpose  : Initializes the RTC values to 0:0:0 0;0;0.
//===============================================================
void StateInitRtc(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // FIRST PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  ds1338_init((ds1338_s *) &ds1338);
  ds1338_EnableOscOutput((ds1338_s *) &ds1338,FREQ_32_768KHZ);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // SECOND PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

}

//===============================================================
// Name     : StateDataAcq
// Purpose  : Data acquisition state, puts all the current values
//            in the structure
//===============================================================
void StateDataAcq(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // FIRST PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if(oNewAdcAvailable)
  {
    GetWindDirection((sSensor_t *) &sSensor);
    GetTorque((sSensor_t *) &sSensor);
    GetThrust((sSensor_t *) &sSensor);
    oNewAdcAvailable = 0;
  }

  if(oNewCanGear)
  {
    GetCanGear((sSensor_t *) &sSensor);
    oNewCanGear = 0;
  }

  if(oNewCanPitch)
  {
    GetCanPitch((sSensor_t *) &sSensor);
    oNewCanPitch = 0;
  }
  if(oNewCanBatteryVoltage)
  {
    GetCanBatteryVoltage((sSensor_t *) &sSensor);
    oNewCanBatteryVoltage = 0;
  }
  if(oNewCanBatteryCurrent)
  {
    GetCanBatteryCurrent((sSensor_t *) &sSensor);
    oNewCanBatteryCurrent = 0;
  }

  if(oCapture5)
  {
    GetWindSpeed((sSensor_t *) &sSensor);
    oCapture5 = 0;
  }

  if(oCapture4)
  {
    GetTurbineRpm((sSensor_t *) &sSensor);
    oCapture4 = 0;
//    LED_DEBG0_TOGGLE;
//    LED_DEBG3_TOGGLE;
//    LED_CAN_TOGGLE;
//    LED_ERROR_TOGGLE;
//    LED_STATUS_TOGGLE;
  }

  if(oCapture3)
  {
    oCapture3 = 0;
    GetWheelRpm((sSensor_t *) &sSensor);
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // SECOND PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	sUartLineBuffer_t buffer =
		{ .buffer = {0}
		 ,.length =  0
		};

	if (Uart.Var.oIsRxDataAvailable[UART6])
	{
		Uart.Var.oIsRxDataAvailable[UART6] = 0;
		INT32 messageLength = Uart.GetRxFifoBuffer(UART6, &buffer, FALSE);
		/* analyser buffer*/
		if(buffer.buffer[0] == 'k'){
			Can.SendByte(CAN1,0x42, 8);        
		}
		else if(buffer.buffer[0] == 'l'){
			Can.SendByte(CAN1,0x42, 0);        
		}
		else 
    {
			UINT32 message;
			memcpy(&message, &buffer.buffer[0], 4);
			if(startTelemetryMessage == message) 
      {
        oStartTelemetry = TRUE;
			}
		}
	}
}

//===============================================================
// Name     : StateDataAvg
// Purpose  : Data averaging state, generates a mean value for each
//            and puts it in the structure
//===============================================================
void StateDataAvg(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VALIDITY CHECK
  // Flag is set to 0 and counters are incremented by 1
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  o100UsFlag = 0;
  countTo1Ms++;
  countTo50Ms++;
  countTo100Ms++;
  countTo1S++;
  
//    LED_DEBG0_TOGGLE;
//    LED_DEBG3_TOGGLE;
//    LED_CAN_TOGGLE;
//    LED_ERROR_TOGGLE;
//    LED_STATUS_TOGGLE;

    
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // AVERAGING OF DATA
  // Data is sampled every 1 ms and averaged every 100 ms
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if(countTo1Ms >= ONE_MS)
  {
    samplesCount++;
    
    if(samplesCount <= SAMPLES_PER_AVERAGE)
    {
      sSensor.sumThrust        += sSensor.fThrust;
      sSensor.sumTorque        += sSensor.fTorque;
      sSensor.sumTurbineRpm    += sSensor.fTurbineRpm;
      sSensor.sumWheelRpm      += sSensor.fWheelRpm;
      sSensor.sumWindDirection += sSensor.fWindDirection;
      sSensor.sumWindSpeed     += sSensor.fWindSpeed;

      if(samplesCount == SAMPLES_PER_AVERAGE)
      {
        sSensor.avgThrust        = sSensor.sumThrust / SAMPLES_PER_AVERAGE;
        sSensor.avgTorque        = sSensor.sumTorque / SAMPLES_PER_AVERAGE;
        sSensor.avgTurbineRpm    = sSensor.sumTurbineRpm / SAMPLES_PER_AVERAGE;
        sSensor.avgWheelRpm      = sSensor.sumWheelRpm / SAMPLES_PER_AVERAGE;
        sSensor.avgWindDirection = sSensor.sumWindDirection / SAMPLES_PER_AVERAGE;
        sSensor.avgWindSpeed     = sSensor.sumWindSpeed / SAMPLES_PER_AVERAGE;

        sSensor.sumThrust        = 0.0f;
        sSensor.sumTorque        = 0.0f;
        sSensor.sumTurbineRpm    = 0.0f;
        sSensor.sumWheelRpm      = 0.0f;
        sSensor.sumWindDirection = 0.0f;
        sSensor.sumWindSpeed     = 0.0f;

        samplesCount = 0;
      }
    }
  }

  dataAvgFlag = 1;
}

//===============================================================
// Name     : StateDataOutput
// Purpose  : Outputs the value of the structure to the Xbee, SD
//            Card, CAN, UART
//===============================================================
void StateDataOutput(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  sUartLineBuffer_t buffer = {0};
  INT8 err = 0;

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // FIRST PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//  Skadi.GetCmdMsgFifo();

  if(countTo50Ms >= 499)
  {
    SEND_WIND_SPEED_TO_CAN;
    SEND_WIND_DIRECTION_TO_CAN;
    SEND_TURBINE_RPM_TO_CAN;
//    temp++;
//    Can.SendFloat(CAN1, TURBINE_RPM_ID, temp);
    SEND_WHEEL_RPM_TO_CAN;
    countTo50Ms = 0;
  }

  if(countTo100Ms >= 999)
  {

    LED_DEBG0_TOGGLE;
    
//    buffer.length = sprintf(buffer.buffer,"%u\t%u\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\r"
//                                                        ,dataId++
//                                                        ,sSensor.canGear
//                                                        ,sSensor.avgWindSpeed
//                                                        ,sSensor.avgWindDirection
//                                                        ,0.0f//fujin.fTurbineDir
//                                                        ,sSensor.avgTurbineRpm
//                                                        ,sSensor.avgWheelRpm
//                                                        ,sSensor.canPitch
//                                                        ,sSensor.avgThrust
//                                                        ,sSensor.avgTorque
//                                                        ,sSensor.canBatteryVoltage
//                                                        ,sSensor.canBatteryCurrent);
//    do
//      {
//        Uart.PutTxFifoBuffer(UART6, &buffer);
//      } while (err < 0);
    
    sensTelPacket[0] = packetHeader;
    sensTelPacket[1] = (float)dataId;
    sensTelPacket[2] = (float)sSensor.canGear;
    sensTelPacket[3] = sSensor.avgWindSpeed;
    sensTelPacket[4] = sSensor.avgWindDirection;
    sensTelPacket[5] = 0.0f;//fujin.fTurbineDir
    sensTelPacket[6] = sSensor.avgTurbineRpm;
    sensTelPacket[7] = sSensor.avgWheelRpm;
    sensTelPacket[8] = sSensor.canPitch;
    sensTelPacket[9] = sSensor.avgThrust;
    sensTelPacket[10] = sSensor.avgTorque;
    sensTelPacket[11] = sSensor.canBatteryVoltage;
    sensTelPacket[12] = sSensor.canBatteryCurrent;
    sensTelPacket[13] = packetFooter;
    
    sUartLineBuffer_t buffer = {0};
    buffer.length = 56;
    int j;
    for(j=0; j < 14 ; j++)
    {
      float f = sensTelPacket[j];
      memcpy((void *)&buffer.buffer[j*4], (void *)&f, 4);
    }
    INT32 err = 0;
		
	if (oStartTelemetry)
	{
		do
		{
			err = Uart.PutTxFifoBuffer(UART6, &buffer);
            SDCardUtilities sd = new SDCardUtilities();
            sd.write(buffer.buffer, buffer.length);            
		}
		while ( err < 0);  
    }
    
    dataId++;
    
    
    countTo100Ms = 0;
  }

  if(countTo1S >= 9999 )
  {
//    PrintWindSpeed((sSensor_t *) &sSensor);
//    PrintWindDirection((sSensor_t *) &sSensor);
//    PrintWheelRpm((sSensor_t *) &sSensor);
//    PrintTurbineRpm((sSensor_t *) &sSensor);
//    PrintTorque((sSensor_t *) &sSensor);
//    PrintThrust((sSensor_t *) &sSensor);

    countTo1S = 0;
  }
  
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // SECOND PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  outputFlag = 1;

}
