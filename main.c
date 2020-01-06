#include <stdint.h>
#include <stdbool.h>


#include "bsd.h"


#include "nrf.h"


extern void board_init(void);

int main(void)
{
        board_init();
        
        int retval = bsd_init();

        if (retval != 0) {
                while (1) {;}
        }

        while (1) {}
        return 0;
}