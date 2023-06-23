#include "modebus.h"

void modbus_init(t_modbus* mb) {
	mb->usart->data = malloc(sizeof(mb->pack.slave_address) + sizeof(mb->pack.func_code) +
			sizeof(mb->pack.data) * MODBUS_DATA_BUF_SIZE + sizeof(mb->pack.crc_low) * 2);
	usart_init(mb->usart);
	modbus_tim_init(mb->timer);
}

void modbus_tim_init(TIM_TypeDef* tim) {
	if (tim == TIM1) {

	}
}

uint8_t MODBUS_TX_RTU(t_modbus* mb) {
//	mb->usart->data = &(mb->pack.data);
  	mb->usart->len = mb->pack.len;
	USART_TX(mb->usart);
}

uint8_t MODBUS_RX_RTU(t_modbus* mb) {
//	mb->usart->data = &(mb->pack.data);
	USART_RX(mb->usart);
	mb->pack.len = mb->usart->len;
}

void USART1_IRQHandler(void) {
	/* По завершению приема передачи */
	if (USART1->SR & USART_SR_RXNE) {
		/* читаем DR для сброса флага */
		MODBUS_RX_RTU(&modbus);
	}

	/* По завершению отправки передачи */
//	if ((USART1->SR & USART_SR_TC) == USART_SR_TC) {
//		/* записываем в DR для сброса флага */
//		MODBUS_TX_RTU(&modbus);
//
//	}
}
