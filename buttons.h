// function to check volume
void checkVolume(uint32_t *volData) {
	  ADCProcessorTrigger(ADC0_BASE, 3);
	  while(!ADCIntStatus(ADC0_BASE, 3, false)){}
	  ADCIntClear(ADC0_BASE, 3);
	  ADCSequenceDataGet(ADC0_BASE, 3, volData);
}

// function to set volume
void setVolume() {
	volData = volData / 32;
    talkMIDI(0xB0, 0x07, volData);
    talkMIDI(0xB1, 0x07, volData);
    talkMIDI(0xB2, 0x07, volData);       // vol of 120 (127 max)
    talkMIDI(0xB3, 0x07, volData);
    talkMIDI(0xB4, 0x07, volData);       // vol of 120 (127 max)
    talkMIDI(0xB5, 0x07, volData);
    talkMIDI(0xB6, 0x07, volData);       // vol of 120 (127 max)
    talkMIDI(0xB7, 0x07, volData);
    talkMIDI(0xB8, 0x07, volData);
}

// function to check if cancel button is pushed
int checkCancel() {
	int cancel = 0;

	I2CWrite8(0xF7, slaveAddButtonOut);
	buttonData = I2CRead8(slaveAddButtonIn);
	if ((buttonData & 0x04) == 0x00) {
		cancel = 1;
	}
	return cancel;
}

// function to check all other buttons for various selections
void pollButtons() {
	char printFree[] = "Free"; 			int freeCount = 4;
	char printTeach[] = "Teach";		int teachCount = 5;
	char printListen[] = "Listen";		int listenCount = 6;

	char printTwinkle[] = "Twinkle";	int twinkleCount = 7;
	char printMary[] = "Mary";			int maryCount = 4;
	char printOde[] = "OdeToJoy";		int odeCount = 8;
	char printMuffin[] = "Muffin";		int muffinCount = 6;
	char printAdams[] = "London";       int adamsCount = 6;
	char printLetGo[] = "YankeeDdle";   int letGoCount = 10;
	char printFight[] = "ThisOldMan";   int fightCount = 10;
	char printHeart[] = "MyHeartGo";	int heartCount = 9;

	char printScheme1[] = "Note Scheme C"; int scheme1 = 13;
	char printScheme2[] = "Note Scheme F"; int scheme2 = 13;
	char printScheme3[] = "Note Scheme G"; int scheme3 = 13;

	int butFlag = 0;
	int accept = 0;
	int scheme = 0;
	int j;

	I2CWrite8(0xFD, slaveAddButtonOut);
	buttonData = I2CRead8(slaveAddButtonIn);
	if ((buttonData & 0x01) == 0x00 && butFlag != 1) {
		butFlag = 1;
		songFlag = 6;
	}
	else if ((buttonData & 0x02) == 0x00 && butFlag != 1) {
		butFlag = 1;
		songFlag = 2;
	}
	else if ((buttonData & 0x04) == 0x00 && butFlag != 1) {
		butFlag = 1;
		scheme = 2;
	}
	else if ((buttonData & 0x08) == 0x00 && butFlag != 1) {
		butFlag = 1;
		modeFlag = 2;
	}

	I2CWrite8(0xF7, slaveAddButtonOut);
	buttonData = I2CRead8(slaveAddButtonIn);
	if ((buttonData & 0x01) == 0x00 && butFlag != 1) {
		songFlag = 8;
		butFlag = 1;
	}
	else if ((buttonData & 0x02) == 0x00 && butFlag != 1) {
		songFlag = 4;
		butFlag = 1;
	}
	else if ((buttonData & 0x08) == 0x00 && butFlag != 1) {
	    accept = 1;
	    butFlag = 1;
	}

	I2CWrite8(0xFB, slaveAddButtonOut);
	buttonData = I2CRead8(slaveAddButtonIn);
	if ((buttonData & 0x01) == 0x00 && butFlag != 1) {
		butFlag = 1;
		songFlag = 7;
	}
	else if ((buttonData & 0x02) == 0x00 && butFlag != 1) {
		butFlag = 1;
		songFlag = 3;
	}
	else if ((buttonData & 0x04) == 0x00 && butFlag != 1) {
		butFlag = 1;
		scheme = 3;
	}
	else if ((buttonData & 0x08) == 0x00 && butFlag != 1) {
		butFlag = 1;
		modeFlag = 3;
	}

	I2CWrite8(0xFE, slaveAddButtonOut);
	buttonData = I2CRead8(slaveAddButtonIn);
	if ((buttonData & 0x01) == 0x00 && butFlag != 1) {
		butFlag = 1;
		songFlag = 5;
	}
	else if ((buttonData & 0x02) == 0x00 && butFlag != 1) {
		butFlag = 1;
		songFlag = 1;
	}
	else if ((buttonData & 0x04) == 0x00 && butFlag != 1) {
		butFlag = 1;
		scheme = 1;
	}
	else if ((buttonData & 0x08) == 0x00 && butFlag != 1) {
		butFlag = 1;
		modeFlag = 1;
	}

	if (scheme == 1) {
      for (j = 0; j < 9; j++)
        playNotes[j] = cScale[j];
      printscheme(printScheme1,scheme1);
      waitNote(4);
      defaultScreen();
	}
	else if (scheme == 2) {
	  for (j = 0; j < 9; j++)
	    playNotes[j] = fScale[j];
	  printscheme(printScheme2, scheme2);
	  waitNote(4);
	  defaultScreen();
	}
	else if (scheme == 3) {
	  for (j = 0; j < 9; j++)
		playNotes[j] = adamsScale[j];
	  printscheme(printScheme3, scheme3);
	  waitNote(4);
	  defaultScreen();
	}

	if (prevSong != songFlag || prevMode != modeFlag)
	{
		defaultScreen();
		prevSong = songFlag;
		prevMode = modeFlag;
	}

	if (songFlag == 1)
		printSong(printTwinkle, twinkleCount);
	else if (songFlag == 2)
		printSong(printMary, maryCount);
	else if (songFlag == 3)
		printSong(printOde, odeCount);
	else if (songFlag == 4)
		printSong(printMuffin, muffinCount);
	else if (songFlag == 5)
		printSong(printAdams, adamsCount);
	else if (songFlag == 6)
		printSong(printLetGo, letGoCount);
	else if (songFlag == 7)
		printSong(printFight, fightCount);
	else if (songFlag == 8)
		printSong(printHeart, heartCount);

	if (modeFlag == 1)
		printMode(printFree, freeCount);
	else if (modeFlag == 2)
		printMode(printTeach, teachCount);
	else if (modeFlag == 3)
		printMode(printListen, listenCount);

	if (accept == 1) {
		mode = modeFlag;
		songChoice = songFlag;
	}
}
