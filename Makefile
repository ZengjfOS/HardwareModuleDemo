CC = arm-linux-gnueabihf-g++

OUTPUT = hardware_test

OBJ = src/main.cpp \
	src/lib_json/json_reader.cpp \
	src/lib_json/json_value.cpp \
	src/lib_json/json_writer.cpp \

FLAG = -Wall

INCLUDE = include

all:
	$(CC) $(OBJ) -I $(INCLUDE) -o $(OUTPUT) $(FLAG)

clean:
	rm -rf hardware_test

