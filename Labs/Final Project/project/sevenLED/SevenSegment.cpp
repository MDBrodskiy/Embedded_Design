/*
 * =====================================================================================
 *
 *       Filename:  SevenSegment.cpp
 *
 *    Description:  Function definition file for the SevenSegment class
 *
 *        Version:  1.0
 *        Created:  04/06/2023
 *       Revision:  none
 *       Compiler:  GCC
 *
 *         Author:  Michael Brodskiy (Brodskiy.M@Northeastern.edu)
 *                  Dylan Powers (Powers.D@Northeastern.edu)
 *
 * =====================================================================================
 */

#include "SevenSegment.h"

SevenSegment::SevenSegment() {

    reg0_hexValue = RegisterRead(HEX3_HEX0_BASE);
    reg1_hexValue = RegisterRead(HEX5_HEX4_BASE);

}

SevenSegment::~SevenSegment() {

    Hex_ClearAll();

}

void SevenSegment::Hex_ClearAll() {

    RegisterWrite(HEX3_HEX0_BASE, 0);
    RegisterWrite(HEX5_HEX4_BASE, 0);

}

void SevenSegment::Hex_ClearSpecific(int index) {

    unsigned int mask;

    if (index < 4) {

        mask = 0xFF << (8 * index);
        RegisterWrite(HEX3_HEX0_BASE, (reg0_hexValue & ~mask))

    } else if (index < 6) {

        mask = 0xFF << (8 * (index - 4));
        RegisterWrite(HEX5_HEX4_BASE, (reg1_hexValue & ~mask))

    } else {

        cout << "Not a valid index value." << endl;

    }

}

void SevenSegment::Hex_WriteSpecific(int display_id, int value) {

    if (index < 4) {

        mask = ~bit_values[value] << (8 * display_id);
        RegisterWrite(HEX3_HEX0_BASE, (reg0_hexValue & ~mask));

    } else if (index < 6) {

        mask = ~bit_values[value] << (8 * (display_id - 4));
        RegisterWrite(HEX5_HEX4_BASE, (reg1_hexValue & ~mask));

    } else {

        cout << "Not a valid index value." << endl;

    }

}

void SevenSegment::Hex_WriteNumber(int number) {



}
