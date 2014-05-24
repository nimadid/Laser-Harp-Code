/******* function to play a teach mode song *******/
void playSong(uint8_t LEDdata0[], uint8_t LEDdata1[], char notes[], double waits[], int noteNum){
	int valid = 0;
	int j, k;
	char note;

	char teachPrint[] = "Teach Mode...";   int teachNum = 13;
	printscheme(teachPrint, teachNum);
	busyFlag = 1;

	for (k = 0; k < noteNum; k++) {
	   writeData[0] = LEDdata0[k]; writeData[1] = LEDdata1[k];
	   I2CWrite16(writeData, slaveAddLED);

	   while(1) {
		 for (j = 0; j < 9; j++) {
			 if (cancel)
				 return;
		     if (noteVals[j] == 1) {
		    	 note = playNotes[j];
				 if (note == notes[k]) {
				   playNote(channel1, note, attackVel);
				   valid = 1;
				   writeData[0] = 0x00; writeData[1] = 0x00;
				   I2CWrite16(writeData, slaveAddLED);
				   waitNote(waits[k]);
				   stopNote(channel1, note, releaseVel);
				   break;
				 }
		     }
		     if (valid)
		        break;
		 }
		 if(valid)
			break;
	  }
	  valid = 0;
	  note = 0;
	}
}
