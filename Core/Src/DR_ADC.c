#include "DR_ADC.h"

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */




ADC_HandleTypeDef hadc1;
uint32_t i_offset = 0;

void MX_ADC1_Init(void)
{
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_ADCEx_Calibration_Start(&hadc1);
}

void ADC_Select_CH0 (void){
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_Select_CH1 (void){
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_Select_CH2 (void){
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_Select_CH3 (void){
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_Select_CH4 (void) {
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_4;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}


uint16_t getValue(uint8_t selection){
    uint32_t val_meas=0;
    uint32_t i_meas =0;
    uint32_t r =0;
    int16_t i=0,k=0;

    switch (selection){
        case VOUT: 
        	i_meas=0;
			for (i=0;i<20;i++){
            ADC_Select_CH4();
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1,1000);
            i_meas += HAL_ADC_GetValue(&hadc1);
            HAL_ADC_Stop(&hadc1);
            HAL_Delay(1);
			}val_meas = i_meas/20;
            val_meas = (val_meas* V_REF * RDIV_N_2 ) / (RDIV_D_2 * N_BITS);
        break;

        case VIN:
            ADC_Select_CH2();
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1,1000);
            val_meas = HAL_ADC_GetValue(&hadc1);
            HAL_ADC_Stop(&hadc1);
            val_meas = (val_meas* V_REF * RDIV_N_1 ) / (N_BITS * RDIV_D_1);
        break;

        case VINTRM:
            ADC_Select_CH3();
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1,1000);
            val_meas = HAL_ADC_GetValue(&hadc1) + i_meas;
            HAL_ADC_Stop(&hadc1);
            val_meas = (val_meas* V_REF * RDIV_N_4 ) / (N_BITS * RDIV_D_4);
        break;

        case IOUT:
        	i_meas=0;
			for (i=0;i<100;i++){
				ADC_Select_CH1();
				HAL_ADC_Start(&hadc1);
				HAL_ADC_PollForConversion(&hadc1,1000);
				i_meas = HAL_ADC_GetValue(&hadc1) + i_meas;
				HAL_ADC_Stop(&hadc1);
				HAL_Delay(1);
			}val_meas = i_meas / 100;
            HAL_Delay(5);
            i_offset = getValue(VINTRM)/2;
            val_meas = (val_meas* V_REF * RDIV_N_3 ) / (N_BITS * RDIV_D_3);
            if (val_meas < i_offset)
                val_meas = 0;
			else val_meas = (val_meas - i_offset ) * 257 / 100;
        break;
        case IIN:
			i_meas=0;
			for (i=0;i<100;i++){
				ADC_Select_CH0();
				HAL_ADC_Start(&hadc1);
				HAL_ADC_PollForConversion(&hadc1,1000);
				i_meas = HAL_ADC_GetValue(&hadc1) + i_meas;
				HAL_ADC_Stop(&hadc1);
				//HAL_Delay(1);
        	}val_meas = i_meas / 100;
			i_offset = getValue(VINTRM)/2;
			val_meas = (val_meas* V_REF * RDIV_N_2 ) / (N_BITS);
            if (val_meas < i_offset)
                val_meas = 0;
			else val_meas = (val_meas - i_offset ) * 177 / 50;
        break;
}
    return (uint16_t) val_meas;
}

