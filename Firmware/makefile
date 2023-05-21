FIRMWARE_NAME = uno-firmware
MMCU_NAME = atmega328p
UART_LIB = uart-protocol

MCU = atmega328p

# Compiler and flags
CC = avr-gcc
CFLAGS = -Wall -Os -DF_CPU=16000000UL -mmcu=$(MCU)

# Source files
SRCS = $(FIRMWARE_NAME)/$(FIRMWARE_NAME).c $(FIRMWARE_NAME)/$(UART_LIB).c
OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDES = -I./$(FIRMWARE_NAME)

# Rule to build the object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to build the final firmware
firmware.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(FIRMWARE_NAME)/$@ $^

# Rule to generate the HEX file
firmware.hex: firmware.elf
	avr-objcopy -O ihex -R .eeprom $(FIRMWARE_NAME)/$< $(FIRMWARE_NAME)/$@

# Rule to upload the firmware to Arduino
upload: firmware.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:$(FIRMWARE_NAME)/firmware.hex

# Rule to clean the build files
clean:
	rm -f $(OBJS) firmware.elf firmware.hex

.PHONY: clean
#default:
#	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MMCU_NAME) -c -o $(FIRMWARE_NAME)/$(FIRMWARE_NAME).o $(FIRMWARE_NAME)/$(FIRMWARE_NAME).c
#	avr-gcc -o $(FIRMWARE_NAME)/main.bin $(FIRMWARE_NAME)/$(FIRMWARE_NAME).o
#	avr-objcopy -O ihex -R .eeprom $(FIRMWARE_NAME)/main.bin $(FIRMWARE_NAME)/main.hex
#	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:$(FIRMWARE_NAME)/main.hex

#clean:
#	rm -f $(FIRMWARE_NAME)/main.hex $(FIRMWARE_NAME)/main.elf $(FIRMWARE_NAME)/*.o
