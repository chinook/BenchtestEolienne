/* 
 * File:   SDCardUtilities.cpp
 * Author: Chinook-Helix
 *
 * Created on 6 janvier 2017, 13:24
 */

#include <cstdlib>
#include <plib.h>
#include <string.h>
#include "headers/SDMMC.h"
using namespace std;
//More info:
//http://hades.mech.northwestern.edu/index.php/PIC32MX:_Interfacing_to_a_Secure_Digital_(SD)_Flash_Card
#define START_ADDRESS       10000
#define N_BLOCKS            10      // number of blocks
#define B_SIZE              512     // sector/data block size



/*
 * 
 */
class SDCardUtilities {
    
    int currentAddress = START_ADDRESS;
    
    char    data[ B_SIZE];
    char  buffer[ B_SIZE];

    
    public:
        
    SDCardUtilities() {
        //initialize what is needed
        initSD();
    }
    bool write(char* buffer, int size) {
        LBA addr = currentAddress;
        int i, j, r;
        
         // 1. initializations
        initSD();		        // init SD/MMC module

        // 2. fill the buffer with pattern
        for( i=0; i<B_SIZE; i++)
            data[i]= i;

        // 3. wait for the card to be inserted
        while( !getCD());       // check CD switch
        Delayms( 100);          // wait contacts de-bounce
        if ( initMedia())       // init card
        {  // if error code returned
            return -1;
        }

        // 4. fill 16 groups of N_BLOCK sectors with data 
        addr = START_ADDRESS;
        for( j=0; j<16; j++)
        {
            for( i=0; i<N_BLOCKS; i++)
            {
                if (!writeSECTOR( addr+i*j, data))
                {  // writing failed
                    return -1;
                }
            } // i
        } // j

        // 5. verify the contents of each sector written  
        addr = START_ADDRESS;
        for( j=0; j<16; j++)
        {
            for( i=0; i<N_BLOCKS; i++)
            {   // read back one block at a time
                if (!readSECTOR( addr+i*j, buffer))
                {   // reading failed
                    return 1;
                }
                // verify each block content
                if ( memcmp( data, buffer, B_SIZE))
                {   // mismatch
                    return 1;
                }
            } // i
        } // j

    // 6. indicate successful execution
    }
    
    /*
** Simple Delay functions
**
** uses:    Timer1
** Notes:   Blocking function
*/

void Delayms( unsigned t)
{
    T1CON = 0x8000;     // enable TMR1, Tpb, 1:1
    while (t--)
    {  // t x 1ms loop
        TMR1 = 0;
        while (TMR1 < 80000000/1000); //this is the clock freq / 1000
    }
} // Delayms

};

