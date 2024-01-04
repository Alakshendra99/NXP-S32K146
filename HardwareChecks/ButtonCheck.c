#include <S32K146.h>

#define LEDG 16		// PORT D : PTD16
#define LEDB 0		// PORT D : PTD0
#define LEDR 15		// PORT D : PTD15
#define BTN1 12		// PORT C : PTC12
#define BTN2 13		// PORT C : PTC13

void DisableWatchDog(){
	WDOG->CNT = 0xD928C520;
	WDOG->TOVAL = 0x0000FFFF;
	WDOG->CS = 0x00002100;
}

void PORTSetup(){
	PCC->nPCC[74]=0x40000000;
	PCC->nPCC[75]=0x40000000;
	PTC->PDDR &= ~(1<<BTN1 | 1<<BTN2);
	PTD->PDDR |= (1<<LEDR | 1<<LEDG | 1<<LEDB);

	PORTC->PCR[BTN1] = 0x00000110;
	PORTC->PCR[BTN2] = 0x00000110;
	PORTD->PCR[LEDR] = 0x00000100;
	PORTD->PCR[LEDG] = 0x00000100;
	PORTD->PCR[LEDB] = 0x00000100;
}

int main(){
	DisableWatchDog();
	PORTSetup();
	while(1){
		uint8_t Flag1 = 0x00;
		uint8_t Flag2 = 0x00;
		if(PTC->PDIR & 1<<BTN1){
			PTD->PCOR |= 1<<LEDG;
			Flag1 = 0x01;
		} else{
			PTD->PSOR |= 1<<LEDG;
			Flag1 = 0x00;
		}

		if(PTC->PDIR & 1<<BTN1){
			PTD->PCOR |= 1<<LEDB;
			Flag2 = 0x01;
		} else{
			PTD->PSOR |= 1<<LEDB;
			Flag2 = 0x00;
		}

		if(Flag1 & Flag2){
			PTD->PSOR |= 1<<LEDR;
		} else{
			PTD->PCOR |= 1<<LEDR;
		}
	}
}
