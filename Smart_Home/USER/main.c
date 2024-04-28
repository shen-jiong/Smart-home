/******************************�¶�����ղ���************************
* �¶������
* �¶���ʾ����ߣ�������ʾ���ұ�
******************************************************************/

#include "sys.h"
#include "led.h"
#include "delay.h"
#include "adc.h"

/***************************������*****************************/
int main()
{
	u8 light;
 	float adcx = 0.0;
	u16 adcValue = 0;
	u8 i = 0;
	light = 0x01;
	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	TemperatureAndLightAdcInit();
	LED_Init();
	LED_SEL = 0;
	adcx = GetTemperature();        //ʹ��PC5 ADC1, ͨ��15
			adcValue = GetLightAdc(14); //ʹ��PC4 ADC1, ͨ��14
	while(1)
	{		
		i++;
		if( i > 50 )                  //��Լÿ��100��ѭ����������ɨ��һ��ADC��ֵ
		{
			adcx = GetTemperature();    //ʹ��PC5 ADC1, ͨ��15
			adcValue = GetLightAdc(14); //ʹ��PC4 ADC1, ͨ��14
			i = 0;
		}
		//�¶�
		SetLed(0, adcx/10);
		delay_ms(1);
		PortationDisplay(1,(u8)adcx%10);
		delay_ms(1);
		SetLed(2, (u8)(adcx*10)%10);
		delay_ms(1);
		SetLed(3, (u8)(adcx*100)%10);
		delay_ms(1);
		
		//����
		SetLed(4, adcValue/1000);
		delay_ms(1);
		SetLed(5, adcValue%1000/100);
		delay_ms(1);
		SetLed(6, adcValue%100/10);
		delay_ms(1);
		SetLed(7, adcValue%10);
		delay_ms(1);
		
		while(adcx>30||adcValue<30){
			LED_SEL = 1;
		adcx = GetTemperature();    //ʹ��PC5 ADC1, ͨ��15
		adcValue = GetLightAdc(14); //ʹ��PC4 ADC1, ͨ��14
			
		GPIOE->ODR |= (light<<8);
			
		delay_ms( 300 ); 
			
		light = light<<1;
		
		if( light==0x00 )
		{
			GPIOE->ODR &= ~(0xff<<8);
			delay_ms( 300 ); 
			light = 0x01;
		}
			
		}
		
		LED_SEL = 0;
		
	
		while(adcValue>150){
			
    LED_SEL = 0;
			
		adcValue = GetLightAdc(14); //ʹ��PC4 ADC1, ͨ��14
		
		SetLed(4, 10);
		delay_ms(1);
		SetLed(5, 4);
		delay_ms(1);
		SetLed(6, 2);
		delay_ms(1);
		SetLed(7, 2);
		delay_ms(1);
		}
		LED_SEL = 0;
		
	}	
}

