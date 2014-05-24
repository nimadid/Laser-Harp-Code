/****** check which laser is tripped  *******/
void checkNote(uint8_t sensorVal[2], int noteVals[]) {
	if ((sensorVal[0] & 0x01) == 0x00)
	  noteVals[0] = 1;
	if ((sensorVal[0] & 0x02) == 0x00)
	  noteVals[1] = 1;
	if ((sensorVal[0] & 0x04) == 0x00)
	  noteVals[2] = 1;
	if ((sensorVal[0] & 0x08) == 0x00)
	  noteVals[3] = 1;
	if ((sensorVal[0] & 0x10) == 0x00)
	  noteVals[4] = 1;
	if ((sensorVal[0] & 0x20) == 0x00)
	  noteVals[5] = 1;
	if ((sensorVal[0] & 0x40) == 0x00)
	  noteVals[6] = 1;
	if ((sensorVal[0] & 0x80) == 0x00)
	  noteVals[7] = 1;
	if ((sensorVal[1] & 0x01) == 0x00)
	  noteVals[8] = 1;
}
