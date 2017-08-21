CC = arm-linux-gnueabihf-g++
# CC = g++

OUTPUT = hardware_test

SRC_DIR = $(CURDIR)/src

OBJ = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/i2c_tmp75.c \
	$(SRC_DIR)/input_detect.c \
	$(SRC_DIR)/rtc_detect.c \
	$(SRC_DIR)/uart_us100.c \
	$(SRC_DIR)/usb_udisk_detect.c \
	$(SRC_DIR)/eeprom_detect.c \
	$(SRC_DIR)/lib_json/json_reader.cpp \
	$(SRC_DIR)/lib_json/json_value.cpp \
	$(SRC_DIR)/lib_json/json_writer.cpp \

FLAG = -Wall -g

INCLUDE = $(CURDIR)/include

all:
	make -C unit_test all
	$(CC) $(OBJ) -I $(INCLUDE) -o $(OUTPUT) $(FLAG)

clean:
	rm -rf hardware_test




