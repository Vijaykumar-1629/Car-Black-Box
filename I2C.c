#include <xc.h>

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;  //

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_idle(void)
{
	while (!SSPIF);  //instruction should be executed or not 
	SSPIF = 0;
}

void i2c_ack(void)
{
	if (ACKSTAT)  
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void)
{
	SEN = 1;  //start bit
	i2c_idle();
}

void i2c_stop(void)
{
	PEN = 1;  //stop the communication
	i2c_idle();
}

void i2c_rep_start(void)
{
	RSEN = 1; //repeat start communication
	i2c_idle();
}

void i2c_write(unsigned char data)
{
	SSPBUF = data;   //data will loading the buffer register
	i2c_idle();
}

void i2c_rx_mode(void)
{
	RCEN = 1;   //enable the receive operation
	i2c_idle();
}

void i2c_no_ack(void)
{
	ACKDT = 1;   //acknowledge  data bit 
	ACKEN = 1;   //acknowledge enable bit
}

unsigned char i2c_read(void) //to receive the data from the slave
{
	i2c_rx_mode();  
	i2c_no_ack();

	return SSPBUF;
}
