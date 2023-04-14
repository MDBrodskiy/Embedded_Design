/*
 * =====================================================================================
 *
 *       Filename:  LEDControl.cpp
 *
 *    Description:  File containing LED and push button controls
 *
 *        Version:  1.0
 *        Created:  04/13/2023
 *       Revision:  none
 *       Compiler:  GCC
 *
 *         Author:  Michael Brodskiy (Brodskiy.M@Northeastern.edu)
 *                  Dylan Powers (Powers.D@Northeastern.edu)
 *
 * =====================================================================================
 */
 
 #include "LEDControl.h"

bool prevVal[4] = {false, false, false, false};
bool butValue[4] = {false, false, false, false};

LEDControl::LEDControl() {

    leds_regValue = RegisterRead(SW_BASE);

}

// Destroy the board and LEDControl objects
LEDControl::~LEDControl() {

    cout << "Closing LEDs, Switches, & Buttons..." << endl;

}

/**Reads the value of a switch
* -Uses base address of I/O
* @param switchNum Switch number (0 to 9)
* @return Switch value read
*/
int LEDControl::Read1Switch(int switchNum) {

    // Read the switch register
    int switchRegisterValue = RegisterRead(SW_BASE);
    
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
void LEDControl::Write1Led(int ledNum, int state) {

    if (ledNum < 0 || ledNum > 9) {
        cout << "ERROR: Invalid LED number. Only LED numbers 0 to 9 are valid." << endl;
        return;

    }
    
    // Read the LED register
    int ledRegisterValue = RegisterRead(LEDR_BASE);

    // Set the state of the specified LED based on the state parameter
    if (state == 1) {
        ledRegisterValue = (1 << ledNum);
    } else {
        ledRegisterValue &= ~(1 << ledNum);
    }

    // Write the new LED register value
    RegisterWrite(LEDR_BASE, ledRegisterValue);

    // Read the LED register again and print out the value to double check (this can be commented out)
    int UpdatedRegisterValue = RegisterRead(LEDR_BASE);
    cout << "LED Register Updated Value: " << UpdatedRegisterValue << endl << endl;

}

/** Reads all the switches and returns their value in a single integer
* @return value that represents the value of the switches
*/
int LEDControl::ReadAllSwitches() {

    return RegisterRead(SW_BASE);

}

/** Set the state of the LEDs with the given value
* @param value	Value between 0 and 1023 written to the LEDs
*/
void LEDControl::WriteAllLeds(int value) {

    RegisterWrite(LEDR_BASE, value);
    
}

int LEDControl::PushButtonGet() {

    // Read the switch register
    int butRegisterValue = RegisterRead(KEY_BASE);

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

