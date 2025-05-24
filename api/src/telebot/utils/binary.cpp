#include "telebot/utils/binary.h"

#include <memory>

namespace telebot::utils::binary {

// reading

bool Bool(const uint8_t* data, size_t& offset) {
    bool value;
    std::memcpy(&value, data + offset, sizeof(bool));
    offset += sizeof(bool);
    return value;
}

uint8_t Byte(const uint8_t* data, size_t& offset) {
    uint8_t value = data[offset];
    offset += sizeof(uint8_t);
    return value;
}

char Char(const uint8_t* data, size_t& offset) {
    char value;
    std::memcpy(&value, data + offset, sizeof(char));
    offset += sizeof(char);
    return value;
}

int16_t Short(const uint8_t* data, size_t& offset) {
    int16_t value;
    std::memcpy(&value, data + offset, sizeof(int16_t));
    offset += sizeof(int16_t);
    return value;
}

int32_t Int(const uint8_t* data, size_t& offset) {
    int32_t value;
    std::memcpy(&value, data + offset, sizeof(int32_t));
    offset += sizeof(int32_t);
    return value;
}

float Float(const uint8_t* data, size_t& offset) {
    float value;
    std::memcpy(&value, data + offset, sizeof(float));
    offset += sizeof(float);
    return value;
}

int64_t Long(const uint8_t* data, size_t& offset) {
    int64_t value;
    std::memcpy(&value, data + offset, sizeof(int64_t));
    offset += sizeof(int64_t);
    return value;
}

double Double(const uint8_t* data, size_t& offset) {
    double value;
    std::memcpy(&value, data + offset, sizeof(double));
    offset += sizeof(double);
    return value;
}

std::string String(const uint8_t* data, size_t& offset, size_t length) {
    std::string value(reinterpret_cast<const char*>(data + offset), length);
    offset += length;
    return value;
}

std::string LenString(const uint8_t* data, size_t& offset) {
    int32_t length = Int(data, offset);
    return String(data, offset, static_cast<size_t>(length));
}

// writing

void Bool(uint8_t* data, bool value, size_t offset) {
    std::memcpy(data + offset, &value, sizeof(bool));
}

void Byte(uint8_t* data, uint8_t value, size_t offset) {
    data[offset] = value;
}

void Char(uint8_t* data, char value, size_t offset) {
    std::memcpy(data + offset, &value, sizeof(char));
}

void Short(uint8_t* data, int16_t value, size_t offset) {
    std::memcpy(data + offset, &value, sizeof(int16_t));
}

void Int(uint8_t* data, int32_t value, size_t offset) {
    std::memcpy(data + offset, &value, sizeof(int32_t));
}

void Float(uint8_t* data, float value, size_t offset) {
    std::memcpy(data + offset, &value, sizeof(float));
}

void Long(uint8_t* data, int64_t value, size_t offset) {
    std::memcpy(data + offset, &value, sizeof(int64_t));
}

void Double(uint8_t* data, double value, size_t offset) {
    std::memcpy(data + offset, &value, sizeof(double));
}

void String(uint8_t* data, std::string value, size_t length, size_t offset) {
    std::memcpy(data + offset, value.data(), std::min(length, value.size()));
    if (value.size() < length) {
        std::memset(data + offset + value.size(), 0, length - value.size());
    }
}

void LenString(uint8_t* data, std::string value, size_t offset) {
    Int(data, static_cast<int32_t>(value.size()), offset);
    String(data, value, value.size(), offset + sizeof(int32_t));
}

} // namespace telebot::utils::binary
