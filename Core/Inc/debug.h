#ifndef DEBUG_H
#define DEBUG_H_

extern UART_HandleTypeDef huart1;

void serial_send_4(void);
void serial_send_3(void);
void serial_send_2(void);
void serial_send (uint16_t * );

void debug_function_1(void);
void debug_function_2 (void);
void debug_function_3(void);

#endif /* DEBUG_H */