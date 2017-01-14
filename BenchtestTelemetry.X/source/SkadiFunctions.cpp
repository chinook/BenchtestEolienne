//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : SourceTemplate.c
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This C file gathers the functions used for Skadi.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : Function names can and should be renamed by the user to improve the
//           readability of the code. User must set the functions here and adjust
//           the structure skadiCommandTable located in Setup.c.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\SkadiFunctions.h"


//==============================================================================
// Private functions prototypes
//==============================================================================


//==============================================================================
// Variable definitions
//==============================================================================


//==============================================================================
// Functions
//==============================================================================

/**************************************************************
 * Function name  : LedDebug
 * Purpose        : Toggle LedDebug depending on the arguments
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void LedDebug(sSkadi_t *skadi, sSkadiArgs_t args)
{
  UINT8 errorMsg[] = {"Cette led n'existe pas!\r\n"};

  int led = atoi(args.elements[0]);   // Convert argument to int

  if (led == 1)
  {
    Port.B.ToggleBits(BIT_11);
  }
  else if (led == 2)
  {
    Port.B.ToggleBits(BIT_13);
  }
  else if (led == 3)
  {
    Port.B.ToggleBits(BIT_11 | BIT_13);
  }
  else
  {
    Uart.SendDataBuffer(UART5, errorMsg, sizeof(errorMsg));
  }
}


/**************************************************************
 * Function name  : LedCan
 * Purpose        : Toggle LedCan depending on the arguments
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void LedCan(sSkadi_t *skadi, sSkadiArgs_t args)
{
  UINT8 errorMsg[] = {"Cette led n'existe pas!\r\n"};

  int led = atoi(args.elements[0]);   // Convert argument to int

  if (led == 2)
  {
    Port.B.ToggleBits(BIT_15);
  }
  else
  {
    Uart.SendDataBuffer(UART5, errorMsg, sizeof(errorMsg));
  }
}


/**************************************************************
 * Function name  : ReInitSystem
 * Purpose        : Redo StateInit()
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void ReInitSystem(sSkadi_t *skadi, sSkadiArgs_t args)
{
  StateInit();
}
