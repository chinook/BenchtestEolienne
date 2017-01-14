//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : StateFunctions.c
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the C file for the functions of the state machine of
//           the system.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : Function names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\StateFunctions.h"
#include "..\headers\CommandFunctions.h"


//==============================================================================
// Variable declarations
//==============================================================================

// EEPROM register containing mast last orientation
I2cEepromInternalRegister_t eepromFirstRegister =
{
  .index.pageIndex = 0b00010000
 ,.index.byteIndex = 0b000000
};

// All the buttons used. 3 on the steering wheel, 3 on the board
volatile sButtonStates_t buttons =
{
  .chng   .byte = 0
 ,.buttons.byte = 0

 // switches on board are at 1 when not pressed
 ,.buttons.bits.boardSw1 = 1
 ,.buttons.bits.boardSw2 = 1
 ,.buttons.bits.boardSw3 = 1
};

extern volatile BOOL oManualMode
                    ;

extern float crabLeftZeroMm
            ,crabRightZeroMm
            ,leftActPosMm
            ,rightActPosMm
            ;


//==============================================================================
// Buttons functions
//==============================================================================
void AssessButtons (void)
{
    
  // <editor-fold defaultstate="collapsed" desc="Check changes on board">
  // <editor-fold defaultstate="collapsed" desc="Change on SW1 on board">
  if (buttons.buttons.bits.boardSw1 != SW1)
  {
    buttons.buttons.bits.boardSw1    = SW1;
    buttons.chng.bits.boardSw1       =   1;
  }
  // </editor-fold>

  // <editor-fold defaultstate="collapsed" desc="Change on SW2 on board">
  if (buttons.buttons.bits.boardSw2 != SW2)
  {
    buttons.buttons.bits.boardSw2    = SW2;
    buttons.chng.bits.boardSw2       =   1;
  }
  // </editor-fold>

  // <editor-fold defaultstate="collapsed" desc="Change on SW3 on board">
  if (buttons.buttons.bits.boardSw3 != SW3)
  {
    buttons.buttons.bits.boardSw3    = SW3;
    buttons.chng.bits.boardSw3       =   1;
  }
  // </editor-fold>
  // </editor-fold>
     
  // <editor-fold defaultstate="collapsed" desc="Assess changes">
  if (buttons.chng.byte)  // If any change has occured on any button
  {
      
    // <editor-fold defaultstate="collapsed" desc="SW1 on board">
    if (buttons.chng.bits.boardSw1)
    {
      buttons.chng.bits.boardSw1 = 0;

      if (!buttons.buttons.bits.boardSw1)     // If SW1 is pressed
      {
        crabLeftZeroMm = leftActPosMm;
        crabRightZeroMm = rightActPosMm;
        
        WriteActZeros2Eeprom();

        SEND_CALIB_DONE;  // Confirm that the calib is done
      }
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="SW2 on board">
    if (buttons.chng.bits.boardSw2)
    {
      buttons.chng.bits.boardSw2 = 0;
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="SW3 on board">
    if (buttons.chng.bits.boardSw3)
    {
      buttons.chng.bits.boardSw3 = 0;
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="SW1 on steering wheel">
    if (buttons.chng.bits.steerWheelSw1)
    {
      buttons.chng.bits.steerWheelSw1 = 0;
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="SW3 on steering wheel">
    if (buttons.chng.bits.steerWheelSw3)
    {
      buttons.chng.bits.steerWheelSw3 = 0;

//      if (buttons.buttons.bits.steerWheelSw3)     // If SW1 is pressed
//      {
//        crabLeftZeroMm = leftActPosMm;
//        crabRightZeroMm = rightActPosMm;
//
//        SEND_CALIB_DONE;  // Confirm that the calib is done
//      }
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="SW10 on steering wheel">
    if (buttons.chng.bits.steerWheelSw10)
    {
      buttons.chng.bits.steerWheelSw10 = 0;
    }
    // </editor-fold>
  }
  // </editor-fold>
}

INT8 SignFloat (float value)
{
  return (value >= 0) ? 1 : -1;
}

INT8 SignInt (INT32 value)
{
  return (value >= 0) ? 1 : -1;
}

float AbsFloat (float value)
{
  return (value >= 0) ? value : -value;
}

INT32 AbsInt (INT32 value)
{
  return (value >= 0) ? value : -value;
}


/*
 * Read recorded zeros of the actuators. Used at init.
 */
void ReadZerosFromEeprom (void)
{
  UINT8 zeros[8];
  UINT8 slaveAddPlusRegBuf[3];

  slaveAddPlusRegBuf[0] = I2c.Var.eepromAddress.byte;
  slaveAddPlusRegBuf[1] = eepromFirstRegister.address.highByte;
  slaveAddPlusRegBuf[2] = eepromFirstRegister.address.lowByte;

  while(I2c.Var.oI2cWriteIsRunning[I2C4]);  // Wait for any I2C4 write sequence to end
  while(I2c.Var.oI2cReadIsRunning[I2C4]);  // Wait for any I2C4 read sequence to end

  I2c.AddDataToFifoReadQueue(I2C4, &slaveAddPlusRegBuf[0], 3, 8);

  while(I2c.Var.oI2cReadIsRunning[I2C4]); // Wait for the read sequence to end

  I2c.ReadRxFifo(I2C4, &zeros[0], 8);

  memcpy((void *) &crabLeftZeroMm , &zeros[0], 4);
  memcpy((void *) &crabRightZeroMm, &zeros[4], 4);
}


/*
 * Write the zero positions of the actuators to EEPROM
 */
void WriteActZeros2Eeprom (void)
{
  UINT8 dataBuffer[11];
  dataBuffer[0] = I2c.Var.eepromAddress.byte;
  dataBuffer[1] = eepromFirstRegister.address.highByte;
  dataBuffer[2] = eepromFirstRegister.address.lowByte;

  memcpy(&dataBuffer[3], (void *) &crabLeftZeroMm , 4);
  memcpy(&dataBuffer[7], (void *) &crabRightZeroMm, 4);

  while(I2c.Var.oI2cReadIsRunning[I2C4]);  // Wait for any I2C4 read sequence to end
  while(I2c.Var.oI2cWriteIsRunning[I2C4]); // Wait for any I2C4 write sequence to end

  I2c.AddDataToFifoWriteQueue(I2C4, &dataBuffer[0], 11, TRUE);
}