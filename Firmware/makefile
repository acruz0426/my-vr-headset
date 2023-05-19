FIRMWARE_NAME=uno-firmware
MMCU_NAME=atmega328p

default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MMCU_NAME) -c -o $(FIRMWARE_NAME).o .$(FIRMWARE_NAME).c
	avr-gcc -o $(FIRMWARE_NAME).bin $(FIRMWARE_NAME).o
	avr-objcopy -O ihex -R .eeprom $(FIRMWARE_NAME).bin $(FIRMWARE_NAME).hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P /dev/ttyACM0 -b 115200 -U flash:w:$(FIRMWARE_NAME).hex
