/*
 * * FILE NAME:		my_zone_read.c
 * * TEST SOME WRITES TO DRAM AND FUTURE CODE TO TEST OUT READS ON NETFPGA 
 * * CHECK ENDIANESS FOR READS ON NETFPGA  
 * * CREATED BY:	RICK W. WALLEN
 * * DATE CREATED:	MARCH.13.2015
 * * DATE LAST MOD:	MARCH.13.2015
 * *     ___________
 * *    |           |
 * *  [[|___________|]]
 * *    \___________/
 * *   __|[ ]||||[ ]|__
 * *   \_| # |||| # |_/
 * *  ___ ===Jeep=== ___
 * * |\/\| ''    '' |\/\|
 * * |/\/|          |/\/|
 * * |_\_|          |_\_|
 * */
/**********************************************************************/
/*
 * * MODIFIED LOG:
 * *       <date>-<description>
 * *	March.13.2015-Initial create
 * *		-Used similar structure that will be written to NetFPGA
 * */
/**********************************************************************/
#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <net/if.h>
#include <stdio.h>
#include "common/nf2.h"
#include "common/nf2util.h"

#define DEFAULT_IFACE	"nf2c0"
#define BASE_MASK 0x4000000

static struct nf2device nf2;

void writeRegisters(int,char**);

int main()
{

	unsigned value;
	unsigned addr;
	char key;
	uint16_t a;
	uint16_t b;

	key = 'c';
	a   = 1234;
	b   = 5678;

	nf2.device_name = DEFAULT_IFACE;

	addr = BASE_MASK;
	printf("Address of DRAM: %X \n\n", addr);

	if(check_iface(&nf2))
		exit(1);
	if(openDescriptor(&nf2))
		exit(1);

	printf("Start to store the nodes in DRAM\n\n");

	printf("Address of DRAM: %X \n\n", addr);
	value = (unsigned) key <<24 | 0;
	writeReg(&nf2, addr, value);
	addr  = addr + sizeof(unsigned);
	
	printf("Address of DRAM: %X \n\n", addr);
	value = addr + sizeof(unsigned);
	writeReg(&nf2, addr, value);
	addr  = addr + sizeof(unsigned);

	printf("Address of DRAM: %X \n\n", addr);
	value = (unsigned) a <<16 | b;
	writeReg(&nf2, addr, value);
	addr  = addr + sizeof(unsigned);

	printf("Address of DRAM: %X \n\n", addr);
	value = (unsigned) a <<16 | 0;
	writeReg(&nf2, addr, value);
	addr  = addr + sizeof(unsigned);
	
	closeDescriptor(&nf2);
	
	return 0;
}
