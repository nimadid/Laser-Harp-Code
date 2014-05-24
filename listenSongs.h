/******* function to play a teach mode song *******/
void listenSong(uint8_t LEDdata0[], uint8_t LEDdata1[], char notes[], double waits[], int noteNum) {
	int j;

	char listenPrint[] = "Listen Mode...";   int listenNum = 14;
	printscheme(listenPrint, listenNum);
	busyFlag = 1;

	for (j = 0; j < noteNum; j++) {
	   if (cancel)
		   return;

	   writeData[0] = LEDdata0[j]; writeData[1] = LEDdata1[j];
	   I2CWrite16(writeData, slaveAddLED);

	   playNote(channel1, notes[j], attackVel);
	   waitNote(waits[j]);
	   stopNote(channel1, notes[j], releaseVel);

	   if (cancel)
		   return;

	   writeData[0] = 0x00; writeData[1] = 0x00;
	   I2CWrite16(writeData, slaveAddLED);
	   waitNote(20);
    }
}
