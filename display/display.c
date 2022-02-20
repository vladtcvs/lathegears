#include <stdio.h>

#include "font.h"

#include "ssd1306_i2c.h"

#define SCREEN_WIDTH 128
#define MAX_SYMBOLS (SCREEN_WIDTH / FONT_WIDTH)

static struct SSD1306_State_s ssd1306;

bool display_init(uint32_t i2c, uint8_t addr,
                  void (*i2c_send_bytes)(uint32_t i2c, uint8_t addr, const uint8_t *data, size_t len, bool *ok),
                  void (*i2c_read_bytes)(uint32_t i2c, uint8_t addr, uint8_t *data, size_t len, bool *ok))
{
    ssd1306_init(&ssd1306, i2c, addr, SCREEN_WIDTH, 32, i2c_send_bytes, i2c_read_bytes);

    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 128; j++)
            ssd1306_draw_block(&ssd1306, i, j, 0x00);
    return true;
}

void display_show(const char *text, int len)
{
    int i, j;
    int pos = 0;
    for (i = 0; i < MAX_SYMBOLS; i++)
    {
        int symbol = ' ';

        if (i < len && text[i] != 0)
            symbol = text[i];

        if (symbol < 0 || symbol >= 128)
            symbol = 0;
        for (j = 0; j < FONT_WIDTH; j++)
        {
            ssd1306_draw_block(&ssd1306, 0, pos, font[symbol][j]);
            pos++;
        }
    }
}

void display_print_state(bool running, int threadid, float pitch, bool right)
{
    char buffer[MAX_SYMBOLS] = {0};
    char istate;
    char dir;
    if (running)
        istate = '*';
    else
        istate = 'S';

    if (right)
        dir = 'R';
    else
        dir = 'L';

    int pitch_i = pitch;
    int pitch_f = (pitch - pitch_i)*100;

    snprintf(buffer, MAX_SYMBOLS, "%c %2i: %2i.%02i%c", istate, threadid, pitch_i, pitch_f, dir);

    display_show(buffer, MAX_SYMBOLS);
}
