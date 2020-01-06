#include <stdint.h>
#include <stdbool.h>

#include <nrf.h>


#define NRFX_PERIPHERAL_ID_GET(base_addr) \
	(uint8_t)((uint32_t)(base_addr) >> 12)


void board_init(void)
{
        for (uint8_t i = 0; i < 32; i++) {
		NRF_SPU_S->RAMREGION[i].PERM = 0x107;
	}

        NRF_CLOCK_S->LFCLKSRC = CLOCK_LFCLKSRCCOPY_SRC_LFRC << CLOCK_LFCLKSRC_SRC_Pos;
	NRF_CLOCK_S->EVENTS_LFCLKSTARTED  = 0;
        NRF_CLOCK_S->TASKS_LFCLKSTART = 1;
        while (NRF_CLOCK_S->EVENTS_LFCLKSTARTED == 0);
        NRF_CLOCK_S->EVENTS_LFCLKSTARTED = 0;

        NRF_SPU_S->PERIPHID[NRFX_PERIPHERAL_ID_GET(NRF_POWER_NS)].PERM = 0x80000102;
        NRF_SPU_S->PERIPHID[NRFX_PERIPHERAL_ID_GET(NRF_POWER_S)].PERM = 0;
        NRF_SPU_S->PERIPHID[NRFX_PERIPHERAL_ID_GET(NRF_IPC_S)].PERM = 0x80000102;
}