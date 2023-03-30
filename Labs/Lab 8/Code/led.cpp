/*
 * =====================================================================================
 *
 *       Filename:  led.cpp
 *
 *    Description:  Interfaces with switches and push-buttons on the De1-SoC board
 *
 *        Version:  1.0
 *        Created:  03/30/2023
 *       Revision:  none
 *       Compiler:  GCC
 *
 *        Authors:  Michael Brodskiy (Brodskiy.M@Northeastern.edu)
 *                  Dylan Powers (Powers.D@Northeastern.edu)
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;

// Physical base address of FPGA Devices
const unsigned int LW_BRIDGE_BASE = 0xFF200000; // Base offset

// Length of memory-mapped IO window
const unsigned int LW_BRIDGE_SPAN = 0x00005000; // Address map size

// Cyclone V FPGA device addresses
const unsigned int LEDR_BASE = 0x00000000; // Leds offset
const unsigned int SW_BASE = 0x00000040; // Switches offset
const unsigned int KEY_BASE = 0x00000050; // Push buttons offset

/**
* Write a 4-byte value at the specified general-purpose I/O location.
*
* @param pBase Base address returned by 'mmap'.
* @parem offset Offset where device is mapped.
* @param value Value to be written.
*/
void RegisterWrite(char *pBase, unsigned int reg_offset, int value) {

    * (volatile unsigned int *)(pBase + reg_offset) = value;
    
}

/**
* Read a 4-byte value from the specified general-purpose I/O location.
*
* @param pBase Base address returned by 'mmap'.
* @param offset Offset where device is mapped.
* @return Value read.
*/
int RegisterRead(char *pBase, unsigned int reg_offset) {

    return * (volatile unsigned int *)(pBase + reg_offset);

}
/**
* Initialize general-purpose I/O
* - Opens access to physical memory /dev/mem
* - Maps memory into virtual address space
*
* @param fd File descriptor passed by reference, where the result
* of function 'open' will be stored.
* @return Address to virtual memory which is mapped to physical,
* or MAP_FAILED on error.
*/

char *Initialize(int *fd) {

    // Open /dev/mem to give access to physical addresses
    *fd = open( "/dev/mem", (O_RDWR | O_SYNC));
    if (*fd == -1) // check for errors in openning /dev/mem
    {
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
    }
    // Get a mapping from physical addresses to virtual addresses
    char *virtual_base = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, *fd, LW_BRIDGE_BASE);
    if (virtual_base == MAP_FAILED) // check for errors
    {
        cout << "ERROR: mmap() failed..." << endl;
        close (*fd); // close memory before exiting
        exit(1); // Returns 1 to the operating system;
    }
    return virtual_base;
}

/**
* Close general-purpose I/O.
*
* @param pBase Virtual address where I/O was mapped.
* @param fd File descriptor previously returned by 'open'.
*/

void Finalize(char *pBase, int fd) {

    if (munmap (pBase, LW_BRIDGE_SPAN) != 0) {

        cout << "ERROR: munmap() failed..." << endl;
        exit(1);

    }

    close (fd); // close memory
}

/**Reads the value of a switch
 * -Uses base address of I/O
 * @param pBaseBase address returned by'mmap'
 * @param switchNumSwitch number (0 to 9)
 * @returnSwitch value read
 */
int Read1Switch(char * pBase, int switchNum) {

    // Read the switch register
    int switchRegisterValue = RegisterRead(pBase, SW_BASE);
    
    // Mask the value to extract the specified switch bit
    int switchBitMask = 1 << switchNum;

    // if the result is non-zero, then the switch is on, off otherwise
    int switchValue;
    //use the bitwise AND operator and compare result against the bit mask
    if (switchRegisterValue & switchBitMask == switchBitMask) {
        switchValue = 1;
    } else {
        switchValue = 0;
    }

    return switchValue;

}

/** Changes the state of an LED (ON or OFF)
 *  @param pBase Base address returned by 'mmap'
 *  @param ledNum LED number (0 to 9)
 *  @param state State to change to (ON or OFF)
 */
void Write1Led(char *pBase,int ledNum, int state) {

    if (ledNum < 0 || ledNum > 9) {
        cout << "ERROR: Invalid LED number. Only LED numbers 0 to 9 are valid." << endl;
        return;

    }
    
    // Read the LED redister
    int ledRegisterValue = RegisterRead(pBase, LEDR_BASE);

    // Set the state of the specified LED based on the state parameter
    if (state == 1) {
        ledRegisterValue = (1 << ledNum);
    } else {
        ledRegisterValue &= ~(1 << ledNum);
    }

    // Write the new LED register value
    RegisterWrite(pBase, LEDR_BASE, ledRegisterValue);

    // Read the LED register again and print out the value to double check (this can be commented out)
    int UpdatedRegisterValue = RegisterRead(pBase, LEDR_BASE);
    cout << "LED Register Updated Value: " << UpdatedRegisterValue << endl << endl;

}

int main() {

    // Initialize
    int fd;
    char *pBase = Initialize(&fd);
    // ************** Put your code here **********************
    // Done
    Finalize(pBase, fd);

}