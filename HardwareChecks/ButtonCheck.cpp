#include <S32K146.h>

void DisableWatchDog(){
	WDOG->CNT = 0xD928C520;
	WDOG->TOVAL = 0x0000FFFF;
	WDOG->CS = 0x00002100;
}

void PORTSetup(){
	PCC->nPCC[74]=0x40000000;
	PCC->nPCC[75]=0x40000000;
	
}
