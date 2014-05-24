/******* initializes all microcontroller settings *******/
void initialization(){
	uint32_t ui32Period;
    // Enable peripherals
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);  // Enable UART1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);  // Enable UART2
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);	  // Enable I2C0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) &= ~0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_DEN) |= 0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;

    // Configure Pins
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    // Enable PinTypes
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,GPIO_PIN_0);  // PB0=INT
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_1);      // UART1
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_7);      // UART2
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);    // PB2=SCL
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);       // PB3=SDA
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);	   // ADC0
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);  // PF4=SW1 input
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_3); // PA5=MIDI reset

	GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
	// Configure Pad
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Enable interrupts from portB pin0
	GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
	GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_0);
	IntEnable(INT_GPIOB);

	// Configure I2C
	I2CMasterEnable(I2C0_BASE);
	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
	I2CMasterTimeoutSet(I2C0_BASE, 0xFF);

	// Configure UART
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 31250,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 9600,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    // Configure ADC
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE |
                                 ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);

    // Configure Timer
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    ui32Period = (SysCtlClockGet() / 5) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    TimerEnable(TIMER0_BASE, TIMER_A);
}
