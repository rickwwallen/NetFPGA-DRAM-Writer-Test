#
# 
#

CFLAGS = -g
CC = gcc

# Location of binary files
BINDIR ?= /usr/local/bin

# Location of common files
COMMON = common/

all : common test_write_dram

test_write_dram : test_write_dram.o common/nf2util.o 

common:
	$(MAKE) -C $(COMMON)

clean :
	rm -rf test_write_dram *.o

install: test_write_dram
	install test_write_dram $(BINDIR)

.PHONY: all clean install

