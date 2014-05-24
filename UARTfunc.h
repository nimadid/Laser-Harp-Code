// function to print current mode
void printMode(char printArray[], int numElements) {
	int j;
	UARTCharPut(UART2_BASE, 254);
	UARTCharPut(UART2_BASE, 134);
    for (j = 0; j < numElements; j++) {
    	UARTCharPut(UART2_BASE, printArray[j]);
    }
}

// function to print current song
void printSong(char printArray[], int numElements) {
	int j;
	UARTCharPut(UART2_BASE, 254);
	UARTCharPut(UART2_BASE, 198);
    for (j = 0; j < numElements; j++) {
    	UARTCharPut(UART2_BASE, printArray[j]);
    }
}

// function to print current note scheme
void printscheme(char printArray[], int numElements){
	int j;
	UARTCharPut(UART2_BASE,254);
	UARTCharPut(UART2_BASE, 0x01);
	for (j=0; j < numElements; j++){
		UARTCharPut(UART2_BASE, printArray[j]);
	}
}

// function to print default screen
void defaultScreen() {
	int j;
	char printMode[] = "Mode:";
	char printSong[] = "Song:";
	UARTCharPut(UART2_BASE, 254);
	UARTCharPut(UART2_BASE, 0x01);

	UARTCharPut(UART2_BASE, 254);
	UARTCharPut(UART2_BASE, 128);
    for (j = 0; j < 5; j++) {
    	UARTCharPut(UART2_BASE, printMode[j]);
    }

    UARTCharPut(UART2_BASE, 254);
	UARTCharPut(UART2_BASE, 192);
    for (j = 0; j < 5; j++) {
    	UARTCharPut(UART2_BASE, printSong[j]);
    }
}
