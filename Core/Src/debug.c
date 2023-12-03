#include "main.h"
#include <string.h>
#include "debug.h"

#define DUTY1 180
#define DUTY2 180

void serial_send_4(void){
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

void serial_send_3(void){
  uint16_t duty[2];
  uint32_t iout, vout;
  uint32_t P_out;
  char bufferTxServer[30];
  
  vout = getValue(VOUT);
  iout = getValue(IOUT);
  P_out = iout * vout / 1000;
  duty[0] = getduty(BUCK_IN) * 100 / PERIOD;
  duty[1] = getduty(BUCK_OUT) * 100 / PERIOD;

  sprintf(bufferTxServer, "\n%d  %d  %d  %d\n", iout, vout, P_out, duty[1]);
  HAL_UART_Transmit(&huart1, bufferTxServer, sizeof(bufferTxServer), 100);
}

void serial_send_2(void){
  uint16_t duty[2];
  uint32_t iin, vi;
  uint32_t P_in;
  char bufferTxServer[30];
  
  vi = getValue(VIN);
  iin = getValue(IIN);
  P_in = vi * iin / 1000;
  duty[0] = getduty(BUCK_IN);
  duty[1] = getduty(BUCK_OUT);

  sprintf(bufferTxServer, "\n%d  %d  %d  %d\n", iin, vi, P_in, duty[0]);
  HAL_UART_Transmit(&huart1, bufferTxServer, sizeof(bufferTxServer), 1000);
}

void serial_send(uint16_t adc_values[5]){
  char bufferTxServer[15] = {"\0"} ;

  sprintf(bufferTxServer, "\n%d  %d\n",adc_values [VINTRM],adc_values[IIN]);
  HAL_UART_Transmit(&huart1, bufferTxServer, sizeof(bufferTxServer), 100);
}



void debug_function_1(void){
  int16_t ADC_VAL[5];  
  TIM3->CCR1 = DUTY1;
  TIM3->CCR2 = DUTY2;
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
  ADC_VAL[VINTRM] = getValue(VINTRM);
  ADC_VAL[IIN] = getValue(IIN);
  serial_send(ADC_VAL);
}

void debug_function_2 (void){
    Mde_MPPT_In();
    serial_send_2();
}

void debug_function_3(void){
    TIM3->CCR1 = DUTY1;
    Mde_MPPT_Out();
}



