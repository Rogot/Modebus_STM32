#ifndef MODEBUS_H
#define MODEBUS_H

#include "main.h"
#include "usart.h"
#include "dma.h"

#define MODBUS_DATA_BUF_SIZE	252


typedef struct MODMUS_PACKAGE {
	uint8_t slave_address; 					/* Адрес подчиненнго устройства */
	uint8_t func_code;						/* Код функции */
	uint8_t data[MODBUS_DATA_BUF_SIZE];		/* Буфер для приема/передачи данных */
	uint8_t len;							/* Размер передваемых данных главным устройством */
	uint8_t crc_high;						/* Высший регистр значения контрольной суммы */
	uint8_t crc_low;						/* Низший регистр значения контрольной суммы */
}t_modbus_pack;

typedef enum PROTOCOL_MODBUS {
	MODBUS_RTU_PROT,
	MODBUS_ASCII_PROT,
} t_prot_modbus;

typedef enum CRC_MODBUS_ENABLE {
	MODBUS_CRC_ENABLE,
	MODBUS_CRC_DISABLE,
}t_crc_modbus_enable;

typedef enum CRC_MODBUS_TYPE {
	MODBUS_CRC16_TYPE,
	MODBUS_LRC8_TYPE,
}t_crc_modbus_type;

typedef struct MODMUS_RTU {
	t_usart* usart;				/* используемый USART (протокол физического уровня) */
	TIM_TypeDef* timer;			/* используемый таймер для синхронизации протокола */
	t_dma* dma;					/* используемый DMA для сохранения данных */
	t_prot_modbus protocol;		/* используемый протокол передачи верхнего уровня (RTU/ASCII) */
	t_crc_modbus_enable crc_en;	/* Использование / неиспользование контрольнной суммы */
	t_crc_modbus_type crc_type;	/* Вид контрольной суммы */
	t_modbus_pack pack;			/* пакет данных */
}t_modbus;

extern t_modbus modbus;

/* Initialization functions */
void modbus_init(t_modbus* mb);
void modbus_tim_init(TIM_TypeDef* mb);
/* ~Initialization functions~ */

/* Transmitting and Receiving functions */

uint8_t MODBUS_TX_RTU(t_modbus* mb);
uint8_t MODBUS_RX_RTU(t_modbus* mb);

/* ~Transmitting and Receiving functions~ */

#endif //!MODEBUS_H
