#include "utils/hash/hash.hpp"

#include "utils/system/random.hpp"

#define HEX_STRING "0123456789ABCDEF"
#define HEX_BYTES(c) ((c >= '0' && c <= '9') ? c - '0' : ((c >= 'A' && c <= 'F') ? c - 'A' + 10 : c - 'a' + 10))

utils::HASH::HASH(int length) : length(length) {
    data = new byte[length];
}

utils::HASH::HASH(string hex) : HASH(hex.length() / 2) {
    hex_bytes(data, hex);
}

utils::HASH::HASH() : HASH(0) {}

utils::HASH::~HASH() {
    delete[] data;
}

string utils::HASH::toHex() {
    return hex_string(data, length);
}

bool utils::HASH::operator==(HASH& other) {
    if (length != other.length) return false;

    for (int i = 0; i < length; i++) {
        if (data[i] != other.data[i]) return false;
    }

    return true;
}

utils::HASH utils::HASH::random(int length) {
    HASH obj = HASH(length);
    random_bytes(obj.data, length);
    return obj;
}

string utils::hex_string(byte* buf, int len) {
    string result = "";
    for (int i = 0; i < len; i++) {
        byte v = buf[i] & 0xFF;

        result += HEX_STRING[v >> 4];
        result += HEX_STRING[v & 0x0F];
    }
    return result;
}

void utils::hex_bytes(byte* buf, string hex) {
    int len = hex.length() / 2;
    for (int i = 0; i < len; i++) {
        char c1 = hex[i * 2];
        char c2 = hex[i * 2 + 1];

        buf[i] = (HEX_BYTES(c1) << 4) | HEX_BYTES(c2);
    }
}
