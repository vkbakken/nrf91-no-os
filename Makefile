TOOCHAIN_LOC		:= C:\gnuarmemb\bin
CROSS_COMPILER		:= arm-none-eabi
CC			:= $(TOOCHAIN_LOC)\$(CROSS_COMPILER)-gcc


PRJ			:= nrf91-no-os

CFILES			:= main.c board.c bsd-os.c
CFILES			+= ./nrfx/mdk/system_nrf9160.c
CINC			:= -I ./nrfx/mdk/ -I ./cmsis/CMSIS/Core/Include -I ./nrfxlib/bsdlib/include/
CFLAGS			:= -Wall -Os -mcpu=cortex-m33 -mlittle-endian -mfloat-abi=soft -mthumb -mtp=soft -munaligned-access
CFLAGS			+= $(CINC)
CFLAGS			+= -DNRF9160_XXAA

ASMFILES		:= ./nrfx/mdk/gcc_startup_nrf9160.S

LDFLAGS			:= $(CFLAGS) -T linker.lds
LDFLAGS			+= -L ./nrfxlib/bsdlib/lib/cortex-m33/soft-float/ -lbsd_nrf9160_xxaa
LDFLAGS			+= -L ./nrfxlib/crypto/nrf_oberon/lib/cortex-m33/soft-float/ -loberon_3.0.2

OBJ       		= $(ASMFILES:.S=.o) $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)


all: $(PRJ).elf


clean:
	rm -f *.hex *.elf *.o

# objects from asm files
.s.o:
	$(CC) -c $(CFLAGS) $< -o $@

# objects from c files
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@


# elf file
$(PRJ).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) --output $@ $(LDFLAGS)