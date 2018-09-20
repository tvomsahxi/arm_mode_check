#include "rpi_lib/rpi.h"

#define GPFSEL1	0x3F200004
#define GPSET0	0x3F20001C
#define GPCLR0	0x3F200028

/*#define SYST_CLO	0x3F003004
#define SYST_CHI	0x3F003008

unsigned long long int get_systime(void){
	unsigned long long int t;
	unsigned int chi;
	unsigned int clo;

	chi = *(volatile unsigned int *)SYST_CHI;
	clo = *(volatile unsigned int *)SYST_CLO;
	
	if(chi != *(volatile unsigned int *)SYST_CHI){
		chi = *(volatile unsigned int *)SYST_CHI;
		clo = *(volatile unsigned int *)SYST_CLO;
	}
	
	t = chi;
	t = t << 32;
	t += clo;

	return t;
}

void delay_ms(unsigned int delay){
	unsigned long long int alermTime;
	
	alermTime = get_systime() ;//+ delay * 1000;

	while(get_systime() < alermTime){	
	//	*(volatile unsigned int *)GPFSEL1 = 0x01 << (3*6);
	//	*(volatile unsigned int *)GPSET0 = 0x01 << 16;
	}
	return ;
}
*/
int main(void){
	rpi_init();
	unsigned int r;
//CPSRの値を取得して, rに代入する
	__asm__ volatile(
		
		"MRS %[Rd], CPSR"
		: [Rd] "=r" (r)
	);

//	*(volatile unsigned int *)SYST_CHI = 0;
//	*(volatile unsigned int *)SYST_CLO = 0;

	*(volatile unsigned int *)GPFSEL1 = 0x01 << (3*4);
	*(volatile unsigned int *)GPFSEL1 |= 0x01 << (3*5);
	*(volatile unsigned int *)GPFSEL1 |= 0x01 << (3*6);
	*(volatile unsigned int *)GPFSEL1 |= 0x01 << (3*7);
	*(volatile unsigned int *)GPFSEL1 |= 0x01 << (3*8);
	while(1){
		//delay_ms(3000);
		if(r&0x00000010)
			*(volatile unsigned int *)GPSET0 = 0x01 << 14;
		if(r&0x00000008)
			*(volatile unsigned int *)GPSET0 = 0x01 << 15;
		if(r&0x00000004)
			*(volatile unsigned int *)GPSET0 = 0x01 << 16;
		if(r&0x00000002)
			*(volatile unsigned int *)GPSET0 = 0x01 << 17;
		if(r&0x00000001)
			*(volatile unsigned int *)GPSET0 = 0x01 << 18;
		//delay_ms(3000);
	//	*(volatile unsigned int *)GPCLR0 = 0x01 << 17;
	}

	
	return 0;
}
