#ifndef _ADC_H_
#define _ADC_H_

extern void adc1_init(void);
extern unsigned short get_adc_value(void);
extern float get_voltage(void);

extern unsigned short get_adc_avg(unsigned int sample_cnt);
extern unsigned short adc_lowpass(unsigned short new_val);
#endif