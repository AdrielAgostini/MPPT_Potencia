// #include "PR_UART.h";

// void serial_send(uint16_t adc_values){
//     uint16_t P_in, P_out;
//     uint16_t aux;
//     uint8_t i=0;
//     uint16_t duty[2];
//     uint8_t linea_1 = {"\nPw in: "};
//     uint8_t linea_2 = {"\nPw out: "};
//     uint8_t linea_3 = {"\n|\tI_in\t|\tI_out\t|\tV_in\t|\tV_intrm\t|\tV_out\t|\n"};
//     uint8_t linea_5 = {"\n|\tduty in\t|\tduty out\t|\n"};
//     uint8_t cell_o = {"|\t"};
//     uint8_t cell_c = {"\t|"};
    
//     P_in = adc_values[IIN] * adc_values[VIN];
//     P_out = adc_values[IOUT] * adc_values[VOUT];


//     duty[0] = getduty(BUCK_IN);
//     duty[1] = getduty(BUCK_OUT);

//     /* Envio Linea 1 : Potencia entrada*/
//     HAL_UART_Transmit(&huart1, linea_1, sizeof(linea_1), 100);
//     HAL_UART_Transmit(&huart1, int8_t(P_in>8), 1, 1);
//     HAL_UART_Transmit(&huart1, int8_t(P_in), 1, 1);

//     /* Envio Linea 2 : Potencia salida*/
//     HAL_UART_Transmit(&huart1, linea_2, sizeof(linea_1), 1);
//     HAL_UART_Transmit(&huart1, int8_t(P_out>8), 1, 1);
//     HAL_UART_Transmit(&huart1, int8_t(P_out), 1, 1);

//     HAL_UART_Transmit(&huart1, linea_3, sizeof(linea_1), 100);
//     for(i=0;i<5;i++){
//         HAL_UART_Transmit(&huart1, cell_o, sizeof(cell_o), 10);
//         HAL_UART_Transmit(&huart1, int8_t(adc_values[i]>8), 1, 1);
//         HAL_UART_Transmit(&huart1, int8_t(adc_values[i]), 1, 1);
//         HAL_UART_Transmit(&huart1, cell_c, sizeof(cell_c), 10);
//     }

//     HAL_UART_Transmit(&huart1, linea_3, sizeof(linea_1), 100);
//     for(i=0;i<2;i++){
//         HAL_UART_Transmit(&huart1, cell_o, sizeof(cell_o), 10);
//         HAL_UART_Transmit(&huart1, int8_t(duty[i]>8), 1, 1);
//         HAL_UART_Transmit(&huart1, int8_t(duty[i]), 1, 1);
//         HAL_UART_Transmit(&huart1, cell_c, sizeof(cell_c), 10);
//     }

//     HAL_UART_Transmit(&huart1, "\n", 1, 10);
// }
