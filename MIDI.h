/******* MIDI functions *******/
void waitNote(double num) {
  SysCtlDelay(SysCtlClockGet()/num);
}

void talkMIDI(char action, char data1, char data2) {
   UARTCharPut(UART1_BASE, action);
   UARTCharPut(UART1_BASE, data1);
   if( (action & 0xF0) <= 0xB0) {
     UARTCharPut(UART1_BASE, data2);
   }
}

void noteOn(char channel, char note, char attackVel)
{
  talkMIDI((0x90 | channel), note, attackVel);
}

void playNote(char channel, char note, char attackVel) {
  noteOn(channel, note, attackVel);
}

void noteOff(char channel, char note, char releaseVel)
{
  talkMIDI((0x80 | channel), note, releaseVel);
}

void stopNote(char channel, char note, char releaseVel) {
  noteOff(channel, note, releaseVel);
}

void resetMIDI() {
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
  waitNote(1);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x20);
  waitNote(1);
}
