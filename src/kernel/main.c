#include "print.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLACK);
    kprint("Welcome to x0S 64-bit Operating System");
}
