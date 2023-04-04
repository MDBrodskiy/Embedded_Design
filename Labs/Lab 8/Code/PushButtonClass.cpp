/*
 * =====================================================================================
 *
 *       Filename:  PushButtonClass.cpp
 *
 *    Description:  Interfaces with switches and push-buttons on the De1-SoC board using
 *                  class De1-SoC
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
#include <cmath>
#include <unistd.h>

using namespace std;

class DE1SoCfpga {

private:
    
    char *pBase;
    int fd;
    
public:
    

    /**
    * Initialize general-purpose I/O
    * - Opens access to physical memory /dev/mem
    * - Maps memory into virtual address space
    *
    * @return Address to virtual memory which is mapped to physical,
    * or MAP_FAILED on error.
    */
    DE1SoCfpga() {
        
        // Open /dev/mem to give access to physical addresses
        fd = open( "/dev/mem", (O_RDWR | O_SYNC));
        if (fd == -1) // check for errors in openning /dev/mem
        {
            cout << "ERROR: could not open /dev/mem..." << endl;
            exit(1);
        }
        // Get a mapping from physical addresses to virtual addresses
        char *virtual_base = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
        if (virtual_base == MAP_FAILED) // check for errors
        {
            cout << "ERROR: mmap() failed..." << endl;
            close (fd); // close memory before exiting
            exit(1); // Returns 1 to the operating system;
        }
        pBase = virtual_base;
    
    }
    

    /**
    * Close general-purpose I/O.
    *
    * @param pBase Virtual address where I/O was mapped.
    * @param fd File descriptor previously returned by 'open'.
    */
    ~DE1SoCfpga() {
        
        if (munmap (pBase, LW_BRIDGE_SPAN) != 0) {

            cout << "ERROR: munmap() failed..." << endl;
            exit(1);

        }

        close (fd); // close memory
    
    }
    
    /**
    * Write a 4-byte value at the specified general-purpose I/O location.
    *
    * @parem offset Offset where device is mapped.
    * @param value Value to be written.
    */
    void RegisterWrite(unsigned int offset, int value) {

        * (volatile unsigned int *)(pBase + offset) = value;
    
    }
    
    /**
    * Read a 4-byte value from the specified general-purpose I/O location.
    *
    * @param offset Offset where device is mapped.
    * @return Value read.
    */
    int RegisterRead(unsigned int offset) {

        return * (volatile unsigned int *)(pBase + offset);
    
    }

};

class LEDControl {

private:

    DE1SoCfpga *board; // Declare a DE1SoCfpga class
    bool prevVal[4]; // Store previous button values globally
    bool butValue[4]; // Store current button values globally

    // Physical base address of FPGA Devices
    const unsigned int LW_BRIDGE_BASE = 0xFF200000; // Base offset

    // Length of memory-mapped IO window
    const unsigned int LW_BRIDGE_SPAN = 0x00005000; // Address map size

    // Cyclone V FPGA device addresses
    const unsigned int LEDR_BASE = 0x00000000; // Leds offset
    const unsigned int SW_BASE = 0x00000040; // Switches offset
    const unsigned int KEY_BASE = 0x00000050; // Push buttons offset

public:

    // Initialize the LEDControl class
    LEDControl() {

        board = new DE1SoCfpga();
        for (int i = 0; i < 4; i++) {

            prevVal[i] = false;
            butValue[i] = false;

        }

    }

    // Destroy the board and LEDControl objects
    ~LEDControl() {

        delete board;

    }

    /**Reads the value of a switch
    * -Uses base address of I/O
    * @param switchNum Switch number (0 to 9)
    * @return Switch value read
    */
    int Read1Switch(int switchNum) {

        // Read the switch register
        int switchRegisterValue = board->RegisterRead(SW_BASE);
    
        // Mask the value to extract the specified switch bit
        int switchBitMask = 1 << switchNum;

        // if the result is non-zero, then the switch is on, off otherwise
        int switchValue;
        //use the bitwise AND operator and compare result against the bit mask
        if (switchRegisterValue & switchBitMask) {
            switchValue = 1;
        } else {
            switchValue = 0;
        }

        return switchValue;

    }

    /** Changes the state of an LED (ON or OFF)
    *  @param ledNum LED number (0 to 9)
    *  @param state State to change to (ON or OFF)
    */
    void Write1Led(int ledNum, int state) {

        if (ledNum < 0 || ledNum > 9) {
            cout << "ERROR: Invalid LED number. Only LED numbers 0 to 9 are valid." << endl;
            return;

        }
    
        // Read the LED register
        int ledRegisterValue = board->RegisterRead(LEDR_BASE);

        // Set the state of the specified LED based on the state parameter
        if (state == 1) {
            ledRegisterValue = (1 << ledNum);
        } else {
            ledRegisterValue &= ~(1 << ledNum);
        }

        // Write the new LED register value
        board->RegisterWrite(LEDR_BASE, ledRegisterValue);

        // Read the LED register again and print out the value to double check (this can be commented out)
        int UpdatedRegisterValue = board->RegisterRead(LEDR_BASE);
        cout << "LED Register Updated Value: " << UpdatedRegisterValue << endl << endl;

    }

    /** Reads all the switches and returns their value in a single integer
    * @return 	A value that represents the value of the switches
    */
    int ReadAllSwitches() {

        return board->RegisterRead(SW_BASE);

    }

    /** Set the state of the LEDs with the given value
    * @param value	Value between 0 and 1023 written to the LEDs
    */
    void WriteAllLeds(int value) {

        board->RegisterWrite(LEDR_BASE, value);
    
    }

    int PushButtonGet() {

        // Read the switch register
        int butRegisterValue = board->RegisterRead(KEY_BASE);
    
        // Mask the value to extract the specified switch bit
        int butBitMask[4];
        for (int i = 0; i < 4; i++) {

            butBitMask[i] = 1 << i;

        }

        // if the result is non-zero, then the switch is on, off otherwise
        //use the bitwise AND operator and compare result against the bit mask
        for (int i = 0; i < 4; i++) {

            if (butRegisterValue & butBitMask[i]) {

                butValue[i] = true;
	        if (butValue[i] != prevVal[i]) { prevVal[i] = !prevVal[i]; }

            } else {

                butValue[i] = false;
	        if (butValue[i] != prevVal[i]) { prevVal[i] = !prevVal[i]; }

            }
        }

        int quantDiff = 0;
        bool diff[] = {false, false, false, false};

        for (int i = 0; i < 4; i++) {

	        if (butValue[i] && prevVal[i]) {

	            diff[i] = true;
	            quantDiff++;

	        }

        }

        if (quantDiff == 2) return 4;
        else if (quantDiff == 0) return -1;
        else {

	        for (int i = 0; i < 4; i ++) {
    
	            if (diff[i]) return i;

	        }

        }

    }

};

int main() {

    int ledDisp = 0;
    LEDControl *control = new LEDControl();
    // ************** Put your code here **********************
    while(true) {

	    usleep(225000);
	    int change = control->PushButtonGet();
	    if (change == 0) {

	        ledDisp++;
	        control->WriteAllLeds(ledDisp);
	        if (ledDisp > 1023) ledDisp = 0;

	    } else if (change == 1) {

	        ledDisp -= 1;
	        control->WriteAllLeds(ledDisp);
	        if (ledDisp < 0) ledDisp = 1023;

	    } else if (change == 2) {

	        ledDisp *= 2;
	        if (ledDisp > 1023) ledDisp -= 1024;
	        control->WriteAllLeds(ledDisp);

	    } else if (change == 3) {

	        ledDisp /= 2;
	        control->WriteAllLeds(ledDisp);

	    } else if (change == 4) {

	        control->WriteAllLeds(control->ReadAllSwitches());
	        ledDisp = control->ReadAllSwitches();

	    }

    }
    // Done
    delete control;

}
