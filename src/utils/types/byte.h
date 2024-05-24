#pragma once

#include "../utils_base.h"

#define byte utils::_Byte

namespace utils {

typedef unsigned char _Byte;

// to bytes (to big endian)

void bool_to_bytes(bool v, function<void(byte)> out);

void byte_to_bytes(byte v, function<void(byte)> out);

void char_to_bytes(char v, function<void(byte)> out);

void int_to_bytes(int v, function<void(byte)> out);

void long_to_bytes(long v, function<void(byte)> out);

void float_to_bytes(float v, function<void(byte)> out);

void double_to_bytes(double v, function<void(byte)> out);

// from bytes (from big endian)

bool bytes_to_bool(function<byte()> in);

byte bytes_to_byte(function<byte()> in);

char bytes_to_char(function<byte()> in);

int bytes_to_int(function<byte()> in);

long bytes_to_long(function<byte()> in);

float bytes_to_float(function<byte()> in);

double bytes_to_double(function<byte()> in);

}
