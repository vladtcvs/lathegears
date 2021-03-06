
#include <stdint.h>
#include "font.h"

const uint8_t font[128][FONT_WIDTH] = {
	{0x00, 0x54, 0x80, 0x04, 0xa8, }, // 0 
	{}, // 1 
	{}, // 2 
	{}, // 3 
	{}, // 4 
	{}, // 5 
	{}, // 6 
	{}, // 7 
	{}, // 8 
	{}, // 9 
	{}, // 10 
	{}, // 11 
	{}, // 12 
	{}, // 13 
	{}, // 14 
	{}, // 15 
	{}, // 16 
	{}, // 17 
	{}, // 18 
	{}, // 19 
	{}, // 20 
	{}, // 21 
	{}, // 22 
	{}, // 23 
	{}, // 24 
	{}, // 25 
	{}, // 26 
	{}, // 27 
	{}, // 28 
	{}, // 29 
	{}, // 30 
	{}, // 31 
	{0x00, 0x00, 0x00, 0x00, 0x00, }, // 32 
	{0x00, 0x00, 0xbc, 0x00, 0x00, }, // 33 
	{0x00, 0x1c, 0x00, 0x1c, 0x00, }, // 34 
	{0x28, 0xfe, 0x28, 0xfe, 0x28, }, // 35 
	{0x08, 0x54, 0xfe, 0x54, 0x20, }, // 36 
	{0x00, 0x2c, 0x10, 0x68, 0x00, }, // 37 
	{0x00, 0x6c, 0x92, 0x6c, 0x80, }, // 38 
	{0x00, 0x00, 0x1c, 0x00, 0x00, }, // 39 
	{0x00, 0x00, 0x78, 0x84, 0x00, }, // 40 
	{0x00, 0x00, 0x84, 0x78, 0x00, }, // 41 
	{0x00, 0xa8, 0x70, 0x70, 0xa8, }, // 42 
	{0x20, 0x20, 0xf8, 0x20, 0x20, }, // 43 
	{0x00, 0x00, 0xc0, 0x40, 0x00, }, // 44 
	{0x00, 0x20, 0x20, 0x20, 0x20, }, // 45 
	{0x00, 0x80, 0xc0, 0x80, 0x00, }, // 46 
	{0x00, 0xc0, 0x20, 0x10, 0x0c, }, // 47 
	{0x00, 0x78, 0x84, 0x78, 0x00, }, // 48 
	{0x00, 0x88, 0xfc, 0x80, 0x00, }, // 49 
	{0x00, 0xc8, 0xa4, 0xa4, 0x98, }, // 50 
	{0x00, 0x44, 0x94, 0x9c, 0x64, }, // 51 
	{0x00, 0x30, 0x28, 0xfc, 0x20, }, // 52 
	{0x00, 0x5c, 0x94, 0x94, 0x64, }, // 53 
	{0x00, 0x78, 0x94, 0x94, 0x60, }, // 54 
	{0x00, 0x04, 0xc4, 0x34, 0x0c, }, // 55 
	{0x00, 0x68, 0x94, 0x94, 0x68, }, // 56 
	{0x00, 0x18, 0xa4, 0xa4, 0x78, }, // 57 
	{0x00, 0x00, 0xd8, 0xd8, 0x00, }, // 58 
	{0x00, 0x00, 0xd8, 0x58, 0x00, }, // 59 
	{0x00, 0x30, 0x48, 0x84, 0x00, }, // 60 
	{0x00, 0x50, 0x50, 0x50, 0x50, }, // 61 
	{0x00, 0x84, 0x48, 0x30, 0x00, }, // 62 
	{0x00, 0x08, 0xa4, 0x18, 0x00, }, // 63 
	{0x78, 0x84, 0x32, 0x4a, 0x3c, }, // 64 
	{0x00, 0xf8, 0x24, 0x24, 0xf8, }, // 65 
	{0x00, 0xfc, 0x94, 0x94, 0x68, }, // 66 
	{0x00, 0x78, 0x84, 0x84, 0x48, }, // 67 
	{0x00, 0xfc, 0x84, 0x84, 0x78, }, // 68 
	{0x00, 0xfc, 0x94, 0x94, 0x84, }, // 69 
	{0x00, 0xfc, 0x14, 0x14, 0x04, }, // 70 
	{0x00, 0x78, 0x84, 0xa4, 0x68, }, // 71 
	{0x00, 0xfc, 0x10, 0x10, 0xfc, }, // 72 
	{0x00, 0x84, 0xfc, 0x84, 0x00, }, // 73 
	{0x00, 0x40, 0x84, 0x7c, 0x04, }, // 74 
	{0x00, 0xfc, 0x10, 0x68, 0x84, }, // 75 
	{0x00, 0xfc, 0x80, 0x80, 0x80, }, // 76 
	{0x00, 0xfc, 0x18, 0x18, 0xfc, }, // 77 
	{0x00, 0xfc, 0x18, 0x70, 0xfc, }, // 78 
	{0x00, 0x78, 0x84, 0x84, 0x78, }, // 79 
	{0x00, 0xfc, 0x24, 0x24, 0x18, }, // 80 
	{0x00, 0x78, 0xa4, 0xc4, 0x78, }, // 81 
	{0x00, 0xfc, 0x24, 0x24, 0xd8, }, // 82 
	{0x00, 0x48, 0x94, 0xa4, 0x48, }, // 83 
	{0x00, 0x04, 0xfc, 0x04, 0x00, }, // 84 
	{0x00, 0x7c, 0x80, 0x80, 0x7c, }, // 85 
	{0x00, 0x3c, 0xc0, 0xc0, 0x3c, }, // 86 
	{0x00, 0xfc, 0x60, 0x60, 0xfc, }, // 87 
	{0x00, 0xcc, 0x30, 0x30, 0xcc, }, // 88 
	{0x0c, 0x10, 0xe0, 0x10, 0x0c, }, // 89 
	{0x00, 0xc4, 0xa4, 0x94, 0x8c, }, // 90 
	{0x00, 0xfc, 0x84, 0x84, 0x00, }, // 91 
	{0x00, 0x0c, 0x10, 0x20, 0xc0, }, // 92 
	{0x00, 0x84, 0x84, 0xfc, 0x00, }, // 93 
	{0x00, 0x08, 0x04, 0x08, 0x00, }, // 94 
	{0x00, 0x00, 0x00, 0x00, 0x00, }, // 95 
	{0x00, 0x00, 0x04, 0x08, 0x00, }, // 96 
	{0x00, 0x60, 0x90, 0x90, 0xf0, }, // 97 
	{0x00, 0xfc, 0x90, 0x90, 0x60, }, // 98 
	{0x00, 0x60, 0x90, 0x90, 0x00, }, // 99 
	{0x00, 0x60, 0x90, 0x90, 0xfc, }, // 100 
	{0x00, 0x60, 0xd0, 0xb0, 0x20, }, // 101 
	{0x00, 0x20, 0xf8, 0x24, 0x08, }, // 102 
	{0x00, 0x20, 0x50, 0x50, 0xe0, }, // 103 
	{0x00, 0xfc, 0x10, 0x10, 0xe0, }, // 104 
	{0x00, 0x90, 0xf4, 0x80, 0x00, }, // 105 
	{0x00, 0x80, 0x00, 0xf4, 0x00, }, // 106 
	{0x00, 0xfc, 0x20, 0x20, 0xd0, }, // 107 
	{0x00, 0x84, 0xfc, 0x80, 0x00, }, // 108 
	{0xf0, 0x10, 0xe0, 0x10, 0xe0, }, // 109 
	{0x00, 0xf0, 0x10, 0x10, 0xe0, }, // 110 
	{0x00, 0x60, 0x90, 0x90, 0x60, }, // 111 
	{0x00, 0xf0, 0x50, 0x50, 0x20, }, // 112 
	{0x00, 0x20, 0x50, 0x50, 0xf0, }, // 113 
	{0x00, 0xf0, 0x20, 0x10, 0x20, }, // 114 
	{0x00, 0xa0, 0xb0, 0x50, 0x00, }, // 115 
	{0x00, 0x10, 0x7c, 0x90, 0x40, }, // 116 
	{0x00, 0x70, 0x80, 0x80, 0xf0, }, // 117 
	{0x00, 0x70, 0x80, 0x70, 0x00, }, // 118 
	{0x70, 0x80, 0x60, 0x80, 0x70, }, // 119 
	{0x00, 0x90, 0x60, 0x60, 0x90, }, // 120 
	{0x00, 0xb0, 0x40, 0x40, 0xf0, }, // 121 
	{0x00, 0x90, 0xd0, 0xb0, 0x90, }, // 122 
	{0x00, 0x10, 0x54, 0xaa, 0x82, }, // 123 
	{0x00, 0x00, 0xfc, 0x00, 0x00, }, // 124 
	{0x00, 0x82, 0xaa, 0x54, 0x10, }, // 125 
	{0x00, 0x08, 0x04, 0x08, 0x04, }, // 126 
	{}, // 127 
};
