#ifndef _I2C_H
#define _I2C_H

#include "stm32f10x.h"


void tps_sleep_to_standby(void);
void tps_standby_to_sleep(void);
void tps_source_gate_enable(void);
void tps_source_gate_disable(void);
void tps_vcom_enable(void);
void tps_vcom_disable(void);
unsigned char ti_read_int_status(void);
void tps_read_all_reg(void);
void tps_init(void);

#endif	//_I2C_H
