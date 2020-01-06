#include <stdint.h>
#include <stdbool.h>


#include "bsd.h"
#include <bsd_limits.h>
#include <bsd_os.h>
#include <bsd_platform.h>
#include <nrf.h>


#define BSD_OS_TRACE_IRQ          EGU2_IRQn
#define BSD_OS_TRACE_IRQ_PRIORITY 6
#define BSD_OS_TRACE_IRQ_HANDLER  EGU2_IRQHandler


static int bsd_error;
static uint8_t __attribute__((section (".bsdlib"), unused)) bsd_mem[BSD_RESERVED_MEMORY_SIZE] ;


void bsd_os_init(void) {
        NVIC_SetPriority(BSD_APPLICATION_IRQ, BSD_APPLICATION_IRQ_PRIORITY);
        NVIC_ClearPendingIRQ(BSD_APPLICATION_IRQ);
        NVIC_SetPriority(BSD_OS_TRACE_IRQ, BSD_OS_TRACE_IRQ_PRIORITY);
        NVIC_ClearPendingIRQ(BSD_OS_TRACE_IRQ);
        NVIC_EnableIRQ(BSD_APPLICATION_IRQ);
        NVIC_EnableIRQ(BSD_OS_TRACE_IRQ);
}


int32_t bsd_os_timedwait(uint32_t context, int32_t *timeout)
{
        return 0;
}

   
void bsd_os_errno_set(int err_code)
{
        bsd_error = err_code;
}


void bsd_os_application_irq_set(void)
{
        NVIC_SetPendingIRQ(BSD_APPLICATION_IRQ);
}


void bsd_os_application_irq_clear(void)
{
        NVIC_ClearPendingIRQ(BSD_APPLICATION_IRQ);
}


void bsd_os_trace_irq_set(void)
{
        NVIC_SetPendingIRQ(BSD_OS_TRACE_IRQ);
}


void bsd_os_trace_irq_clear(void)
{
        NVIC_ClearPendingIRQ(BSD_OS_TRACE_IRQ);
}


int32_t bsd_os_trace_put(const uint8_t * const p_buffer, uint32_t buf_len)
{
        return 0;
}


void BSD_OS_TRACE_IRQ_HANDLER(void)
{
        bsd_os_trace_irq_handler();
}


void BSD_APPLICATION_IRQ_HANDLER(void)
{
        bsd_os_application_irq_handler();
}
