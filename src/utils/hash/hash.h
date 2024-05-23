#pragma once

#include "../utils_base.h"
#include "../types/byte.h"

namespace utils {

class HASH {
private:
    int length;
    byte* data;

public:
    HASH(int length);

    HASH();

    ~HASH();

    string toHex();

    bool operator==(HASH& other);

    static HASH random(int length);
};

string hex_string(byte* buf, int len);

void hex_bytes(byte* buf, string hex);

}
