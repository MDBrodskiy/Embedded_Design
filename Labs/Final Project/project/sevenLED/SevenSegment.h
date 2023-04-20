/*
 * =======================================================
 *
 *       Filename:  SevenSegment.h
 *
 *    Description:  Header file for the SevenSegment class
 *
 *        Version:  1.0
 *        Created:  04/06/2023
 *       Revision:  none
 *       Compiler:  GCC
 *
 *         Author:  Michael Brodskiy (Brodskiy.M@Northeastern.edu)
 *                  Dylan Powers (Powers.D@Northeastern.edu)
 *
 * ======================================================
 */

#include "DE1SoCfpga.h"

const unsigned int bit_values[17] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x40};

class SevenSegment : public DE1SoCfpga {

    private:

        unsigned int reg0_hexValue;
        unsigned int reg1_hexValue;

    public:

        SevenSegment();
        ~SevenSegment();
        void Hex_ClearAll();
        void Hex_ClearSpecific(int index);
        void Hex_WriteSpecific(int display_id, int value);
        void Hex_WriteNumber(int number);

};
