#ifndef __ONEWIRE_H_
#define __ONEWIRE_H_

bit init_ds18b20(void);
unsigned char Read_DS18B20(void);
void Write_DS18B20(unsigned char dat);
void Delay_OneWire(unsigned int t);
#endif
