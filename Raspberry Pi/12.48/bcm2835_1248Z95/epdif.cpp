#include "epdif.h"
#include <bcm2835.h>

EpdIf::EpdIf() {
};
EpdIf::~EpdIf() {
};

void EpdIf::DigitalWrite(int pin, int value) {
    bcm2835_gpio_write(pin, value);
}

int EpdIf::DigitalRead(int pin) {
    return bcm2835_gpio_lev(pin);
}

void EpdIf::DelayMs(unsigned int delaytime) {
    bcm2835_delay(delaytime);
}

void EpdIf::SpiTransfer(unsigned char data) {
    bcm2835_spi_transfer(data);
}

int EpdIf::IfInit(void) {
    if(!bcm2835_init()) {
        return -1;
    }







    bcm2835_gpio_fsel(CSB_M1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RST_M1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(DC_M1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(CSB_S1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(BUSY_M1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(BUSY_S1, BCM2835_GPIO_FSEL_INPT);


    bcm2835_gpio_fsel(CSB_M2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RST_M2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(DC_M2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(CSB_S2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(BUSY_M2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(BUSY_S2, BCM2835_GPIO_FSEL_INPT);
     //SCL  SDA
    bcm2835_gpio_fsel(SDI, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(SCL, BCM2835_GPIO_FSEL_OUTP);

    /*
    bcm2835_spi_begin();                                         //Start spi interface, set spi pin for the reuse function
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     //High first transmission
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  //spi mode 0
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);  //Frequency
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     //set CE0
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     //enable cs0
    */
return 0;
}

