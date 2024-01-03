void DisableWatchDog(){
	WDOG->CNT = 0xD928C520;				/*- Unlocking Sequence of Watchdog -*/
	WDOG->TOVAL = 0x0000FFFF;			/*- Setting Maximum Value of Watchdog -*/
	WDOG->CS = 0x00002100;				/*- Disabling Watchdog Timer -*/
}
void ClocksSOSC(){
	SCG->SOSCDIV = 0x00000101;			/*- System Clock Dividers -*/
	SCG->SOSCCFG = 0x00000024;			/*- System Clock Selector -*/

	while(SCG->SOSCCSR & 0x00800000){		/*- Checking If SOSCCSR is Unlocked -*/
		SCG->SOSCCSR &= ~(0x00800000);		/*- Unlocking SOSCCSR -*/
	}

	SCG->SOSCCSR = 0x00000001;			/*- System Clock Enabled-*/
	while(SCG->SOSCCSR & 0x01000000);		/*- System Clock Validation -*/
}

	
