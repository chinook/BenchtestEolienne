//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : HeaderTemplate.h
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This header file gathers the functions used for Skadi.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : Function names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __SKADI_FUNCTIONS__
#define	__SKADI_FUNCTIONS__

#include "Setup.h"


//==============================================================================
// Public functions prototypes
//==============================================================================

/**************************************************************
 * Function name  : LedDebug
 * Purpose        : Toggle LED_DEBUG.
 * Arguments      : 1.
 * Returns        : None.
 *************************************************************/
void LedDebug();

/**************************************************************
 * Function name  : SetPrint
 * Purpose        : Tells the software to print or not the
 *                  regulation data.
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void SetPrint();

/**************************************************************
 * Function name  : LedStatus
 * Purpose        : Toggle LED_STATUS.
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void LedStatus();

/**************************************************************
 * Function name  : LedError
 * Purpose        : Toggle LED_ERROR.
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void LedError();

/**************************************************************
 * Function name  : LedCan
 * Purpose        : Toggle LED_CAN.
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void LedCan();

/**************************************************************
 * Function name  : ReInitSystem
 * Purpose        : Redo StateInit().
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void ReInitSystem();

/**************************************************************
 * Function name  : SetWind
 * Purpose        : Set the wind angle
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void SetWind();

/**************************************************************
 * Function name  : GetWind
 * Purpose        : Send the wind angle
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void GetWind();

/**************************************************************
 * Function name  : GetMode
 * Purpose        : Send the current mast mode of operation
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void GetMode();

/**************************************************************
 * Function name  : ClearScreen
 * Purpose        : Clear the terminal window
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void ClearScreen();

/**************************************************************
 * Function name  : WriteStatus
 * Purpose        : Write STATUS msg to the drive
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void WriteStatus();

/**************************************************************
 * Function name  : SetCrabManualCmd
 * Purpose        : Set the manual cmd for the crab [angle]
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void SetCrabManualCmd();


#endif	/* __SKADI_FUNCTIONS__ */

