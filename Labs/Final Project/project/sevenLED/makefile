main: Main.o LEDControl.o SevenSegment.o DE1SoCfpga.o
	g++ -g -Wall Main.o LEDControl.o SevenSegment.o DE1SoCfpga.o -o main

Main.o: Main.cpp LEDControl.h SevenSegment.h DE1SoCfpga.h
	g++ -g -Wall Main.cpp -c

LEDControl.o: LEDControl.cpp LEDControl.h DE1SoCfpga.h
	g++ -g -Wall LEDControl.cpp -c

SevenSegment.o: SevenSegment.cpp SevenSegment.h DE1SoCfpga.h
	g++ -g -Wall SevenSegment.cpp -c

DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -g -Wall DE1SoCfpga.cpp -c

clean:
	rm main Main.o LEDControl.o SevenSegment.o DE1SoCfpga.o
