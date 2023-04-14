#include "SevenSegment.h"
#include "LEDControl.h"

int main() {

    SevenSegment display;
    LEDControl LEDs;
    int ledDisp = LEDs.ReadAllSwitches();
    // ************** Put your code here **********************
    while(true) {

	    usleep(225000);
	    int change = LEDs.PushButtonGet();
	    if (change == 0) {

	        ledDisp++;
	        LEDs.WriteAllLeds(ledDisp);
		display.Hex_WriteNumber(ledDisp);
	        if (ledDisp > 1023) ledDisp = 0;

	    } else if (change == 1) {

	        ledDisp -= 1;
	        LEDs.WriteAllLeds(ledDisp);
		display.Hex_WriteNumber(ledDisp);
	        if (ledDisp < 0) ledDisp = 1023;

	    } else if (change == 2) {

	        ledDisp *= 2;
	        if (ledDisp > 1023) ledDisp -= 1024;
	        LEDs.WriteAllLeds(ledDisp);
		display.Hex_WriteNumber(ledDisp);

	    } else if (change == 3) {

	        ledDisp /= 2;
	        LEDs.WriteAllLeds(ledDisp);
		display.Hex_WriteNumber(ledDisp);

	    } else if (change == 4) {

	        ledDisp = LEDs.ReadAllSwitches();
	        LEDs.WriteAllLeds(ledDisp);
		display.Hex_WriteNumber(ledDisp);

	    }

    }

}
