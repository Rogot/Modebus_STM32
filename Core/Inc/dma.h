#ifndef DMA_H
#define DMA_H

#include "main.h"

#define DMA_CH_0			0x000
#define DMA_CH_1 			DMA_SxCR_CHSEL_0
#define DMA_CH_2 			DMA_SxCR_CHSEL_1
#define DMA_CH_3 			DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1
#define DMA_CH_4 			DMA_SxCR_CHSEL_2
#define DMA_CH_5 			DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_2
#define DMA_CH_6 			DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_2
#define DMA_CH_7 			DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_2

typedef enum DMA_PERMISSION_INTERRUPT {
	DMA_INTERRUPT_PERMISSION_DISABLE,
	DMA_INTERRUPT_PERMISSION_ENABLE,
} t_dma_permis_interrupt;

typedef enum DMA_DIRECTION {
	DMA_PER_TO_MEM = DMA_SxCR_DIR_0,
	DMA_MEM_TO_PER = DMA_SxCR_DIR_1,
	DMA_MEM_TO_MEM = DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1,
} t_dma_dir;

typedef enum DMA_CIRCULAR_MODE{
	DMA_CIRC_DISABLE = 0,
	DMA_CIRC_ENABLE = DMA_SxCR_CIRC,
} t_dma_circ;

typedef enum DMA_PRIORITY_LEVEL{
	DMA_PRIORITY_LEVEL_LOW = 0,
	DMA_PRIORITY_LEVEL_MEDIUM = DMA_SxCR_PL_0,
	DMA_PRIORITY_LEVEL_HIGH = DMA_SxCR_PL_1,
	DMA_PRIORITY_LEVEL_VERY_HIGH = DMA_SxCR_PL_0 | DMA_SxCR_PL_1
} t_dma_priot_lvl;

typedef enum DMA_DATA_SIZE{
	DMA_BYTE_SIZE = 0,
	DMA_HALF_WORD_SIZE = DMA_SxCR_PSIZE_0,
	DMA_WORD_SIZE = DMA_SxCR_PSIZE_1,
} t_dma_data_size;

typedef enum DMA_INCREMENT_ENABLE {
	DMA_INCREMENT_DISABLE = 0,
	DMA_INCREMENT_ENABLE,
} t_dma_incrmt_en;

typedef enum DMA_INTERRUPT_TRAN_COMP_ENABLE {
	DMA_INTERRUPT_TRAN_COMP_DISABLE = 0,
	DMA_INTERRUPT_TRAN_COMP_ENABLE,
} t_dma_intrpt_tran_com_en;

typedef enum DMA_INTERRUPT_HALF_TRAN_COMP_ENABLE {
	DMA_INTERRUPT_HALF_TRAN_COMP_DISABLE = 0,
	DMA_INTERRUPT_HALF_TRAN_COMP_ENABLE,
} t_dma_intrpt_half_tran_com_en;

typedef enum DMA_ENABLE {
	DMA_DISABLE = 0,
	DMA_ENABLE,
} t_dma_en;

typedef struct DMA {
	DMA_TypeDef* dma_type;
	DMA_Stream_TypeDef* dma_stream;
	uint8_t dma_channel;
	t_dma_dir dma_dir;
	t_dma_circ dma_circ;
	t_dma_priot_lvl dma_pl;
	t_dma_data_size dma_psize;
	t_dma_data_size dma_msize;
	t_dma_incrmt_en dma_minc;
	t_dma_incrmt_en dma_pinc;
	t_dma_intrpt_tran_com_en dma_intrpt_en;
	t_dma_intrpt_half_tran_com_en dma_intrpt_half_en;
	uint32_t* dma_par;
	uint32_t* dma_m0ar;
	uint32_t* dma_m1ar;
	uint32_t dma_ndtr;
	t_dma_en dma_en;
	t_dma_permis_interrupt dma_permis_intrpt_en;
}t_dma;

void dma_init(t_dma* dma);
void dma_config(t_dma* dma);

#endif //!DMA_H
