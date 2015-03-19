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
#include <stdio.h>

struct two_sixteens
{
	uint16_t one;
	uint16_t two;
};

struct four_chars
{
	char key[4];
};

int main()
{

	unsigned value;
	unsigned *vp;
	unsigned temps;
	char key;
	uint16_t a;
	uint16_t b;
	char keys[4];
	struct two_sixteens *ts;
	struct four_chars *fc;

	key = 'a';
	a   = 1234;
	b   = 5678;

	vp = NULL;
	printf("VP: %p \n", vp);
	if(vp == NULL)
		printf("VP: NULL\n");

	value = (unsigned) vp;	
	printf("Value: %p \n", (void *) value);

	value = (unsigned) '\0';	
	printf("Value: %08X \n", value);
	if(value == (unsigned) '\0')
		printf("Value: NULL\n");

	printf("unsigned *:\t%i\n", sizeof(unsigned *));
	vp = (unsigned *) value;
	printf("VP: %p \n", vp);
	if(vp == NULL)
		printf("VP: NULL\n");

	value = (unsigned) 0 <<24 | key;
	printf("Value: %08X \n", value);
	memcpy(&keys, &value, sizeof(unsigned));
	printf("Key 1:\t%c\n",keys[0]);
	printf("Key 2:\t%c\n",keys[1]);
	printf("Key 3:\t%c\n",keys[2]);
	printf("Key 4:\t%c\n",keys[3]);
	fc = (struct four_chars*) &value;
	printf("FC:\t%s\n", fc->key);
	printf("FC Key 1:\t%c\n", fc->key[0]);
	printf("FC Key 2:\t%c\n", fc->key[1]);
	printf("FC Key 3:\t%c\n", fc->key[2]);
	printf("FC Key 4:\t%c\n", fc->key[3]);


	temps = (unsigned) htons(b) <<16 | htons(a);
	value = temps;
	ts = (struct two_sixteens*) &value;
	printf("Value: %08X \n", value);
	printf("one:\t%u\n", ts->one);
	printf("two:\t%u\n", ts->two);
	printf("Network Byte Order Value: %08X \n", htonl(value));
	printf("Network Byte Order one:\t%u\n", ntohs(ts->one));
	printf("Network Byte Order two:\t%u\n", ntohs(ts->two));

	value = (unsigned) 0 <<16 | a;
	ts = (struct two_sixteens*) &value;
	printf("Value: %08X \n", value);
	printf("one:\t%u\n", ts->one);
	printf("two:\t%u\n", ts->two);
	
	keys[0] = 'a';
	keys[1] = 'b';
	keys[2] = 'c';
	keys[3] = 'd';
	memcpy(&value, &keys, sizeof(unsigned));
	printf("Value: %08X \n", value);
	printf("Key 1:\t%c\n",keys[0]);
	printf("Key 2:\t%c\n",keys[1]);
	printf("Key 3:\t%c\n",keys[2]);
	printf("Key 4:\t%c\n",keys[3]);
	
	temps = htonl(value);
	memcpy(&keys, &temps, sizeof(unsigned));
	printf("Network Byte Order Value: %08X \n", temps);
	printf("Network Byte Order Key 1:\t%c\n",keys[0]);
	printf("Network Byte Order Key 2:\t%c\n",keys[1]);
	printf("Network Byte Order Key 3:\t%c\n",keys[2]);
	printf("Network Byte Order Key 4:\t%c\n",keys[3]);

	printf("1/4:%i\n",1/4);	
	printf("1/4:%i\n",(1/4)+(1%4));	

	printf("5/4:%i\n",5/4);	
	printf("5/4:%i\n",(5/4)+(5%4));	
	return 0;
}
