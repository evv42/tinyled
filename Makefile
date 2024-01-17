all:
	avr-gcc -mmcu=attiny13a -DF_CPU=800000  \
		-Os -o main.elf -I. *.c
	avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex main.elf main.hex
	minipro -p ATTINY13A -E
	minipro -p ATTINY13A -c config -w fuses.cfg -e
	minipro -p ATTINY13A -e -c code -f ihex -w main.hex
