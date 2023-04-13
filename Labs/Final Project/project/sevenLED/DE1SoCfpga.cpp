/*
 * ========================================================
 *
 *       Filename:  DE1SoCfpga.cpp
 *
 *    Description:  Contains function definitions for DE1SoCfpga header file
 *
 *        Version:  1.0
 *        Created:  03/30/2023
 *       Revision:  none
 *       Compiler:  GCC
 *
 *        Authors:  Michael Brodskiy (Brodskiy.M@Northeastern.edu)
 *                  Dylan Powers (Powers.D@Northeastern.edu)
 *
 * ========================================================
 */

#include "DE1SoCfpga.h"

    /**
    * Initialize general-purpose I/O
    * - Opens access to physical memory /dev/mem
    * - Maps memory into virtual address space
    *
    * @return Address to virtual memory which is mapped to physical,
    * or MAP_FAILED on error.
    */
DE1SoCfpga::DE1SoCfpga() {
        
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
DE1SoCfpga::~DE1SoCfpga() {
        
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
    void DE1SoCfpga::RegisterWrite(unsigned int offset, int value) {

        * (volatile unsigned int *)(pBase + offset) = value;
    
    }
    
    /**
    * Read a 4-byte value from the specified general-purpose I/O location.
    *
    * @param offset Offset where device is mapped.
    * @return Value read.
    */
    int DE1SoCfpga::RegisterRead(unsigned int offset) {

        return * (volatile unsigned int *)(pBase + offset);
    
    }

