//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : Interrupts.h
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This file declares all interrupt subroutines used.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : All priorities must be set and verified by the developper. All
//           priorities and subpriorities used are there as example. Also, note
//           that interrupt can be defined as iplnauto, iplnsrs and iplnsoft,
//           where n can be from 0 to 7. 7 is the highest priority, while 1 is
//           the lowest. A priority of 0 will disable the interrupt.
//           Subpriorities can go from (lowest to highest) 0 to 3.
//           SRS mode uses the shadow registers, soft uses the software
//           registers and auto is an automatic assignment.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __INTERRUPT_H__
#define	__INTERRUPT_H__

#include "Setup.h"

//==============================================================================
// DEFINITIONS
//==============================================================================

//===============================================
// Timer interrupts priorities and subpriorities
//===============================================
#define TIMER1_INTERRUPT_PRIORITY       2         // Used in ChinookLib function
#define T1_INTERRUPT_PRIORITY           ipl2auto  // Used in ISR
#define TIMER2_INTERRUPT_PRIORITY       5         // Used in ChinookLib function
#define T2_INTERRUPT_PRIORITY           ipl5auto  // Used in ISR
#define TIMER3_INTERRUPT_PRIORITY       7         // Used in ChinookLib function
#define T3_INTERRUPT_PRIORITY           ipl7auto  // Used in ISR
#define TIMER4_INTERRUPT_PRIORITY       1         // Used in ChinookLib function
#define T4_INTERRUPT_PRIORITY           ipl2auto  // Used in ISR
#define TIMER5_INTERRUPT_PRIORITY       1         // Used in ChinookLib function
#define T5_INTERRUPT_PRIORITY           ipl1auto  // Used in ISR

#define TIMER1_INTERRUPT_SUBPRIORITY    3         // Highest subpriority
#define TIMER2_INTERRUPT_SUBPRIORITY    1
#define TIMER3_INTERRUPT_SUBPRIORITY    3         // Highest subpriority
#define TIMER4_INTERRUPT_SUBPRIORITY    2
#define TIMER5_INTERRUPT_SUBPRIORITY    0         // Lowest subpriority
//===============================================


//===============================================
// UART interrupts priorities and subpriorities
//===============================================
#define UART5_INTERRUPT_PRIORITY        6           // Used in ChinookLib function
#define U5_INTERRUPT_PRIORITY           ipl6auto    // Used in ISR
#define UART6_INTERRUPT_PRIORITY        6           // Used in ChinookLib function
#define U6_INTERRUPT_PRIORITY           ipl6auto    // Used in ISR

#define UART5_INTERRUPT_SUBPRIORITY     1           // Lowest subpriority
#define UART6_INTERRUPT_SUBPRIORITY     2           // Lowest subpriority
//===============================================


//===============================================
// SPI interrupts priorities and subpriorities
//===============================================
#define SPI3_INTERRUPT_PRIORITY         1           // Used in ChinookLib function
#define S3_INTERRUPT_PRIORITY           ipl1auto    // Used in ISR

#define SPI3_INTERRUPT_SUBPRIORITY      3           // Highest subpriority
//===============================================


//===============================================
// ADC interrupts priorities and subpriorities
//===============================================
#define ADC_INTERRUPT_PRIORITY          2           // Used in ChinookLib function
#define ADC_INTERRUPT_PRIO              ipl2auto    // Used in ISR

#define ADC_INTERRUPT_SUBPRIORITY       3           // Highest subpriority
//===============================================


//===============================================
// Input Capture interrupts priorities and subpriorities
//===============================================
#define IC1_INTERRUPT_PRIORITY          4           // Used in ChinookLib function
#define IC1_INT_PRIORITY                ipl4auto    // Used in ISR
#define IC2_INTERRUPT_PRIORITY          4           // Used in ChinookLib function
#define IC2_INT_PRIORITY                ipl4auto    // Used in ISR
#define IC3_INTERRUPT_PRIORITY          3           // Used in ChinookLib function
#define IC3_INT_PRIORITY                ipl3auto    // Used in ISR
#define IC4_INTERRUPT_PRIORITY          5           // Used in ChinookLib function
#define IC4_INT_PRIORITY                ipl5auto    // Used in ISR
#define IC5_INTERRUPT_PRIORITY          4           // Used in ChinookLib function
#define IC5_INT_PRIORITY                ipl4auto    // Used in ISR

#define IC1_INTERRUPT_SUBPRIORITY       3           // Highest subpriority
#define IC2_INTERRUPT_SUBPRIORITY       1
#define IC3_INTERRUPT_SUBPRIORITY       3           // Highest subpriority
#define IC4_INTERRUPT_SUBPRIORITY       0           // Lowest subpriority
#define IC5_INTERRUPT_SUBPRIORITY       1           // Lowest subpriority
//===============================================

//===============================================
// I2C interrupts priorities and subpriorities
//===============================================
#define I2C4_INTERRUPT_PRIORITY          1           // Used in ChinookLib function
#define I2C4_INT_PRIORITY                ipl1auto    // Used in ISR
#define I2C5_INTERRUPT_PRIORITY          6           // Used in ChinookLib function
#define I2C5_INT_PRIORITY                ipl6auto    // Used in ISR

#define I2C4_INTERRUPT_SUBPRIORITY       2
#define I2C5_INTERRUPT_SUBPRIORITY       0
//===============================================

//===============================================
// CAN interrupts priorities and subpriorities
//===============================================
#define CAN1_INTERRUPT_PRIORITY          4
#define CAN1_INT_PRIORITY                ipl4auto    // Used in ISR
#define CAN1_INTERRUPT_SUBPRIORITY       0


#endif	/* __INTERRUPT_H__ */

