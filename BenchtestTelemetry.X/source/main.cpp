//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : main.c
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the main C file of the template project used by all
//           developpers of Chinook. It uses ChinookLib, which is another
//           repository on Github.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : For ChinookLib to be useable, it must be cloned on your hard
//           drive so the path
//               "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"
//           references an existing file.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#include "..\headers\Interrupts.h"
#include "..\headers\Setup.h"
#include "..\headers\StateMachine.h"
#include "..\headers\HardwareProfile.h"



//==============================================================================
// FUNCTION PROTOTYPES
//==============================================================================


//==============================================================================
// VARIABLE DECLARATIONS
//==============================================================================

//extern volatile INT32 oFlagMainWhile;
//extern volatile INT32 oFlagTenMillis;

//==============================================================================
// MAIN CODE
//==============================================================================
void main(void)
{

//==============================================================================
// Following memcopies are used to be able to use the form 
// Chinook.LibraryX.FunctionX in case the developper wants to see the available
// functions.
//==============================================================================
  memcpy( &Chinook.Port  , &Port  , sizeof ( struct sChinookPort  ) );
  memcpy( &Chinook.Uart  , &Uart  , sizeof ( struct sChinookUart  ) );
  memcpy( &Chinook.Pwm   , &Pwm   , sizeof ( struct sChinookPwm   ) );
  memcpy( &Chinook.Timer , &Timer , sizeof ( struct sChinookTimer ) );
//  memcpy( &Chinook.Wdt   , &Wdt   , sizeof ( struct sChinookWdt   ) );
  memcpy( &Chinook.Adc   , &Adc   , sizeof ( struct sChinookAdc   ) );
  memcpy( &Chinook.Can   , &Can   , sizeof ( struct sChinookCan   ) );
  memcpy( &Chinook.Spi   , &Spi   , sizeof ( struct sChinookSpi   ) );
  memcpy( &Chinook.I2c   , &I2c   , sizeof ( struct sChinookI2c   ) );
  memcpy( &Chinook.Skadi   , &Skadi   , sizeof ( struct sChinookSkadi   ) );
  memcpy( &Chinook.InputCapture , &InputCapture , sizeof ( struct sChinookInputCapture ) );
//==============================================================================


//==============================================================================
// The next line disables the JTAG for the PIC. If the JTAG is enabled, pins
// RB10-13 can't be used as I/Os. If you want to use the JTAG, comment or
// remove this line.
//==============================================================================
  DDPCONbits.JTAGEN = 0;
//==============================================================================

// State machine init
	pState = &StateInit;

//  StateInit();
//  UINT8 count = 0;
//
  
	while(1)  //infinite loop
	{   
		// State machine entry & exit point
		//===========================================================
		(*pState)();          // jump to next state
		//===========================================================


//      LED_DEBG0_ON;
//      LED_DEBG3_ON;
//      LED_CAN_ON;
//      LED_ERROR_ON;
//      LED_STATUS_ON;

//      LED_DEBG0_TOGGLE;
//      LED_DEBG3_TOGGLE;
//      LED_CAN_TOGGLE;
//      LED_ERROR_TOGGLE;
//      LED_STATUS_TOGGLE;

//      LED_DEBG0_OFF;
//      LED_DEBG3_OFF;
//      LED_CAN_OFF;
//      LED_ERROR_OFF;
//      LED_STATUS_OFF;

    // State scheduler
		//===========================================================
      StateScheduler();   // Decides which state will be next
		//===========================================================
	}
} //END MAIN CODE