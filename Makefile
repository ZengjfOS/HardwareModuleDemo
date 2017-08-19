CC = arm-linux-gnueabihf-g++
# CC = g++

OUTPUT = hardware_test

OBJ = \
	src/main.cpp \
	src/i2c_tmp75.c \
	src/input_detect.c \
	src/rtc_detect.c \
	src/uart_us100.c \
	src/usb_udisk_detect.c \
	src/eeprom_detect.c \
	src/lib_json/json_reader.cpp \
	src/lib_json/json_value.cpp \
	src/lib_json/json_writer.cpp \

FLAG = -Wall -g

INCLUDE = include

all:
	$(CC) $(OBJ) -I $(INCLUDE) -o $(OUTPUT) $(FLAG)

clean:
	rm -rf hardware_test

