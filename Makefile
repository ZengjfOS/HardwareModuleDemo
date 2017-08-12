CC = arm-linux-gnueabihf-g++

all:
	$(CC) src/main.cpp -I ./include -o hardware_test

clean:

