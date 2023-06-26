#include "usart.h"

void usart_init(t_usart* usart) {

	if (usart->usart_type == USART1) {
		/*
		 * For STM32H405:
		 * * PA10 - RX;
		 * * PA9 - TX;
		 * * PA8 - CK
		 * */
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	/* GPIOA Enable */
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;	/* USART1 Enable */

		GPIOA->MODER |= GPIO_MODER_MODE10_1
						| GPIO_MODER_MODE9_1
						| GPIO_MODER_MODE8_1; /* Alternate function */

		GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1;
		GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;
		GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1; //High speed

		GPIOA->AFR[1] |= GPIO_AFRH_AFRH2_0
						| GPIO_AFRH_AFRH2_1
						| GPIO_AFRH_AFRH2_2; //Alternate function for PA10 - AF7 (USART1)
		GPIOA->AFR[1] |= GPIO_AFRH_AFRH1_0
						| GPIO_AFRH_AFRH1_1
						| GPIO_AFRH_AFRH1_2; //Alternate function for PA9 - AF7 (USART1)
		GPIOA->AFR[1] |= GPIO_AFRH_AFRH0_0
						| GPIO_AFRH_AFRH0_1
						| GPIO_AFRH_AFRH0_2; //Alternate function for PA8 - AF7 (USART1)
	}

	usart_config(usart);
}

void usart_config(t_usart *usart) {

	/* Set default functions */
//	if (usart->rx_func == NULL) {
//		usart->rx_func = USART_RX_RTU;
//	}
//	if (usart->tx_func == NULL) {
//		usart->tx_func = USART_TX_RTU;
//	}
	/* ~Set default functions~ */

	/* Speed configuration */

	usart->usart_type->BRR |= f2BRR(usart->usart_type, usart->friq);
//	usart->usart_type->BRR |= 0x271;

	/* ~Speed configuration~ */

	/* Data Direction configuration */
	if (usart->data_dir == RX_MODE) {
		usart->usart_type->CR1 |= USART_CR1_RE; /* Rx Only Enable */
	} else if (usart->data_dir == TX_MODE) {
		usart->usart_type->CR1 |= USART_CR1_TE; /* Tx only Enable */
	} else if (usart->data_dir == RX_TX_MODE) {
		usart->usart_type->CR1 |= USART_CR1_TE | USART_CR1_RE; /* Rx, Tx Enable */
	}
	/* ~Data Direction configuration~ */

	/* Word length configuration */

	if (usart->word_length == BIT_8) {
		usart->usart_type->CR1 &= ~USART_CR1_M;
	} else {
		usart->usart_type->CR1 |= USART_CR1_M;
	}

	/* ~Word length configuration~ */

	/* Interrupt configuration */

	usart_interrupt_en(usart);

	/* ~Interrupt configuration~ */

	/* USART enable */
	if (usart->usart_en == USART_ENABLE) {
		usart->usart_type->CR1 |= USART_CR1_UE;
	}
	/* ~USART enable~ */
}

void usart_interrupt_en(t_usart *usart) {

	if (usart->intrpt_en == RXNE_INTERRUPT_ENABLE) {
		usart->usart_type->CR1 |= USART_CR1_RXNEIE;
	} else if (usart->intrpt_en == TXE_INTERRUPT_ENABLE) {
		usart->usart_type->CR1 |= USART_CR1_TXEIE;
	} else if (usart->intrpt_en == RXNE_TXE_INTERRUPT_ENABLE) {
		usart->usart_type->CR1 |= USART_CR1_RXNEIE;
		usart->usart_type->CR1 |= USART_CR1_TXEIE;
	}

	if (usart->intrpt_compl_en == TXC_INTERRUPT_ENABLE) {
		usart->usart_type->CR1 |= USART_CR1_TCIE;
	}

	if (usart->dma_en == RXE_DMA_ENABLE) {
		usart->usart_type->CR3 |= USART_CR3_DMAR;
	} else if (usart->dma_en == TXE_DMA_ENABLE) {
		usart->usart_type->CR3 |= USART_CR3_DMAT;
	} else if (usart->dma_en == RXE_TXE_DMA_ENABLE) {
		usart->usart_type->CR3 |= USART_CR3_DMAR;
		usart->usart_type->CR3 |= USART_CR3_DMAT;
	}

	if ((usart->usart_type == USART1) && (usart->intrpt_perm == INTERRUPT_PERMISSION_ENABLE)) {
		NVIC_EnableIRQ (USART1_IRQn);
	}
}

uint8_t USART_TX(t_usart* usart) {
	uint8_t i = 0;
//	GPIOA->BSRR |= GPIO_BSRR_BS4;
	while (i < usart->len) {
		while ((usart->usart_type->SR & USART_SR_TXE) != USART_SR_TXE);
		usart->usart_type->DR = (uint8_t)usart->data[i];
		i++;
	}
//	GPIOA->BSRR |= GPIO_BSRR_BR4;

	return 0;
}

uint8_t USART_RX(t_usart* usart) {
	uint8_t i = 0;
	while ((usart->usart_type->SR & USART_SR_RXNE) == USART_SR_RXNE) {
		usart->data[i] = usart->usart_type->DR;
		i++;
	}
	if (i > 0){
		usart->len = i;
		USART_TX(usart);
	}
}

float BRR2f(USART_TypeDef* usart) {
	return (usart->BRR & 0xfff0) + ((usart->BRR & 0x000f) / 16);
}

uint16_t f2BRR(USART_TypeDef* usart, float val) {
	uint32_t usart_clock = HAL_RCC_GetSysClockFreq() / 1;
	return usart_clock / val;
}

