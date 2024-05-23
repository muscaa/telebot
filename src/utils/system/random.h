#pragma once

#include "../utils_base.h"
#include "../types/byte.h"

namespace utils {

int random_int(int min, int max);

void random_bytes(byte* buf, int len);

}
