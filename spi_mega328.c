#include <avr/io.h>
#include "spi_mega328.h"

void spi_init(void)
{
	//pullup miso ?

	SPCR |= (1 << SPE) | (1 << MSTR); //DORD ?
	SPSR |= (1 << SPI2X);
}

uint8_t spi_xfer(uint8_t dat) 
{
	SPDR = dat;
	while (!(SPSR & (1 << SPIF)));

	return SPDR;
}

// internally used alias for spi function (to not force name for generic spi transfer functions)
uint8_t rfm7x_xfer_spi(uint8_t dat) __attribute__((alias("spi_xfer")));

// void spi_reg_write(uint8_t reg, uint8_t dat)
// {
// 	spi_xfer(reg);
// 	spi_xfer(dat);
// }
// 
// uint8_t spi_reg_read(uint8_t reg)
// {
// 	uint8_t tmp;
// 	
// 	spi_xfer(reg);
// 	tmp = spi_xfer(0);  
// 	
// 	return tmp; // spi_xfer(spi_xfer(reg))
// }

// void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_xfer(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		spi_xfer(buff[i]);
// }

void spi_buff_write(uint8_t *buff, uint8_t len)
{
	for (uint8_t i = 0; i<len; i++)
		spi_xfer(buff[i]);
}

void rfm7x_buff_write(uint8_t *buff, uint8_t len) __attribute__((alias("spi_buff_write")));

// void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_xfer(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		buff[i] = spi_xfer(0);
// }

void spi_buff_read(uint8_t *buff, uint8_t len)
{
	for (uint8_t i = 0; i<len; i++)
		buff[i] = spi_xfer(0);
}

void rfm7x_buff_read(uint8_t *buff, uint8_t len) __attribute__((alias("spi_buff_read")));