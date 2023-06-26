#include "dma.h"

void dma_init(t_dma *dma) {
	if (dma->dma_stream == DMA2_Stream2) {
		/*
		 * For STM32H405:
		 * * PA10 - RX;
		 * * PA9 - TX;
		 * * PA8 - CK
		 * */

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* GPIOA Enable */
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; /* Enable DMA2 */
	}

	dma->dma_stream->CR &= ~DMA_SxCR_EN;
	dma->dma_stream->CR = 0x0; /* Clear register */

  	DMA2_Stream2->CR |= DMA_SxCR_CHSEL_2;
//	dma->dma_stream->CR |= dma->dma_channel;
	dma->dma_stream->CR |= dma->dma_circ; //Circular mode enable
	dma->dma_stream->CR |= dma->dma_pl; //Priority level high
	dma->dma_stream->CR |= dma->dma_msize; // 16 bit
	dma->dma_stream->CR |= dma->dma_psize; // 16 bit
	if (dma->dma_minc) {
		dma->dma_stream->CR |= dma->dma_minc; //Memory increment mode enable
	} else {
		dma->dma_stream->CR &= ~dma->dma_minc; //Memory increment mode disable
	}
	dma->dma_stream->CR &= ~dma->dma_pinc; //Peripheral increment mode disable

	dma->dma_stream->CR |= dma->dma_intrpt_en; //Interrupt enable
	dma->dma_stream->CR |= dma->dma_intrpt_half_en; //Interrupt half enable

	dma_config(dma);
}


void dma_config(t_dma* dma){
	dma->dma_stream->PAR = (uint32_t) dma->dma_par;

	dma->dma_stream->M0AR = (uint32_t) dma->dma_m0ar;

	dma->dma_stream->NDTR = (uint32_t) dma->dma_ndtr;

	dma->dma_stream->CR |= dma->dma_en;

	if (dma->dma_stream == DMA2_Stream2 && dma->dma_intrpt_en == DMA_INTERRUPT_PERMISSION_ENABLE) {
		NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	} else if (dma->dma_stream == DMA2_Stream2 && dma->dma_intrpt_en == DMA_INTERRUPT_PERMISSION_DISABLE) {
		NVIC_EnableIRQ(~DMA2_Stream2_IRQn);
	}
}
