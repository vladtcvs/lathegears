#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "common.h"

struct screw_desc_s {
    real pitch;
    bool dir;
    uint32_t steps;

    void (*set_dir)(bool dir);
    void (*make_step)(void);
};
