#include <stdio.h>
#include "control.h"

void message(const char *msg)
{
    puts(msg);
}


void make_step(void)
{

}

void set_dir(bool dir)
{

}

int main(void)
{
    control_init(100, 200*2*3, 2.0, false, set_dir, make_step);

    control_register_thread(0.20, true); // 0
    control_register_thread(0.25, true); // 1
    control_register_thread(0.30, true); // 2
    control_register_thread(0.35, true); // 3
    control_register_thread(0.40, true); // 4
    control_register_thread(0.45, true); // 5
    control_register_thread(0.50, true); // 6
    control_register_thread(0.60, true); // 7
    control_register_thread(0.70, true); // 8
    control_register_thread(0.75, true); // 9
    control_register_thread(0.80, true); // 10
    control_register_thread(1.00, true); // 11
    control_register_thread(1.25, true); // 12
    control_register_thread(1.50, true); // 13
    control_register_thread(1.75, true); // 14
    control_register_thread(2.00, true); // 15
    control_register_thread(2.50, true); // 16
    control_register_thread(3.00, true); // 17

    control_select_thread(0);

    while (true)
        ;

    return 0;
}
