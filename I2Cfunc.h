/******* I2C communication functions *******/
void I2CWrite8(uint8_t data, uint8_t address){
	I2CMasterSlaveAddrSet(I2C0_BASE, address, false);
	I2CMasterDataPut(I2C0_BASE, data);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(I2C0_BASE));
}

void I2CWrite16(uint8_t data[2], uint8_t address){
	I2CMasterSlaveAddrSet(I2C0_BASE, address, false);

	I2CMasterDataPut(I2C0_BASE, data[0]);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C0_BASE));

	I2CMasterDataPut(I2C0_BASE, data[1]);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C0_BASE));
}

uint8_t I2CRead8(uint8_t address){
	I2CMasterSlaveAddrSet(I2C0_BASE, address, true);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
	while(I2CMasterBusy(I2C0_BASE));

	return I2CMasterDataGet(I2C0_BASE);
}

void I2CRead16(uint8_t address){
	I2CMasterSlaveAddrSet(I2C0_BASE, address, true);

	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
	while(I2CMasterBusy(I2C0_BASE));
	sensorVal[0] = I2CMasterDataGet(I2C0_BASE);

	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
	while(I2CMasterBusy(I2C0_BASE));
	sensorVal[1] = I2CMasterDataGet(I2C0_BASE);
}
