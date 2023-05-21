FIRMWARE_NAME=uno-firmware
MMCU_NAME=atmega328p
UART_LIB=uart-protocol


default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MMCU_NAME) -c -o $(FIRMWARE_NAME)/$(FIRMWARE_NAME).o $(FIRMWARE_NAME)/$(FIRMWARE_NAME).c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MMCU_NAME) -c -o $(FIRMWARE_NAME)/$(UART_LIB).o $(FIRMWARE_NAME)/$(UART_LIB).c
	avr-gcc -o $(FIRMWARE_NAME)/main.elf $(FIRMWARE_NAME)/$(FIRMWARE_NAME).o $(FIRMWARE_NAME)/$(UART_LIB).o
	avr-objcopy -O ihex -R .eeprom $(FIRMWARE_NAME)/main.elf $(FIRMWARE_NAME)/main.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(FIRMWARE_NAME)/main.hex

clean:
	rm -f $(FIRMWARE_NAME)/main.hex $(FIRMWARE_NAME)/main.elf $(FIRMWARE_NAME)/*.o
