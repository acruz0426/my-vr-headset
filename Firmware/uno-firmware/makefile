FIRMWARE_NAME = uno-firmware
MMCU_NAME = atmega328p
UART_LIB = uart-protocol
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin
MCU = atmega328p

# Compiler and flags
CC = avr-gcc
CFLAGS = -Wall -Os -DF_CPU=16000000UL -mmcu=$(MCU) -u,vfprintf,

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Include directories
INCLUDES = -I./include

# Rule to create the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to build the final firmware
$(BIN_DIR)/firmware.elf: $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to generate the HEX file
$(BIN_DIR)/firmware.hex: $(BIN_DIR)/firmware.elf
	avr-objcopy -O ihex -R .eeprom $< $@

# Rule to upload the firmware to Arduino
upload: $(BIN_DIR)/firmware.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:$<

# Rule to clean the build files
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY: clean
#default:
#	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MMCU_NAME) -c -o $(FIRMWARE_NAME)/$(FIRMWARE_NAME).o $(FIRMWARE_NAME)/$(FIRMWARE_NAME).c
#	avr-gcc -o $(FIRMWARE_NAME)/main.bin $(FIRMWARE_NAME)/$(FIRMWARE_NAME).o
#	avr-objcopy -O ihex -R .eeprom $(FIRMWARE_NAME)/main.bin $(FIRMWARE_NAME)/main.hex
#	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:$(FIRMWARE_NAME)/main.hex

#clean:
#	rm -f $(FIRMWARE_NAME)/main.hex $(FIRMWARE_NAME)/main.elf $(FIRMWARE_NAME)/*.o
