#include "telebot/utils/binary.h"

#include <cstring>

namespace telebot::utils::binary {

// reading

template<typename T>
static T read(const uint8_t* data, size_t& offset) {
    return data[offset++];
}

bool Bool(const uint8_t* data, size_t& offset) {
    return read<uint8_t>(data, offset) != 0;
}

uint8_t Byte(const uint8_t* data, size_t& offset) {
    return read<uint8_t>(data, offset);
}

char Char(const uint8_t* data, size_t& offset) {
    return (read<int16_t>(data, offset) & 0xFF) << 8
        | (read<int16_t>(data, offset) & 0xFF);
}

int16_t Short(const uint8_t* data, size_t& offset) {
    return (read<int16_t>(data, offset) & 0xFF) << 8
        | (read<int16_t>(data, offset) & 0xFF);
}

int32_t Int(const uint8_t* data, size_t& offset) {
    return (read<int32_t>(data, offset) & 0xFF) << 24
        | (read<int32_t>(data, offset) & 0xFF) << 16
        | (read<int32_t>(data, offset) & 0xFF) << 8
        | (read<int32_t>(data, offset) & 0xFF);
}

float Float(const uint8_t* data, size_t& offset) {
    int32_t valueInt = Int(data, offset);
    float value = 0.0;
    std::memcpy(&value, &valueInt, sizeof(float));
    return value;
}

int64_t Long(const uint8_t* data, size_t& offset) {
    return (read<int64_t>(data, offset) & 0xFF) << 56
        | (read<int64_t>(data, offset) & 0xFF) << 48
        | (read<int64_t>(data, offset) & 0xFF) << 40
        | (read<int64_t>(data, offset) & 0xFF) << 32
        | (read<int64_t>(data, offset) & 0xFF) << 24
        | (read<int64_t>(data, offset) & 0xFF) << 16
        | (read<int64_t>(data, offset) & 0xFF) << 8
        | (read<int64_t>(data, offset) & 0xFF);
}

double Double(const uint8_t* data, size_t& offset) {
    int64_t valueLong = Long(data, offset);
    double value = 0.0;
    std::memcpy(&value, &valueLong, sizeof(double));
    return value;
}

std::string String(const uint8_t* data, size_t& offset, size_t length) {
    std::string value = "";
    for (size_t i = 0; i < length; i++) {
        value += Char(data, offset);
    }
    return value;
}

std::string LenString(const uint8_t* data, size_t& offset) {
    int32_t length = Int(data, offset);
    return String(data, offset, length);
}

// writing

static void write(uint8_t* data, size_t& offset, uint8_t value) {
    data[offset++] = value;
}

void Bool(uint8_t* data, size_t& offset, bool value) {
    write(data, offset, value ? 1 : 0);
}

void Byte(uint8_t* data, size_t& offset, uint8_t value) {
    write(data, offset, value);
}

void Char(uint8_t* data, size_t& offset, char value) {
    write(data, offset, (value >> 8) & 0xFF);
    write(data, offset, value & 0xFF);
}

void Short(uint8_t* data, size_t& offset, int16_t value) {
    write(data, offset, (value >> 8) & 0xFF);
    write(data, offset, value & 0xFF);
}

void Int(uint8_t* data, size_t& offset, int32_t value) {
    write(data, offset, (value >> 24) & 0xFF);
    write(data, offset, (value >> 16) & 0xFF);
    write(data, offset, (value >> 8) & 0xFF);
    write(data, offset, value & 0xFF);
}

void Float(uint8_t* data, size_t& offset, float value) {
    int32_t valueInt = 0;
    std::memcpy(&valueInt, &value, sizeof(float));

    Int(data, offset, valueInt);
}

void Long(uint8_t* data, size_t& offset, int64_t value) {
    write(data, offset, (value >> 56) & 0xFF);
    write(data, offset, (value >> 48) & 0xFF);
    write(data, offset, (value >> 40) & 0xFF);
    write(data, offset, (value >> 32) & 0xFF);
    write(data, offset, (value >> 24) & 0xFF);
    write(data, offset, (value >> 16) & 0xFF);
    write(data, offset, (value >> 8) & 0xFF);
    write(data, offset, value & 0xFF);
}

void Double(uint8_t* data, size_t& offset, double value) {
    int64_t valueLong = 0;
    std::memcpy(&valueLong, &value, sizeof(double));

    Long(data, offset, valueLong);
}

void String(uint8_t* data, size_t& offset, std::string value, size_t length) {
    for (size_t i = 0; i < length; i++) {
        Char(data, offset, value[i]);
    }
}

void LenString(uint8_t* data, size_t& offset, std::string value) {
    Int(data, offset, static_cast<int32_t>(value.size()));
    String(data, offset, value, value.size());
}

} // namespace telebot::utils::binary
