# Makefile for this AVR project

# make code       Compiles the source code
# make fuses      Program fuses
# make program    Program flash and eeprom

# make list       Create generated code listing
# make clean      Delete all generated files

# Programmer hardware settings for avrdude
# AVRDUDE_HW = -c avr910 -P /dev/ttyUSB0 -b 115200
# AVRDUDE_HW = -c arduino -P COM3 -b 57600
AVRDUDE_HW = -c avrispmkII -P usb -B20

# Name of the program without extension
PRG = HelloWorld

# Microcontroller type and clock frequency
MCU = attiny2313
F_CPU = 1000000

# Optional fuse settings, for example
# LFUSE = 0x64
# HFUSE = 0xDF
# EFUSE = 0xFF

# Source files, separated by space.
SRC = driver/serialconsole.c driver/systemtimer.c main.c


###################################################################
# You possibly do not need to change settings below this marker
###################################################################

# Binaries to be used
# You may add the path to them if they are not in the PATH variable.
CC       = avr-gcc
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump
AVRDUDE  = avrdude
AVR_SIZE = avr-size

# Do we need to write Eeprom? (yes/no)
EEPROM = no

# Libraries
#LIBS = -L path/to/libraries -llibrary1 -llibrary2

# Includes
#INCLUDES = -Ipath/to/include/files

# Compiler options for all c source files
CFLAGS = -std=c99 -Wall -O1 -fshort-enums -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(INCLUDES)

# Enable map file
# LDFLAGS += -Wl,-Map,$(PRG).map

# Enable floating-point support in printf
#LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm

# Enable automatic removal of unused functions
CFLAGS += -ffunction-sections -fdata-sections
LDFLAGS += -Wl,--gc-sections

# Collect fuse operations for avrdude
ifdef FUSE
  FUSES += -U fuse:w:$(FUSE):m
endif
ifdef LFUSE
  FUSES += -U lfuse:w:$(LFUSE):m
endif
ifdef HFUSE
  FUSES += -U hfuse:w:$(HFUSE):m
endif
ifdef EFUSE
  FUSES += -U efuse:w:$(EFUSE):m
endif
ifdef FUSE0
  FUSES += -U fuse0:w:$(FUSE0):m
endif
ifdef FUSE1
  FUSES += -U fuse1:w:$(FUSE1):m
endif
ifdef FUSE2
  FUSES += -U fuse2:w:$(FUSE2):m
endif
ifdef FUSE3
  FUSES += -U fuse3:w:$(FUSE3):m
endif
ifdef FUSE4
  FUSES += -U fuse4:w:$(FUSE4):m
endif
ifdef FUSE5
  FUSES += -U fuse5:w:$(FUSE5):m
endif
ifdef FUSE6
  FUSES += -U fuse6:w:$(FUSE6):m
endif
ifdef FUSE7
  FUSES += -U fuse7:w:$(FUSE7):m
endif

# Workaround: avrdude does not support attiny13a
ifeq ($(MCU),attiny13a)
  AVRDUDE_MCU = attiny13
else
  AVRDUDE_MCU = $(MCU)
endif

# Default sections
ifeq ($(EEPROM),yes)
all: code eeprom
else
all: code
endif

# Program code
code: $(PRG).hex

# Eeprom content
eeprom: $(PRG)_eeprom.hex

# Generated code listing
list: $(PRG).lst

# Remove all generated files
clean:
	rm -rf *.o driver/*.o $(PRG).hex $(PRG).elf $(PRG).lst $(PRG).map $(PRG)_eeprom.hex $(PRG).bin

minipro: $(PRG).hex
	avr-objcopy --gap-fill 0xFF --pad-to 2048 -I ihex -O binary $(PRG).hex $(PRG).bin
	minipro -w $(PRG).bin -c code -p ATTINY2313

# Program flash memory with or without eeprom
ifeq ($(EEPROM),yes)
program: code eeprom
	$(AVRDUDE) -p $(AVRDUDE_MCU) $(AVRDUDE_HW) -U flash:w:$(PRG).hex:i -U eeprom:w:$(PRG)_eeprom.hex:i
else
program: code 
	$(AVRDUDE) -p $(AVRDUDE_MCU) $(AVRDUDE_HW) -U flash:w:$(PRG).hex:i
endif

# Program fuses
fuses:
	$(AVRDUDE) -p $(AVRDUDE_MCU) $(AVRDUDE_HW) $(FUSES)

$(PRG).elf: $(SRC:.c=.o)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(AVR_SIZE) $(PRG).elf

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 
