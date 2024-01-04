#include<S32K146.h>

void DisableWatchDog(void){
	WDOG->CNT = 0xD928C520;				/*- Unlocking Sequence of Watchdog -*/
	WDOG->TOVAL = 0x0000FFFF;			/*- Setting Maximum Value of Watchdog -*/
	WDOG->CS = 0x00002100;				/*- Disabling Watchdog Timer -*/
}
void ClocksSOSC(void){
	SCG->SOSCDIV = 0x00000101;			/*- SOSC Clock Dividers -*/
	SCG->SOSCCFG = 0x00000024;			/*- SOSC Clock Selector -*/

	while(SCG->SOSCCSR & 0x00800000){		/*- Checking If SOSCCSR is Unlocked -*/
		SCG->SOSCCSR &= ~(0x00800000);		/*- Unlocking SOSCCSR -*/
	}

	SCG->SOSCCSR = 0x00000001;			/*- SOSC Clock Enabled -*/
	while(!(SCG->SOSCCSR & 0x01000000));		/*- SOSC Clock Validation -*/
}
void ClocksSPLL(void){
	while(SCG->SPLLCSR & 0x00800000){		/*- Chechking If SPLLCSR is Unlocked -*/
		SCG->SPLLCSR = 0x00000000;		/*- Disabling SPLL -*/
	}
	SCG->SPLLCSR = 0x00000000;			/*- Disabling SPLL -*/
	SCG->SPLLDIV = 0x00000302;			/*- SPLL Clock Divider -*/
	SCG->SPLLCFG = 0x00180000;			/*- Clock At 40 MHZ -*/
	while(SCG->SPLLCSR & 0x00800000){		/*- Chechking If SPLLCSR is Unlocked -*/
		SCG->SPLLCSR = 0x00000001;		/*- Enabling SPLL -*/
	}
	while(!(SCG->SPLLCSR & 0x01000000));		/*- SPLL Clock Validation -*/
	
	while(SCG->CSR != 0x06010032){			/*- System Clock Validation -*/
		SCG->RCCR = 0x06010032;			/*- System Clock Setting -*/
	}
}
void LPSInitialization(void){
	PCC->PCCn[45] = 0x00000000;			/*- Disabling PCC -*/
	PCC->PCCn[45] = 0xC6000000;			/*- Enabling PCC With SPLL_DIV2 -*/

	LPSPI1->CR = 0x00000000;			/*- Disabling LPSPI -*/
	LPSPI1->IER = 0x00000000;			/*- Disabling LPSPI Interrupts -*/
	LPSPI1->DER = 0x00000000;			/*- Disabling LPSPI DMA -*/
	LPSPI1->CFGR0 = 0x00000000;
	LPSPI1->CFGR1 = 0x00000001;			/*- Enabling Master Mode -*/
	LPSPI1->TCR = 0x5300000F;			/*- Transmit Settings -*/
	LPSPI1->CCR = 0x04090808;			/*- SCK Clock Settings -*/
	LPSPI1->FCR = 0x00000003;			/*- FIFO Controlled Register -*/
	LPSPI1->CR = 0x00000009;			/*- Enabling LPSPI -*/

	PCC->PCCn[74] = 0xC0000000;			/*- PCC PORT B -*/
	PORTB->PCR[14] |= 0x00000300;			/*- PTB-14 As LPSPI-SCK -*/
	PORTB->PCR[15] |= 0x00000300;			/*- PTB-15 As LPSPI-SIN -*/
	PORTB->PCR[16] |= 0x00000300;			/*- PTB-16 As LPSPI-SOUT -*/
	PORTB->PCR[17] |= 0x00000300;			/*- PTB-17 As LPSPI-PCS3 -*/
}
