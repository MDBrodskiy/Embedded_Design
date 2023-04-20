/*
 * =======================================================
 *
 *       Filename:  LEDControl.h
 *
 *    Description:  Header file for the LEDControl class
 *
 *        Version:  1.0
 *        Created:  04/13/2023
 *       Revision:  none
 *       Compiler:  GCC
 *
 *         Author:  Michael Brodskiy (Brodskiy.M@Northeastern.edu)
 *                  Dylan Powers (Powers.D@Northeastern.edu)
 *
 * =======================================================
 */

#include "DE1SoCfpga.h"

class LEDControl : public DE1SoCfpga {

    private:

	unsigned int leds_regValue;

    public:

	LEDControl();
	~LEDControl();
	int Read1Switch(int switchNum);
	void Write1Led(int ledNum, int state);
	int ReadAllSwitches();
	void WriteAllLeds(int value);
	int PushButtonGet();

};
