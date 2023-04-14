main: Main.o SevenSegment.o DE1SoCfpga.o
	g++ -g -Wall Main.o SevenSegment.o DE1SoCfpga.o -o main

Main.o: Main.cpp SevenSegment.h DE1SoCfpga.h
	g++ -g -Wall Main.cpp -c

SevenSegment.o: SevenSegment.cpp SevenSegment.h DE1SoCfpga.h
	g++ -g -Wall SevenSegment.cpp -c

DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -g -Wall DE1SoCfpga.cpp -c

clean:
	rm main Main.o SevenSegment.o DE1SoCfpga.o
