void setup_hardware_spi(void)
{
	byte clr;
	SPCR |= (_BV(SPE) | _BV(MSTR));   // enable SPI as Master 
	clr = SPSR;                       // delete SPSR register 
	clr = SPDR;                       // delete SPDR register 
	SPCR &= ~(_BV(SPR1) | _BV(SPR0)); // set prescaler to half processor cycles
	SPSR |= _BV(SPI2X);               // last bit first
}

byte spi_shiftOut(byte data)
{
	SPDR = data;		        // start the SPA data transmision
	while (!(SPSR & _BV(SPIF))) {}; // wait for end of transmission
	return SPDR;	
}

