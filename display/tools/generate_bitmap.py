from bdflib import reader
import sys

import numpy as np

def convert_glyph(glyph, W, H):
    bitmap = np.zeros((H, W))
    w = glyph.bbW
    h = glyph.bbH
    x = glyph.bbX
    y = glyph.bbY

    #print("name = %s" % glyph.name)
    #print("w = %i, h = %i" % (w, h))
    #print("x = %i, y = %i" % (x, y))

    for yp in range(0, h):
        by = H - y - yp - 1
        for xp in range(0, w):
            bx = W - 1 - x - xp
            data = glyph.data[yp]
            bit = (data >> xp) & 1
            if (bx >= 0 and by >= 0 and bx < W and by < H):
                bitmap[by,bx] = bit
    return bitmap

bdfname = sys.argv[1]
output_c = sys.argv[2]

with open(bdfname, "rb") as f:
    font = reader.read_bdf(f)

print("Font size: %i" % font.ptSize)

if font.ptSize != 8:
    print("Font MUST be 8 pixel height!")
    sys.exit()

height = 8
width = 5

glyphs = {}

for code in font.codepoints():
    if code <= 128:
        glyph = font[code]
        glyphs[code] = convert_glyph(glyph, width, height).transpose()

for code in glyphs:
    glyph = glyphs[code]
#    print("%i \"%c\"" % (code, chr(code)))
#    print(glyph)
    glyphbytes = []
    for col in range(glyph.shape[0]):
        byte = 0
        for row in range(glyph.shape[1]):
            byte += int(glyph[col, row] * (2 ** row))
        glyphbytes.append(byte)
    glyphs[code] = glyphbytes


code = """
#include <stdint.h>
#include "font.h"

const uint8_t font[128][FONT_WIDTH] = {\n"""

for i in range(128):
    code += "\t{"
    if i in glyphs:
        glyph = glyphs[i]
        for val in glyph:
            code += "0x%02x, " % val
    code += "}, // %i \n" % (i)

code += "};\n"

with open(output_c, "wt") as f:
    f.write(code)

