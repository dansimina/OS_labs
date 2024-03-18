#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    unsigned int num = 0;
    
    if(2 != argc){
        printf("USAGE: %s number\n", argv[0]);
        exit(-1);
    }

	sscanf(argv[1], "%x", &num);
	
	int firstByte = num & 0x0000000F;
	int secondByte = num & 0xF0000000;
	
	num &= 0x0FFFFFF0;
	num |= (firstByte << 28);
	num |= ((secondByte >> 28) & 0x0000000F);
	
	firstByte = num & 0x000000F0;
	secondByte = num & 0x0F000000;
	
	num &= 0xF0FFFF0F;
	num |= (firstByte << 20);
	num |= ((secondByte >> 20) & 0x000000F0);
	
	printf("%x", num);
   
    return 0;
}
