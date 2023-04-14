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
        RegisterWrite(HEX3_HEX0_BASE, (RegisterRead(HEX3_HEX0_BASE) & ~mask));

    } else if (index < 6) {

        mask = 0xFF << (8 * (index - 4));
        RegisterWrite(HEX5_HEX4_BASE, (RegisterRead(HEX5_HEX4_BASE) & ~mask));

    } else {

        cout << "Not a valid index value." << endl;

    }

}

void SevenSegment::Hex_WriteSpecific(int display_id, int value) {

    unsigned int mask;

    if (display_id < 4) {

	reg0_hexValue &= ~((~bit_values[value]) << (8 * display_id));
	reg0_hexValue |= bit_values[value] << (8 * display_id);
        RegisterWrite(HEX3_HEX0_BASE, reg0_hexValue);

    } else if (display_id < 6) {

	reg1_hexValue &= ~((~bit_values[value]) << (8 * (display_id - 4)));
	reg1_hexValue |= bit_values[value] << (8 * (display_id - 4));
        RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue);

    } else {

        cout << "Not a valid index value." << endl;

    }

}

void SevenSegment::Hex_WriteNumber(int number) {

    int count = 0;
    bool negative = false;

    if (number < 0) {

	number = -1 * number;
	negative = true;
	
    } else if (number == 0) {

	Hex_WriteSpecific(0, 0);

    }

    while (number > 0) {


        Hex_WriteSpecific(count, number % 16);
        number /= 16;

        count++;

    }

    if (negative) { Hex_WriteSpecific(count, 16); }

}
