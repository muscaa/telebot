#pragma once

#include "../utils_base.h"

#define byte utils::_Byte

namespace utils {

typedef unsigned char _Byte;

// to bytes (to big endian)
void bool_to_bytes(bool v, void function(out, byte));

void byte_to_bytes(byte v, void function(out, byte));

void char_to_bytes(char v, void function(out, byte));

void int_to_bytes(int v, void function(out, byte));

void long_to_bytes(long v, void function(out, byte));

void float_to_bytes(float v, void function(out, byte));

void double_to_bytes(double v, void function(out, byte));

// from bytes (from big endian)
bool bytes_to_bool(byte function(in));

byte bytes_to_byte(byte function(in));

char bytes_to_char(byte function(in));

int bytes_to_int(byte function(in));

long bytes_to_long(byte function(in));

float bytes_to_float(byte function(in));

double bytes_to_double(byte function(in));

}
