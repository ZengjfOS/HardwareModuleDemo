# CC = arm-linux-gnueabihf-g++
# CC = g++
CC=/home/aplex/zengjf/zengjfos/buildroot-2017.02.3/output/host/usr/bin/arm-linux-g++

OUTPUT_DIR = $(CURDIR)/bin

NAME = hardware_test
SHARE_LIB = lib$(NAME).so
SHARE_LIB_PATH = $(OUTPUT_DIR)/lib

SRC_DIR = $(CURDIR)/../src

OBJ = \
	$(SRC_DIR)/i2c_tmp75.c \
	$(SRC_DIR)/input_detect.c \
	$(SRC_DIR)/rtc_detect.c \
	$(SRC_DIR)/uart_us100.c \
	$(SRC_DIR)/usb_udisk_detect.c \
	$(SRC_DIR)/eeprom_detect.c \
	$(SRC_DIR)/lib_json/json_reader.cpp \
	$(SRC_DIR)/lib_json/json_value.cpp \
	$(SRC_DIR)/lib_json/json_writer.cpp \

INCLUDE = $(CURDIR)/../include

SHARE_LIB_FLAG = -Wall -g -I$(INCLUDE)
FLAG = -Wall -g -L$(SHARE_LIB_PATH) -l$(NAME) -I$(INCLUDE)

all:
	if [ -d SHARE_LIB_PATH ];then \
		mkdir $(SHARE_LIB_PATH); \
	fi

	$(CC) -shared -fPIC -o $(SHARE_LIB_PATH)/$(SHARE_LIB) $(OBJ) $(SHARE_LIB_FLAG)

	$(CC) eeprom_detect.c -o $(OUTPUT_DIR)/eeprom $(FLAG)
	$(CC) i2c_tmp75.c -o $(OUTPUT_DIR)/tmp75 $(FLAG)
	$(CC) rtc_detect.c -o $(OUTPUT_DIR)/rtc $(FLAG)
	$(CC) uart_us100.c -o $(OUTPUT_DIR)/us100 $(FLAG)
	$(CC) usb_udisk_detect.c -o $(OUTPUT_DIR)/udisk $(FLAG)
	$(CC) input_detect.c -o $(OUTPUT_DIR)/input $(FLAG)
	$(CC) gpio_detect.c -o $(OUTPUT_DIR)/gpio ../src/gpio.cpp -Wall -g -I$(INCLUDE)
	$(CC) buzzer.c -o $(OUTPUT_DIR)/buzzer 

