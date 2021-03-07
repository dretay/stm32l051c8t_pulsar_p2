#include "Adc.h"

#if defined __STM32L0xx_HAL_ADC_H
extern ADC_HandleTypeDef hadc;
extern void EXT_MX_ADC_Init();
#endif

volatile u16 ADC1ConvertedValues[ADC_DMA_SIZE] = { 0 };

#define VREFINT_CAL_ADDR ((uint16_t*)((uint32_t)0x1FF80078))
#define ADC_BUFFER_SIZE ((uint8_t)1)
extern TIM_HandleTypeDef htim6;

static inline unsigned short adc_to_voltage(unsigned short reading)
{
    static const unsigned long range_12_bits = 4096;
    static const unsigned long vdda = 3000;
    return ((reading * vdda) / range_12_bits);
}
static void poll()
{
    u32 vcal = 3000;
    u32 meas = ADC1ConvertedValues[0];
    u32 cal = *VREFINT_CAL_ADDR;
    u32 vmeas = vcal * cal / meas;
    //	uint16_t voltage = (3000 * (*VREFINT_CAL_ADDR)) / meas;
    app_log_info("voltage: %d", adc_to_voltage(meas));
}
static void ADC_Sequence_Powerhungry_Channels(void)
{
#if defined __STM32L0xx_HAL_ADC_H
    ADC_ChannelConfTypeDef sConfig;
    sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
    sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
        app_log_debug("unable to enable temp adc channel");
    }
    sConfig.Channel = ADC_CHANNEL_VREFINT;
    sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
        app_log_debug("unable to enable vrefint adc channel");
    }
#endif
}
static void start()
{
#if defined __STM32L0xx_HAL_ADC_H
    ADC_Sequence_Powerhungry_Channels();
    if (HAL_ADC_Start_DMA(&hadc, (uint32_t*)ADC1ConvertedValues, ADC_DMA_SIZE) != HAL_OK) {
        app_log_error("could not start ADC poll");
    }
    HAL_TIM_Base_Start(&htim6);
    HAL_GPIO_WritePin(LIGHT_SENSE_GPIO_Port, LIGHT_SENSE_Pin, GPIO_PIN_SET);
    app_log_debug("ADC Started");
#endif
}
static void ADC_Desequence_Powerhungry_Channels(void)
{
#if defined __STM32L0xx_HAL_ADC_H
    ADC_ChannelConfTypeDef sConfig;
    sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
    sConfig.Rank = ADC_RANK_NONE;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
        app_log_debug("unable to disable temp adc channel");
    }
    sConfig.Channel = ADC_CHANNEL_VREFINT;
    sConfig.Rank = ADC_RANK_NONE;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
        app_log_debug("unable to disable vrefint adc channel");
    }
#endif
}

static void stop()
{
#if defined __STM32L0xx_HAL_ADC_H
    if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK) {
        app_log_error("could not stop ADC poll");
    }
    ADC_Desequence_Powerhungry_Channels();
    HAL_TIM_Base_Stop(&htim6);
    HAL_GPIO_WritePin(LIGHT_SENSE_GPIO_Port, LIGHT_SENSE_Pin, GPIO_PIN_RESET);
    ADC1ConvertedValues[0] = 0;
    ADC1ConvertedValues[1] = 0;
    ADC1ConvertedValues[2] = 0;
    app_log_debug("ADC Stopped");
#endif
}
static void init()
{
#if defined __STM32L0xx_HAL_ADC_H
    //	// todo: read this to get adc to work with low power mode
    //	//https: //hackaday.io/project/134018-coin-cell-powered-temperaturehumidity-display/log/145444-adc-voltage-measurement
    if (HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED) != HAL_OK) {
        app_log_error("failed to calibrate adc");
    }
    start();

    //async clocks have the advantage os max clock frequency
    //
    //The total conversion time is calculated as follows :
    //	tCONV = Sampling time + 12.5 x ADC clock cycles

    //Example : With ADC_CLK = 16 MHz and a sampling time of 1.5 ADC clock cycles :
    //	tCONV = 1.5 + 12.5 = 14 ADC clock cycles = 0.875 µs
#endif
}
static u32 get_brightness()
{
    u32 vcal = 3000;
    u32 meas = ADC1ConvertedValues[0];
    u32 cal = *VREFINT_CAL_ADDR;
    u32 vmeas = vcal * cal / meas;
    return vmeas;
}

const struct adc Adc = {
    .init = init,
    .poll = poll,
    .start = start,
    .stop = stop,
    .get_brightness = get_brightness,
};
