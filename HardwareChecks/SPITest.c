void DisableWatchDog(){
	WDOG->CNT = 0xD928C520;				/*- Unlocking Sequence of Watchdog -*/
	WDOG->TOVAL = 0x0000FFFF;			/*- Setting Maximum Value of Watchdog -*/
	WDOG->CS = 0x00002100;				/*- Disabling Watchdog Timer -*/
}
void ClocksSOSC(){
	SCG->SOSCDIV = 0x00000101;			/*- SOSC Clock Dividers -*/
	SCG->SOSCCFG = 0x00000024;			/*- SOSC Clock Selector -*/

	while(SCG->SOSCCSR & 0x00800000){		/*- Checking If SOSCCSR is Unlocked -*/
		SCG->SOSCCSR &= ~(0x00800000);		/*- Unlocking SOSCCSR -*/
	}

	SCG->SOSCCSR = 0x00000001;			/*- SOSC Clock Enabled -*/
	while(!(SCG->SOSCCSR & 0x01000000));		/*- SOSC Clock Validation -*/
}
void ClocksSPLL(){
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
