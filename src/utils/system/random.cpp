#include "random.h"

#include <cstdlib>
#include <time.h>

static bool inited = false;

static void init_random() {
    if (inited) return;
    inited = true;

    srand(time(NULL));
}

int utils::random_int(int min, int max) {
    init_random();

    return (rand() % (max - min)) + min;
}

void utils::random_bytes(byte* buf, int len) {
    init_random();

    for (int i = 0; i < len; i++) {
        buf[i] = rand() % 256;
    }
}
