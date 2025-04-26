#include "DebugLog.h"
#include <stdio.h>

void print_hex_table(uint8_t *data, uint16_t len)
{
#if DBG_ENABLE
    //打印标题
    PRINT_ANSI_COLOR(ANSI_COLOR_CYAN);
    printf("     ");
    for(size_t i = 0; i < 0x10; i++)
    {
        printf("%02X ", (unsigned int) i);
    }
    PRINT_ANSI_COLOR(ANSI_COLOR_RESET);
    printf("\n");
    size_t rows = (len + 15) / 16;
    //计算行
    for(size_t i = 0; i < rows; i++)
    {
        PRINT_ANSI_COLOR(ANSI_COLOR_CYAN);
        printf("%04X ", (unsigned int) i * 16);

        PRINT_ANSI_COLOR(ANSI_COLOR_MAGENTA);
        size_t j;
        for(j = 0; j < 16 && i * 16 +j < len; j++)
        {
            printf("%02X ", data[i * 16 + j]);
        }

        for(; j < 16; j++)
        {
            printf("   ");
        }

        printf("\n");
        PRINT_ANSI_COLOR(ANSI_COLOR_RESET);
    }
#endif
}
