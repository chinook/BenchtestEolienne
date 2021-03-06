//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : StateMachine.h
// Author  : Mikael Ducharme
// Date    : 2015-02-25
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the header file for the state machine of the system.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : State names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef STATE_MACHINE_H
#define	STATE_MACHINE_H

#include "Setup.h"


//==============================================================================
// State Machine public function prototypes
//==============================================================================
void StateInit      (void);   // Initialization state of the system
void StateInitRtc   (void);   // RTC Initialization state of the system
void StateDataAcq   (void);   // State for the acquisition of data, put into processed data structure
void StateDataAvg   (void);    // State for the averaging of data
void StateDataOutput(void);   // State for the output of processed data into SD Card, Xbee and CAN Bus
void StateScheduler (void);   // State Scheduler. Decides which state is next
                              // depending on current state and flags. Used as a function


//==============================================================================
// Macro definitions
//==============================================================================

#define SAMPLES_PER_AVERAGE 100
#define ONE_MS 10   // 10*100us = 1ms (Timer5 is 100us)


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// State scheduler flags
// The state scheduler is at the end of each state and
// decides which state is next. Following flags
// are used in this decision. The names used can and
// should be renamed to improve readability. Also, the
// conditions tested in the defines should be changed
// to proper tests
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define INIT_2_DATAACQ          initFlag    // StateInit/StateInitRtc to State1
#define INIT_2_INITRTC          initRtcFlag // StateInit to StateInitRTC
#define DATAACQ_2_DATAAVG       o100UsFlag  // StateDataAcq to StateDataAvg
#define DATAAVG_2_DATAOUTPUT    dataAvgFlag // StateDataAvg to StateDataOutput
#define DATAOUTPUT_2_DATAACQ    outputFlag  // StateDataOutput to StateDataACQ

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//==============================================================================
// Variable declarations
//==============================================================================
void (*pState)(void);       // State pointer, used to navigate between states
volatile  INT8  initFlag     // Flag indicating if the peripherals' initialization has been completed
               ,initRtcFlag  // Flag indicating if the RTC initialization has been completed
               ,o100UsFlag  // Flag indicating if the raw data acquisition has been completed
               ,dataAvgFlag  // Flag indicating if the averaging of data has been completed
               ,outputFlag   // Flag indicatinf if the processed data has been outputed to SDCARD, CAN BUS, XBEE
               ;

#endif	/* STATE_MACHINE_H */

