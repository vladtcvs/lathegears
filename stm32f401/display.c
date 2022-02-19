#include "config.h"

#include "ssd1306_i2c.h"
#include "driver_i2c.h"

static struct SSD1306_State_s ssd1306;

bool display_init(uint32_t i2c, uint8_t addr)
{
    ssd1306_init(&ssd1306, i2c, addr, 128, 32, i2c_send_bytes, i2c_read_bytes);

    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 128; j++)
            ssd1306_draw_block(&ssd1306, i, j, 0xCC);
    return true;
}
