#include "utils/types/byte.hpp"

#include <limits>

static bool is_big_endian() {
    int big_endian = 1;
    return *((byte*) &big_endian) == 1;
}

static void write_bytes(byte* p, int size, function<void(byte)> out) {
    if (is_big_endian()) {
        for (int i = 0; i < size; i++) {
            out(p[i]);
        }
    } else {
        for (int i = size - 1; i >= 0; i--) {
            out(p[i]);
        }
    }
}

static void read_bytes(byte* p, int size, function<byte()> in) {
    if (is_big_endian()) {
        for (int i = 0; i < size; i++) {
            p[i] = in();
        }
    } else {
        for (int i = size - 1; i >= 0; i--) {
            p[i] = in();
        }
    }
}

// to bytes

void utils::bool_to_bytes(bool v, function<void(byte)> out) {
    out(v ? 1 : 0);
}

void utils::byte_to_bytes(byte v, function<void(byte)> out) {
    out(v);
}

void utils::char_to_bytes(char v, function<void(byte)> out) {
    out(v);
}

void utils::int_to_bytes(int v, function<void(byte)> out) {
    write_bytes((byte*) &v, sizeof(int), out);
}

void utils::long_to_bytes(long v, function<void(byte)> out) {
    write_bytes((byte*) &v, sizeof(long), out);
}

void utils::float_to_bytes(float v, function<void(byte)> out) {
    write_bytes((byte*) &v, sizeof(float), out);
}

void utils::double_to_bytes(double v, function<void(byte)> out) {
    write_bytes((byte*) &v, sizeof(double), out);
}

// from bytes

bool utils::bytes_to_bool(function<byte()> in) {
    return in() == 0 ? false : true;
}

byte utils::bytes_to_byte(function<byte()> in) {
    return in();
}

char utils::bytes_to_char(function<byte()> in) {
    byte b = in();
    return b > CHAR_MAX ? (b % (CHAR_MAX + 1)) - (CHAR_MAX + 1) : b;
}

int utils::bytes_to_int(function<byte()> in) {
    int v;
    read_bytes((byte*) &v, sizeof(int), in);
    return v;
}

long utils::bytes_to_long(function<byte()> in) {
    long v;
    read_bytes((byte*) &v, sizeof(long), in);
    return v;
}

float utils::bytes_to_float(function<byte()> in) {
    float v;
    read_bytes((byte*) &v, sizeof(float), in);
    return v;
}

double utils::bytes_to_double(function<byte()> in) {
    double v;
    read_bytes((byte*) &v, sizeof(double), in);
    return v;
}
