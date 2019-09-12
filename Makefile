
COMPILER= clang
CFLAGS= -o
INCDIRS = -Iinc
LIBFLAGS += -lrt -lpthread -lcurl 
CFILES= src/*.c src/util/*.c src/network/*.c
OUTPUTEXE= surge.elf

all:
	$(COMPILER) -std=c99 $(CFILES) $(LIBFLAGS) $(INCDIRS) $(CFLAGS) $(OUTPUTEXE)