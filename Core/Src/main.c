/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define DEBUG_MODE 3
#define DUTY1 	180
#define	DUTY2   250

#define L_PERIOD 50 //Titilar 1 segundo
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
//ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

uint8_t flag_led=1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
//static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void T_Led_Out(void);
void debug_function(void);
void serial_send(uint16_t *);
void serial_send2(void);
void serial_send3(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void T_Led_Out(void){
  flag_led=1;
}
void serial_send4(void){
	  char bufferTxServer[70];
	  int16_t ADC_VAL[5];
	  uint16_t duty[2];
	  int8_t k=0;
	  for (k=0;k<70;k++){
		  bufferTxServer[k] = '\0';
	  }
	  ADC_VAL[VOUT] = getValue(VOUT);
	  ADC_VAL[VIN] = getValue(VIN);
	  ADC_VAL[IOUT] = getValue(IOUT);
	  ADC_VAL[IIN] = getValue(IIN);
	  duty[0] = (getduty(BUCK_IN)*1000)/PERIOD;
	  duty[1] = (getduty(BUCK_OUT)*1000)/PERIOD;
	  sprintf(bufferTxServer, "{\"vin\":%d,\"vmed\":0,\"vout\":%d,\"cin\":%d,\"cout\":%d,\"d1\":%d,\"d2\":%d}\n",
			  ADC_VAL[VIN],
			  ADC_VAL[VOUT],
			  ADC_VAL[IIN],
			  ADC_VAL[IOUT],
			  duty[0],
			  duty[1]);
	  HAL_UART_Transmit(&huart1, bufferTxServer, strlen(bufferTxServer), 100);
}
void serial_send3(void){
  int32_t P_in = 0, P_out;
  uint16_t duty[2];
  uint32_t iout, vout;
  char bufferTxServer[30];
  
  vout = getValue(VOUT);
  iout = getValue(IOUT);
  P_out = iout * vout / 1000;
  duty[0] = getduty(BUCK_IN) * 100 / PERIOD;
  duty[1] = getduty(BUCK_OUT) * 100 / PERIOD;

	sprintf(bufferTxServer, "\n%d  %d  %d  %d\n", iout, vout, P_out, duty[1]);
  HAL_UART_Transmit(&huart1, bufferTxServer, sizeof(bufferTxServer), 100);
}



void serial_send2(void){
  int32_t P_in = 0, P_out;
  uint16_t duty[2];
  uint32_t iin, vi;
  char bufferTxServer[30];
  
  vi = getValue(VIN);
  iin = getValue(IIN);
  P_in = vi * iin / 1000;
  duty[0] = getduty(BUCK_IN);
  duty[1] = getduty(BUCK_OUT);

	sprintf(bufferTxServer, "\n%d  %d  %d  %d\n", iin, vi, P_in, duty[0]);
  HAL_UART_Transmit(&huart1, bufferTxServer, sizeof(bufferTxServer), 1000);
}

void debug_function(void){
  int16_t ADC_VAL[5];  
  TIM3->CCR1 = DUTY1;
  TIM3->CCR2 = DUTY2;
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
 // ADC_VAL[VOUT] = getValue(VOUT);
  //ADC_VAL[VIN] = getValue(VIN);
  ADC_VAL[VINTRM] = getValue(VINTRM);
  //ADC_VAL[IOUT] = getValue(IOUT);
  ADC_VAL[IIN] = getValue(IIN);

  serial_send(ADC_VAL);
}

void serial_send(uint16_t adc_values[5]){
  uint32_t P_in, P_out;
  uint16_t duty[2];
  char bufferTxServer[15] = {"\0"} ;

  //P_in = adc_values[IIN] * adc_values[VIN];
  //P_out = adc_values[IOUT] * adc_values[VOUT];


     duty[0] = getduty(BUCK_IN);
     duty[1] = getduty(BUCK_OUT);

//bufferTxServer[97] = '\n';
//bufferTxServer[98] = '\n';
    // uint32_t P_in, P_out;
    // uint16_t aux;
    // uint8_t i=1;
    // uint16_t duty[2];
    // uint8_t linea_1[] = {"\nPw in: "};
    // uint8_t linea_2 = {"\nPw out: "};
    // uint8_t linea_3 = {"\n|\tI_in\t|\tI_out\t|\tV_in\t|\tV_intrm\t|\tV_out\t|\n"};
    // uint8_t linea_5 = {"\n|\tduty in\t|\tduty out\t|\n"};
    // uint8_t cell_o = {"|\t"};
    // uint8_t cell_c = {"\t|"};
    
/*
    sprintf(bufferTxServer, "Vout: %d\nVin: %d\nVmed: %d\nIout: %d\nIin: %d\nduty_in: %d\nduty_out %d\n", adc_values[0],
          adc_values[1],adc_values[2],adc_values[3],adc_values[4],duty[0],duty[1]
          );
          */
	sprintf(bufferTxServer, "\n%d  %d\n",adc_values [VINTRM],adc_values[IIN]);
    HAL_UART_Transmit(&huart1, bufferTxServer, sizeof(bufferTxServer), 100);
    // P_in = adc_values[IIN] * adc_values[VIN];
    // P_out = adc_values[IOUT] * adc_values[VOUT];


    // duty[0] = getduty(BUCK_IN);
    // duty[1] = getduty(BUCK_OUT);

    //  HAL_UART_Transmit(&huart1, &i, 1, 1000);
    //  /* Envio Linea 1 : Potencia entrada*/
    //  HAL_UART_Transmit(&huart1, linea_1, sizeof(linea_1), 1000);
    //  HAL_UART_Transmit(&huart1, &P_in, 1, 1);


    // /* Envio Linea 2 : Potencia salida*/
    // HAL_UART_Transmit(&huart1, linea_2, sizeof(linea_1), 1);
    // HAL_UART_Transmit(&huart1, &P_out, 1, 1);


    // HAL_UART_Transmit(&huart1, linea_3, sizeof(linea_1), 50);
    // for(i=0;i<5;i++){
    //     HAL_UART_Transmit(&huart1, cell_o, sizeof(cell_o), 5);
    //     HAL_UART_Transmit(&huart1, adc_values[i], 1, 1);
    //     HAL_UART_Transmit(&huart1, cell_c, sizeof(cell_c), 5);
    // }

    // HAL_UART_Transmit(&huart1, linea_3, sizeof(linea_1), 50);
    // for(i=0;i<2;i++){
    //     HAL_UART_Transmit(&huart1, cell_o, sizeof(cell_o), 5);
    //     HAL_UART_Transmit(&huart1, duty[i], 1, 1);
    //     HAL_UART_Transmit(&huart1, cell_c, sizeof(cell_c), 5);
    // }

    // HAL_UART_Transmit(&huart1, "\n", 1, 10);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  BUCK_init ();
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /*
    TIM3->CCR1 = DUTY1;
	  TIM3->CCR2 = DUTY2;
    */
	  if (DEBUG_MODE == 1){
		  if (flag_led == 1){
			  debug_function();
			  flag_led = 0;
			  TimerStart(1,L_PERIOD,&T_Led_Out);
    }}
	  else if (DEBUG_MODE == 2){
		  if (flag_led == 1){

			  Mde_MPPT_In();
			  serial_send2();
			  flag_led = 0;
			  TimerStart(1,L_PERIOD,&T_Led_Out);
		  }
    }
  else if (DEBUG_MODE == 3){
    if (flag_led == 1){
    	TIM3->CCR1 = DUTY1;
			  Mde_MPPT_Out();
			  //serial_send4();
			  flag_led = 0;
			  TimerStart(1,L_PERIOD,&T_Led_Out);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
  }}
  else{
	  Mde_MPPT_Out();

	}
    /* Prueba Titilar LED */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  TimerEvent();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
// static void MX_ADC1_Init(void)
// {

//   /* USER CODE BEGIN ADC1_Init 0 */

//   /* USER CODE END ADC1_Init 0 */

//   ADC_ChannelConfTypeDef sConfig = {0};

//   /* USER CODE BEGIN ADC1_Init 1 */

//   /* USER CODE END ADC1_Init 1 */

//   /** Common config
//   */
//   hadc1.Instance = ADC1;
//   hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
//   hadc1.Init.ContinuousConvMode = DISABLE;
//   hadc1.Init.DiscontinuousConvMode = DISABLE;
//   hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
//   hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
//   hadc1.Init.NbrOfConversion = 5;
//   if (HAL_ADC_Init(&hadc1) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /** Configure Regular Channel
//   */
//   sConfig.Channel = ADC_CHANNEL_0;
//   sConfig.Rank = ADC_REGULAR_RANK_1;
//   sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
//   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /** Configure Regular Channel
//   */
//   sConfig.Channel = ADC_CHANNEL_1;
//   sConfig.Rank = ADC_REGULAR_RANK_2;
//   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /** Configure Regular Channel
//   */
//   sConfig.Channel = ADC_CHANNEL_2;
//   sConfig.Rank = ADC_REGULAR_RANK_3;
//   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /** Configure Regular Channel
//   */
//   sConfig.Channel = ADC_CHANNEL_3;
//   sConfig.Rank = ADC_REGULAR_RANK_4;
//   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /** Configure Regular Channel
//   */
//   sConfig.Channel = ADC_CHANNEL_4;
//   sConfig.Rank = ADC_REGULAR_RANK_5;
//   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//   {
//     Error_Handler();
//   }
//   /* USER CODE BEGIN ADC1_Init 2 */

//   /* USER CODE END ADC1_Init 2 */

// }

// /**
//   * @brief TIM3 Initialization Function
//   * @param None
//   * @retval None
//   */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 360;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 150;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 0;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();   
  __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
