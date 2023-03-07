#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "control.h"
#include "adc.h"
#include "stdio.h"
#define DelayT 30
#define SOFT_VERSION 	13
#define BAUD_RATE1 		115200
const char STATION_INFO[30]="H28 SIP1&SIP2_R Station-1";
const char VERINFO[20]="2023-02-27";

uint16_t getAdcValue(uint32_t ch)
{
    ADC_ChannelConfTypeDef ADC_Config;   //配置ADC
    ADC_Config.Rank=1;                  //只开启一个序列
    ADC_Config.Channel= ch;             // 通道
    ADC_Config.SamplingTime = ADC_SAMPLETIME_144CYCLES;   //采样时间，越长月精确
    HAL_ADC_ConfigChannel(&hadc1,&ADC_Config);
    HAL_ADC_Start(&hadc1);    //开始转换
    HAL_ADC_PollForConversion(&hadc1,10); //等待转换完成
    return (uint16_t)HAL_ADC_GetValue(&hadc1);    //获取ADC的值
}
void bubble_sort(uint16_t list[],int len)
{
    for (int i = 0; i <len-1 ; ++i)
    {
        for (int j = 0; j < len-1-i; ++j)
        {
            if (list[j]>list[j+1])
            {
                uint16_t temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

uint16_t getVoltage(uint32_t ch, uint16_t n)
{
    uint16_t AD[n];
    uint16_t ad_data;
    for (int i = 0; i < n; ++i) {
        AD[i] = getAdcValue(ch);
    }
    bubble_sort(AD,n);
    for (int i = 5; i < n-5; ++i) {
        ad_data= (AD[i]+ad_data)/2;
    }
    return ad_data*3000/4096;
}
void getDutVoltage(void)
{
    uint16_t data_adc0 = getVoltage(0,20);
    uint16_t data_dut = 1200-data_adc0;
    printf("%04dmV\r\n",data_dut);
}
void voltageRead(uint16_t ch)
{

}
void GET_RESULT(void)
{
	uint16_t a=0;
	uint8_t dut=0;
	for(char i=1;i<=14;i++)//14
    {
        printf("10PIN->PP_VBATT%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->ANALOG_AMP_OUT_P%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->ANALOG_AMP_OUT_N%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->IO_SOC__TO_FRONT_MIC_SEL_PERF%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->PP1V8_LSC_0_KADABRA_TX%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->PP1V8_LSC_0%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->IO_PMU_TO_PCM_UVP_TRIG%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->I2C0_RTP_BI_KADABRA_SDA_D%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->PDM_AUD_FROM_TOP_FRONT_MIC_DATA%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->PDM_AUD_TO_FRONT_MIC_CLK%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->I2C0_RTP_TO_KADABRA_SCL_D%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->PP1V2_LSB_0%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->IO_SOC_FROM_KADABRA_INT_L%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->PACK_NEG%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->PP2V7_LDO2%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->I2C1_RTP_TO_MANDO_SCL%02d=",i);
        voltageRead(a);a++;
        printf("10PIN->I2C1_RTP_BI_MANDO_SDA%02d=",i);
        voltageRead(a);a++;
        a+=3;
    }
	printf("DATA_FINISH\r\n");	
}

void Start(void)
{

}

void RF_TEST(void)	
{

}


void PC_state(void)
{
	printf("PASS\r\n");
}

void Reset(void)
{

}

/**************************************
**  Fixture_Information
**************************************/
void Fixture_Information(void)
{
    uint32_t CpuID[3] = {0};
    uint32_t CPU_IdCode;
    uint16_t Flash_Size;
    float	SoftVersion = SOFT_VERSION;

    printf("COPYRIGHT(C):SF-Tek\r\n");
    printf("======================================\r\n");
    printf("MOD:%s\r\nDate:%s\r\n",STATION_INFO,VERINFO);
    printf("UART Baud rate:%d,(8,1,N)\r\n",BAUD_RATE1);
    /* CPU_ID  Flash*/

    CpuID[0] = *(uint32_t*)(0x1FFF7A10);
    CpuID[1] = *(uint32_t*)(0x1FFF7A14);
    CpuID[2] = *(uint32_t*)(0x1FFF7A18);
    CPU_IdCode = *(__IO uint32_t*)(0xE0042000);
    Flash_Size = *(__IO uint32_t*)(0x1FFF7A22);
    printf("CPU-ID:%X-%X-%X\r\n",CpuID[0],CpuID[1],CpuID[2]);
    printf("CPU:%03X %04X, Flash size = %d KB\r\n",CPU_IdCode&0xFFF0,CPU_IdCode>>16,Flash_Size);
    printf("CLK:SystemCore = %d MHz\r\n",SystemCoreClock/1000000);
    printf("Software version:V%.1f\r\n",(float)(SoftVersion/10));
    printf("======================================\r\n");
}

void Help(void)
{
    uint8_t i = 0;
    Fixture_Information();//V1.3 add 2023-02-27
    printf("This is the help command:\r\n");
    printf("%d.PC_READY\r\n",++i);
    printf("%d.START_TEST\r\n",++i);
    printf("%d.GET_RESULT\r\n",++i);
    printf("%d.RF_START_TEST\r\n",++i);
    printf("%d.CAT9555_CHECK\r\n",++i);
    printf("%d.END_TEST\r\n",++i);
    printf("%d.SYSTEM_RESET\r\n",++i);
    printf("%d.GET_3V3_VOL\r\n",++i);
    printf("%d.GET_5V_VOL\r\n",++i);
    printf("%d.GET_1V2_VOL\r\n",++i);
    printf("%d.GET_D4_VOL\r\n",++i);
    printf("%d.GET_DUT_VOL\r\n",++i);
    printf("%d.GET_ADC0_VOL\r\n",++i);
    printf("%d.PP5V_POWER_ON\r\n",++i);
    printf("%d.PP5V_POWER_OFF\r\n",++i);
    printf("%d.SWITCH_BOARD_POWER_ON\r\n",++i);
    printf("%d.SWITCH_BOARD_POWER_OFF\r\n",++i);
    printf("%d.RF_BOARD_POWER_ON\r\n",++i);
    printf("%d.RF_BOARD_POWER_OFF\r\n",++i);
    printf("%d.SIGNAL_CONNECT_ON\r\n",++i);
    printf("%d.SIGNAL_CONNECT_OFF\r\n",++i);
    printf("======================================\r\n");
}
