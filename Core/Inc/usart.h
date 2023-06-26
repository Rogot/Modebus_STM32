#ifndef USART_H
#define USART_H

#include "main.h"
#include "malloc.h"

typedef enum USART_TRANSMISSON_MODE {
	ASYNCHRONOUS,
	SYNCHRONOUS,
} t_usart_trans_mode;

typedef enum USART_WORD_LENGTH {
	BIT_8,
	BIT_9,
} t_usart_word_length;

typedef enum USART_DATA_DIRECTION {
	RX_MODE,
	TX_MODE,
	RX_TX_MODE,
} t_usart_data_dir;

typedef enum USART_INTERRUPT_ENABLE {
	RXNE_INTERRUPT_DISABLE,
	TXE_INTERRUPT_DISABLE,
	RXNE_TXE_INTERRUPT_DISABLE,
	RXNE_INTERRUPT_ENABLE,
	TXE_INTERRUPT_ENABLE,
	RXNE_TXE_INTERRUPT_ENABLE,
} t_usart_interrupt_enable;

typedef enum USART_INTERRUPT_COMPLETE{
	TXC_INTERRUPT_DISABLE,
	TXC_INTERRUPT_ENABLE,
} t_usart_interrupt_complete_en;

typedef enum USART_DMA_INTERRUPT_ENABLE {
	RXE_DMA_DISABLE,
	TXE_DMA_DISABLE,
	RXE_TXE_DMA_DISABLE,
	RXE_DMA_ENABLE,
	TXE_DMA_ENABLE,
	RXE_TXE_DMA_ENABLE,
} t_usart_dma_enable;

typedef enum USART_PERMISSION_INTERRUPT {
	INTERRUPT_PERMISSION_DISABLE,
	INTERRUPT_PERMISSION_ENABLE,
} t_usart_permis_interrupt;

typedef enum USART_ENABLE {
	USART_DISABLE,
	USART_ENABLE,
} t_usart_enable;

typedef struct USART {
	USART_TypeDef* usart_type;
	t_usart_data_dir data_dir;
	t_usart_trans_mode tran_mode;
	t_usart_word_length word_length;
	t_usart_enable usart_en;
	t_usart_interrupt_enable intrpt_en;
	t_usart_interrupt_complete_en intrpt_compl_en;
	t_usart_dma_enable dma_en;
	t_usart_permis_interrupt intrpt_perm;
	float friq; 	/* in BOD values */
	uint16_t len;
	uint8_t* data;
	void (*rx_func)(struct USART*);
	void (*tx_func)(struct USART*);
}t_usart;

/* Initialization functions */
void usart_init(t_usart* usart);
void usart_config(t_usart* usart);
void usart_interrupt_en(t_usart* usart);
/* ~Initialization functions~ */

/* Transmitting and Receiving functions */

uint8_t USART_TX(t_usart* usart);
uint8_t USART_RX(t_usart* usart);

/* ~Transmitting and Receiving functions~ */

/* Utils */
float BRR2f(USART_TypeDef* usart);
uint16_t f2BRR(USART_TypeDef* usart, float val);
/* ~Utils~ */

#endif //!USART_H
